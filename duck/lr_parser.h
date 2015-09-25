/* lr_parser.h */
#ifndef _LR_PARSER_H
#define _LR_PARSER_H

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// unsigned types
typedef unsigned char u8;
typedef unsigned long u32;

/* ************************************************************************** */
/*                               CONSTANTS                                    */
/* ************************************************************************** */

// constant constraints for language spec
//#define _LR1
#define _SLR

#define LEX_NEWLINES
#define IGNORE_MACROS
#define SEMICOLON_COMMENTS
#define CASE_SENSITIVE
#define CASE_SENSITIVE_KEYWORDS

#define SYMBOL_BUFFER_SIZE  4096
#define TOKEN_BUFFER_SIZE   4096
#define MAX_RULES           256
#define RULE_RHS_SIZE       24
#define K_VALUE             (256*16 - 1)
#define K_SYMBOL            (256*16)
#define K_TOKEN             (256*32)
#define ACTION_ERROR        0
#define ACTION_SHIFT        1
#define ACTION_REDUCE       2
#define ACTION_ACCEPT       3
#define TOKEN_L_TOKEN       1
#define TOKEN_SYNTAX_TREE   2

// Clang doesn't seem to support this kind of memory tracking.
#if defined(__clang__) && defined(_MEM_TRACKING)
#undef _MEM_TRACKING
#endif

#ifdef _MEM_TRACKING
#ifndef malloc
#define malloc      MallocTrackMemory
#endif

#ifndef free
#define free        FreeTrackMemory
#endif

#ifndef realloc
#define realloc     ReallocTrackMemory
#endif
#endif

// Mem tracking accessors
unsigned int CheckMemoryUsage();
void PrintMemoryUsage();

/* ************************************************************************** */
/*                                GLOBALS                                     */
/* ************************************************************************** */

// built in symbols

extern int gSymbolEpsilon;
extern int gSymbolEOF;
extern int gSymbolEndLine;
extern int gSymbolInteger;
extern int gSymbolFloat;
extern int gSymbolString;
extern int gSymbolIdentifier;
extern int gSymbolRoot;
extern int gSymbolGoal;

/* ************************************************************************** */
/*                             DATA STRUCTURES                                */
/* ************************************************************************** */

// context free grammar data structures
typedef struct RULE
{
    int  lhs;
    int  rhsLength;
    int* rhs;
} RULE;

typedef struct GRAMMAR_TABLE
{
    int    numSymbols;
    char*  symbols;
    int    numTokens;
    char*  tokens;
    int    numRules;
    RULE*  rules;
} GRAMMAR_TABLE;

// LR parser generator data structures
typedef struct LR_ITEM
{
    int production;
    int dot;
    int lookahead;
} LR_ITEM;

typedef struct LR_ITEM_SET
{
    LR_ITEM item;
    struct LR_ITEM_SET*
            next;
} LR_ITEM_SET;

typedef struct LR_ITEM_COLLECTION
{
    LR_ITEM_SET* set;
    struct LR_ITEM_COLLECTION*
                 next;
} LR_ITEM_COLLECTION;

// lexer token data structure
typedef struct L_TOKEN
{
    // token information
    int         token;
    char*       string;
    int         length;
    /* meta data */
    int      line;
    // char*    comment;
    // linked list
    struct L_TOKEN* next;
} L_TOKEN;

// parse table data structures
typedef struct ACTION
{
    int type;
    int value;
} ACTION;

typedef struct LR_TABLE
{
    int numTokens;
    int numSymbols;
    int numStates;
    ACTION* actionTable;
    int*    gotoTable;
} LR_TABLE;

// parser data structures
typedef struct PARSE_STACK
{
    void*  token;
    int    type;
    int    state;
    struct PARSE_STACK* next;
    struct PARSE_STACK* prev;
} PARSE_STACK;


struct AST_TAG;

// abstract syntax tree data structure
typedef struct SYNTAX_TREE
{
    // current node
    int         token;
    int         production;
    const char* string;
    int         length;
    int         line;
    // compiler information
    struct AST_TAG *tag;
    // child nodes
    unsigned int numChildren;
    struct SYNTAX_TREE** children;
} SYNTAX_TREE;


/* ************************************************************************** */
/*                        FUNCTION DEFINITIONS                                */
/* ************************************************************************** */

#ifdef _MEM_TRACKING
void* MallocTrackMemory(size_t);
void  FreeTrackMemory(void*);
void* ReallocTrackMemory(void*, size_t);
//void  FreeTrackMemory(void*);
//void* MallocTrackMemory(size_t, const char*, int);
//void FreeTrackMemory(void*, const char*, int);
//void PrintMemoryUsage();
#endif

/* GRAMMAR.C */

char* GetElement(int i, GRAMMAR_TABLE grammar);
RULE* GetRule(int lhs, int n, GRAMMAR_TABLE grammar);

int AddSymbol(char*          string,
              int            len,
              GRAMMAR_TABLE* grammar);

