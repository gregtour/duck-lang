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
void  DEALLOCATE(void* memory);
void  CreateEnvironment();
void  FreeEnvironment();

//void* ALLOC(size_t amount);
//void  DEALLOC(void* addr);
#define ALLOC   malloc
#define DEALLOC free

/* accessor functions */
VALUE GetRecord(const char* identifier, CLOSURE* context);
void  StoreRecord(const char* identifier, VALUE value, CLOSURE* context);
void RemoveRecord(const char* identifier, CLOSURE* context);

/* hash table */
#define HT_MIN_CAPACITY     2048
#define HT_RESIZE_FACTOR    8

typedef struct KEY_VALUE_PAIR
{
    VALUE key;
    VALUE value;
} KEY_VALUE_PAIR;

typedef struct HASH_TABLE
{
    unsigned int capacity;
    unsigned int size;
    KEY_VALUE_PAIR* table;    
    // ...
    int ref_count;
} HASH_TABLE;

VALUE HashGet(VALUE key_identifier, HASH_TABLE* table);
void  HashStore(VALUE key_identifier, VALUE store, HASH_TABLE* table);

unsigned int HashFunction(VALUE value);
HASH_TABLE* CreateHashTable();
HASH_TABLE* CreateHashTableN(int size);
void FreeHashTable(HASH_TABLE* table);
void ResizeHashTable(HASH_TABLE* table);

#endif // _MEMORY_H

