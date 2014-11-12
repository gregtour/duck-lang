/* auto-generated compiler stubs */
#include "lr_parser.h"
#include "test/C_parser.h"


/* production stubs */

/* 1. <program> -> <def list> */
int ReduceProgram(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 1;
    SYNTAX_TREE* def_list1 = node->children[0];

    int error = 0;
    error = error || CompileNode(def_list1);

    return error;
}

/* 2. <def list> -> <def> <def list> */
int ReduceDefListA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 2;
    SYNTAX_TREE* def1 = node->children[0];
    SYNTAX_TREE* def_list1 = node->children[1];

    int error = 0;
    error = error || CompileNode(def1);
    error = error || CompileNode(def_list1);

    return error;
}

/* 3. <def list> -> */
int ReduceDefListB(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 3;

    int error = 0;

    return error;
}

/* 4. <def> -> typedef <type> <identifier> ; */
int ReduceDefA(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 4;
    SYNTAX_TREE* type1 = node->children[1];
    SYNTAX_TREE* identifier1 = node->children[2];

    int error = 0;
    error = error || CompileNode(type1);
    error = error || CompileNode(identifier1);

    return error;
}

/* 5. <type> -> int */
int ReduceTypeA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 5;

    int error = 0;

    return error;
}

/* 6. <type> -> char */
int ReduceTypeB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 6;

    int error = 0;

    return error;
}

/* 7. <type> -> void */
int ReduceTypeC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 7;

    int error = 0;

    return error;
}

/* 8. <type> -> size_t */
int ReduceTypeD(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 8;

    int error = 0;

    return error;
}

/* 9. <type> -> long */
int ReduceTypeE(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 9;

    int error = 0;

    return error;
}

/* 10. <type> -> const <type> */
int ReduceTypeF(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 10;
    SYNTAX_TREE* type1 = node->children[1];

    int error = 0;
    error = error || CompileNode(type1);

    return error;
}

/* 11. <type> -> unsigned <type> */
int ReduceTypeG(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 11;
    SYNTAX_TREE* type1 = node->children[1];

    int error = 0;
    error = error || CompileNode(type1);

    return error;
}

/* 12. <type> -> struct { <struct> } */
int ReduceTypeH(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 12;
    SYNTAX_TREE* struct1 = node->children[2];

    int error = 0;
    error = error || CompileNode(struct1);

    return error;
}

/* 13. <type> -> <type> * */
int ReduceTypeI(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 13;
    SYNTAX_TREE* type1 = node->children[0];

    int error = 0;
    error = error || CompileNode(type1);

    return error;
}

/* 14. <type> -> <identifier> */
int ReduceTypeJ(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 14;
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;
    error = error || CompileNode(identifier1);

    return error;
}

/* 15. <type> -> <type> [] */
int ReduceTypeK(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 15;
    SYNTAX_TREE* type1 = node->children[0];

    int error = 0;
    error = error || CompileNode(type1);

    return error;
}

/* 16. <struct> -> <type> <identifier> ; <struct> */
int ReduceStructA(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 16;
    SYNTAX_TREE* type1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* struct1 = node->children[3];

    int error = 0;
    error = error || CompileNode(type1);
    error = error || CompileNode(identifier1);
    error = error || CompileNode(struct1);

    return error;
}

/* 17. <struct> -> */
int ReduceStructB(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 17;

    int error = 0;

    return error;
}

/* 18. <def> -> <type> <identifier> ; */
int ReduceDefB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 18;
    SYNTAX_TREE* type1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[1];

    int error = 0;
    error = error || CompileNode(type1);
    error = error || CompileNode(identifier1);

    return error;
}

