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

/* 4. <identifier list> -> <identifier> , <identifier list> */
int ReduceIdentifierListA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 4;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* identifier_list1 = node->children[2];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(identifier_list1);

    return error;
}

/* 5. <identifier list> -> <identifier> */
int ReduceIdentifierListB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 5;
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;
    error = error || CompileNode(identifier1);

    return error;
}

/* 6. <opt endl> -> <endl> */
int ReduceOptEndlA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 6;

    int error = 0;

    return error;
}

/* 7. <opt endl> -> */
int ReduceOptEndlB(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 7;

    int error = 0;

    return error;
}

/* 8. <stmt> -> import <identifier list> <endl> */
int ReduceStmtA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 8;
    SYNTAX_TREE* identifier_list1 = node->children[1];

    int error = 0;
    error = error || CompileNode(identifier_list1);

    return error;
}

/* 9. <stmt> -> include <string> */
int ReduceStmtB(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 9;
    SYNTAX_TREE* string1 = node->children[1];

    int error = 0;
    error = error || CompileNode(string1);

    return error;
}

/* 10. <stmt> -> <endl> */
int ReduceStmtC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 10;

    int error = 0;

    return error;
}

/* 11. <stmt> -> <expr> <endl> */
int ReduceStmtD(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 11;
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 12. <stmt> -> <assignment> <endl> */
int ReduceStmtE(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 12;
    SYNTAX_TREE* assignment1 = node->children[0];

    int error = 0;
    error = error || CompileNode(assignment1);

    return error;
}

/* 13. <stmt> -> <self assignment> <endl> */
int ReduceStmtF(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 13;
    SYNTAX_TREE* self_assignment1 = node->children[0];

    int error = 0;
    error = error || CompileNode(self_assignment1);

    return error;
}

/* 14. <stmt> -> <function def> <endl> */
int ReduceStmtG(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 14;
    SYNTAX_TREE* function_def1 = node->children[0];

    int error = 0;
    error = error || CompileNode(function_def1);

    return error;
}

/* 15. <stmt> -> <if> <endl> */
int ReduceStmtH(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 15;
    SYNTAX_TREE* if1 = node->children[0];

    int error = 0;
    error = error || CompileNode(if1);

    return error;
}

/* 16. <stmt> -> <for loop> <endl> */
int ReduceStmtI(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 16;
    SYNTAX_TREE* for_loop1 = node->children[0];

    int error = 0;
    error = error || CompileNode(for_loop1);

    return error;
}

/* 17. <stmt> -> <while loop> <endl> */
int ReduceStmtJ(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 17;
    SYNTAX_TREE* while_loop1 = node->children[0];

    int error = 0;
    error = error || CompileNode(while_loop1);

    return error;
}

/* 18. <stmt> -> <for each> <endl> */
int ReduceStmtK(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 18;
    SYNTAX_TREE* for_each1 = node->children[0];

    int error = 0;
    error = error || CompileNode(for_each1);

    return error;
}

/* 19. <stmt> -> <let block> <endl> */
int ReduceStmtL(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 19;
    SYNTAX_TREE* let_block1 = node->children[0];

    int error = 0;
    error = error || CompileNode(let_block1);

    return error;
}

/* 20. <stmt> -> <try block> <endl> */
int ReduceStmtM(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 20;
    SYNTAX_TREE* try_block1 = node->children[0];

    int error = 0;
    error = error || CompileNode(try_block1);

    return error;
}

/* 21. <stmt> -> return <expr> <endl> */
int ReduceStmtN(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 21;
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 22. <stmt> -> break <endl> */
int ReduceStmtO(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 22;

    int error = 0;

    return error;
}

/* 23. <stmt> -> continue <endl> */
int ReduceStmtP(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 23;

    int error = 0;

    return error;
}

/* 24. <stmt> -> throw <expr> <endl> */
int ReduceStmtQ(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 24;
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 25. <stmt> -> <object def> <endl> */
int ReduceStmtR(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 25;
    SYNTAX_TREE* object_def1 = node->children[0];

    int error = 0;
    error = error || CompileNode(object_def1);

    return error;
}

/* 26. <assignment> -> <l-value> = <assignment> */
int ReduceAssignmentA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 26;
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* assignment1 = node->children[2];

    int error = 0;
    error = error || CompileNode(l_value1);
    error = error || CompileNode(assignment1);

    return error;
}

/* 27. <assignment> -> <l-value> = <condition> */
int ReduceAssignmentB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 27;
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* condition1 = node->children[2];

    int error = 0;
    error = error || CompileNode(l_value1);
    error = error || CompileNode(condition1);

    return error;
}

/* 28. <self assignment> -> <l-value> += <arithmetic> */
int ReduceSelfAssignmentA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 28;
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(l_value1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 29. <self assignment> -> <l-value> -= <arithmetic> */
int ReduceSelfAssignmentB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 29;
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(l_value1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 30. <self assignment> -> <l-value> *= <arithmetic> */
int ReduceSelfAssignmentC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 30;
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(l_value1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 31. <self assignment> -> <l-value> /= <arithmetic> */
int ReduceSelfAssignmentD(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 31;
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(l_value1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 32. <function def> -> function <identifier> <parameters> <endl> <stmt list> end */
int ReduceFunctionDef(SYNTAX_TREE* node)
{
    if (node->numChildren != 6) return 32;
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* parameters1 = node->children[2];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(parameters1);
    error = error || CompileNode(stmt_list1);

    return error;
}

/* 33. <parameters> -> */
int ReduceParametersA(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 33;

    int error = 0;

    return error;
}

/* 34. <parameters> -> ( ) */
int ReduceParametersB(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 34;

    int error = 0;

    return error;
}

/* 35. <parameters> -> ( <param decl> ) */
int ReduceParametersC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 35;
    SYNTAX_TREE* param_decl1 = node->children[1];

    int error = 0;
    error = error || CompileNode(param_decl1);

    return error;
}

/* 36. <param decl> -> <identifier> */
int ReduceParamDeclA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 36;
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;
    error = error || CompileNode(identifier1);

    return error;
}

/* 37. <param decl> -> <param decl> , <identifier> */
int ReduceParamDeclB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 37;
    SYNTAX_TREE* param_decl1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];

    int error = 0;
    error = error || CompileNode(param_decl1);
    error = error || CompileNode(identifier1);

    return error;
}

/* 38. <if> -> if <condition> then <endl> <stmt list> <else if> */
int ReduceIf(SYNTAX_TREE* node)
{
    if (node->numChildren != 6) return 38;
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];
    SYNTAX_TREE* else_if1 = node->children[5];

    int error = 0;
    error = error || CompileNode(condition1);
    error = error || CompileNode(stmt_list1);
    error = error || CompileNode(else_if1);

    return error;
}

/* 39. <else if> -> else <endl> <stmt list> end */
int ReduceElseIfA(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 39;
    SYNTAX_TREE* stmt_list1 = node->children[2];

    int error = 0;
    error = error || CompileNode(stmt_list1);

    return error;
}

/* 40. <else if> -> else <if> */
int ReduceElseIfB(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 40;
    SYNTAX_TREE* if1 = node->children[1];

    int error = 0;
    error = error || CompileNode(if1);

    return error;
}

/* 41. <else if> -> end */
int ReduceElseIfC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 41;

    int error = 0;

    return error;
}

