/* memory.c */

#include "memory.h"
#include "interpreter.h"
#include "garbage.h"

MEM_PAGE* gBaseMemory;
MEM_PAGE* gWorkingMemory;

/* managed objects */

/*
HASH_TABLE* gObjectPool;
void InitObjectPool()
{
    gObjectPool = CreateHashTable();
}
int  AddObjectPool(VALUE object)
{
    int count;
    count = 0;
    if (IsDynamic(object))
    {
        VALUE entry = HashGet(object, gObjectPool);
        if (entry.type == VAL_PRIMITIVE)
        {
            count = ++(entry.data.primitive);
            HashStore(object, entry, gObjectPool);
        } else {
            entry.type = VAL_PRIMITIVE;
            entry.data.primitive = 1;
            HashStore(object, entry, gObjectPool);
            count = 1;
        }
    }
    return count;
}
int  RemoveObjectPool(VALUE object)
{
    if (IsDynamic(object)) 
    {
        VALUE entry = HashGet(object, gObjectPool)
        if (entry.type == VAL_PRIMITIVE)
        {
            int count = entry.data.primitive;
            entry.data.primitive = 0;
            if (count) {
                HashStore(object, entry, gObjectPool);
            }
            return count;
        } else {
            return 0;
        }
    }

    return 0;
}
void ClearObjectPool()
{
    int itr = 0;
    while (itr < gObjectPool->capacity)
    {
        KEY_VALUE_PAIR pair = gObjectPool->table[itr];
        int count;
        VALUE key;
        VALUE value;

        key = pair.key;
        value = pair.value;

        count = (value.type == VAL_PRIMITIVE ? value.data.primitive : 0);
        if (count) 
        {
            // FreeObject(&key);
        }

        itr++;
    }

    FreeHashTable(gObjectPool);
    gObjectPool = NULL;
}
*/


// ***************************************************************************
//
//


/* ************************************************************************* */

#if 0
void ForceFreeFunction(FUNCTION* func)
{
    return;
}

void ADD_POINTER_ARRAY(void*** array,
                       unsigned int* capacity, 
                       unsigned int* size, 
                       void* entry)
{
    if (entry) {
        int i;
        for (i = 0; i < *size; i++)
            if ((*array)[i] == entry)
                break;
        if (i == *size)
        {
            (*array)[*size] = entry;
            (*size)++;
            
            if (*size == *capacity) {
                *capacity = *capacity * 2;
                *array = realloc((void*)(*array), sizeof(void*) * *capacity);
                /* assert(*array); */
                if (array == 0) printf("Error: Out of memory.\n");
            }
        }
    }
}

