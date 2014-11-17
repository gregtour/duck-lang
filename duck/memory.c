/* memory.c */

#include "memory.h"
#include "interpreter.h"

MEM_PAGE* gBaseMemory;
MEM_PAGE* gWorkingMemory;

void ForceFreeFunction(FUNCTION* func)
{
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
    PAIR *itr, *next;
    itr = context->list;
    context->ref_count = -1;
    while (itr)
    {
        next = itr->next;
        if (itr->value.type == VAL_REFERENCE
            && itr->value.reference
            /*&& itr->value.reference->ref_count != -1*/)
        {
            ForceFreeContext(itr->value.reference);
        }
        else if (itr->value.type == VAL_FUNCTION)
        {
            ForceFreeFunction(itr->value.function);
        }
        DEALLOC(itr);
        itr = next;
    }
    DEALLOC(context);
}

void FreeContext(CONTEXT* context)
{
//    return;
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
//    return;
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

void InvalidateExpr(VALUE expression)
{
    if (expression.type == VAL_REFERENCE)
    {
        if (expression.reference->ref_count > 0)
        {
            expression.reference->ref_count--;
            if (expression.reference->ref_count == 0)
            {
                FreeContext(expression.reference);
            }
        }
    }
    else if (expression.type == VAL_FUNCTION)
    {
        if (expression.function->ref_count > 0)
        {
            expression.function->ref_count--;
            if (expression.function->ref_count == 0)
            {
                FreeFunction(expression.function);
            }
        }
    }
}

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
    nill.primitive = 0;
    nill.floatp = 0.0f;
    nill.string = NULL;
    nill.function = NULL;
    nill.reference = NULL;

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

