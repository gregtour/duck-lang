/* auto-generated lr parse tables */
#ifndef _GENERATED_PARSER_H
#define _GENERATED_PARSER_H

#include "lr_parser.h"


/* main function */
int ProcessNode(SYNTAX_TREE* node);

/* symbol constants */
#define SYMBOL_PROGRAM                    0x1001
#define SYMBOL_STMTLIST                   0x1002
#define SYMBOL_STMT                       0x1003
#define SYMBOL_IDENTIFIER_LIST            0x1004
#define SYMBOL_EXPR                       0x1005
#define SYMBOL_ASSIGNMENT                 0x1006
#define SYMBOL_SELF_ASSIGNMENT            0x1007
#define SYMBOL_FUNCTION_DEF               0x1008
#define SYMBOL_IF                         0x1009
#define SYMBOL_FOR_LOOP                   0x100A
#define SYMBOL_FOR_EACH                   0x100B
#define SYMBOL_WHILE_LOOP                 0x100C
#define SYMBOL_DO_WHILE                   0x100D
#define SYMBOL_LET_BLOCK                  0x100E
#define SYMBOL_TRY_BLOCK                  0x100F
#define SYMBOL_CLASS                      0x1010
#define SYMBOL_L_VALUE                    0x1011
#define SYMBOL_CONDITION                  0x1012
#define SYMBOL_ARITHMETIC                 0x1013
#define SYMBOL_FUNCTION_DECL              0x1014
#define SYMBOL_PARAMETERS                 0x1015
#define SYMBOL_PARAM_DECL                 0x1016
#define SYMBOL_ELSEIF                     0x1017
#define SYMBOL_STEP                       0x1018
#define SYMBOL_BINDINGS                   0x1019
#define SYMBOL_CATCH_BLOCK                0x101A
#define SYMBOL_REFERENCE                  0x101B
#define SYMBOL_LOGIC                      0x101C
#define SYMBOL_COMPARISON                 0x101D
#define SYMBOL_FINAL                      0x101E
#define SYMBOL_TERM                       0x101F
#define SYMBOL_FACTOR                     0x1020
#define SYMBOL_BOOLEAN                    0x1021
#define SYMBOL_OBJECT                     0x1022
#define SYMBOL_ARGUMENTS                  0x1023
#define SYMBOL_ARRAY_INIT                 0x1024
#define SYMBOL_DICTIONARY_INIT            0x1025