void ForceFreeContext(CONTEXT* gContext)
{
    CONTEXT** contexts;
    unsigned int ctx_capacity = 128;
    unsigned int ctx_size = 0;
    contexts = (CONTEXT**)malloc(sizeof(CONTEXT*) * ctx_capacity);

    FUNCTION** functions;
    unsigned int func_capacity = 128;
    unsigned int func_size = 0;
    functions = (FUNCTION**)malloc(sizeof(FUNCTION*) * func_capacity);

    char** strings;
    unsigned int strs_capacity = 128;
    unsigned int strs_size = 0;
    strings = (char**)malloc(sizeof(char*) * strs_capacity);

    HASH_TABLE** tables;
    unsigned int tables_capacity = 128;
    unsigned int tables_size = 0;
    tables = (HASH_TABLE**)malloc(sizeof(HASH_TABLE) * tables_capacity);

    contexts[ctx_size++] = gContext;

    unsigned int cur_context = 0;
    /* traverse every context / closure */
    while (cur_context < ctx_size)
    {
        //printf("%i / %i\n", cur_context, ctx_size);
        CONTEXT* context = contexts[cur_context];
        PAIR *itr, *itr_next;

        context = context->parent;
        while (context) {
            //printf("adding parent\n");
            ADD_POINTER_ARRAY(&contexts, &ctx_capacity, &ctx_size,
                              context);
            context = context->parent;
        }

        context = contexts[cur_context];
        itr = context->list;
        while (itr) {
            itr_next = itr->next;

            printf("%s\n", itr->identifier);

            if (itr->value.type == VAL_REFERENCE) 
            {
                //printf("ref - ");
                ADD_POINTER_ARRAY(&contexts, &ctx_capacity, &ctx_size,
                                  itr->value.data.reference);
            }
            else if (itr->value.type == VAL_FUNCTION)
            {
                ADD_POINTER_ARRAY(&functions, &func_capacity, &func_size,
                                  itr->value.data.function);
                ADD_POINTER_ARRAY(&contexts, &ctx_capacity, &ctx_size,
                                  itr->value.data.function->closure);
            }
            else if (itr->value.type == VAL_DICTIONARY)
            {
                ADD_POINTER_ARRAY(&tables, &tables_capacity, &tables_size,
                                  itr->value.data.dictionary);
            }
            else if (itr->value.type == VAL_STRING)
            {
                if (itr->value.const_string == 0)
                {
                    ADD_POINTER_ARRAY(&strings, &strs_capacity, &strs_size,
                                      itr->value.data.string);
                }
            }

            // free pairs
            DEALLOC(itr);
            itr = itr_next;
        }
        //printf("\nnext context\n\n");
        printf("\n");
        cur_context++;
        /* DEALLOC(context); */
    }

    unsigned int iterator;
    printf("clearing functions\n");
    /* free all functions */
    for (iterator = 0; iterator < func_size; iterator++) 
    {
        PAIR *itr, *itr_next;
        itr = functions[iterator]->parameters;
        while (itr) {
            itr_next = itr->next;
            DEALLOC(itr);
            itr = itr_next;
        }
        DEALLOC(functions[iterator]);
    }

    printf("clearing dictionaries\n");
    /* free all dictionaries */
    for (iterator = 0; iterator < tables_size; iterator++)
    {
        FreeHashTable(tables[iterator]);
    }

    printf("clearing strings\n");
    /* free all strings */
    for (iterator = 0; iterator < strs_size; iterator++)
    {
        DEALLOC(strings[iterator]);
    }

    printf("clearing closures\n");
    /* free all closures */
    for (iterator = 0; iterator < ctx_size; iterator++)
    {
        DEALLOC(contexts[iterator]);
    }

    printf("removing object lists\n");
    /* free dynamic arrays */
    free(contexts);
    free(functions);
    free(tables);
    free(strings);
    
    return;
}

void FreeContext(CONTEXT* context)
{
    return;
}

void FreeFunction(FUNCTION* func)
{
    return;
}

VALUE MakeTemporary(VALUE expr)
{
    return;
    if (expr.type == VAL_STRING) {
        char* new_string = (char*)ALLOC(strlen(expr.data.string)+1);
        sprintf(new_string, "%s", expr.data.string);
        expr.type = VAL_STRING;
        expr.data.string = new_string;
    }
    return expr;
}

void IncrementReferences(VALUE* expr)
{
    return;
    if (expr) {
        if (expr->type == VAL_FUNCTION) {

        } else if (expr->type == VAL_REFERENCE) {

        } else if (expr->type == VAL_DICTIONARY) {
            expr->data.dictionary->ref_count++;
            printf("dict ref_count: %i\n", expr->data.dictionary->ref_count);
        }
    }
}

void InvalidateExpr(VALUE* expr)
{
    return;
    if (expr) 
    {
/*      if (expr->type == VAL_STRING) 
        {
            free(expr->data.string);
            expr->data.string = NULL;
        } 
        else if (expr->type == VAL_FUNCTION) 
        {
            free(expr->data.function);
            expr->data.function = NULL;
        } 
        else if (expr->type == VAL_REFERENCE) 
        {
            free(expr->data.reference);
            expr->data.reference = NULL;
        }*/
        /*if (expr->type == VAL_DICTIONARY) 
        {
            FreeHashTable(expr->data.dictionary);
            expr->data.dictionary = NULL;
        }*/

        if (expr->type == VAL_DICTIONARY) {
            expr->data.dictionary->ref_count--;
            printf("dict ref_count: %i\n", expr->data.dictionary->ref_count);
            if (expr->data.dictionary->ref_count <= 0) {
                FreeHashTable(expr->data.dictionary);
                expr->data.dictionary = NULL;
            }
        }

        if (expr->type == VAL_STRING &&
            expr->const_string == 0)
        {
            printf("freeing: '%s'\n", expr->data.string);
            DEALLOC((char*)expr->data.string);
            expr->data.string = NULL;
        }

        expr->type = VAL_NIL;
        expr->data.primitive = 0;
    }
}