/* 42. <for loop> -> for <identifier> = <arithmetic> to <arithmetic> do <endl> <stmt list> loop */
int ReduceForLoopA(SYNTAX_TREE* node)
{
    if (node->numChildren != 10) return 42;
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

/* 43. <for loop> -> for <identifier> = <arithmetic> to <arithmetic> step <arithmetic> do <endl> <stmt list> loop */
int ReduceForLoopB(SYNTAX_TREE* node)
{
    if (node->numChildren != 12) return 43;
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* arithmetic1 = node->children[3];
    SYNTAX_TREE* arithmetic2 = node->children[5];
    SYNTAX_TREE* arithmetic3 = node->children[7];
    SYNTAX_TREE* stmt_list1 = node->children[10];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(arithmetic1);
    error = error || CompileNode(arithmetic2);
    error = error || CompileNode(arithmetic3);
    error = error || CompileNode(stmt_list1);

    return error;
}

/* 44. <for each> -> for <identifier> in <expr> do <endl> <stmt list> loop */
int ReduceForEach(SYNTAX_TREE* node)
{
    if (node->numChildren != 8) return 44;
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* expr1 = node->children[3];
    SYNTAX_TREE* stmt_list1 = node->children[6];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);
    error = error || CompileNode(stmt_list1);

    return error;
}

