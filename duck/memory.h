/* memory.h */
#ifndef _MEMORY_H
#define _MEMORY_H

#include <ctype.h>
#include <stdlib.h>
#include "interpreter.h"

#define PAGE_SIZE       4096

/* memory pages */
typedef struct MEM_PAGE 
{
    void* data_ptrs[PAGE_SIZE];
    unsigned int page_index;
    struct MEM_PAGE* next_page;    
} MEM_PAGE;

extern MEM_PAGE* gBaseMemory;
extern MEM_PAGE* gWorkingMemory;

/* memory management */
void* ALLOCATE(size_t amount);
void  CreateEnvironment();
void  FreeEnvironment();

/* accessor functions */
VALUE GetRecord(const char* identifier, CONTEXT* context);
void  StoreRecord(const char* identifier, VALUE value, CONTEXT* context);

#endif // _MEMORY_H