/*
void InvalidateExpr(VALUE expression)
{
    return;
    if (expression.type == VAL_REFERENCE)
    {
        if (expression.data.reference->ref_count > 0)
        {
            expression.data.reference->ref_count--;
            if (expression.data.reference->ref_count == 0)
            {
                FreeContext(expression.data.reference);
            }
        }
    }
    else if (expression.type == VAL_FUNCTION)
    {
        if (expression.data.function->ref_count > 0)
        {
            expression.data.function->ref_count--;
            if (expression.data.function->ref_count == 0)
            {
                FreeFunction(expression.data.function);
            }
        }
    }
}
*/
#endif

/* temporary values */
void* ALLOC(size_t amount)
{
    return malloc(amount);
}

void DEALLOC(void* addr)
{
    free(addr);
}

/* immutable strings? */
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

void  DEALLOCATE(void* memory)
{
    MEM_PAGE* base = gBaseMemory;
    if (memory == NULL) return;

    while (base) {
        unsigned int index;

        for (index = 0; index < base->page_index; index++) {
            void* addr = base->data_ptrs[index];
            if (addr == memory) {
                free(addr);
                base->data_ptrs[index] = NULL;
                return;
            }
        }
        base = base->next_page;
    }
}

/* create sandbox */
void CreateEnvironment()
{
    gBaseMemory = NULL;
    gWorkingMemory = NULL;
    gBaseMemory = (MEM_PAGE*)malloc(sizeof(MEM_PAGE));
    gBaseMemory->page_index = 0;
    gBaseMemory->next_page = NULL;
    gWorkingMemory = gBaseMemory;

    // gc
    gGCManager = InitGC(gGCManager);
}

