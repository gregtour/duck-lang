/* interpreter.c */

#include "interpreter.h"
#include "lr_parser.h"
#include "memory.h"
#include "lib/library.h"
#include "lib/stdduck.h"
#include "lib/dmath.h"
#include "lib/drand.h"
#include "garbage.h"

// global data
CLOSURE* gGlobalContext;
CLOSURE* gCurrentContext;
VALUE    gLastExpression;
PAIR*    gParameterListing;

//CLOSURE* gDictionaryInit;
HASH_TABLE* gDictionaryInit;
long int    gArrayIndex;
PAIR*       gArgumentEvaluation;

const char* gLValueIdentifier;
CLOSURE*    gLValueContext;
VALUE       gLValueStringReference;
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

int gc_collect_count;
int gc_inst_count;

long int test_inst_count;

// memory tracker
#ifdef _MEM_TRACKING
int gTotalMemoryUsage = 0;
int gPeakMemoryUsage = 0;
int gMallocCalls = 0;
int gFreeCalls = 0;

#ifdef malloc
#undef malloc
#endif

#ifdef free
#undef free
#endif

#ifdef realloc
#undef realloc
#endif

void* MallocTrackMemory(size_t size)
{
    char* data;
    unsigned int* size_record;

    gTotalMemoryUsage = gTotalMemoryUsage + (unsigned int)size;
    gMallocCalls++;

    if (gTotalMemoryUsage > gPeakMemoryUsage) {
        gPeakMemoryUsage = gTotalMemoryUsage;
    }

    data = (char*)malloc(size + sizeof(unsigned int));
	if (data == NULL) {
		printf("Error: Could not allocate memory.\n");
		fflush(stdout);
		return 0l;
	}
    size_record = (unsigned int*)data;
    data = (data + sizeof(unsigned int));

    (*size_record) = (unsigned int)size;
    return (void*)data;
}

void FreeTrackMemory(void* data)
{
    char* pointer = (char*)data;
    if (data) 
    {
        unsigned int* size_record = (unsigned int*)(pointer - sizeof(unsigned int));
        unsigned int data_size = (*size_record);

        gTotalMemoryUsage = gTotalMemoryUsage - data_size;

        free((void*)size_record);

        gFreeCalls++;
    }
}

void* ReallocTrackMemory(void* data, size_t size)
{
    char* pointer = (char*)data;
    if (data) 
    {
        unsigned int* size_record = (unsigned int*)(pointer - sizeof(unsigned int));
        unsigned int data_size = (*size_record);

        gTotalMemoryUsage = gTotalMemoryUsage - data_size;
        gTotalMemoryUsage = gTotalMemoryUsage + (unsigned int)size;

        if (gTotalMemoryUsage > gPeakMemoryUsage) {
            gPeakMemoryUsage = gTotalMemoryUsage;
        }

        char* new_data = (char*)malloc(size + sizeof(unsigned int));
		if (new_data == NULL) {
			printf("Error: Could not allocate memory.\n");
			fflush(stdout);
			return 0l;
		}

        unsigned int* new_size_record = (unsigned int*)new_data;
        new_data = (new_data + sizeof(unsigned int));

        (*new_size_record) = (unsigned int)size;

        unsigned int i;
        for (i = 0; i < data_size && i < (unsigned int)size; i++) {
            new_data[i] = pointer[i];
        }

        free((void*)size_record);
        return (void*)new_data;
    } else {
        return MallocTrackMemory(size);
    }
}

#ifndef malloc
#define malloc      MallocTrackMemory
#endif

#ifndef free
#define free        FreeTrackMemory
#endif

#ifndef realloc
#define realloc     ReallocTrackMemory
#endif
#endif // _MEM_TRACKING

void PrintMemoryUsage()
{
#ifdef _MEM_TRACKING
    int b = gPeakMemoryUsage % 1000;
    int kb = (gPeakMemoryUsage / 1000) % 1000;
    int mb = (gPeakMemoryUsage / 1000000) % 1000;
    if (mb) {
        float n = (float)mb + (float)kb/1000.0f;
        printf("Peak memory usage: %g mb\n", n);
    } else {
        float n = (float)kb + (float)b/1000.0f;
        printf("Peak memory usage: %g kb\n", n);
    }

    printf("%i calls to malloc() with %i calls to free()\n",
        gMallocCalls,
        gFreeCalls);

    if (gTotalMemoryUsage) {
        printf("Error: %i bytes still in use at program exit.\n",
            gTotalMemoryUsage);
    } else {
        printf("No unallocated memory.\n");
    }
#else
    return;
#endif
}

unsigned int CheckMemoryUsage()
{
#ifdef _MEM_TRACKING
    return gTotalMemoryUsage;
#else
    printf("Warning: Platform not built with memory tracking.\n");
    return 0;
#endif
}

void PrintContext(CLOSURE* context)
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
//#ifdef WIN32
//                printf("%l64i", value.data.primitive);
//#else
                printf("%lli", value.data.primitive);
//#endif
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

/* closure stack */
CONTEXT_STACK*   gExecutionStack = NULL;

void PushExecutionStack(CLOSURE* context)
{
    if (gExecutionStack == NULL) {
        gExecutionStack = (CONTEXT_STACK*)malloc(sizeof(CONTEXT_STACK));
        gExecutionStack->context = context;
        gExecutionStack->next = NULL;
        gExecutionStack->prev = NULL;
    } else {
        CONTEXT_STACK*  tail = gExecutionStack;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = (CONTEXT_STACK*)malloc(sizeof(CONTEXT_STACK));
        tail->next->context = context;
        tail->next->next = NULL;
        tail->next->prev = tail;
    }
}

