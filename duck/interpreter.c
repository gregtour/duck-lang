/* interpreter.c */

#include "interpreter.h"
#include "lr_parser.h"
#include "memory.h"
#include "lib/library.h"
#include "lib/stdduck.h"
#include "lib/dmath.h"
#include "lib/drand.h"

// global data
CONTEXT* gGlobalContext;
CONTEXT* gCurrentContext;
VALUE    gLastExpression;
PAIR*    gParameterListing;

//CONTEXT* gDictionaryInit;
HASH_TABLE* gDictionaryInit;
int      gArrayIndex;
PAIR*    gArgumentEvaluation;

const char* gLValueIdentifier;
CONTEXT*    gLValueContext;
VALUE       gLValueIndex;
HASH_TABLE* gLValueDictionary;

int array_indexing;

int returning;
int breaking;
int continuing;
int halting;

CALLSTACK gStackTrace;

int line_error;
SYNTAX_TREE* failed_production;

int greatest_stack_depth;
int stack_depth;

// memory tracker
#ifdef _MEM_TRACKING
int gTotalMemoryUsage = 0;
int gMallocCalls = 0;
int gFreeCalls = 0;

#ifdef malloc
#undef malloc
#endif

#ifdef free
#undef free
#endif

void* MallocTrackMemory(size_t size)
{
    void* data;
    gTotalMemoryUsage += (int)size;
    gMallocCalls++;
    return malloc(size);
}

void FreeTrackMemory(void* data)
{
    free(data);
    gFreeCalls++;
    return;
}

#ifndef malloc
#define malloc      MallocTrackMemory
#endif

#ifndef free
#define free        FreeTrackMemory
#endif

void PrintMemoryUsage()
{
    int b = gTotalMemoryUsage % 1000;
    int kb = (gTotalMemoryUsage / 1000) % 1000;
    int mb = (gTotalMemoryUsage / 1000000) % 1000;
    if (mb) {
        printf("Total memory usage: %i.%i mb\n", mb, kb);
    } else {
        printf("Total memory usage: %i.%i kb\n", kb, b);
    }

    printf("%i calls to malloc() with %i calls to free()\n",
        gMallocCalls,
        gFreeCalls);
}
#endif // _MEM_TRACKING

void PrintContext(CONTEXT* context)
{
    while (context)
    {
        printf("{");
        PAIR* list = context->list;
        while (list)
        {
            printf("%s: ", list->identifier);
            VALUE value = list->value;
            if (value.type == VAL_PRIMITIVE)
                printf("%i", value.data.primitive);
            else if (value.type == VAL_STRING)
                printf("%s", value.data.string);
            else if (value.type == VAL_REFERENCE)
            {
                printf("[");
                PrintContext(value.data.reference);
                printf("]");
            }
            else if (value.type == VAL_FUNCTION)
                printf("f()");
            else
                printf("nil");
            printf(", ");

            list = list->next;
        }
        context = context->parent;
        printf("}");
        if (context) printf("\n");
    }
}


/* Standard Library Function Binding */

VALUE LinkNamespace(const char* identifier)
{
    VALUE ref_namespace;
    ref_namespace.type = VAL_REFERENCE;
    ref_namespace.data.reference = (CONTEXT*)ALLOC(sizeof(CONTEXT));
    ref_namespace.data.reference->parent = NULL;
    ref_namespace.data.reference->list = NULL;
    ref_namespace.data.reference->ref_count = -1;
    StoreRecord(identifier, ref_namespace, gGlobalContext);
    return ref_namespace;
}

void  LinkFunction(VALUE ref_namespace, const char* identifier, VALUE function)
{
    if (function.type == VAL_FUNCTION) {
        function.data.function->fn_name = identifier;
        StoreRecord(identifier, function, ref_namespace.data.reference);
    }
}

void  LinkConstPrimitive(VALUE ref_namespace, const char* identifier, int value)
{
    VALUE constant;
    constant.type = VAL_PRIMITIVE;
    constant.data.primitive = value;
    StoreRecord(identifier, constant, ref_namespace.data.reference);
}

void  LinkConstFloatp(VALUE ref_namespace, const char* identifier, double value)
{
    VALUE constant;
    constant.type = VAL_FLOATING_POINT;
    constant.data.floatp = value;
    StoreRecord(identifier, constant, ref_namespace.data.reference);
}

void  LinkConstString(VALUE namespace, const char* identifier, const char* string)
{
    VALUE constant;
    constant.type = VAL_STRING;
    constant.data.string = string;
    StoreRecord(identifier, constant, namespace.data.reference);
}

VALUE CreateFunction(int (*function)(int))
{
    VALUE record;
    record.type = VAL_FUNCTION;
    record.data.function = (FUNCTION*)ALLOCATE(sizeof(FUNCTION));
    record.data.function->parameters = NULL; // ??
    record.data.function->body = NULL;
	record.data.function->closure = gCurrentContext;
    record.data.function->built_in = 1;
    record.data.function->functor = function;
    record.data.function->ref_count = -1;
    record.data.function->fn_name = "[built-in]";
    return record;
}

void  AddParameter(VALUE functor, const char* argument_name)
{
    PAIR* parameter = (PAIR*)ALLOCATE(sizeof(PAIR));
    parameter->identifier = argument_name;
    parameter->value.type = VAL_NIL;
    parameter->value.data.primitive = 0;
    parameter->next = NULL;

    PAIR* iterator;
    if (functor.data.function->parameters)
    {
        for (iterator = functor.data.function->parameters;
             iterator->next;
             iterator = iterator->next);
        iterator->next = parameter;
        return;
    }
    functor.data.function->parameters = parameter;
}