int AddToken(char*           string,
              int            len,
              GRAMMAR_TABLE* grammar);

int FindToken(char*          string,
              int            len,
              GRAMMAR_TABLE  grammar);
              
int  LoadGrammar(const char* file, GRAMMAR_TABLE* table);
void FreeGrammarTable(GRAMMAR_TABLE* table);
void PrintGrammar(GRAMMAR_TABLE table);

/* LEXER.C */

void LexAddBlock(L_TOKEN** start,
                 L_TOKEN** end,
                 L_TOKEN*  next);

L_TOKEN* EOFSYMBOL(int line);
L_TOKEN* NEWLINE(int line);
L_TOKEN* INTEGER(char* source, int start, int end, int line);
L_TOKEN* STRING(char* source, int start, int end, int line);
L_TOKEN* TOKEN(char* source, int start, int end, int line, GRAMMAR_TABLE grammar);
L_TOKEN* IDENTIFIER(char* source, int start, int end, int line, GRAMMAR_TABLE grammar);

int isAlpha(char c);
int isNumeric(char c);
int isSpace(char c);
int isGlyph(char c);

L_TOKEN* LexSource(const char*    file,
                   char**         stripped,
                   GRAMMAR_TABLE  table);
L_TOKEN* LexSourceBuffer(const char*    source_buffer,
                         char**         stripped,
                         GRAMMAR_TABLE  table);
void FreeLexing(L_TOKEN* lexing, char* buffer);
void PrintLexing(L_TOKEN* lexing);

/* LR_TABLE.C */

ACTION ActionTable(LR_TABLE table, int state, int token);
int GotoTable(LR_TABLE table, int state, int symbol);

LR_TABLE ConstructTable(LR_ITEM_COLLECTION* C, GRAMMAR_TABLE* G);
LR_ITEM_SET* Closure(LR_ITEM_SET* I, GRAMMAR_TABLE* G);
LR_ITEM_SET* Goto(LR_ITEM_SET* I, int X, GRAMMAR_TABLE* G);
int CompareItems(LR_ITEM one, LR_ITEM two);
int CompareItemSets(LR_ITEM_SET* one, LR_ITEM_SET* two);
void FreeItemSet(LR_ITEM_SET* I);
LR_ITEM_SET* Sort(LR_ITEM_SET* I);
LR_ITEM_SET* CopyItemSet(LR_ITEM_SET* I);
void SWAP_ITEMS(LR_ITEM* one, LR_ITEM* two);
int GotoState(LR_ITEM_SET* set, LR_ITEM_COLLECTION* find);

LR_ITEM_COLLECTION* CanonicalCollection(GRAMMAR_TABLE* G);
void FreeCollection(LR_ITEM_COLLECTION* collection);

void BuildFirstSets(GRAMMAR_TABLE* G);
void BuildFollowSets(GRAMMAR_TABLE* G);
int  SetFirstTable(int symbol, int token, int value, GRAMMAR_TABLE* G);
int  GetFirstTable(int symbol, int token, GRAMMAR_TABLE* G);
int  SetFollowTable(int symbol, int token, int value, GRAMMAR_TABLE* G);
int  GetFollowTable(int symbol, int token, GRAMMAR_TABLE* G);
void FindNullableNonterminals(GRAMMAR_TABLE* G);
int  IsNullable(int symbol);
void RemoveEpsilons(GRAMMAR_TABLE* G);

void PrintItem(LR_ITEM item, GRAMMAR_TABLE* G);
void PrintItemSet(LR_ITEM_SET* I, GRAMMAR_TABLE* G);
void PrintCollection(LR_ITEM_COLLECTION* C, GRAMMAR_TABLE* G);
void PrintParseTable(LR_TABLE      parser,
                     GRAMMAR_TABLE grammar);
                   
int BuildLRParser(GRAMMAR_TABLE grammar,
                LR_TABLE*     parser);
void FreeLRParser(LR_TABLE* parseTable);
void PrintLRParser(LR_TABLE      parser,
                   GRAMMAR_TABLE grammar);

/* PARSER.C */

SYNTAX_TREE* ParseSource(L_TOKEN*      input,
                         LR_TABLE      parser,
                         GRAMMAR_TABLE grammar);
int  ParseSucceeds(L_TOKEN* input, 
                   LR_TABLE parser, 
                   GRAMMAR_TABLE grammar);
void FreeParseTree(SYNTAX_TREE* syntaxTree);
void PrintParseTree(SYNTAX_TREE*  ast,
                    GRAMMAR_TABLE grammar);
void PrintParseTreeFormat(SYNTAX_TREE*  ast,
                          GRAMMAR_TABLE grammar);
                    
/* GENERATOR.C */

int SaveLRParser(const char*   file,
                 LR_TABLE      parser,
                 GRAMMAR_TABLE grammar);

/* COMPILER.C */
                    

#endif /* _LR_PARSER_H */

