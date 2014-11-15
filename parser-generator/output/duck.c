/* auto-generated compiler stubs */
#include "lr_parser.h"
#include "output/duck.h"


/* production stubs */

/* 1. <program> -> <stmt list> */
int ReduceProgram(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 1;
    SYNTAX_TREE* stmt_list1 = node->children[0];

    int error = 0;
    error = error || CompileNode(stmt_list1);

    return error;
}

/* 2. <stmt list> -> <stmt> <stmt list> */
int ReduceStmtListA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 2;
    SYNTAX_TREE* stmt1 = node->children[0];
    SYNTAX_TREE* stmt_list1 = node->children[1];

    int error = 0;
    error = error || CompileNode(stmt1);
    error = error || CompileNode(stmt_list1);

    return error;
}

/* 3. <stmt list> -> */
int ReduceStmtListB(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 3;

    int error = 0;

    return error;
}

/* 4. <stmt> -> import <identifier> <endl> */
int ReduceStmtA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 4;
    SYNTAX_TREE* identifier1 = node->children[1];

    int error = 0;
    error = error || CompileNode(identifier1);

    return error;
}

/* 5. <stmt> -> call <reference> <endl> */
int ReduceStmtB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 5;
    SYNTAX_TREE* reference1 = node->children[1];

    int error = 0;
    error = error || CompileNode(reference1);

    return error;
}

/* 6. <stmt> -> <endl> */
int ReduceStmtC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 6;

    int error = 0;

    return error;
}

/* 7. <stmt> -> <expr> <endl> */
int ReduceStmtD(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 7;
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 8. <stmt> -> <assignment> <endl> */
int ReduceStmtE(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 8;
    SYNTAX_TREE* assignment1 = node->children[0];

    int error = 0;
    error = error || CompileNode(assignment1);

    return error;
}

/* 9. <stmt> -> <function def> <endl> */
int ReduceStmtF(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 9;
    SYNTAX_TREE* function_def1 = node->children[0];

    int error = 0;
    error = error || CompileNode(function_def1);

    return error;
}

/* 10. <stmt> -> <if> <endl> */
int ReduceStmtG(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 10;
    SYNTAX_TREE* if1 = node->children[0];

    int error = 0;
    error = error || CompileNode(if1);

    return error;
}

/* 11. <stmt> -> <if else> <endl> */
int ReduceStmtH(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 11;
    SYNTAX_TREE* if_else1 = node->children[0];

    int error = 0;
    error = error || CompileNode(if_else1);

    return error;
}

/* 12. <stmt> -> <for loop> <endl> */
int ReduceStmtI(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 12;
    SYNTAX_TREE* for_loop1 = node->children[0];

    int error = 0;
    error = error || CompileNode(for_loop1);

    return error;
}

/* 13. <stmt> -> <while loop> <endl> */
int ReduceStmtJ(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 13;
    SYNTAX_TREE* while_loop1 = node->children[0];

    int error = 0;
    error = error || CompileNode(while_loop1);

    return error;
}

/* 14. <stmt> -> return <expr> <endl> */
int ReduceStmtK(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 14;
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 15. <stmt> -> break <endl> */
int ReduceStmtL(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 15;

    int error = 0;

    return error;
}

/* 16. <stmt> -> continue <endl> */
int ReduceStmtM(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 16;

    int error = 0;

    return error;
}

/* 17. <function def> -> function <identifier> <parameters> <endl> <stmt list> end */
int ReduceFunctionDef(SYNTAX_TREE* node)
{
    if (node->numChildren != 6) return 17;
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* parameters1 = node->children[2];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(parameters1);
    error = error || CompileNode(stmt_list1);

    return error;
}

/* 18. <parameters> -> */
int ReduceParametersA(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 18;

    int error = 0;

    return error;
}

/* 19. <parameters> -> ( ) */
int ReduceParametersB(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 19;

    int error = 0;

    return error;
}

/* 20. <parameters> -> ( <param decl> ) */
int ReduceParametersC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 20;
    SYNTAX_TREE* param_decl1 = node->children[1];

    int error = 0;
    error = error || CompileNode(param_decl1);

    return error;
}

/* 21. <param decl> -> <identifier> */
int ReduceParamDeclA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 21;
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;
    error = error || CompileNode(identifier1);

    return error;
}

