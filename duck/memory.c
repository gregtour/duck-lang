/* memory.c */

#include "memory.h"
#include "interpreter.h"

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