/* 45. <while loop> -> while <condition> do <endl> <stmt list> loop */
int ReduceWhileLoop(SYNTAX_TREE* node)
{
    if (node->numChildren != 6) return 45;
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;
    error = error || CompileNode(condition1);
    error = error || CompileNode(stmt_list1);

    return error;
}

/* 46. <let block> -> let <bindings> begin <endl> <stmt list> end */
int ReduceLetBlock(SYNTAX_TREE* node)
{
    if (node->numChildren != 6) return 46;
    SYNTAX_TREE* bindings1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;
    error = error || CompileNode(bindings1);
    error = error || CompileNode(stmt_list1);

    return error;
}

/* 47. <bindings> -> <identifier> = <expr> , <bindings> */
int ReduceBindingsA(SYNTAX_TREE* node)
{
    if (node->numChildren != 5) return 47;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];
    SYNTAX_TREE* bindings1 = node->children[4];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);
    error = error || CompileNode(bindings1);

    return error;
}

/* 48. <bindings> -> <identifier> = <expr> */
int ReduceBindingsB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 48;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 49. <try block> -> try <endl> <stmt list> <catch block> complete */
int ReduceTryBlock(SYNTAX_TREE* node)
{
    if (node->numChildren != 5) return 49;
    SYNTAX_TREE* stmt_list1 = node->children[2];
    SYNTAX_TREE* catch_block1 = node->children[3];

    int error = 0;
    error = error || CompileNode(stmt_list1);
    error = error || CompileNode(catch_block1);

    return error;
}

/* 50. <catch block> -> catch <identifier> <endl> <stmt list> */
int ReduceCatchBlockA(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 50;
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[3];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(stmt_list1);

    return error;
}

/* 51. <catch block> -> */
int ReduceCatchBlockB(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 51;

    int error = 0;

    return error;
}

/* 52. <object def> -> object <identifier> <endl> <object body> end */
int ReduceObjectDef(SYNTAX_TREE* node)
{
    if (node->numChildren != 5) return 52;
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* object_body1 = node->children[3];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(object_body1);

    return error;
}

/* 53. <object body> -> static <identifier> <endl> <object body> */
int ReduceObjectBodyA(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 53;
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* object_body1 = node->children[3];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(object_body1);

    return error;
}

/* 54. <object body> -> static <identifier> = <expr> <endl> <object body> */
int ReduceObjectBodyB(SYNTAX_TREE* node)
{
    if (node->numChildren != 6) return 54;
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* expr1 = node->children[3];
    SYNTAX_TREE* object_body1 = node->children[5];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);
    error = error || CompileNode(object_body1);

    return error;
}

/* 55. <object body> -> <stmt> <object body> */
int ReduceObjectBodyC(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 55;
    SYNTAX_TREE* stmt1 = node->children[0];
    SYNTAX_TREE* object_body1 = node->children[1];

    int error = 0;
    error = error || CompileNode(stmt1);
    error = error || CompileNode(object_body1);

    return error;
}

/* 56. <object body> -> operator [ ] ( <identifier> ) <endl> <stmt list> end <endl> <object body> */
int ReduceObjectBodyD(SYNTAX_TREE* node)
{
    if (node->numChildren != 11) return 56;
    SYNTAX_TREE* identifier1 = node->children[4];
    SYNTAX_TREE* stmt_list1 = node->children[7];
    SYNTAX_TREE* object_body1 = node->children[10];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(stmt_list1);
    error = error || CompileNode(object_body1);

    return error;
}