/* 22. <param decl> -> <param decl> , <identifier> */
int ReduceParamDeclB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 22;
    SYNTAX_TREE* param_decl1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];

    int error = 0;
    error = error || CompileNode(param_decl1);
    error = error || CompileNode(identifier1);

    return error;
}

/* 23. <if> -> if <condition> then <endl> <stmt list> end */
int ReduceIf(SYNTAX_TREE* node)
{
    if (node->numChildren != 6) return 23;
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;
    error = error || CompileNode(condition1);
    error = error || CompileNode(stmt_list1);

    return error;
}

/* 24. <if else> -> if <condition> then <endl> <stmt list> else <endl> <stmt list> end */
int ReduceIfElse(SYNTAX_TREE* node)
{
    if (node->numChildren != 9) return 24;
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];
    SYNTAX_TREE* stmt_list2 = node->children[7];

    int error = 0;
    error = error || CompileNode(condition1);
    error = error || CompileNode(stmt_list1);
    error = error || CompileNode(stmt_list2);

    return error;
}

/* 25. <for loop> -> for <identifier> = <arithmetic> to <arithmetic> do <endl> <stmt list> loop */
int ReduceForLoop(SYNTAX_TREE* node)
{
    if (node->numChildren != 10) return 25;
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* arithmetic1 = node->children[3];
    SYNTAX_TREE* arithmetic2 = node->children[5];
    SYNTAX_TREE* stmt_list1 = node->children[8];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(arithmetic1);
    error = error || CompileNode(arithmetic2);
    error = error || CompileNode(stmt_list1);

    return error;
}

/* 26. <while loop> -> while <condition> do <endl> <stmt list> loop */
int ReduceWhileLoop(SYNTAX_TREE* node)
{
    if (node->numChildren != 6) return 26;
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;
    error = error || CompileNode(condition1);
    error = error || CompileNode(stmt_list1);

    return error;
}

/* 27. <assignment> -> <l-value> = <assignment> */
int ReduceAssignmentA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 27;
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* assignment1 = node->children[2];

    int error = 0;
    error = error || CompileNode(l_value1);
    error = error || CompileNode(assignment1);

    return error;
}

/* 28. <assignment> -> <l-value> = <condition> */
int ReduceAssignmentB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 28;
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* condition1 = node->children[2];

    int error = 0;
    error = error || CompileNode(l_value1);
    error = error || CompileNode(condition1);

    return error;
}

/* 29. <l-value> -> <identifier> */
int ReduceLValueA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 29;
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;
    error = error || CompileNode(identifier1);

    return error;
}

/* 30. <l-value> -> ( <l-value> ) */
int ReduceLValueB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 30;
    SYNTAX_TREE* l_value1 = node->children[1];

    int error = 0;
    error = error || CompileNode(l_value1);

    return error;
}

/* 31. <l-value> -> <reference> . <identifier> */
int ReduceLValueC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 31;
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];

    int error = 0;
    error = error || CompileNode(reference1);
    error = error || CompileNode(identifier1);

    return error;
}

/* 32. <l-value> -> <reference> [ <expr> ] */
int ReduceLValueD(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 32;
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(reference1);
    error = error || CompileNode(expr1);

    return error;
}

/* 33. <expr> -> <condition> */
int ReduceExpr(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 33;
    SYNTAX_TREE* condition1 = node->children[0];

    int error = 0;
    error = error || CompileNode(condition1);

    return error;
}

/* 34. <condition> -> <condition> and <logic> */
int ReduceConditionA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 34;
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(condition1);
    error = error || CompileNode(logic1);

    return error;
}

/* 35. <condition> -> <condition> or <logic> */
int ReduceConditionB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 35;
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(condition1);
    error = error || CompileNode(logic1);

    return error;
}

/* 36. <condition> -> <condition> nor <logic> */
int ReduceConditionC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 36;
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(condition1);
    error = error || CompileNode(logic1);

    return error;
}

