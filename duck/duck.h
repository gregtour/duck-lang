/* auto-generated lr parse tables */
#ifndef _DUCK_H
#define _DUCK_H

#include "lr_parser.h"


/* main function */
int InterpretNode(SYNTAX_TREE* node);
void PrintNode(SYNTAX_TREE* node);

/* symbol constants */
#define SYMBOL_PROGRAM                  0x1001
#define SYMBOL_STMT_LIST                0x1002
#define SYMBOL_STMT                     0x1003
#define SYMBOL_REFERENCE                0x1004
#define SYMBOL_EXPR                     0x1005
#define SYMBOL_ASSIGNMENT               0x1006
#define SYMBOL_FUNCTION_DEF             0x1007
#define SYMBOL_IF                       0x1008
#define SYMBOL_FOR_LOOP                 0x1009
#define SYMBOL_WHILE_LOOP               0x100A
#define SYMBOL_PARAMETERS               0x100B
#define SYMBOL_PARAM_DECL               0x100C
#define SYMBOL_CONDITION                0x100D
#define SYMBOL_ELSE_IF                  0x100E
#define SYMBOL_ARITHMETIC               0x100F
#define SYMBOL_L_VALUE                  0x1010
#define SYMBOL_LOGIC                    0x1011
#define SYMBOL_COMPARISON               0x1012
#define SYMBOL_TERM                     0x1013
#define SYMBOL_FACTOR                   0x1014
#define SYMBOL_FINAL                    0x1015
#define SYMBOL_BOOLEAN                  0x1016
#define SYMBOL_OBJECT                   0x1017
#define SYMBOL_ARGUMENTS                0x1018
#define SYMBOL_ARRAY_INIT               0x1019
#define SYMBOL_DICTIONARY_INIT          0x101A


/* Grammar Symbols */
extern char GRAMMAR_SYMBOLS[283];

/* Grammar Tokens */
extern char GRAMMAR_TOKENS[218];

/* CFG Productions */
extern RULE GRAMMAR_RULES[81];

/* Context Free Grammar */
extern GRAMMAR_TABLE CONTEXT_FREE_GRAMMAR;

/* SLR GOTO table */
extern int GOTO_TABLE[4368];

/* SLR ACTION table */
extern ACTION ACTION_TABLE[8400];

/* SLR parse table structure */
extern LR_TABLE PARSE_TABLE;

#endif // _DUCK_H