/* 57. <object body> -> operator + ( <identifier> , <identifier> ) <endl> <stmt list> end <endl> <object body> */
int ReduceObjectBodyE(SYNTAX_TREE* node)
{
    if (node->numChildren != 12) return 57;
    SYNTAX_TREE* identifier1 = node->children[3];
    SYNTAX_TREE* identifier2 = node->children[5];
    SYNTAX_TREE* stmt_list1 = node->children[8];
    SYNTAX_TREE* object_body1 = node->children[11];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(identifier2);
    error = error || CompileNode(stmt_list1);
    error = error || CompileNode(object_body1);

    return error;
}

/* 58. <object body> -> operator - ( <identifier> , <identifier> ) <endl> <stmt list> end <endl> <object body> */
int ReduceObjectBodyF(SYNTAX_TREE* node)
{
    if (node->numChildren != 12) return 58;
    SYNTAX_TREE* identifier1 = node->children[3];
    SYNTAX_TREE* identifier2 = node->children[5];
    SYNTAX_TREE* stmt_list1 = node->children[8];
    SYNTAX_TREE* object_body1 = node->children[11];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(identifier2);
    error = error || CompileNode(stmt_list1);
    error = error || CompileNode(object_body1);

    return error;
}

/* 59. <object body> -> operator * ( <identifier> , <identifier> ) <endl> <stmt list> end <endl> <object body> */
int ReduceObjectBodyG(SYNTAX_TREE* node)
{
    if (node->numChildren != 12) return 59;
    SYNTAX_TREE* identifier1 = node->children[3];
    SYNTAX_TREE* identifier2 = node->children[5];
    SYNTAX_TREE* stmt_list1 = node->children[8];
    SYNTAX_TREE* object_body1 = node->children[11];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(identifier2);
    error = error || CompileNode(stmt_list1);
    error = error || CompileNode(object_body1);

    return error;
}

/* 60. <object body> -> operator / ( <identifier> , <identifier> ) <endl> <stmt list> end <endl> <object body> */
int ReduceObjectBodyH(SYNTAX_TREE* node)
{
    if (node->numChildren != 12) return 60;
    SYNTAX_TREE* identifier1 = node->children[3];
    SYNTAX_TREE* identifier2 = node->children[5];
    SYNTAX_TREE* stmt_list1 = node->children[8];
    SYNTAX_TREE* object_body1 = node->children[11];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(identifier2);
    error = error || CompileNode(stmt_list1);
    error = error || CompileNode(object_body1);

    return error;
}

/* 61. <object body> -> static <function def> <endl> <object body> */
int ReduceObjectBodyI(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 61;
    SYNTAX_TREE* function_def1 = node->children[1];
    SYNTAX_TREE* object_body1 = node->children[3];

    int error = 0;
    error = error || CompileNode(function_def1);
    error = error || CompileNode(object_body1);

    return error;
}

/* 62. <object body> -> */
int ReduceObjectBodyJ(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 62;

    int error = 0;

    return error;
}

/* 63. <l-value> -> <identifier> */
int ReduceLValueA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 63;
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;
    error = error || CompileNode(identifier1);

    return error;
}

/* 64. <l-value> -> ( <l-value> ) */
int ReduceLValueB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 64;
    SYNTAX_TREE* l_value1 = node->children[1];

    int error = 0;
    error = error || CompileNode(l_value1);

    return error;
}

/* 65. <l-value> -> <reference> . <identifier> */
int ReduceLValueC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 65;
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];

    int error = 0;
    error = error || CompileNode(reference1);
    error = error || CompileNode(identifier1);

    return error;
}

/* 66. <l-value> -> <reference> [ <expr> ] */
int ReduceLValueD(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 66;
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(reference1);
    error = error || CompileNode(expr1);

    return error;
}