/* 19. <def> -> <type> <identifier> = <expr> ; */
int ReduceDefC(SYNTAX_TREE* node)
{
    if (node->numChildren != 5) return 19;
    SYNTAX_TREE* type1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* expr1 = node->children[3];

    int error = 0;
    error = error || CompileNode(type1);
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 20. <def> -> <type> <identifier> ( <param list> ) ; */
int ReduceDefD(SYNTAX_TREE* node)
{
    if (node->numChildren != 6) return 20;
    SYNTAX_TREE* type1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* param_list1 = node->children[3];

    int error = 0;
    error = error || CompileNode(type1);
    error = error || CompileNode(identifier1);
    error = error || CompileNode(param_list1);

    return error;
}

/* 21. <def> -> <type> <identifier> ( <param list> ) { <function body> } */
int ReduceDefE(SYNTAX_TREE* node)
{
    if (node->numChildren != 8) return 21;
    SYNTAX_TREE* type1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* param_list1 = node->children[3];
    SYNTAX_TREE* function_body1 = node->children[6];

    int error = 0;
    error = error || CompileNode(type1);
    error = error || CompileNode(identifier1);
    error = error || CompileNode(param_list1);
    error = error || CompileNode(function_body1);

    return error;
}

/* 22. <param list> -> */
int ReduceParamListA(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 22;

    int error = 0;

    return error;
}

/* 23. <param list> -> <param> */
int ReduceParamListB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 23;
    SYNTAX_TREE* param1 = node->children[0];

    int error = 0;
    error = error || CompileNode(param1);

    return error;
}

/* 24. <param list> -> <param> , <param list> */
int ReduceParamListC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 24;
    SYNTAX_TREE* param1 = node->children[0];
    SYNTAX_TREE* param_list1 = node->children[2];

    int error = 0;
    error = error || CompileNode(param1);
    error = error || CompileNode(param_list1);

    return error;
}

/* 25. <param> -> <type> <identifier> */
int ReduceParam(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 25;
    SYNTAX_TREE* type1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[1];

    int error = 0;
    error = error || CompileNode(type1);
    error = error || CompileNode(identifier1);

    return error;
}

/* 26. <function body> -> */
int ReduceFunctionBodyA(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 26;

    int error = 0;

    return error;
}

/* 27. <function body> -> <stmt> <function body> */
int ReduceFunctionBodyB(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 27;
    SYNTAX_TREE* stmt1 = node->children[0];
    SYNTAX_TREE* function_body1 = node->children[1];

    int error = 0;
    error = error || CompileNode(stmt1);
    error = error || CompileNode(function_body1);

    return error;
}

/* 28. <stmt> -> <type> <identifier> ; */
int ReduceStmtA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 28;
    SYNTAX_TREE* type1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[1];

    int error = 0;
    error = error || CompileNode(type1);
    error = error || CompileNode(identifier1);

    return error;
}

/* 29. <stmt> -> <type> <identifier> = <expr> ; */
int ReduceStmtB(SYNTAX_TREE* node)
{
    if (node->numChildren != 5) return 29;
    SYNTAX_TREE* type1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* expr1 = node->children[3];

    int error = 0;
    error = error || CompileNode(type1);
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 30. <stmt> -> for ( <expr> ; <expr> ; <expr> ) <loop body> */
int ReduceStmtC(SYNTAX_TREE* node)
{
    if (node->numChildren != 9) return 30;
    SYNTAX_TREE* expr1 = node->children[2];
    SYNTAX_TREE* expr2 = node->children[4];
    SYNTAX_TREE* expr3 = node->children[6];
    SYNTAX_TREE* loop_body1 = node->children[8];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);
    error = error || CompileNode(expr3);
    error = error || CompileNode(loop_body1);

    return error;
}

/* 31. <stmt> -> while ( <expr> ) <loop body> */
int ReduceStmtD(SYNTAX_TREE* node)
{
    if (node->numChildren != 5) return 31;
    SYNTAX_TREE* expr1 = node->children[2];
    SYNTAX_TREE* loop_body1 = node->children[4];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(loop_body1);

    return error;
}

/* 32. <stmt> -> if ( <expr> ) <stmt> */
int ReduceStmtE(SYNTAX_TREE* node)
{
    if (node->numChildren != 5) return 32;
    SYNTAX_TREE* expr1 = node->children[2];
    SYNTAX_TREE* stmt1 = node->children[4];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(stmt1);

    return error;
}

/* 33. <stmt> -> if ( <expr> ) <stmt> else <stmt> */
int ReduceStmtF(SYNTAX_TREE* node)
{
    if (node->numChildren != 7) return 33;
    SYNTAX_TREE* expr1 = node->children[2];
    SYNTAX_TREE* stmt1 = node->children[4];
    SYNTAX_TREE* stmt2 = node->children[6];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(stmt1);
    error = error || CompileNode(stmt2);

    return error;
}

