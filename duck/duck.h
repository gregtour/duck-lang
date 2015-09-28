/* auto-generated lr parse tables */
#ifndef _DUCK_H
#define _DUCK_H

#include "lr_parser.h"


/* main function */
int InterpretNode(SYNTAX_TREE* node);
void PrintNode(SYNTAX_TREE* node);

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
#define SYMBOL_REFERENCE                  0x1011
#define SYMBOL_L_VALUE                    0x1012
#define SYMBOL_CONDITION                  0x1013
#define SYMBOL_ARITHMETIC                 0x1014
#define SYMBOL_FUNCTION_DECL              0x1015
#define SYMBOL_PARAMETERS                 0x1016
#define SYMBOL_OPT_EXTENDS                0x1017
#define SYMBOL_PARAM_DECL                 0x1018
#define SYMBOL_ELSEIF                     0x1019
#define SYMBOL_STEP                       0x101A
#define SYMBOL_BINDINGS                   0x101B
#define SYMBOL_CATCH_BLOCK                0x101C
#define SYMBOL_LOGIC                      0x101D
#define SYMBOL_COMPARISON                 0x101E
#define SYMBOL_FINAL                      0x101F
#define SYMBOL_TERM                       0x1020
#define SYMBOL_FACTOR                     0x1021
#define SYMBOL_BOOLEAN                    0x1022
#define SYMBOL_OBJECT                     0x1023
#define SYMBOL_ARGUMENTS                  0x1024
#define SYMBOL_ARRAY_BEGIN                0x1025
#define SYMBOL_OBJECT_ARRAY               0x1026
#define SYMBOL_DICTIONARY_BEGIN           0x1027
#define SYMBOL_OBJECT_DICTIONARY          0x1028