int PopExecutionStack()
{
    CONTEXT_STACK* tail = gExecutionStack;
    while (tail && tail->next) {
        tail = tail->next;
    }
    if (tail) {
        gCurrentContext = tail->context;
        tail = tail->prev;
        if (tail) {
            free(tail->next);
            tail->next = NULL;
        } else {
            free(gExecutionStack);
            gExecutionStack = NULL;
        }
        return 1;
    }
    return 0;
}


/* Standard Library Function Binding */

VALUE LinkNamespace(const char* identifier)
{
    VALUE ref_namespace;
    ref_namespace.type = VAL_REFERENCE;
    ref_namespace.data.reference = (CLOSURE*)ALLOC(sizeof(CLOSURE));
    ref_namespace.data.reference->parent = NULL;
    ref_namespace.data.reference->list = NULL;
    ref_namespace.data.reference->ref_count = -1;
    StoreRecord(identifier, ref_namespace, gGlobalContext);

    GCAddContext(ref_namespace.data.reference, &gGCManager);

    return ref_namespace;
}

void  LinkFunction(VALUE ref_namespace, const char* identifier, VALUE function)
{
    if (function.type == VAL_FUNCTION) {
        function.data.function->fn_name = identifier;
        StoreRecord(identifier, function, ref_namespace.data.reference);
    }
}

void  LinkConstPrimitive(VALUE ref_namespace, const char* identifier, long long int value)
{
    VALUE constant;
    constant.type = VAL_PRIMITIVE;
    constant.data.primitive = value;
    StoreRecord(identifier, constant, ref_namespace.data.reference);
}

void  LinkConstFloatp(VALUE ref_namespace, const char* identifier, long double value)
{
    VALUE constant;
    constant.type = VAL_FLOATING_POINT;
    constant.data.floatp = value;
    StoreRecord(identifier, constant, ref_namespace.data.reference);
}

void  LinkConstString(VALUE NameSpace, const char* identifier, const char* string)
{
    VALUE constant;
    constant.type = VAL_STRING;
    constant.data.string = string;
    constant.const_string = 1;
    StoreRecord(identifier, constant, NameSpace.data.reference);
}

VALUE CreateFunction(int (*function)(int, void*))
{
    VALUE record;
    record.type = VAL_FUNCTION;
    record.data.function = (FUNCTION*)ALLOC(sizeof(FUNCTION));
    record.data.function->parameters = NULL; // ??
    record.data.function->body = NULL;
    record.data.function->closure = gCurrentContext;
    record.data.function->built_in = 1;
    record.data.function->functor = function;
    record.data.function->ref_count = -1;
  //record.data.function->fn_name = "[built-in]";
    record.data.function->fn_name = "function";
    record.data.function->func_data = NULL;

    GCAddFunction(record.data.function, &gGCManager);

    return record;
}

void  AddParameter(VALUE functor, const char* argument_name)
{
    PAIR* parameter = (PAIR*)ALLOC(sizeof(PAIR));
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
int Interpret(SYNTAX_TREE* tree)
    ---------------------------------------------------------
    Run a duck program from the command console by parsing it
    into a syntax tree and then interating over the program
    definitions.
*/
int Interpret(SYNTAX_TREE* tree)
{
    CreateEnvironment();

    gc_inst_count = 0;
    gc_collect_count = 0;

    test_inst_count = 0;

    /* global NameSpace */
    gCurrentContext = gGlobalContext = (CLOSURE*)ALLOC(sizeof(CLOSURE));
    gCurrentContext->parent = NULL;
    gCurrentContext->list = NULL;
    gCurrentContext->ref_count = -1;
    GCAddContext(gGlobalContext, &gGCManager);

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
    while (PopExecutionStack());
    //ForceFreeContext(gGlobalContext);
    return error;
}


/* reduce or remove trivial abstract syntax tree productions */
void ReduceProgramAST(SYNTAX_TREE** program)
{
    const unsigned int empty_production = 0xFF;
    
    unsigned int child0_productions[] = 
            {7, 8, 9, 10, 11, 12, 33, 38, 
            40, 47, 52, 55, 58, 60, 64, 65};
    unsigned int child1_productions[] = 
            {19, 24, 30, 59};
    unsigned int child2_productions[] = 
            {23};
    unsigned int empty_productions[] = 
            {3, 5, 6, 17, 18, 78};

    unsigned int i; 
    unsigned int reducible = 1;
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
        /* 7, 8, 9, 10, 11, 12, 33, 38, 40, 47, 52, 55, 58, 60, 64, 65 */
        for (i = 0; i < sizeof(child0_productions)/sizeof(int); i++)
        {
            if ((*program)->production == child0_productions[i])
            {
                SYNTAX_TREE* cur = *program;
                unsigned int child;

                for (child = 1; child < cur->numChildren; child++)
                {
                    FreeParseTree(cur->children[child]);
                }

                *program = (*program)->children[0];
                free(cur->children);
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
                unsigned int child;

                for (child = 0; child < cur->numChildren; child++)
                {
                    if (child != 1) {
                        FreeParseTree(cur->children[child]);
                    }
                }
                *program = (*program)->children[1];
                free(cur->children);
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
                unsigned int child;

                for (child = 0; child < cur->numChildren; child++)
                {
                    if (child != 2) {
                        FreeParseTree(cur->children[child]);
                    }
                }

                *program = (*program)->children[2];
                free(cur->children);
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