/* 34. <stmt> -> return ; */
int ReduceStmtG(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 34;

    int error = 0;

    return error;
}

/* 35. <stmt> -> return <expr> ; */
int ReduceStmtH(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 35;
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 36. <stmt> -> break ; */
int ReduceStmtI(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 36;

    int error = 0;

    return error;
}

/* 37. <stmt> -> continue ; */
int ReduceStmtJ(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 37;

    int error = 0;

    return error;
}

/* 38. <stmt> -> <expr> ; */
int ReduceStmtK(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 38;
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 39. <stmt> -> { <block stmt> } */
int ReduceStmtL(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 39;
    SYNTAX_TREE* block_stmt1 = node->children[1];

    int error = 0;
    error = error || CompileNode(block_stmt1);

    return error;
}

/* 40. <loop body> -> <stmt> */
int ReduceLoopBodyA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 40;
    SYNTAX_TREE* stmt1 = node->children[0];

    int error = 0;
    error = error || CompileNode(stmt1);

    return error;
}

/* 41. <loop body> -> { <block stmt> } */
int ReduceLoopBodyB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 41;
    SYNTAX_TREE* block_stmt1 = node->children[1];

    int error = 0;
    error = error || CompileNode(block_stmt1);

    return error;
}

/* 42. <block stmt> -> */
int ReduceBlockStmtA(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 42;

    int error = 0;

    return error;
}

/* 43. <block stmt> -> <stmt> <block stmt> */
int ReduceBlockStmtB(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 43;
    SYNTAX_TREE* stmt1 = node->children[0];
    SYNTAX_TREE* block_stmt1 = node->children[1];

    int error = 0;
    error = error || CompileNode(stmt1);
    error = error || CompileNode(block_stmt1);

    return error;
}

/* 44. <expr> -> <identifier> = <expr> */
int ReduceExprA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 44;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 45. <expr> -> <identifier> += <expr> */
int ReduceExprB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 45;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 46. <expr> -> <identifier> */
int ReduceExprC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 46;
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;
    error = error || CompileNode(identifier1);

    return error;
}

/* 47. <expr> -> <integer> */
int ReduceExprD(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 47;
    SYNTAX_TREE* integer1 = node->children[0];

    int error = 0;
    error = error || CompileNode(integer1);

    return error;
}

/* 48. <expr> -> <float> f */
int ReduceExprE(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 48;

    int error = 0;

    return error;
}

/* 49. <expr> -> <string> */
int ReduceExprF(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 49;
    SYNTAX_TREE* string1 = node->children[0];

    int error = 0;
    error = error || CompileNode(string1);

    return error;
}

/* 50. <expr> -> <boolean> */
int ReduceExprG(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 50;
    SYNTAX_TREE* boolean1 = node->children[0];

    int error = 0;
    error = error || CompileNode(boolean1);

    return error;
}

/* 51. <boolean> -> true */
int ReduceBooleanA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 51;

    int error = 0;

    return error;
}

/* 52. <boolean> -> false */
int ReduceBooleanB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 52;

    int error = 0;

    return error;
}

/* 53. <expr> -> <expr> . <identifier> */
int ReduceExprH(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 53;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(identifier1);

    return error;
}

/* 54. <expr> -> <expr> -> <identifier> */
int ReduceExprI(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 54;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(identifier1);

    return error;
}