/* 37. <condition> -> <condition> xor <logic> */
int ReduceConditionD(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 37;
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(condition1);
    error = error || CompileNode(logic1);

    return error;
}

/* 38. <condition> -> <logic> */
int ReduceConditionE(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 38;
    SYNTAX_TREE* logic1 = node->children[0];

    int error = 0;
    error = error || CompileNode(logic1);

    return error;
}

/* 39. <logic> -> not <comparison> */
int ReduceLogicA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 39;
    SYNTAX_TREE* comparison1 = node->children[1];

    int error = 0;
    error = error || CompileNode(comparison1);

    return error;
}

/* 40. <logic> -> <comparison> */
int ReduceLogicB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 40;
    SYNTAX_TREE* comparison1 = node->children[0];

    int error = 0;
    error = error || CompileNode(comparison1);

    return error;
}

/* 41. <comparison> -> <comparison> == <arithmetic> */
int ReduceComparisonA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 41;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(comparison1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 42. <comparison> -> <comparison> != <arithmetic> */
int ReduceComparisonB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 42;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(comparison1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 43. <comparison> -> <comparison> < <arithmetic> */
int ReduceComparisonC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 43;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(comparison1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 44. <comparison> -> <comparison> > <arithmetic> */
int ReduceComparisonD(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 44;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(comparison1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 45. <comparison> -> <comparison> <= <arithmetic> */
int ReduceComparisonE(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 45;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(comparison1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 46. <comparison> -> <comparison> >= <arithmetic> */
int ReduceComparisonF(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 46;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(comparison1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 47. <comparison> -> <arithmetic> */
int ReduceComparisonG(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 47;
    SYNTAX_TREE* arithmetic1 = node->children[0];

    int error = 0;
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 48. <arithmetic> -> <arithmetic> + <term> */
int ReduceArithmeticA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 48;
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = error || CompileNode(arithmetic1);
    error = error || CompileNode(term1);

    return error;
}

/* 49. <arithmetic> -> <arithmetic> - <term> */
int ReduceArithmeticB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 49;
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = error || CompileNode(arithmetic1);
    error = error || CompileNode(term1);

    return error;
}

/* 50. <arithmetic> -> <arithmetic> & <term> */
int ReduceArithmeticC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 50;
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = error || CompileNode(arithmetic1);
    error = error || CompileNode(term1);

    return error;
}

/* 51. <arithmetic> -> <arithmetic> | <term> */
int ReduceArithmeticD(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 51;
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = error || CompileNode(arithmetic1);
    error = error || CompileNode(term1);

    return error;
}

/* 52. <arithmetic> -> <term> */
int ReduceArithmeticE(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 52;
    SYNTAX_TREE* term1 = node->children[0];

    int error = 0;
    error = error || CompileNode(term1);

    return error;
}

/* 53. <term> -> <term> * <factor> */
int ReduceTermA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 53;
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    int error = 0;
    error = error || CompileNode(term1);
    error = error || CompileNode(factor1);

    return error;
}

/* 54. <term> -> <term> / <factor> */
int ReduceTermB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 54;
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    int error = 0;
    error = error || CompileNode(term1);
    error = error || CompileNode(factor1);

    return error;
}

/* 55. <term> -> <factor> */
int ReduceTermC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 55;
    SYNTAX_TREE* factor1 = node->children[0];

    int error = 0;
    error = error || CompileNode(factor1);

    return error;
}

/* 56. <factor> -> - <factor> */
int ReduceFactorA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 56;
    SYNTAX_TREE* factor1 = node->children[1];

    int error = 0;
    error = error || CompileNode(factor1);

    return error;
}

/* 57. <factor> -> ! <factor> */
int ReduceFactorB(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 57;
    SYNTAX_TREE* factor1 = node->children[1];

    int error = 0;
    error = error || CompileNode(factor1);

    return error;
}

/* 58. <factor> -> <final> */
int ReduceFactorC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 58;
    SYNTAX_TREE* final1 = node->children[0];

    int error = 0;
    error = error || CompileNode(final1);

    return error;
}

/* 59. <final> -> ( <expr> ) */
int ReduceFinalA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 59;
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 60. <final> -> <boolean> */
int ReduceFinalB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 60;
    SYNTAX_TREE* boolean1 = node->children[0];

    int error = 0;
    error = error || CompileNode(boolean1);

    return error;
}

/* 61. <final> -> <integer> */
int ReduceFinalC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 61;
    SYNTAX_TREE* integer1 = node->children[0];

    int error = 0;
    error = error || CompileNode(integer1);

    return error;
}