/* production constants */
#define PROD_PROGRAM_STMTLIST                       0x0001
#define PROD_STMTLIST_STMT                          0x0002
#define PROD_STMTLIST                               0x0003
#define PROD_IDENTIFIER_LIST_IDENTIFIER_A           0x0004
#define PROD_IDENTIFIER_LIST_IDENTIFIER_B           0x0005
#define PROD_STMT_IMPORT                            0x0006
#define PROD_STMT_REQUIRE                           0x0007
#define PROD_STMT_INCLUDE                           0x0008
#define PROD_STMT_EXPR                              0x0009
#define PROD_STMT_ENDL                              0x000A
#define PROD_STMT_GLOBAL_A                          0x000B
#define PROD_STMT_LOCAL_A                           0x000C
#define PROD_STMT_ASSIGNMENT                        0x000D
#define PROD_STMT_GLOBAL_B                          0x000E
#define PROD_STMT_LOCAL_B                           0x000F
#define PROD_STMT_STATIC_A                          0x0010
#define PROD_STMT_SELF_ASSIGNMENT                   0x0011
#define PROD_STMT_FUNCTION_DEF                      0x0012
#define PROD_STMT_GLOBAL_C                          0x0013
#define PROD_STMT_LOCAL_C                           0x0014
#define PROD_STMT_STATIC_B                          0x0015
#define PROD_STMT_IF                                0x0016
#define PROD_STMT_FOR_LOOP                          0x0017
#define PROD_STMT_FOR_EACH                          0x0018
#define PROD_STMT_WHILE_LOOP                        0x0019
#define PROD_STMT_DO_WHILE                          0x001A
#define PROD_STMT_LET_BLOCK                         0x001B
#define PROD_STMT_TRY_BLOCK                         0x001C
#define PROD_STMT_CLASS                             0x001D
#define PROD_STMT_RETURN_A                          0x001E
#define PROD_STMT_RETURN_B                          0x001F
#define PROD_STMT_BREAK                             0x0020
#define PROD_STMT_CONTINUE                          0x0021
#define PROD_STMT_THROW                             0x0022
#define PROD_STMT_CALL                              0x0023
#define PROD_ASSIGNMENT_L_VALUE                     0x0024
#define PROD_SELF_ASSIGNMENT_L_VALUE_A              0x0025
#define PROD_SELF_ASSIGNMENT_L_VALUE_B              0x0026
#define PROD_SELF_ASSIGNMENT_L_VALUE_C              0x0027
#define PROD_SELF_ASSIGNMENT_L_VALUE_D              0x0028
#define PROD_SELF_ASSIGNMENT_L_VALUE_E              0x0029
#define PROD_SELF_ASSIGNMENT_L_VALUE_F              0x002A
#define PROD_FUNCTION_DEF_FUNC                      0x002B
#define PROD_FUNCTION_DECL_IDENTIFIER               0x002C
#define PROD_FUNCTION_DECL_STRING                   0x002D
#define PROD_CLASS_CLASS                            0x002E
#define PROD_PARAMETERS_A                           0x002F
#define PROD_PARAMETERS_B                           0x0030
#define PROD_PARAMETERS                             0x0031
#define PROD_PARAM_DECL_IDENTIFIER_A                0x0032
#define PROD_PARAM_DECL_IDENTIFIER_B                0x0033
#define PROD_OPT_EXTENDS                            0x0034
#define PROD_OPT_EXTENDS_                           0x0035
#define PROD_IF_IF                                  0x0036
#define PROD_ELSEIF_ELSE_A                          0x0037
#define PROD_ELSEIF_ELSE_B                          0x0038
#define PROD_ELSEIF_ENDIF                           0x0039
#define PROD_FOR_LOOP_FOR                           0x003A
#define PROD_STEP_STEP                              0x003B
#define PROD_STEP_DO                                0x003C
#define PROD_FOR_EACH_FOR                           0x003D
#define PROD_WHILE_LOOP_WHILE                       0x003E
#define PROD_DO_WHILE_DO                            0x003F
#define PROD_LET_BLOCK_LET                          0x0040
#define PROD_BINDINGS_IDENTIFIER_A                  0x0041
#define PROD_BINDINGS_IDENTIFIER_B                  0x0042
#define PROD_BINDINGS_IDENTIFIER_C                  0x0043
#define PROD_BINDINGS_IDENTIFIER_D                  0x0044
#define PROD_TRY_BLOCK_TRY                          0x0045
#define PROD_CATCH_BLOCK_CATCH                      0x0046
#define PROD_CATCH_BLOCK_DONE                       0x0047
#define PROD_L_VALUE_IDENTIFIER                     0x0048
#define PROD_L_VALUE                                0x0049
#define PROD_L_VALUE_REFERENCE_A                    0x004A
#define PROD_L_VALUE_REFERENCE_B                    0x004B
#define PROD_EXPR_CONDITION                         0x004C
#define PROD_CONDITION_CONDITION_A                  0x004D
#define PROD_CONDITION_CONDITION_B                  0x004E
#define PROD_CONDITION_LOGIC                        0x004F
#define PROD_LOGIC_NOT                              0x0050
#define PROD_LOGIC_COMPARISON                       0x0051
#define PROD_COMPARISON_COMPARISON_A                0x0052
#define PROD_COMPARISON_COMPARISON_B                0x0053
#define PROD_COMPARISON_COMPARISON_C                0x0054
#define PROD_COMPARISON_COMPARISON_D                0x0055
#define PROD_COMPARISON_COMPARISON_E                0x0056
#define PROD_COMPARISON_COMPARISON_F                0x0057
#define PROD_COMPARISON_FINAL_A                     0x0058
#define PROD_COMPARISON_FINAL_B                     0x0059
#define PROD_COMPARISON_ARITHMETIC                  0x005A
#define PROD_ARITHMETIC_ARITHMETIC_A                0x005B
#define PROD_ARITHMETIC_ARITHMETIC_B                0x005C
#define PROD_ARITHMETIC_TERM                        0x005D
#define PROD_TERM_TERM_A                            0x005E
#define PROD_TERM_TERM_B                            0x005F
#define PROD_TERM_TERM_C                            0x0060
#define PROD_TERM_FACTOR                            0x0061
#define PROD_FACTOR_A                               0x0062
#define PROD_FACTOR_B                               0x0063
#define PROD_FACTOR_C                               0x0064
#define PROD_FACTOR_D                               0x0065
#define PROD_FACTOR_FINAL                           0x0066
#define PROD_FINAL                                  0x0067
#define PROD_FINAL_BOOLEAN                          0x0068
#define PROD_FINAL_OBJECT                           0x0069
#define PROD_FINAL_REFERENCE                        0x006A
#define PROD_FINAL_NEW                              0x006B
#define PROD_FINAL_INTEGER                          0x006C
#define PROD_FINAL_FLOAT                            0x006D
#define PROD_FINAL_STRING                           0x006E
#define PROD_REFERENCE_L_VALUE                      0x006F
#define PROD_REFERENCE_THIS                         0x0070
#define PROD_REFERENCE_REFERENCE_A                  0x0071
#define PROD_REFERENCE_REFERENCE_B                  0x0072
#define PROD_ARGUMENTS_ARGUMENTS                    0x0073
#define PROD_ARGUMENTS_EXPR                         0x0074
#define PROD_OBJECT_A                               0x0075
#define PROD_OBJECT_ENDL_A                          0x0076
#define PROD_OBJECT_B                               0x0077
#define PROD_ARRAY_BEGIN_ENDL                       0x0078
#define PROD_ARRAY_BEGIN_EXPR                       0x0079
#define PROD_OBJECT_ARRAY_A                         0x007A
#define PROD_OBJECT_ARRAY_B                         0x007B
#define PROD_OBJECT_ARRAY_ENDL                      0x007C
#define PROD_OBJECT_ARRAY_C                         0x007D
#define PROD_OBJECT_ENDL_B                          0x007E
#define PROD_OBJECT_C                               0x007F
#define PROD_DICTIONARY_BEGIN_ENDL                  0x0080
#define PROD_DICTIONARY_BEGIN_IDENTIFIER            0x0081
#define PROD_OBJECT_DICTIONARY_A                    0x0082
#define PROD_OBJECT_DICTIONARY_B                    0x0083
#define PROD_OBJECT_DICTIONARY_ENDL                 0x0084
#define PROD_OBJECT_DICTIONARY_C                    0x0085
#define PROD_BOOLEAN_TRUE                           0x0086
#define PROD_BOOLEAN_FALSE                          0x0087


/* Grammar Symbols */
extern char GRAMMAR_SYMBOLS[471];

/* Grammar Tokens */
extern char GRAMMAR_TOKENS[329];


/* Context Free Grammar */
extern GRAMMAR_TABLE CONTEXT_FREE_GRAMMAR;


/* SLR GOTO table */
extern int COMPRESSED_GOTO_TABLE[1653];


/* SLR ACTION table */
extern int COMPRESSED_ACTION_TABLE[15896];

/* SLR parse table struct */
extern LR_TABLE PARSE_TABLE;

#endif // _DUCK_H