/* 67. <l-value> -> this */
int ReduceLValueE(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 67;

    int error = 0;

    return error;
}

/* 68. <expr> -> <condition> */
int ReduceExpr(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 68;
    SYNTAX_TREE* condition1 = node->children[0];

    int error = 0;
    error = error || CompileNode(condition1);

    return error;
}

/* 69. <condition> -> <condition> and <logic> */
int ReduceConditionA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 69;
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(condition1);
    error = error || CompileNode(logic1);

    return error;
}

/* 70. <condition> -> <condition> or <logic> */
int ReduceConditionB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 70;
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(condition1);
    error = error || CompileNode(logic1);

    return error;
}

/* 71. <condition> -> <logic> */
int ReduceConditionC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 71;
    SYNTAX_TREE* logic1 = node->children[0];

    int error = 0;
    error = error || CompileNode(logic1);

    return error;
}

/* 72. <logic> -> not <comparison> */
int ReduceLogicA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 72;
    SYNTAX_TREE* comparison1 = node->children[1];

    int error = 0;
    error = error || CompileNode(comparison1);

    return error;
}

/* 73. <logic> -> <comparison> */
int ReduceLogicB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 73;
    SYNTAX_TREE* comparison1 = node->children[0];

    int error = 0;
    error = error || CompileNode(comparison1);

    return error;
}

/* 74. <comparison> -> <comparison> == <arithmetic> */
int ReduceComparisonA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 74;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(comparison1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 75. <comparison> -> <comparison> != <arithmetic> */
int ReduceComparisonB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 75;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(comparison1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 76. <comparison> -> <comparison> < <arithmetic> */
int ReduceComparisonC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 76;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(comparison1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 77. <comparison> -> <comparison> > <arithmetic> */
int ReduceComparisonD(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 77;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(comparison1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 78. <comparison> -> <comparison> <= <arithmetic> */
int ReduceComparisonE(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 78;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(comparison1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 79. <comparison> -> <comparison> >= <arithmetic> */
int ReduceComparisonF(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 79;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(comparison1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 80. <comparison> -> <comparison> is <arithmetic> */
int ReduceComparisonG(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 80;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || CompileNode(comparison1);
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 81. <comparison> -> <arithmetic> */
int ReduceComparisonH(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 81;
    SYNTAX_TREE* arithmetic1 = node->children[0];

    int error = 0;
    error = error || CompileNode(arithmetic1);

    return error;
}

/* 82. <arithmetic> -> <arithmetic> + <term> */
int ReduceArithmeticA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 82;
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = error || CompileNode(arithmetic1);
    error = error || CompileNode(term1);

    return error;
}

/* 83. <arithmetic> -> <arithmetic> - <term> */
int ReduceArithmeticB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 83;
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = error || CompileNode(arithmetic1);
    error = error || CompileNode(term1);

    return error;
}

/* 84. <arithmetic> -> <term> */
int ReduceArithmeticC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 84;
    SYNTAX_TREE* term1 = node->children[0];

    int error = 0;
    error = error || CompileNode(term1);

    return error;
}

/* 85. <term> -> <term> * <factor> */
int ReduceTermA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 85;
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    int error = 0;
    error = error || CompileNode(term1);
    error = error || CompileNode(factor1);

    return error;
}

/* 86. <term> -> <term> / <factor> */
int ReduceTermB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 86;
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    int error = 0;
    error = error || CompileNode(term1);
    error = error || CompileNode(factor1);

    return error;
}

/* 87. <term> -> <term> mod <factor> */
int ReduceTermC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 87;
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    int error = 0;
    error = error || CompileNode(term1);
    error = error || CompileNode(factor1);

    return error;
}

/* 88. <term> -> <factor> */
int ReduceTermD(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 88;
    SYNTAX_TREE* factor1 = node->children[0];

    int error = 0;
    error = error || CompileNode(factor1);

    return error;
}

/* 89. <factor> -> - <factor> */
int ReduceFactorA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 89;
    SYNTAX_TREE* factor1 = node->children[1];

    int error = 0;
    error = error || CompileNode(factor1);

    return error;
}

/* 90. <factor> -> ! <factor> */
int ReduceFactorB(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 90;
    SYNTAX_TREE* factor1 = node->children[1];

    int error = 0;
    error = error || CompileNode(factor1);

    return error;
}

/* 91. <factor> -> <final> */
int ReduceFactorC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 91;
    SYNTAX_TREE* final1 = node->children[0];

    int error = 0;
    error = error || CompileNode(final1);

    return error;
}

/* 92. <final> -> ( <expr> ) */
int ReduceFinalA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 92;
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 93. <final> -> <boolean> */
int ReduceFinalB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 93;
    SYNTAX_TREE* boolean1 = node->children[0];

    int error = 0;
    error = error || CompileNode(boolean1);

    return error;
}

/* 94. <final> -> <integer> */
int ReduceFinalC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 94;
    SYNTAX_TREE* integer1 = node->children[0];

    int error = 0;
    error = error || CompileNode(integer1);

    return error;
}