/* 62. <final> -> <float> */
int ReduceFinalD(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 62;
    SYNTAX_TREE* float1 = node->children[0];

    int error = 0;
    error = error || CompileNode(float1);

    return error;
}

/* 63. <final> -> <string> */
int ReduceFinalE(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 63;
    SYNTAX_TREE* string1 = node->children[0];

    int error = 0;
    error = error || CompileNode(string1);

    return error;
}

/* 64. <final> -> <object> */
int ReduceFinalF(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 64;
    SYNTAX_TREE* object1 = node->children[0];

    int error = 0;
    error = error || CompileNode(object1);

    return error;
}

/* 65. <final> -> <reference> */
int ReduceFinalG(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 65;
    SYNTAX_TREE* reference1 = node->children[0];

    int error = 0;
    error = error || CompileNode(reference1);

    return error;
}

/* 66. <reference> -> <l-value> */
int ReduceReferenceA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 66;
    SYNTAX_TREE* l_value1 = node->children[0];

    int error = 0;
    error = error || CompileNode(l_value1);

    return error;
}

/* 67. <reference> -> <reference> ( ) */
int ReduceReferenceB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 67;
    SYNTAX_TREE* reference1 = node->children[0];

    int error = 0;
    error = error || CompileNode(reference1);

    return error;
}

/* 68. <reference> -> <reference> ( <arguments> ) */
int ReduceReferenceC(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 68;
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* arguments1 = node->children[2];

    int error = 0;
    error = error || CompileNode(reference1);
    error = error || CompileNode(arguments1);

    return error;
}

/* 69. <arguments> -> <arguments> , <expr> */
int ReduceArgumentsA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 69;
    SYNTAX_TREE* arguments1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(arguments1);
    error = error || CompileNode(expr1);

    return error;
}

/* 70. <arguments> -> <expr> */
int ReduceArgumentsB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 70;
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 71. <object> -> [ ] */
int ReduceObjectA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 71;

    int error = 0;

    return error;
}

/* 72. <object> -> [ <array init> ] */
int ReduceObjectB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 72;
    SYNTAX_TREE* array_init1 = node->children[1];

    int error = 0;
    error = error || CompileNode(array_init1);

    return error;
}

/* 73. <object> -> [ <dictionary init> ] */
int ReduceObjectC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 73;
    SYNTAX_TREE* dictionary_init1 = node->children[1];

    int error = 0;
    error = error || CompileNode(dictionary_init1);

    return error;
}

/* 74. <array init> -> <array init> , <expr> */
int ReduceArrayInitA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 74;
    SYNTAX_TREE* array_init1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(array_init1);
    error = error || CompileNode(expr1);

    return error;
}

/* 75. <array init> -> <expr> */
int ReduceArrayInitB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 75;
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 76. <dictionary init> -> <dictionary init> , <identifier> : <expr> */
int ReduceDictionaryInitA(SYNTAX_TREE* node)
{
    if (node->numChildren != 5) return 76;
    SYNTAX_TREE* dictionary_init1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];
    SYNTAX_TREE* expr1 = node->children[4];

    int error = 0;
    error = error || CompileNode(dictionary_init1);
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 77. <dictionary init> -> <identifier> : <expr> */
int ReduceDictionaryInitB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 77;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 78. <boolean> -> true */
int ReduceBooleanA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 78;

    int error = 0;

    return error;
}

/* 79. <boolean> -> false */
int ReduceBooleanB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 79;

    int error = 0;

    return error;
}

