/* memory.c */

#include "memory.h"
#include "interpreter.h"

MEM_PAGE* gBaseMemory;
MEM_PAGE* gWorkingMemory;

void ForceFreeFunction(FUNCTION* func)
{
    return;
    {
        if (func->closure->ref_count >= 0)
        {
            FreeContext(func->closure);
        }
    }
    if (!func->built_in)
        DEALLOC(func);
}

void ForceFreeContext(CONTEXT* context)
{
    return;
    PAIR *itr, *next;
    itr = context->list;
    context->ref_count = -1;
    while (itr)
    {
        next = itr->next;
        if (itr->value.type == VAL_REFERENCE
            && itr->value.data.reference
            /*&& itr->value.reference->ref_count != -1*/)
        {
            ForceFreeContext(itr->value.data.reference);
        }
        else if (itr->value.type == VAL_FUNCTION)
        {
            ForceFreeFunction(itr->value.data.function);
        }
        DEALLOC(itr);
        itr = next;
    }
    DEALLOC(context);
}

void FreeContext(CONTEXT* context)
{
    return;
    PAIR *itr, *next;
    itr = context->list;
    while (itr)
    {
        next = itr->next;
        InvalidateExpr(itr->value);
        DEALLOC(itr);
        itr = next;
    }
    DEALLOC(context);
}

void FreeFunction(FUNCTION* func)
{
    return;
    //PAIR *itr, *next;
    if (func->closure->ref_count > 0)
    {
        func->closure->ref_count--;
        if (func->closure->ref_count == 0)
        {
            FreeContext(func->closure);
        }
    }
    DEALLOC(func);
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
}

void FreeEnvironment()
{
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
    HASH_TABLE* ht = (HASH_TABLE*)malloc(sizeof(HASH_TABLE));
    ht->capacity = HT_MIN_CAPACITY;
    ht->size = 0;
    ht->table = (KEY_VALUE_PAIR*)malloc(HT_MIN_CAPACITY * sizeof(KEY_VALUE_PAIR));
    memset((void*)ht->table, 0, HT_MIN_CAPACITY * sizeof(KEY_VALUE_PAIR));
//    printf("Creating hash table.\n");
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



