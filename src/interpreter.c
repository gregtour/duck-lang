/* interpreter.c */

#include "interpreter.h"
#ifdef FLAG_GDUCK
#include "stdduck.h"
#include "sdllib.h"
#endif

// global data
CONTEXT* gGlobalContext;
CONTEXT* gCurrentContext;
VALUE    gLastExpression;
PAIR*    gParameterListing;

CONTEXT* gDictionaryInit;
int      gArrayIndex;
PAIR*    gArgumentEvaluation;

const char* gLValueIdentifier;
CONTEXT* gLValueContext;

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
    int level = 0;

    while (context)
    {
        printf("{");
        PAIR* list = context->list;
        while (list)
        {
            printf("%s: ", list->identifier);
            VALUE value = list->value;
            if (value.type == VAL_PRIMITIVE)
                printf("%i", value.primitive);
            else if (value.type == VAL_STRING)
                printf("%s", value.string);
            else if (value.type == VAL_REFERENCE)
            {
                printf("[");
                PrintContext(value.reference);
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

/* release all allocated memory */
#define PAGE_SIZE       2048

typedef struct MEM_PAGE 
{
    void* data_ptrs[PAGE_SIZE];
    unsigned int page_index;
    struct MEM_PAGE* next_page;    
} MEM_PAGE;

MEM_PAGE* gBaseMemory;
MEM_PAGE* gWorkingMemory;

void* ALLOCATE(size_t amount)
{
    unsigned int index;
    void* data;

    index = gWorkingMemory->page_index;
    data = malloc(amount);

    if (index < PAGE_SIZE)
    {
        gWorkingMemory->data_ptrs[index] = data;
        gWorkingMemory->page_index = index + 1;
    }
    else
    {
        gWorkingMemory->next_page = (MEM_PAGE*)malloc(sizeof(MEM_PAGE));
        gWorkingMemory = gWorkingMemory->next_page;
        gWorkingMemory->page_index = 0;
        gWorkingMemory->next_page = NULL;
        gWorkingMemory->data_ptrs[0] = data;
        gWorkingMemory->page_index++;
    }
    return data;
}

void CreateEnvironment()
{
    FreeEnvironment();
    gBaseMemory = (MEM_PAGE*)malloc(sizeof(MEM_PAGE));
    gBaseMemory->page_index = 0;
    gBaseMemory->next_page = NULL;
    gWorkingMemory = gBaseMemory;
}

void FreeEnvironment()
{
    while (gBaseMemory) {
        MEM_PAGE* cur_page;
        unsigned int index;

        for (index = 0; index < gBaseMemory->page_index; index++) {
            free(gBaseMemory->data_ptrs[index]);
        }
        cur_page = gBaseMemory;
        gBaseMemory = gBaseMemory->next_page;
        free(cur_page);
    }

    gBaseMemory = NULL;
    gWorkingMemory = NULL;
}

/* accessor functions */
VALUE GetRecord(const char* identifier, CONTEXT* context)
{
    while (context)
    {
        PAIR* iterator = context->list;
        while (iterator)
        {
            if (strcmp(identifier, iterator->identifier) == 0)
            {
                return iterator->value;
            }
            iterator = iterator->next;
        }
        context = context->parent;
    }
    
    VALUE nil;
    nil.type = VAL_NIL;
    return nil;
}

void StoreRecord(const char* identifier, VALUE value, CONTEXT* context)
{
    CONTEXT* top = context;
    while (context)
    {
        PAIR* iterator = context->list;
        while (iterator)
        {
            if (strcmp(identifier, iterator->identifier) == 0)
            {
                iterator->value = value;
                return;
            }
            iterator = iterator->next;
        }
        context = context->parent;
    }
    
    if (top)
    {
        PAIR* iterator = top->list;
        if (top->list) {
            PAIR* iterator = top->list;
            while (iterator->next) {
                iterator = iterator->next;
            }
            iterator->next = (PAIR*)ALLOCATE(sizeof(PAIR));
            iterator->next->value = value;
            iterator->next->identifier = identifier;
            iterator->next->next = NULL;
        } else {
            top->list = (PAIR*)ALLOCATE(sizeof(PAIR));
            top->list->value = value;
            top->list->identifier = identifier;
            top->list->next = NULL;
        }
    }
}



/* Standard Library Function Binding */

VALUE LinkNamespace(const char* identifier)
{
    VALUE namespace;
    namespace.type = VAL_REFERENCE;
    namespace.reference = (CONTEXT*)ALLOCATE(sizeof(CONTEXT));
    namespace.reference->parent = NULL;
    namespace.reference->list = NULL;
    StoreRecord(identifier, namespace, gGlobalContext);
    return namespace;
}

void  LinkFunction(VALUE namespace, const char* identifier, VALUE function)
{
    StoreRecord(identifier, function, namespace.reference);
}

#ifdef FLAG_GDUCK
void  LinkConstPrimitive(VALUE namespace, const char* identifier, int value)
{
    VALUE constant;
    constant.type = VAL_PRIMITIVE;
    constant.primitive = value;
    StoreRecord(identifier, constant, namespace.reference);
}
#endif

VALUE CreateFunction(int (*function)(int))
{
    VALUE record;
    record.type = VAL_FUNCTION;
    record.function = (FUNCTION*)ALLOCATE(sizeof(FUNCTION));
    record.function->parameters = NULL; // ??
    record.function->body = NULL;
	record.function->closure = gCurrentContext;
    record.function->built_in = 1;
    record.function->functor = function;
    return record;
}

void  AddParameter(VALUE functor, const char* argument_name)
{
    PAIR* parameter = (PAIR*)ALLOCATE(sizeof(PAIR));
    parameter->identifier = argument_name;
    parameter->value.type = VAL_NIL;
    parameter->next = NULL;

    PAIR* iterator;
    if (functor.function->parameters)
    {
        for (iterator = functor.function->parameters;
             iterator->next;
             iterator = iterator->next);
        iterator->next = parameter;
        return;
    }
    functor.function->parameters = parameter;
}

/*
    identifiers & scope
    types
*/

int Interpret(SYNTAX_TREE* tree)
{
    CreateEnvironment();

    gCurrentContext = gGlobalContext = (CONTEXT*)ALLOCATE(sizeof(CONTEXT));
    gCurrentContext->parent = NULL;
    gCurrentContext->list = NULL;
    gLastExpression.type = VAL_NIL;
    gParameterListing = NULL;
    gDictionaryInit = NULL;
    gArrayIndex = 0;
    gArgumentEvaluation = NULL;

    gLValueIdentifier = NULL;
    gLValueContext = NULL;

    /* libraries */
    BindStandardLibrary();
#ifdef FLAG_GDUCK
    BindSDL();
#endif
    gParameterListing = NULL;

    returning = 0;
    breaking = 0;
    continuing = 0;

    return InterpretNode(tree);
}


int main(int argc, char* argv[])
{
    const char*   program;
    L_TOKEN*      lexing;
    SYNTAX_TREE*  ast;
    char*         buffer;
    int           error;

    if (argc > 1)
        program = argv[1];
    else {
#ifdef FLAG_GDUCK
        printf("gduck program.src\n");
#else
        printf("duck program.src\n");
#endif
        return 1;
    }

    //printf("%s\n", program);

    // lex source
    buffer = 0;
    lexing = LexSource(program, &buffer, CONTEXT_FREE_GRAMMAR);
    if (lexing == NULL)
    {
        printf("Error lexing source or empty source file.\n");
        FreeLexing(lexing, buffer);
        getchar();
        return 1;
    }
    //PrintLexing(lexing);

    // parse source
    ast = ParseSource(lexing, PARSE_TABLE, CONTEXT_FREE_GRAMMAR);
    if (ast == NULL)
    {
        printf("Error parsing source.\n");
        FreeLexing(lexing, buffer);
        getchar();
        return 1;
    }
    //PrintParseTree(ast, CONTEXT_FREE_GRAMMAR);

    // compile source
    //printf("Interpretting...\n");
    error = Interpret(ast);
    if (error)
    {
        printf("Error %i.\n", error);
        FreeLexing(lexing, buffer);
        FreeParseTree(ast);
        getchar();
        return 1;
    }
    
    //printf("Done.\n");
    //getchar();
    
    // clean up
    FreeEnvironment();
    FreeLexing(lexing, buffer);
    FreeParseTree(ast);

#ifdef _MEM_TRACKING
    PrintMemoryUsage();
#endif // _MEM_TRACKING
    return 0;
}