/* reduce one node */
int CompileNode(SYNTAX_TREE* node)
{
    if (node == NULL || node->production == 0)
        return 1;

    switch (node->production)
    {
        case 0x01: return ReduceProgram(node);
        case 0x02: return ReduceStmtListA(node);
        case 0x03: return ReduceStmtListB(node);
        case 0x04: return ReduceStmtA(node);
        case 0x05: return ReduceStmtB(node);
        case 0x06: return ReduceStmtC(node);
        case 0x07: return ReduceStmtD(node);
        case 0x08: return ReduceStmtE(node);
        case 0x09: return ReduceStmtF(node);
        case 0x0A: return ReduceStmtG(node);
        case 0x0B: return ReduceStmtH(node);
        case 0x0C: return ReduceStmtI(node);
        case 0x0D: return ReduceStmtJ(node);
        case 0x0E: return ReduceStmtK(node);
        case 0x0F: return ReduceStmtL(node);
        case 0x10: return ReduceStmtM(node);
        case 0x11: return ReduceFunctionDef(node);
        case 0x12: return ReduceParametersA(node);
        case 0x13: return ReduceParametersB(node);
        case 0x14: return ReduceParametersC(node);
        case 0x15: return ReduceParamDeclA(node);
        case 0x16: return ReduceParamDeclB(node);
        case 0x17: return ReduceIf(node);
        case 0x18: return ReduceIfElse(node);
        case 0x19: return ReduceForLoop(node);
        case 0x1A: return ReduceWhileLoop(node);
        case 0x1B: return ReduceAssignmentA(node);
        case 0x1C: return ReduceAssignmentB(node);
        case 0x1D: return ReduceLValueA(node);
        case 0x1E: return ReduceLValueB(node);
        case 0x1F: return ReduceLValueC(node);
        case 0x20: return ReduceLValueD(node);
        case 0x21: return ReduceExpr(node);
        case 0x22: return ReduceConditionA(node);
        case 0x23: return ReduceConditionB(node);
        case 0x24: return ReduceConditionC(node);
        case 0x25: return ReduceConditionD(node);
        case 0x26: return ReduceConditionE(node);
        case 0x27: return ReduceLogicA(node);
        case 0x28: return ReduceLogicB(node);
        case 0x29: return ReduceComparisonA(node);
        case 0x2A: return ReduceComparisonB(node);
        case 0x2B: return ReduceComparisonC(node);
        case 0x2C: return ReduceComparisonD(node);
        case 0x2D: return ReduceComparisonE(node);
        case 0x2E: return ReduceComparisonF(node);
        case 0x2F: return ReduceComparisonG(node);
        case 0x30: return ReduceArithmeticA(node);
        case 0x31: return ReduceArithmeticB(node);
        case 0x32: return ReduceArithmeticC(node);
        case 0x33: return ReduceArithmeticD(node);
        case 0x34: return ReduceArithmeticE(node);
        case 0x35: return ReduceTermA(node);
        case 0x36: return ReduceTermB(node);
        case 0x37: return ReduceTermC(node);
        case 0x38: return ReduceFactorA(node);
        case 0x39: return ReduceFactorB(node);
        case 0x3A: return ReduceFactorC(node);
        case 0x3B: return ReduceFinalA(node);
        case 0x3C: return ReduceFinalB(node);
        case 0x3D: return ReduceFinalC(node);
        case 0x3E: return ReduceFinalD(node);
        case 0x3F: return ReduceFinalE(node);
        case 0x40: return ReduceFinalF(node);
        case 0x41: return ReduceFinalG(node);
        case 0x42: return ReduceReferenceA(node);
        case 0x43: return ReduceReferenceB(node);
        case 0x44: return ReduceReferenceC(node);
        case 0x45: return ReduceArgumentsA(node);
        case 0x46: return ReduceArgumentsB(node);
        case 0x47: return ReduceObjectA(node);
        case 0x48: return ReduceObjectB(node);
        case 0x49: return ReduceObjectC(node);
        case 0x4A: return ReduceArrayInitA(node);
        case 0x4B: return ReduceArrayInitB(node);
        case 0x4C: return ReduceDictionaryInitA(node);
        case 0x4D: return ReduceDictionaryInitB(node);
        case 0x4E: return ReduceBooleanA(node);
        case 0x4F: return ReduceBooleanB(node);
    default:
        printf("Unknown production %i.\n", node->production);
        return 1;
    }
}