/* 55. <expr> -> ( <expr> ) */
int ReduceExprJ(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 55;
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 56. <expr> -> & <expr> */
int ReduceExprK(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 56;
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 57. <expr> -> * <expr> */
int ReduceExprL(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 57;
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 58. <expr> -> ( <type> ) <expr> */
int ReduceExprM(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 58;
    SYNTAX_TREE* type1 = node->children[1];
    SYNTAX_TREE* expr1 = node->children[3];

    int error = 0;
    error = error || CompileNode(type1);
    error = error || CompileNode(expr1);

    return error;
}

/* 59. <expr> -> <expr> [ <expr> ] */
int ReduceExprN(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 59;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 60. <expr> -> <expr> + <expr> */
int ReduceExprO(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 60;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 61. <expr> -> <expr> - <expr> */
int ReduceExprP(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 61;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 62. <expr> -> <expr> * <expr> */
int ReduceExprQ(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 62;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 63. <expr> -> <expr> / <expr> */
int ReduceExprR(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 63;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 64. <expr> -> <expr> % <expr> */
int ReduceExprS(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 64;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 65. <expr> -> <expr> & <expr> */
int ReduceExprT(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 65;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 66. <expr> -> <expr> | <expr> */
int ReduceExprU(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 66;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 67. <expr> -> <expr> ^ <expr> */
int ReduceExprV(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 67;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 68. <expr> -> <expr> && <expr> */
int ReduceExprW(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 68;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 69. <expr> -> <expr> || <expr> */
int ReduceExprX(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 69;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 70. <expr> -> <identifier> ++ */
int ReduceExprY(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 70;
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;
    error = error || CompileNode(identifier1);

    return error;
}

/* 71. <expr> -> <identifer> -- */
int ReduceExprZ(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 71;
    SYNTAX_TREE* identifer1 = node->children[0];

    int error = 0;
    error = error || CompileNode(identifer1);

    return error;
}

/* 72. <expr> -> <identifier> -= <expr> */
int ReduceExprAA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 72;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 73. <expr> -> <identifier> *= <expr> */
int ReduceExprBA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 73;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 74. <expr> -> <identifier> /= <expr> */
int ReduceExprCA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 74;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 75. <expr> -> <identifier> %= <expr> */
int ReduceExprDA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 75;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 76. <expr> -> <identifier> &= <expr> */
int ReduceExprEA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 76;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 77. <expr> -> <identifier> |= <expr> */
int ReduceExprFA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 77;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 78. <expr> -> <identifier> ^= <expr> */
int ReduceExprGA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 78;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 79. <expr> -> <expr> ( <expr list> ) */
int ReduceExprHA(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 79;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr_list1 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr_list1);

    return error;
}

/* 80. <expr list> -> */
int ReduceExprListA(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 80;

    int error = 0;

    return error;
}

/* 81. <expr list> -> <expr list+> */
int ReduceExprListB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 81;
    SYNTAX_TREE* expr_list_1 = node->children[0];

    int error = 0;
    error = error || CompileNode(expr_list_1);

    return error;
}

/* 82. <expr list+> -> <expr> */
int ReduceExprListA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 82;
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 83. <expr list+> -> <expr> , <expr list+> */
int ReduceExprListB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 83;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr_list_1 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr_list_1);

    return error;
}

/* 84. <expr> -> <expr> == <expr> */
int ReduceExprIA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 84;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 85. <expr> -> <expr> != <expr> */
int ReduceExprJA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 85;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 86. <expr> -> <expr> < <expr> */
int ReduceExprKA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 86;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 87. <expr> -> <expr> -> <expr> */
int ReduceExprLA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 87;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 88. <expr> -> <expr> <= <expr> */
int ReduceExprMA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 88;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 89. <expr> -> <expr> >= <expr> */
int ReduceExprNA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 89;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);

    return error;
}

/* 90. <expr> -> ! <expr> */
int ReduceExprOA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 90;
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 91. <expr> -> <expr> ? <expr> : <expr> */
int ReduceExprPA(SYNTAX_TREE* node)
{
    if (node->numChildren != 5) return 91;
    SYNTAX_TREE* expr1 = node->children[0];
    SYNTAX_TREE* expr2 = node->children[2];
    SYNTAX_TREE* expr3 = node->children[4];

    int error = 0;
    error = error || CompileNode(expr1);
    error = error || CompileNode(expr2);
    error = error || CompileNode(expr3);

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
        case 0x02: return ReduceDefListA(node);
        case 0x03: return ReduceDefListB(node);
        case 0x04: return ReduceDefA(node);
        case 0x05: return ReduceTypeA(node);
        case 0x06: return ReduceTypeB(node);
        case 0x07: return ReduceTypeC(node);
        case 0x08: return ReduceTypeD(node);
        case 0x09: return ReduceTypeE(node);
        case 0x0A: return ReduceTypeF(node);
        case 0x0B: return ReduceTypeG(node);
        case 0x0C: return ReduceTypeH(node);
        case 0x0D: return ReduceTypeI(node);
        case 0x0E: return ReduceTypeJ(node);
        case 0x0F: return ReduceTypeK(node);
        case 0x10: return ReduceStructA(node);
        case 0x11: return ReduceStructB(node);
        case 0x12: return ReduceDefB(node);
        case 0x13: return ReduceDefC(node);
        case 0x14: return ReduceDefD(node);
        case 0x15: return ReduceDefE(node);
        case 0x16: return ReduceParamListA(node);
        case 0x17: return ReduceParamListB(node);
        case 0x18: return ReduceParamListC(node);
        case 0x19: return ReduceParam(node);
        case 0x1A: return ReduceFunctionBodyA(node);
        case 0x1B: return ReduceFunctionBodyB(node);
        case 0x1C: return ReduceStmtA(node);
        case 0x1D: return ReduceStmtB(node);
        case 0x1E: return ReduceStmtC(node);
        case 0x1F: return ReduceStmtD(node);
        case 0x20: return ReduceStmtE(node);
        case 0x21: return ReduceStmtF(node);
        case 0x22: return ReduceStmtG(node);
        case 0x23: return ReduceStmtH(node);
        case 0x24: return ReduceStmtI(node);
        case 0x25: return ReduceStmtJ(node);
        case 0x26: return ReduceStmtK(node);
        case 0x27: return ReduceStmtL(node);
        case 0x28: return ReduceLoopBodyA(node);
        case 0x29: return ReduceLoopBodyB(node);
        case 0x2A: return ReduceBlockStmtA(node);
        case 0x2B: return ReduceBlockStmtB(node);
        case 0x2C: return ReduceExprA(node);
        case 0x2D: return ReduceExprB(node);
        case 0x2E: return ReduceExprC(node);
        case 0x2F: return ReduceExprD(node);
        case 0x30: return ReduceExprE(node);
        case 0x31: return ReduceExprF(node);
        case 0x32: return ReduceExprG(node);
        case 0x33: return ReduceBooleanA(node);
        case 0x34: return ReduceBooleanB(node);
        case 0x35: return ReduceExprH(node);
        case 0x36: return ReduceExprI(node);
        case 0x37: return ReduceExprJ(node);
        case 0x38: return ReduceExprK(node);
        case 0x39: return ReduceExprL(node);
        case 0x3A: return ReduceExprM(node);
        case 0x3B: return ReduceExprN(node);
        case 0x3C: return ReduceExprO(node);
        case 0x3D: return ReduceExprP(node);
        case 0x3E: return ReduceExprQ(node);
        case 0x3F: return ReduceExprR(node);
        case 0x40: return ReduceExprS(node);
        case 0x41: return ReduceExprT(node);
        case 0x42: return ReduceExprU(node);
        case 0x43: return ReduceExprV(node);
        case 0x44: return ReduceExprW(node);
        case 0x45: return ReduceExprX(node);
        case 0x46: return ReduceExprY(node);
        case 0x47: return ReduceExprZ(node);
        case 0x48: return ReduceExprAA(node);
        case 0x49: return ReduceExprBA(node);
        case 0x4A: return ReduceExprCA(node);
        case 0x4B: return ReduceExprDA(node);
        case 0x4C: return ReduceExprEA(node);
        case 0x4D: return ReduceExprFA(node);
        case 0x4E: return ReduceExprGA(node);
        case 0x4F: return ReduceExprHA(node);
        case 0x50: return ReduceExprListA(node);
        case 0x51: return ReduceExprListB(node);
        case 0x52: return ReduceExprListA(node);
        case 0x53: return ReduceExprListB(node);
        case 0x54: return ReduceExprIA(node);
        case 0x55: return ReduceExprJA(node);
        case 0x56: return ReduceExprKA(node);
        case 0x57: return ReduceExprLA(node);
        case 0x58: return ReduceExprMA(node);
        case 0x59: return ReduceExprNA(node);
        case 0x5A: return ReduceExprOA(node);
        case 0x5B: return ReduceExprPA(node);
    default:
        printf("Unknown production %i.\n", node->production);
        return 1;
    }
}