/* 95. <final> -> <float> */
int ReduceFinalD(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 95;
    SYNTAX_TREE* float1 = node->children[0];

    int error = 0;
    error = error || CompileNode(float1);

    return error;
}

/* 96. <final> -> <string> */
int ReduceFinalE(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 96;
    SYNTAX_TREE* string1 = node->children[0];

    int error = 0;
    error = error || CompileNode(string1);

    return error;
}

/* 97. <final> -> <object> */
int ReduceFinalF(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 97;
    SYNTAX_TREE* object1 = node->children[0];

    int error = 0;
    error = error || CompileNode(object1);

    return error;
}

/* 98. <final> -> <reference> */
int ReduceFinalG(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 98;
    SYNTAX_TREE* reference1 = node->children[0];

    int error = 0;
    error = error || CompileNode(reference1);

    return error;
}

/* 99. <reference> -> <l-value> */
int ReduceReferenceA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 99;
    SYNTAX_TREE* l_value1 = node->children[0];

    int error = 0;
    error = error || CompileNode(l_value1);

    return error;
}

/* 100. <reference> -> <reference> ( ) */
int ReduceReferenceB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 100;
    SYNTAX_TREE* reference1 = node->children[0];

    int error = 0;
    error = error || CompileNode(reference1);

    return error;
}

/* 101. <reference> -> <reference> ( <arguments> ) */
int ReduceReferenceC(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 101;
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* arguments1 = node->children[2];

    int error = 0;
    error = error || CompileNode(reference1);
    error = error || CompileNode(arguments1);

    return error;
}

/* 102. <arguments> -> <arguments> , <expr> */
int ReduceArgumentsA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 102;
    SYNTAX_TREE* arguments1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(arguments1);
    error = error || CompileNode(expr1);

    return error;
}

/* 103. <arguments> -> <expr> */
int ReduceArgumentsB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 103;
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 104. <object> -> [ ] */
int ReduceObjectA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 104;

    int error = 0;

    return error;
}

/* 105. <object> -> [ <array init> ] */
int ReduceObjectB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 105;
    SYNTAX_TREE* array_init1 = node->children[1];

    int error = 0;
    error = error || CompileNode(array_init1);

    return error;
}

/* 106. <object> -> [ <dictionary init> ] */
int ReduceObjectC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 106;
    SYNTAX_TREE* dictionary_init1 = node->children[1];

    int error = 0;
    error = error || CompileNode(dictionary_init1);

    return error;
}

/* 107. <object> -> { } */
int ReduceObjectD(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 107;

    int error = 0;

    return error;
}

/* 108. <object> -> { <dictionary init> } */
int ReduceObjectE(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 108;
    SYNTAX_TREE* dictionary_init1 = node->children[1];

    int error = 0;
    error = error || CompileNode(dictionary_init1);

    return error;
}

