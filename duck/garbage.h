#ifndef _GARBAGE_H
#define _GARBAGE_H

#include "memory.h"
#include "interpreter.h"

#define GC_COLLECT_LIMIT        8192

typedef struct LEXING_STORE
{
    L_TOKEN* tokens;
    char*    buffer;
    struct LEXING_STORE* next;
} LEXING_STORE;

typedef struct AST_STORE
{
    SYNTAX_TREE* parseTree;
    struct AST_STORE* next;
} AST_STORE;

typedef struct
GC_DATA_MANAGEMENT
{
    // eval environment
    LEXING_STORE*   lexings;
    AST_STORE*      parseTrees;

    // program data
    CLOSURE**   contexts;
    unsigned int ctx_capacity;
    unsigned int ctx_size;

    FUNCTION**  functions;
    unsigned int func_capacity;
    unsigned int func_size;

    char**      strings;
    unsigned int str_capacity;
    unsigned int str_size;

    HASH_TABLE** tables;
    unsigned int table_capacity;
    unsigned int table_size;
} GC_DATA_MANAGEMENT;

GC_DATA_MANAGEMENT InitGC(/*GC_DATA_MANAGEMENT*/);
void FreeGCMgmtObject(GC_DATA_MANAGEMENT);

int CallGCRecurseContext(CLOSURE*, GC_DATA_MANAGEMENT*);
int CallGCRecurseDictionary(HASH_TABLE*, GC_DATA_MANAGEMENT*);
int CallGCRecurseFunction(FUNCTION*, GC_DATA_MANAGEMENT*);

void CallGCTraceRoot(CLOSURE*, VALUE);
void ClearAllGC();

int GCAddValue(VALUE, GC_DATA_MANAGEMENT*);
int GCAddString(char*, GC_DATA_MANAGEMENT*);
int GCAddContext(CLOSURE*, GC_DATA_MANAGEMENT*);
int GCAddFunction(FUNCTION*, GC_DATA_MANAGEMENT*);
int GCAddDictionary(HASH_TABLE*, GC_DATA_MANAGEMENT*);

void GCAddLexing(L_TOKEN* lexing, char* buffer);
void GCAddParseTree(SYNTAX_TREE* syntax);

extern GC_DATA_MANAGEMENT   gGCManager;

// aux type clearing functions
void ClearFunction(FUNCTION*);
void ClearString(char*);
void ClearContext(CLOSURE*);
void ClearDictionary(HASH_TABLE*);

#endif // _GARBAGE_H
