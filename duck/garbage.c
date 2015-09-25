/* garbage collector */
#include "garbage.h"

GC_DATA_MANAGEMENT    gGCManager;

int  ADD_POINTER_ARRAY(void*** array,
                       unsigned int* capacity, 
                       unsigned int* size, 
                       void* entry)
{
    int result = 0;

    if (entry) {
        unsigned int i;
        for (i = 0; i < *size; i++)
            if ((*array)[i] == entry)
                break;
        if (i == *size)
        {
            result = 1;
            (*array)[*size] = entry;
            (*size)++;
            
            if (*size == *capacity) {
                *capacity = *capacity * 2;
                *array = (void**)realloc((void*)(*array), sizeof(void*) * *capacity);
                /* assert(*array); */
                if (array == 0) printf("Error: Out of memory.\n");
            }
        }
    }

    return result;
}

int CONTAINS_POINTER_ARRAY(void** array,
                           unsigned int size,
                           void* entry)
{
    unsigned int i;
    for (i = 0; i < size; i++)
    {
        if (array[i] == entry)
            return 1;
    }
    return 0;
}


/* memory management */

GC_DATA_MANAGEMENT 
InitGC(/*GC_DATA_MANAGEMENT gcStore*/)
{
    GC_DATA_MANAGEMENT gcStore;
    gcStore.lexings = NULL;
    gcStore.parseTrees = NULL;

    gcStore.ctx_size = 0;
    gcStore.ctx_capacity = 128;
    gcStore.contexts = (CLOSURE**)malloc(sizeof(CLOSURE*) * gcStore.ctx_capacity);

    gcStore.func_size = 0;
    gcStore.func_capacity = 128;
    gcStore.functions = (FUNCTION**)malloc(sizeof(FUNCTION*) * gcStore.func_capacity);

    gcStore.str_size = 0;
    gcStore.str_capacity = 128;
    gcStore.strings = (char**)malloc(sizeof(char*) * gcStore.str_capacity);

    gcStore.table_size = 0;
    gcStore.table_capacity = 128;
    gcStore.tables = (HASH_TABLE**)malloc(sizeof(HASH_TABLE*) * gcStore.table_capacity);
    return gcStore;
}

void FreeGCMgmtObject(GC_DATA_MANAGEMENT gcStore)
{
    free(gcStore.contexts);
    free(gcStore.functions);
    free(gcStore.strings);
    free(gcStore.tables);
}


int CallGCRecurseContext(CLOSURE* context, 
                         GC_DATA_MANAGEMENT* managed)
{
    PAIR* itr;
    int result = 0;

    while (context) {
        itr = context->list;
        if (GCAddContext(context, managed))
        {
            result = 1;
            while (itr) {
                if (itr->value.type == VAL_REFERENCE) {
                    CallGCRecurseContext(itr->value.data.reference, 
                                         managed);
                } else if (itr->value.type == VAL_FUNCTION) {
                    CallGCRecurseFunction(itr->value.data.function,
                                          managed);
                } else if (itr->value.type == VAL_DICTIONARY) {
                    CallGCRecurseDictionary(itr->value.data.dictionary,
                                            managed);
                } else if (itr->value.type == VAL_STRING &&
                           itr->value.const_string == 0) {
                    GCAddString((char*)itr->value.data.string, managed);
                }
                itr = itr->next;
            }
        }

        context = context->parent;
    }

    return result;
}

int CallGCRecurseDictionary(HASH_TABLE* table, 
                            GC_DATA_MANAGEMENT* managed)
{
    int result = 0;
    if (table && GCAddDictionary(table, managed))
    {
        unsigned int index;
        result = 1;

        for (index = 0;
             index < table->capacity;
             index++)
        {
            if (table->table[index].key.type != VAL_NIL)
            {
                VALUE value = table->table[index].value;
                
                if (value.type == VAL_REFERENCE) {
                    CallGCRecurseContext(value.data.reference, 
                                         managed);
                } else if (value.type == VAL_FUNCTION) {
                    CallGCRecurseFunction(value.data.function,
                                          managed);
                } else if (value.type == VAL_DICTIONARY) {
                    CallGCRecurseDictionary(value.data.dictionary,
                                            managed);
                } else if (value.type == VAL_STRING &&
                           value.const_string == 0) {
                    GCAddString((char*)value.data.string, managed);
                }
            }
        }
    }

    return result;
}

