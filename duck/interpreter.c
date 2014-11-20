/* interpreter.c */

#include "interpreter.h"
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
    VALUE namespace;
    namespace.type = VAL_REFERENCE;
    namespace.data.reference = (CONTEXT*)ALLOC(sizeof(CONTEXT));
    namespace.data.reference->parent = NULL;
    namespace.data.reference->list = NULL;
    namespace.data.reference->ref_count = -1;
    StoreRecord(identifier, namespace, gGlobalContext);
    return namespace;
}

void  LinkFunction(VALUE namespace, const char* identifier, VALUE function)
{
    StoreRecord(identifier, function, namespace.data.reference);
}

void  LinkConstPrimitive(VALUE namespace, const char* identifier, int value)
{
    VALUE constant;
    constant.type = VAL_PRIMITIVE;
    constant.data.primitive = value;
    StoreRecord(identifier, constant, namespace.data.reference);
}

void  LinkConstFloatp(VALUE namespace, const char* identifier, float value)
{
    VALUE constant;
    constant.type = VAL_FLOATING_POINT;
    constant.data.floatp = value;
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

/*
    identifiers & scope
    types
*/

int Interpret(SYNTAX_TREE* tree)
{
    CreateEnvironment();

    gCurrentContext = gGlobalContext = (CONTEXT*)ALLOC(sizeof(CONTEXT));
    gCurrentContext->parent = NULL;
    gCurrentContext->list = NULL;
    gCurrentContext->ref_count = -1;

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;

    gParameterListing = NULL;
    gDictionaryInit = NULL;
    gArrayIndex = 0;
    gArgumentEvaluation = NULL;

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

    gParameterListing = NULL;

    returning = 0;
    breaking = 0;
    continuing = 0;

    //return InterpretNode(tree);
    int error = InterpretNode(tree);
    ForceFreeContext(gGlobalContext);
    return error;
}