void FreeEnvironment()
{
    // gc
    ClearAllGC();
    FreeGCMgmtObject(gGCManager);

    // sandbox
    while (gBaseMemory) {
        MEM_PAGE* cur_page;
        unsigned int index;

        for (index = 0; index < gBaseMemory->page_index; index++) {
            void* addr = gBaseMemory->data_ptrs[index];
            if (addr) 
                free(addr);
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
    
    VALUE nill;
    nill.type = VAL_NIL;
    nill.data.primitive = 0;
    return nill;
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
        if (top->list) {
            PAIR* iterator = top->list;
            while (iterator->next) {
                iterator = iterator->next;
            }
            iterator->next = (PAIR*)ALLOC(sizeof(PAIR));
            iterator->next->value = value;
            iterator->next->identifier = identifier;
            iterator->next->next = NULL;
        } else {
            top->list = (PAIR*)ALLOC(sizeof(PAIR));
            top->list->value = value;
            top->list->identifier = identifier;
            top->list->next = NULL;
        }
    }
}

void RemoveRecord(const char* identifier, CONTEXT* context)
{
    PAIR* prev = NULL;
    while (context)
    {
        PAIR* iterator = context->list;
        while (iterator)
        {
            if (strcmp(identifier, iterator->identifier) == 0)
            {
                if (prev) {
                    prev->next = iterator->next;
                } else {
                    context->list = iterator->next;
                }
                free (iterator);
                return;
            }
            prev = iterator;
            iterator = iterator->next;
        }
        context = context->parent;
    }
}


/* hash function */
unsigned int HashFunction(VALUE value)
{
    unsigned int hash;
    const char* p;
    switch (value.type) {
        case VAL_NIL: return 0;
        case VAL_PRIMITIVE: return (unsigned int)value.data.primitive;
        case VAL_FLOATING_POINT: return (unsigned int)value.data.floatp;
        case VAL_REFERENCE: return (unsigned long)value.data.reference;
        case VAL_FUNCTION: return (unsigned long)value.data.function;
        case VAL_DICTIONARY: return (unsigned long)value.data.dictionary;
        case VAL_STRING:
            hash = 0;
            p = value.data.string;
            while (*p) {
                hash = (hash << 7) ^ hash;
                hash += (*p);
                p++;
            }
            return hash;
    }
    return 0;
}

/* hash table */
HASH_TABLE* CreateHashTable()
{
    return CreateHashTableN(HT_MIN_CAPACITY);
}

HASH_TABLE* CreateHashTableN(int htsize)
{
    if (htsize <= 2) htsize = HT_MIN_CAPACITY;

    HASH_TABLE* ht = (HASH_TABLE*)malloc(sizeof(HASH_TABLE));
    ht->capacity = htsize;
    ht->size = 0;
    ht->table = (KEY_VALUE_PAIR*)malloc(htsize * sizeof(KEY_VALUE_PAIR));
    memset((void*)ht->table, 0, htsize * sizeof(KEY_VALUE_PAIR));
    return ht;
}

void FreeHashTable(HASH_TABLE* table)
{
    free(table->table);
    free(table);
}

void ResizeHashTable(HASH_TABLE* table)
{
    // double size
    int new_capacity;
    KEY_VALUE_PAIR* new_table;

    new_capacity = table->capacity * HT_RESIZE_FACTOR;
    //printf("Resizing hash table to %i entries.\n", new_capacity);
    // if (new_capacity < table->size) new_capacity += ...
    new_table = (KEY_VALUE_PAIR*)malloc(new_capacity * sizeof(KEY_VALUE_PAIR));
    memset((void*)new_table, 0, new_capacity * sizeof(KEY_VALUE_PAIR));

    int itr; int cap;
    unsigned int index;
    KEY_VALUE_PAIR pair;
    cap = table->capacity;
    // copy table
    for (itr = 0; itr < cap; itr++)
    {
        if (table->table[itr].key.type != VAL_NIL)
        {
            pair = table->table[itr];
            index = HashFunction(pair.key) % new_capacity;
            while (new_table[index].key.type != VAL_NIL)
                { index = (index + 1) % new_capacity; }
            new_table[index] = pair;
        }
    }
    
    table->capacity = new_capacity;
    // free old array
    free(table->table);
    table->table = new_table;
}

/* hash table */
VALUE HashGet(VALUE key_identifier, HASH_TABLE* table)
{
//    printf("Hash Get: %i %x, %p\n", key_identifier.type, key_identifier.data.primitive, table);

    unsigned int index;
    index = HashFunction(key_identifier);
    index = index % table->capacity;

    KEY_VALUE_PAIR* table_entries;
    table_entries = table->table;

    if (key_identifier.type == VAL_STRING) 
    {
        while (table_entries[index].key.type != VAL_NIL &&
               !(table_entries[index].key.type == VAL_STRING &&
                 strcmp(table_entries[index].key.data.string,
                        key_identifier.data.string) == 0))
        {
            index = (index+1) % table->capacity;
        }
    } else {
        while (table_entries[index].key.type != VAL_NIL &&
               !(key_identifier.type == table_entries[index].key.type &&
                 key_identifier.data.primitive == table_entries[index].key.data.primitive))
        {
            index = (index+1) % table->capacity;
        }
    }
    if (table_entries[index].key.type == VAL_NIL) 
    {
        VALUE null;
        null.type = VAL_NIL;
        null.data.primitive = 0;
        return null;
    }
    return table_entries[index].value;
}

void HashStore(VALUE key_identifier, VALUE store, HASH_TABLE* table)
{
//    printf("Hash Store: %i %x, %p => %i %x\n", key_identifier.type, key_identifier.data.primitive, table, store.type, store.data.primitive);

    if (key_identifier.type == VAL_NIL) return;
    if (table->size > 5*table->capacity/7) 
    {
        ResizeHashTable(table);
    }

    unsigned int index;
    index = HashFunction(key_identifier);
    index = index % table->capacity;

    KEY_VALUE_PAIR* table_entries;
    table_entries = table->table;

    if (key_identifier.type == VAL_STRING)
    {
        while (table_entries[index].key.type != VAL_NIL &&
               !(table_entries[index].key.type == VAL_STRING &&
                 strcmp(table_entries[index].key.data.string,
                        key_identifier.data.string) == 0))
        {
            index = (index+1) % table->capacity;
        }
    }
    else
    {
        while (table_entries[index].key.type != VAL_NIL &&
               !(key_identifier.type == table_entries[index].key.type &&
                 key_identifier.data.primitive == table_entries[index].key.data.primitive))
        {
            index = (index+1) % table->capacity;
        }
    }

    if (table_entries[index].key.type == VAL_NIL) table->size++;
    table_entries[index].key = key_identifier;
    table_entries[index].value = store;
    return;    
}