/* 109. <object> -> new <identifier> */
int ReduceObjectF(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 109;
    SYNTAX_TREE* identifier1 = node->children[1];

    int error = 0;
    error = error || CompileNode(identifier1);

    return error;
}

/* 110. <object> -> new <identifier> ( ) */
int ReduceObjectG(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 110;
    SYNTAX_TREE* identifier1 = node->children[1];

    int error = 0;
    error = error || CompileNode(identifier1);

    return error;
}

/* 111. <object> -> new <identifier> ( <arguments> ) */
int ReduceObjectH(SYNTAX_TREE* node)
{
    if (node->numChildren != 5) return 111;
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* arguments1 = node->children[3];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(arguments1);

    return error;
}

/* 112. <array init> -> <array init> , <expr> */
int ReduceArrayInitA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 112;
    SYNTAX_TREE* array_init1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(array_init1);
    error = error || CompileNode(expr1);

    return error;
}

/* 113. <array init> -> <expr> */
int ReduceArrayInitB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 113;
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = error || CompileNode(expr1);

    return error;
}

/* 114. <dictionary init> -> <dictionary init> , <identifier> : <expr> */
int ReduceDictionaryInitA(SYNTAX_TREE* node)
{
    if (node->numChildren != 5) return 114;
    SYNTAX_TREE* dictionary_init1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];
    SYNTAX_TREE* expr1 = node->children[4];

    int error = 0;
    error = error || CompileNode(dictionary_init1);
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 115. <dictionary init> -> <identifier> : <expr> */
int ReduceDictionaryInitB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 115;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);

    return error;
}

/* 116. <boolean> -> true */
int ReduceBooleanA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 116;

    int error = 0;

    return error;
}