int CallGCRecurseFunction(FUNCTION* function, 
                          GC_DATA_MANAGEMENT* managed)
{
    int result = 0;
    if (function && GCAddFunction(function, managed)) 
    {
        result = 1;
        
        CallGCRecurseContext(function->closure, managed);
    }
    return result;
}


void CallGCTraceRoot(CLOSURE* root,
                     VALUE    curExpr)
{
    //printf("RUNNING GARBAGE COLLECTOR\n");
    //printf(".");

    GC_DATA_MANAGEMENT  managed;
    unsigned int index;

    managed = InitGC(/*managed*/);

    GCAddValue(curExpr, &managed);
//    CallGCRecurseContext(root, &managed);
    CallGCRecurseContext(gCurrentContext, &managed);

    CONTEXT_STACK* stack = gExecutionStack;
    while (stack) {
        CallGCRecurseContext(stack->context, &managed);
        stack = stack->next;
    }
    //CallGCRecurseContext(gGlobalContext, &managed);

    // find elements in gGCManager that are not
    // members of gc managed
    // then remove those elements and free()
    // their memory
    
    /* contexts */
    for (index = 0;
         index < gGCManager.ctx_size;
         index++)
    {
        CLOSURE* context = gGCManager.contexts[index];
        if (!CONTAINS_POINTER_ARRAY((void**)managed.contexts,
                                    managed.ctx_size,
                                    (void*)context))
        {
            ClearContext(context);
            gGCManager.contexts[index] = NULL;
            gGCManager.contexts[index] = gGCManager.contexts[gGCManager.ctx_size-1];
            gGCManager.ctx_size--;
            index--;
        }
    }

    /* functions */
    for (index = 0;
         index < gGCManager.func_size;
         index++)
    {
        FUNCTION* function = gGCManager.functions[index];
        if (!CONTAINS_POINTER_ARRAY((void**)managed.functions,
                                    managed.func_size,
                                    (void*)function))
        {
            ClearFunction(function);
            gGCManager.functions[index] = NULL;
            gGCManager.functions[index] = gGCManager.functions[gGCManager.func_size-1];
            gGCManager.func_size--;
            index--;
        }
    }

    /* dictionaries */
    for (index = 0;
         index < gGCManager.table_size;
         index++)
    {
        HASH_TABLE* table = gGCManager.tables[index];
        if (!CONTAINS_POINTER_ARRAY((void**)managed.tables,
                                    managed.table_size,
                                    (void*)table))
        {
            ClearDictionary(table);
            gGCManager.tables[index] = NULL;
            gGCManager.tables[index] = gGCManager.tables[gGCManager.table_size-1];
            gGCManager.table_size--;
            index--;
        }
    }

    /* strings */
    for (index = 0;
         index < gGCManager.str_size;
         index++)
    {
        char* string = gGCManager.strings[index];
        if (!CONTAINS_POINTER_ARRAY((void**)managed.strings,
                                    managed.str_size,
                                    (void*)string))
        {
            ClearString(string);
            gGCManager.strings[index] = NULL;
            gGCManager.strings[index] = gGCManager.strings[gGCManager.str_size-1];
            gGCManager.str_size--;
            index--;
        }
    }

    FreeGCMgmtObject(managed);
}


void ClearAllGC()
{
    unsigned int index;
    /* contexts */
    for (index = 0;
         index < gGCManager.ctx_size;
         index++)
    {
        CLOSURE* context = gGCManager.contexts[index];
        ClearContext(context);
    }

    /* functions */
    for (index = 0;
         index < gGCManager.func_size;
         index++)
    {
        FUNCTION* function = gGCManager.functions[index];
        ClearFunction(function);
    }

    /* dictionaries */
    for (index = 0;
         index < gGCManager.table_size;
         index++)
    {
        HASH_TABLE* table = gGCManager.tables[index];
        ClearDictionary(table);
    }

    /* strings */
    for (index = 0;
         index < gGCManager.str_size;
         index++)
    {
        char* string = gGCManager.strings[index];
        ClearString(string);
    }

    /* parse tree */
    AST_STORE *cur_ast, *next_ast;
    cur_ast = gGCManager.parseTrees;
    while (cur_ast) {
        next_ast = cur_ast->next;
        FreeParseTree(cur_ast->parseTree);
        free(cur_ast);
        cur_ast = next_ast;
    }

    /* lexings */
    LEXING_STORE *cur_lex, *next_lex;
    cur_lex = gGCManager.lexings;
    while (cur_lex) {
        next_lex = cur_lex->next;
        FreeLexing(cur_lex->tokens, cur_lex->buffer);
        free(cur_lex);
        cur_lex = next_lex;
    }
}