/* production constants */
#define PROD_PROGRAM_STMTLIST                       0x0001
#define PROD_STMTLIST_STMT                          0x0002
#define PROD_STMTLIST                               0x0003
#define PROD_IDENTIFIER_LIST_IDENTIFIER_A           0x0004
#define PROD_IDENTIFIER_LIST_IDENTIFIER_B           0x0005
#define PROD_STMT_IMPORT                            0x0006
#define PROD_STMT_INCLUDE                           0x0007
#define PROD_STMT_EXPR                              0x0008
#define PROD_STMT_ENDL                              0x0009
#define PROD_STMT_ASSIGNMENT                        0x000A
#define PROD_STMT_SELF_ASSIGNMENT                   0x000B
#define PROD_STMT_FUNCTION_DEF                      0x000C
#define PROD_STMT_IF                                0x000D
#define PROD_STMT_FOR_LOOP                          0x000E
#define PROD_STMT_FOR_EACH                          0x000F
#define PROD_STMT_WHILE_LOOP                        0x0010
#define PROD_STMT_DO_WHILE                          0x0011
#define PROD_STMT_LET_BLOCK                         0x0012
#define PROD_STMT_TRY_BLOCK                         0x0013
#define PROD_STMT_CLASS                             0x0014
#define PROD_STMT_STATIC_A                          0x0015
#define PROD_STMT_STATIC_B                          0x0016
#define PROD_STMT_RETURN_A                          0x0017
#define PROD_STMT_RETURN_B                          0x0018
#define PROD_STMT_BREAK                             0x0019
#define PROD_STMT_CONTINUE                          0x001A
#define PROD_STMT_THROW                             0x001B
#define PROD_ASSIGNMENT_L_VALUE                     0x001C
#define PROD_SELF_ASSIGNMENT_L_VALUE_A              0x001D
#define PROD_SELF_ASSIGNMENT_L_VALUE_B              0x001E
#define PROD_SELF_ASSIGNMENT_L_VALUE_C              0x001F
#define PROD_SELF_ASSIGNMENT_L_VALUE_D              0x0020
#define PROD_SELF_ASSIGNMENT_L_VALUE_E              0x0021
#define PROD_SELF_ASSIGNMENT_L_VALUE_F              0x0022
#define PROD_FUNCTION_DEF_FUNC                      0x0023
#define PROD_FUNCTION_DECL_IDENTIFIER               0x0024
#define PROD_FUNCTION_DECL_STRING                   0x0025
#define PROD_CLASS_CLASS                            0x0026
#define PROD_PARAMETERS_A                           0x0027
#define PROD_PARAMETERS_B                           0x0028
#define PROD_PARAMETERS                             0x0029
#define PROD_PARAM_DECL_IDENTIFIER_A                0x002A
#define PROD_PARAM_DECL_IDENTIFIER_B                0x002B
#define PROD_IF_IF                                  0x002C
#define PROD_ELSEIF_ELSE_A                          0x002D
#define PROD_ELSEIF_ELSE_B                          0x002E
#define PROD_ELSEIF_ENDIF                           0x002F
#define PROD_FOR_LOOP_FOR                           0x0030
#define PROD_STEP_STEP                              0x0031
#define PROD_STEP_DO                                0x0032
#define PROD_FOR_EACH_FOR                           0x0033
#define PROD_WHILE_LOOP_WHILE                       0x0034
#define PROD_DO_WHILE_DO                            0x0035
#define PROD_LET_BLOCK_LET                          0x0036
#define PROD_BINDINGS_IDENTIFIER_A                  0x0037
#define PROD_BINDINGS_IDENTIFIER_B                  0x0038
#define PROD_TRY_BLOCK_TRY                          0x0039
#define PROD_CATCH_BLOCK_CATCH                      0x003A
#define PROD_CATCH_BLOCK_DONE                       0x003B
#define PROD_L_VALUE_IDENTIFIER                     0x003C
#define PROD_L_VALUE                                0x003D
#define PROD_L_VALUE_REFERENCE_A                    0x003E
#define PROD_L_VALUE_REFERENCE_B                    0x003F
#define PROD_EXPR_CONDITION                         0x0040
#define PROD_CONDITION_CONDITION_A                  0x0041
#define PROD_CONDITION_CONDITION_B                  0x0042
#define PROD_CONDITION_LOGIC                        0x0043
#define PROD_LOGIC_NOT                              0x0044
#define PROD_LOGIC_COMPARISON                       0x0045
#define PROD_COMPARISON_COMPARISON_A                0x0046
#define PROD_COMPARISON_COMPARISON_B                0x0047
#define PROD_COMPARISON_COMPARISON_C                0x0048
#define PROD_COMPARISON_COMPARISON_D                0x0049
#define PROD_COMPARISON_COMPARISON_E                0x004A
#define PROD_COMPARISON_COMPARISON_F                0x004B
#define PROD_COMPARISON_FINAL_A                     0x004C
#define PROD_COMPARISON_FINAL_B                     0x004D
#define PROD_COMPARISON_ARITHMETIC                  0x004E
#define PROD_ARITHMETIC_ARITHMETIC_A                0x004F
#define PROD_ARITHMETIC_ARITHMETIC_B                0x0050
#define PROD_ARITHMETIC_TERM                        0x0051
#define PROD_TERM_TERM_A                            0x0052
#define PROD_TERM_TERM_B                            0x0053
#define PROD_TERM_TERM_C                            0x0054
#define PROD_TERM_FACTOR                            0x0055
#define PROD_FACTOR_A                               0x0056
#define PROD_FACTOR_B                               0x0057
#define PROD_FACTOR_C                               0x0058
#define PROD_FACTOR_FINAL                           0x0059
#define PROD_FINAL                                  0x005A
#define PROD_FINAL_BOOLEAN                          0x005B
#define PROD_FINAL_OBJECT                           0x005C
#define PROD_FINAL_REFERENCE                        0x005D
#define PROD_FINAL_NEW                              0x005E
#define PROD_FINAL_INTEGER                          0x005F
#define PROD_FINAL_FLOAT                            0x0060
#define PROD_FINAL_STRING                           0x0061
#define PROD_REFERENCE_L_VALUE                      0x0062
#define PROD_REFERENCE_THIS                         0x0063
#define PROD_REFERENCE_REFERENCE_A                  0x0064
#define PROD_REFERENCE_REFERENCE_B                  0x0065
#define PROD_ARGUMENTS_ARGUMENTS                    0x0066
#define PROD_ARGUMENTS_EXPR                         0x0067
#define PROD_OBJECT_A                               0x0068
#define PROD_OBJECT_B                               0x0069
#define PROD_OBJECT_C                               0x006A
#define PROD_ARRAY_INIT_ARRAY_INIT                  0x006B
#define PROD_ARRAY_INIT_EXPR                        0x006C
#define PROD_DICTIONARY_INIT_DICTIONARY_INIT        0x006D
#define PROD_DICTIONARY_INIT_IDENTIFIER             0x006E
#define PROD_BOOLEAN_TRUE                           0x006F
#define PROD_BOOLEAN_FALSE                          0x0070


/* Grammar Symbols */
extern char GRAMMAR_SYMBOLS[420];

/* Grammar Tokens */
extern char GRAMMAR_TOKENS[302];


/* Context Free Grammar */
extern GRAMMAR_TABLE CONTEXT_FREE_GRAMMAR;


/* SLR GOTO table */
extern int GOTO_TABLE[9472];


/* SLR ACTION table */
extern ACTION ACTION_TABLE[17408];


/* SLR parse table struct */
extern LR_TABLE PARSE_TABLE;

#endif // _GENERATED_PARSER_H