/* function call stack */
void ClearCallStack(CALLSTACK* stack)
{
    stack->next = 0l;
    stack->fn_name = NULL;
}

void PushCallStack(CALLSTACK* stack, FUNCTION* func)
//const char* identifier)
{
    if (stack && func) {
        const char* identifier = (func ? func->fn_name : NULL);
    
        if (stack->fn_name == NULL) {
            (*stack).fn_name = identifier;
            (*stack).function = func;
            (*stack).next = 0l;
        } else {
            CALLSTACK* next;
            next = (CALLSTACK*)malloc(sizeof(CALLSTACK));
            next->fn_name = stack->fn_name;
            next->function = stack->function;
            next->next = stack->next;
            (*stack).fn_name = identifier;
            (*stack).function = func;
            stack->next = next;
        }
    }
}

void PrintStackTrace()
{
    CALLSTACK* stack = &gStackTrace;
    printf("Program halted on line %i.\n", (line_error+1));
    if (failed_production) {
        printf("Failed production: ");
        /* PrintParseTree(failed_production, CONTEXT_FREE_GRAMMAR); */
        PrintParseTreeFormat(failed_production, CONTEXT_FREE_GRAMMAR);
        printf("\n");
    }

    if (stack->fn_name) {
        printf("Printing stack trace:\n\n");
        int depth = 0; int i;
        while (stack) {
            for (i = 0; i < depth; i++) printf("  ");
            //printf("%i. %s:\n", depth, stack->fn_name);
            PrintFunction(stack->function);
            printf("\n");
            stack = stack->next;
            depth++;
        }
    }
}

/*
int Interpret(SYNTAX_TRE* tree)
    ---------------------------------------------------------
    Run a duck program from the command console by parsing it
    into a syntax tree and then interating over the program
    definitions.
*/
int Interpret(SYNTAX_TREE* tree)
{
    CreateEnvironment();

    /* global namespace */
    gCurrentContext = gGlobalContext = (CONTEXT*)ALLOC(sizeof(CONTEXT));
    gCurrentContext->parent = NULL;
    gCurrentContext->list = NULL;
    gCurrentContext->ref_count = -1;

    /* current expression */
    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;

    /* global variables */
    gParameterListing = NULL;
    gDictionaryInit = NULL;
    gArrayIndex = 0;
    gArgumentEvaluation = NULL;

    /* l-value bound context */
    gLValueIdentifier = NULL;
    gLValueContext = NULL;
    gLValueIndex.type = VAL_NIL;
    gLValueIndex.data.primitive = 0;
    gLValueDictionary = NULL;
    array_indexing = 0;

    /* libraries */
    BindStandardLibrary();
    BindMathLibrary();
    BindAdditionalLibraries();
    BindRandLibrary();

    /* function definition */
    gParameterListing = NULL;

    /* program control */
    returning = 0;
    breaking = 0;
    continuing = 0;
    halting = 0;

    /* profiling */
    greatest_stack_depth;
    stack_depth;

    /* clear call stack */
    ClearCallStack(&gStackTrace);
    line_error = 0;
    failed_production = NULL;
    
    /* run */
    int error = InterpretNode(tree);
    //ForceFreeContext(gGlobalContext);
    return error;
}


/* reduce or remove trivial abstract syntax tree productions */
void ReduceProgramAST(SYNTAX_TREE** program)
{
    const int empty_production = 0xFF;
    
    int empty_productions[] = {3, 5, 6, 17, 18, 78};
    int child0_productions[] = {7, 8, 9, 10, 11, 12, 33, 38, 40, 47, 55, 58, 60, 64, 65};
    int child1_productions[] = {19, 24, 30, 59};
    int child2_productions[] = {23};

    int i; int reducible = 1;
    // continue while reducible
    while (reducible)
    {
        reducible = 0;
        /* empty productions: 3, 5, 6, 17, 18, 78 */
        for (i = 0; i < sizeof(empty_productions)/sizeof(int); i++)
        {
            if ((*program)->production == empty_productions[i]) 
            {
                (*program)->production = empty_production;
                reducible = 1;
            }
        }

        /* productions that reduce to node->children[0] */
        /* 7, 8, 9, 10, 11, 12, 33, 38, 40, 47, 55, 58, 60, 64, 65 */
        for (i = 0; i < sizeof(child0_productions)/sizeof(int); i++)
        {
            if ((*program)->production == child0_productions[i])
            {
                SYNTAX_TREE* cur = *program;
                *program = (*program)->children[0];
                free(cur);
                reducible = 1;
            }
        }

        /* productions that reduce to node->children[1] */
        /* 19, 24, 30, 59 */
        for (i = 0; i < sizeof(child1_productions)/sizeof(int); i++)
        {
            if ((*program)->production == child1_productions[i])
            {
                SYNTAX_TREE* cur = *program;
                *program = (*program)->children[1];
                free(cur);
                reducible = 1;
            }
        }

        /* productions that reduce to node->children[2] */
        /* 23 */
        for (i = 0; i < sizeof(child2_productions)/sizeof(int); i++)
        {
            if ((*program)->production == child2_productions[i])
            {
                SYNTAX_TREE* cur = *program;
                *program = (*program)->children[2];
                free(cur);
                reducible = 1;
            }
        }
    }

    // apply for all sub-trees
    for (i = 0; i < (*program)->numChildren; i++)
    {
        ReduceProgramAST(&(*program)->children[i]);
    }
}