// ***************************************************************************
//
//

int GCAddValue(VALUE value,
                GC_DATA_MANAGEMENT* gc) 
{
    if (value.type == VAL_STRING &&
        value.const_string == 0 &&
        value.data.string)
    {
        return GCAddString((char*)value.data.string, gc);
    }
    else if (value.type == VAL_REFERENCE &&
             value.data.reference)
    {
        return GCAddContext(value.data.reference, gc);
    }
    else if (value.type == VAL_FUNCTION &&
             value.data.function)
    {
        return GCAddFunction(value.data.function, gc);
    }
    else if (value.type == VAL_DICTIONARY &&
             value.data.dictionary)
    {
        return GCAddDictionary(value.data.dictionary, gc);
    }
    return 0;
}

int GCAddString(char* string, GC_DATA_MANAGEMENT* gc) 
{ 
    return
    ADD_POINTER_ARRAY((void***)&gc->strings,
                      &(gc->str_capacity),
                      &(gc->str_size),
                      (void*)string);
}

int GCAddContext(CLOSURE* context, GC_DATA_MANAGEMENT* gc)
{ 
    return
    ADD_POINTER_ARRAY((void***)&gc->contexts,
                      &(gc->ctx_capacity),
                      &(gc->ctx_size),
                      (void*)context);

}
int GCAddFunction(FUNCTION* function, GC_DATA_MANAGEMENT* gc) 
{ 
    return
    ADD_POINTER_ARRAY((void***)&gc->functions,
                      &(gc->func_capacity),
                      &(gc->func_size),
                      (void*)function);
}
int GCAddDictionary(HASH_TABLE* table, GC_DATA_MANAGEMENT* gc)
{ 
    return 
    ADD_POINTER_ARRAY((void***)&gc->tables,
                      &(gc->table_capacity),
                      &(gc->table_size),
                      (void*)table);
}

void GCAddLexing(L_TOKEN* lexing, 
                 char*    buffer)
{
    if (gGCManager.lexings == NULL)
    {
        gGCManager.lexings = (LEXING_STORE*)malloc(sizeof(LEXING_STORE));
        gGCManager.lexings->tokens = lexing;
        gGCManager.lexings->buffer = buffer;
        gGCManager.lexings->next = NULL;
    } else {
        LEXING_STORE* cur = gGCManager.lexings;
        while (cur->next) cur = cur->next;
        cur->next = (LEXING_STORE*)malloc(sizeof(LEXING_STORE));
        cur = cur->next;
        cur->tokens = lexing;
        cur->buffer = buffer;
        cur->next = NULL;
    }
}

void GCAddParseTree(SYNTAX_TREE* syntax)
{
    if (gGCManager.parseTrees == NULL)
    {
        gGCManager.parseTrees = (AST_STORE*)malloc(sizeof(AST_STORE));
        gGCManager.parseTrees->parseTree = syntax;
        gGCManager.parseTrees->next = NULL;
    } else {
        AST_STORE* cur = gGCManager.parseTrees;
        while (cur->next) cur = cur->next;
        cur->next = (AST_STORE*)malloc(sizeof(AST_STORE));
        cur = cur->next;
        cur->parseTree = syntax;
        cur->next = NULL;
    }
}

/* ************************************************************************* */

// aux type clearing functions
void ClearFunction(FUNCTION* function)
{
    if (function) {
        PAIR *itr, *itr_next;
        itr = function->parameters;
        while (itr) {
            itr_next = itr->next;
            free(itr);
            itr = itr_next;
        }
        //ClearContext(function->closure);
        if (function->built_in) {
            free(function->func_data);
        }
        free(function);
    }
}

void ClearString(char* string)
{
    //printf("freeing string '%s'\n", string);
    free(string);
}

void ClearContext(CLOSURE* context)
{
    if (context) {
        PAIR *itr, *itr_next;
        itr = context->list;
        while (itr) {
            itr_next = itr->next;
            free(itr);
        itr = itr_next;
        }
        free(context);
    }
}

void ClearDictionary(HASH_TABLE* table)
{
    FreeHashTable(table);
}