/* 117. <boolean> -> false */
int ReduceBooleanB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 117;

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
        case 0x04: return ReduceIdentifierListA(node);
        case 0x05: return ReduceIdentifierListB(node);
        case 0x06: return ReduceOptEndlA(node);
        case 0x07: return ReduceOptEndlB(node);
        case 0x08: return ReduceStmtA(node);
        case 0x09: return ReduceStmtB(node);
        case 0x0A: return ReduceStmtC(node);
        case 0x0B: return ReduceStmtD(node);
        case 0x0C: return ReduceStmtE(node);
        case 0x0D: return ReduceStmtF(node);
        case 0x0E: return ReduceStmtG(node);
        case 0x0F: return ReduceStmtH(node);
        case 0x10: return ReduceStmtI(node);
        case 0x11: return ReduceStmtJ(node);
        case 0x12: return ReduceStmtK(node);
        case 0x13: return ReduceStmtL(node);
        case 0x14: return ReduceStmtM(node);
        case 0x15: return ReduceStmtN(node);
        case 0x16: return ReduceStmtO(node);
        case 0x17: return ReduceStmtP(node);
        case 0x18: return ReduceStmtQ(node);
        case 0x19: return ReduceStmtR(node);
        case 0x1A: return ReduceAssignmentA(node);
        case 0x1B: return ReduceAssignmentB(node);
        case 0x1C: return ReduceSelfAssignmentA(node);
        case 0x1D: return ReduceSelfAssignmentB(node);
        case 0x1E: return ReduceSelfAssignmentC(node);
        case 0x1F: return ReduceSelfAssignmentD(node);
        case 0x20: return ReduceFunctionDef(node);
        case 0x21: return ReduceParametersA(node);
        case 0x22: return ReduceParametersB(node);
        case 0x23: return ReduceParametersC(node);
        case 0x24: return ReduceParamDeclA(node);
        case 0x25: return ReduceParamDeclB(node);
        case 0x26: return ReduceIf(node);
        case 0x27: return ReduceElseIfA(node);
        case 0x28: return ReduceElseIfB(node);
        case 0x29: return ReduceElseIfC(node);
        case 0x2A: return ReduceForLoopA(node);
        case 0x2B: return ReduceForLoopB(node);
        case 0x2C: return ReduceForEach(node);
        case 0x2D: return ReduceWhileLoop(node);
        case 0x2E: return ReduceLetBlock(node);
        case 0x2F: return ReduceBindingsA(node);
        case 0x30: return ReduceBindingsB(node);
        case 0x31: return ReduceTryBlock(node);
        case 0x32: return ReduceCatchBlockA(node);
        case 0x33: return ReduceCatchBlockB(node);
        case 0x34: return ReduceObjectDef(node);
        case 0x35: return ReduceObjectBodyA(node);
        case 0x36: return ReduceObjectBodyB(node);
        case 0x37: return ReduceObjectBodyC(node);
        case 0x38: return ReduceObjectBodyD(node);
        case 0x39: return ReduceObjectBodyE(node);
        case 0x3A: return ReduceObjectBodyF(node);
        case 0x3B: return ReduceObjectBodyG(node);
        case 0x3C: return ReduceObjectBodyH(node);
        case 0x3D: return ReduceObjectBodyI(node);
        case 0x3E: return ReduceObjectBodyJ(node);
        case 0x3F: return ReduceLValueA(node);
        case 0x40: return ReduceLValueB(node);
        case 0x41: return ReduceLValueC(node);
        case 0x42: return ReduceLValueD(node);
        case 0x43: return ReduceLValueE(node);
        case 0x44: return ReduceExpr(node);
        case 0x45: return ReduceConditionA(node);
        case 0x46: return ReduceConditionB(node);
        case 0x47: return ReduceConditionC(node);
        case 0x48: return ReduceLogicA(node);
        case 0x49: return ReduceLogicB(node);
        case 0x4A: return ReduceComparisonA(node);
        case 0x4B: return ReduceComparisonB(node);
        case 0x4C: return ReduceComparisonC(node);
        case 0x4D: return ReduceComparisonD(node);
        case 0x4E: return ReduceComparisonE(node);
        case 0x4F: return ReduceComparisonF(node);
        case 0x50: return ReduceComparisonG(node);
        case 0x51: return ReduceComparisonH(node);
        case 0x52: return ReduceArithmeticA(node);
        case 0x53: return ReduceArithmeticB(node);
        case 0x54: return ReduceArithmeticC(node);
        case 0x55: return ReduceTermA(node);
        case 0x56: return ReduceTermB(node);
        case 0x57: return ReduceTermC(node);
        case 0x58: return ReduceTermD(node);
        case 0x59: return ReduceFactorA(node);
        case 0x5A: return ReduceFactorB(node);
        case 0x5B: return ReduceFactorC(node);
        case 0x5C: return ReduceFinalA(node);
        case 0x5D: return ReduceFinalB(node);
        case 0x5E: return ReduceFinalC(node);
        case 0x5F: return ReduceFinalD(node);
        case 0x60: return ReduceFinalE(node);
        case 0x61: return ReduceFinalF(node);
        case 0x62: return ReduceFinalG(node);
        case 0x63: return ReduceReferenceA(node);
        case 0x64: return ReduceReferenceB(node);
        case 0x65: return ReduceReferenceC(node);
        case 0x66: return ReduceArgumentsA(node);
        case 0x67: return ReduceArgumentsB(node);
        case 0x68: return ReduceObjectA(node);
        case 0x69: return ReduceObjectB(node);
        case 0x6A: return ReduceObjectC(node);
        case 0x6B: return ReduceObjectD(node);
        case 0x6C: return ReduceObjectE(node);
        case 0x6D: return ReduceObjectF(node);
        case 0x6E: return ReduceObjectG(node);
        case 0x6F: return ReduceObjectH(node);
        case 0x70: return ReduceArrayInitA(node);
        case 0x71: return ReduceArrayInitB(node);
        case 0x72: return ReduceDictionaryInitA(node);
        case 0x73: return ReduceDictionaryInitB(node);
        case 0x74: return ReduceBooleanA(node);
        case 0x75: return ReduceBooleanB(node);
    default:
        printf("Unknown production %i.\n", node->production);
        return 1;
    }
}
