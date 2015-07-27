/* auto-generated compiler stubs */
#include "lr_parser.h"
#include "duck3.h"


/* production stubs */

/* 1. <program> -> <stmtlist> */
int ReduceProgram(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* stmtlist1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(stmtlist1));

    return error;
}

/* 2. <stmtlist> -> <stmt> <stmtlist> */
int ReduceStmtlistA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* stmt1 = node->children[0];
    SYNTAX_TREE* stmtlist1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(stmt1));
    error = (error ? error : ProcessNode(stmtlist1));

    return error;
}

/* 3. <stmtlist> -> */
int ReduceStmtlistB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 0);

    int error = 0;

    return error;
}

/* 4. <identifier-list> -> <identifier> , <identifier-list> */
int ReduceIdentifierListA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* identifier_list1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(identifier1));
    error = (error ? error : ProcessNode(identifier_list1));

    return error;
}

/* 5. <identifier-list> -> <identifier> */
int ReduceIdentifierListB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(identifier1));

    return error;
}

/* 6. <stmt> -> import <identifier-list> <endl> */
int ReduceStmtA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* identifier_list1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(identifier_list1));

    return error;
}

/* 7. <stmt> -> include <string> */
int ReduceStmtB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* string1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(string1));

    return error;
}

/* 8. <stmt> -> <expr> <endl> */
int ReduceStmtC(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(expr1));

    return error;
}

/* 9. <stmt> -> <endl> */
int ReduceStmtD(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);

    int error = 0;

    return error;
}

/* 10. <stmt> -> <assignment> <endl> */
int ReduceStmtE(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* assignment1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(assignment1));

    return error;
}

/* 11. <stmt> -> <self-assignment> <endl> */
int ReduceStmtF(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* self_assignment1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(self_assignment1));

    return error;
}

/* 12. <stmt> -> <function-def> <endl> */
int ReduceStmtG(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* function_def1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(function_def1));

    return error;
}

/* 13. <stmt> -> <if> <endl> */
int ReduceStmtH(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* if1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(if1));

    return error;
}

/* 14. <stmt> -> <for-loop> <endl> */
int ReduceStmtI(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* for_loop1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(for_loop1));

    return error;
}

/* 15. <stmt> -> <for-each> <endl> */
int ReduceStmtJ(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* for_each1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(for_each1));

    return error;
}

/* 16. <stmt> -> <while-loop> <endl> */
int ReduceStmtK(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* while_loop1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(while_loop1));

    return error;
}

/* 17. <stmt> -> <do-while> <endl> */
int ReduceStmtL(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* do_while1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(do_while1));

    return error;
}

/* 18. <stmt> -> <let-block> <endl> */
int ReduceStmtM(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* let_block1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(let_block1));

    return error;
}

/* 19. <stmt> -> <try-block> <endl> */
int ReduceStmtN(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* try_block1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(try_block1));

    return error;
}

/* 20. <stmt> -> <class> <endl> */
int ReduceStmtO(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* class1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(class1));

    return error;
}

/* 21. <stmt> -> static <assignment> */
int ReduceStmtP(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* assignment1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(assignment1));

    return error;
}

/* 22. <stmt> -> static <function-def> */
int ReduceStmtQ(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* function_def1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(function_def1));

    return error;
}

/* 23. <stmt> -> return <endl> */
int ReduceStmtR(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);

    int error = 0;

    return error;
}

/* 24. <stmt> -> return <expr> <endl> */
int ReduceStmtS(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(expr1));

    return error;
}

/* 25. <stmt> -> break <endl> */
int ReduceStmtT(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);

    int error = 0;

    return error;
}

/* 26. <stmt> -> continue <endl> */
int ReduceStmtU(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);

    int error = 0;

    return error;
}

/* 27. <stmt> -> throw <expr> <endl> */
int ReduceStmtV(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(expr1));

    return error;
}

/* 28. <assignment> -> <l-value> = <condition> */
int ReduceAssignment(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* condition1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(l_value1));
    error = (error ? error : ProcessNode(condition1));

    return error;
}

/* 29. <self-assignment> -> <l-value> += <arithmetic> */
int ReduceSelfAssignmentA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(l_value1));
    error = (error ? error : ProcessNode(arithmetic1));

    return error;
}

/* 30. <self-assignment> -> <l-value> -= <arithmetic> */
int ReduceSelfAssignmentB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(l_value1));
    error = (error ? error : ProcessNode(arithmetic1));

    return error;
}

/* 31. <self-assignment> -> <l-value> *= <arithmetic> */
int ReduceSelfAssignmentC(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(l_value1));
    error = (error ? error : ProcessNode(arithmetic1));

    return error;
}

/* 32. <self-assignment> -> <l-value> /= <arithmetic> */
int ReduceSelfAssignmentD(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(l_value1));
    error = (error ? error : ProcessNode(arithmetic1));

    return error;
}

/* 33. <self-assignment> -> <l-value> ++ */
int ReduceSelfAssignmentE(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* l_value1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(l_value1));

    return error;
}

/* 34. <self-assignment> -> <l-value> -- */
int ReduceSelfAssignmentF(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* l_value1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(l_value1));

    return error;
}

/* 35. <function-def> -> func <function-decl> */
int ReduceFunctionDef(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* function_decl1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(function_decl1));

    return error;
}

/* 36. <function-decl> -> <identifier> <parameters> <endl> <stmtlist> end */
int ReduceFunctionDeclA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 5);
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* parameters1 = node->children[1];
    SYNTAX_TREE* stmtlist1 = node->children[3];

    int error = 0;
    error = (error ? error : ProcessNode(identifier1));
    error = (error ? error : ProcessNode(parameters1));
    error = (error ? error : ProcessNode(stmtlist1));

    return error;
}

/* 37. <function-decl> -> <string> <parameters> <endl> <stmtlist> end */
int ReduceFunctionDeclB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 5);
    SYNTAX_TREE* string1 = node->children[0];
    SYNTAX_TREE* parameters1 = node->children[1];
    SYNTAX_TREE* stmtlist1 = node->children[3];

    int error = 0;
    error = (error ? error : ProcessNode(string1));
    error = (error ? error : ProcessNode(parameters1));
    error = (error ? error : ProcessNode(stmtlist1));

    return error;
}

/* 38. <class> -> class <identifier> <parameters> <endl> <stmtlist> end def */
int ReduceClass(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 7);
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* parameters1 = node->children[2];
    SYNTAX_TREE* stmtlist1 = node->children[4];

    int error = 0;
    error = (error ? error : ProcessNode(identifier1));
    error = (error ? error : ProcessNode(parameters1));
    error = (error ? error : ProcessNode(stmtlist1));

    return error;
}

/* 39. <parameters> -> ( ) */
int ReduceParametersA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);

    int error = 0;

    return error;
}

/* 40. <parameters> -> ( <param-decl> ) */
int ReduceParametersB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* param_decl1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(param_decl1));

    return error;
}

/* 41. <parameters> -> */
int ReduceParametersC(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 0);

    int error = 0;

    return error;
}

/* 42. <param-decl> -> <identifier> */
int ReduceParamDeclA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(identifier1));

    return error;
}

/* 43. <param-decl> -> <identifier> , <param-decl> */
int ReduceParamDeclB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* param_decl1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(identifier1));
    error = (error ? error : ProcessNode(param_decl1));

    return error;
}

/* 44. <if> -> if <condition> then <endl> <stmtlist> <elseif> */
int ReduceIf(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 6);
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmtlist1 = node->children[4];
    SYNTAX_TREE* elseif1 = node->children[5];

    int error = 0;
    error = (error ? error : ProcessNode(condition1));
    error = (error ? error : ProcessNode(stmtlist1));
    error = (error ? error : ProcessNode(elseif1));

    return error;
}

/* 45. <elseif> -> else <endl> <stmtlist> endif */
int ReduceElseifA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 4);
    SYNTAX_TREE* stmtlist1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(stmtlist1));

    return error;
}

/* 46. <elseif> -> else <if> */
int ReduceElseifB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* if1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(if1));

    return error;
}

/* 47. <elseif> -> endif */
int ReduceElseifC(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);

    int error = 0;

    return error;
}

/* 48. <for-loop> -> for <identifier> = <arithmetic> to <arithmetic> <step> */
int ReduceForLoop(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 7);
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* arithmetic1 = node->children[3];
    SYNTAX_TREE* arithmetic2 = node->children[5];
    SYNTAX_TREE* step1 = node->children[6];

    int error = 0;
    error = (error ? error : ProcessNode(identifier1));
    error = (error ? error : ProcessNode(arithmetic1));
    error = (error ? error : ProcessNode(arithmetic2));
    error = (error ? error : ProcessNode(step1));

    return error;
}

/* 49. <step> -> step <arithmetic> do <endl> <stmtlist> loop */
int ReduceStepA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 6);
    SYNTAX_TREE* arithmetic1 = node->children[1];
    SYNTAX_TREE* stmtlist1 = node->children[4];

    int error = 0;
    error = (error ? error : ProcessNode(arithmetic1));
    error = (error ? error : ProcessNode(stmtlist1));

    return error;
}

/* 50. <step> -> do <endl> <stmtlist> loop */
int ReduceStepB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 4);
    SYNTAX_TREE* stmtlist1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(stmtlist1));

    return error;
}

/* 51. <for-each> -> for <identifier> in <expr> do <endl> <stmtlist> loop */
int ReduceForEach(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 8);
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* expr1 = node->children[3];
    SYNTAX_TREE* stmtlist1 = node->children[6];

    int error = 0;
    error = (error ? error : ProcessNode(identifier1));
    error = (error ? error : ProcessNode(expr1));
    error = (error ? error : ProcessNode(stmtlist1));

    return error;
}

/* 52. <while-loop> -> while <condition> do <endl> <stmtlist> loop */
int ReduceWhileLoop(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 6);
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmtlist1 = node->children[4];

    int error = 0;
    error = (error ? error : ProcessNode(condition1));
    error = (error ? error : ProcessNode(stmtlist1));

    return error;
}

/* 53. <do-while> -> do <endl> <stmtlist> loop while <condition> */
int ReduceDoWhile(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 6);
    SYNTAX_TREE* stmtlist1 = node->children[2];
    SYNTAX_TREE* condition1 = node->children[5];

    int error = 0;
    error = (error ? error : ProcessNode(stmtlist1));
    error = (error ? error : ProcessNode(condition1));

    return error;
}

/* 54. <let-block> -> let <bindings> begin <endl> <stmtlist> end */
int ReduceLetBlock(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 6);
    SYNTAX_TREE* bindings1 = node->children[1];
    SYNTAX_TREE* stmtlist1 = node->children[4];

    int error = 0;
    error = (error ? error : ProcessNode(bindings1));
    error = (error ? error : ProcessNode(stmtlist1));

    return error;
}

/* 55. <bindings> -> <identifier> = <expr> , <bindings> */
int ReduceBindingsA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 5);
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];
    SYNTAX_TREE* bindings1 = node->children[4];

    int error = 0;
    error = (error ? error : ProcessNode(identifier1));
    error = (error ? error : ProcessNode(expr1));
    error = (error ? error : ProcessNode(bindings1));

    return error;
}

/* 56. <bindings> -> <identifier> = <expr> */
int ReduceBindingsB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(identifier1));
    error = (error ? error : ProcessNode(expr1));

    return error;
}

/* 57. <try-block> -> try <endl> <stmtlist> <catch-block> */
int ReduceTryBlock(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 4);
    SYNTAX_TREE* stmtlist1 = node->children[2];
    SYNTAX_TREE* catch_block1 = node->children[3];

    int error = 0;
    error = (error ? error : ProcessNode(stmtlist1));
    error = (error ? error : ProcessNode(catch_block1));

    return error;
}

/* 58. <catch-block> -> catch <l-value> <endl> <stmtlist> done */
int ReduceCatchBlockA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 5);
    SYNTAX_TREE* l_value1 = node->children[1];
    SYNTAX_TREE* stmtlist1 = node->children[3];

    int error = 0;
    error = (error ? error : ProcessNode(l_value1));
    error = (error ? error : ProcessNode(stmtlist1));

    return error;
}

/* 59. <catch-block> -> done */
int ReduceCatchBlockB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);

    int error = 0;

    return error;
}

/* 60. <l-value> -> <identifier> */
int ReduceLValueA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(identifier1));

    return error;
}

/* 61. <l-value> -> ( <l-value> ) */
int ReduceLValueB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* l_value1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(l_value1));

    return error;
}

/* 62. <l-value> -> <reference> . <identifier> */
int ReduceLValueC(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(reference1));
    error = (error ? error : ProcessNode(identifier1));

    return error;
}

/* 63. <l-value> -> <reference> [ <expr> ] */
int ReduceLValueD(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 4);
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(reference1));
    error = (error ? error : ProcessNode(expr1));

    return error;
}

/* 64. <expr> -> <condition> */
int ReduceExpr(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* condition1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(condition1));

    return error;
}

/* 65. <condition> -> <condition> and <logic> */
int ReduceConditionA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(condition1));
    error = (error ? error : ProcessNode(logic1));

    return error;
}

/* 66. <condition> -> <condition> or <logic> */
int ReduceConditionB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(condition1));
    error = (error ? error : ProcessNode(logic1));

    return error;
}

/* 67. <condition> -> <logic> */
int ReduceConditionC(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* logic1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(logic1));

    return error;
}

/* 68. <logic> -> not <comparison> */
int ReduceLogicA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* comparison1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(comparison1));

    return error;
}

/* 69. <logic> -> <comparison> */
int ReduceLogicB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* comparison1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(comparison1));

    return error;
}

/* 70. <comparison> -> <comparison> == <arithmetic> */
int ReduceComparisonA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(comparison1));
    error = (error ? error : ProcessNode(arithmetic1));

    return error;
}

/* 71. <comparison> -> <comparison> != <arithmetic> */
int ReduceComparisonB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(comparison1));
    error = (error ? error : ProcessNode(arithmetic1));

    return error;
}

/* 72. <comparison> -> <comparison> < <arithmetic> */
int ReduceComparisonC(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(comparison1));
    error = (error ? error : ProcessNode(arithmetic1));

    return error;
}

/* 73. <comparison> -> <comparison> > <arithmetic> */
int ReduceComparisonD(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(comparison1));
    error = (error ? error : ProcessNode(arithmetic1));

    return error;
}

/* 74. <comparison> -> <comparison> <= <arithmetic> */
int ReduceComparisonE(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(comparison1));
    error = (error ? error : ProcessNode(arithmetic1));

    return error;
}

/* 75. <comparison> -> <comparison> >= <arithmetic> */
int ReduceComparisonF(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(comparison1));
    error = (error ? error : ProcessNode(arithmetic1));

    return error;
}

/* 76. <comparison> -> <final> is <reference> */
int ReduceComparisonG(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* final1 = node->children[0];
    SYNTAX_TREE* reference1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(final1));
    error = (error ? error : ProcessNode(reference1));

    return error;
}

/* 77. <comparison> -> <final> is not <reference> */
int ReduceComparisonH(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 4);
    SYNTAX_TREE* final1 = node->children[0];
    SYNTAX_TREE* reference1 = node->children[3];

    int error = 0;
    error = (error ? error : ProcessNode(final1));
    error = (error ? error : ProcessNode(reference1));

    return error;
}

/* 78. <comparison> -> <arithmetic> */
int ReduceComparisonI(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* arithmetic1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(arithmetic1));

    return error;
}

/* 79. <arithmetic> -> <arithmetic> + <term> */
int ReduceArithmeticA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(arithmetic1));
    error = (error ? error : ProcessNode(term1));

    return error;
}

/* 80. <arithmetic> -> <arithmetic> - <term> */
int ReduceArithmeticB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(arithmetic1));
    error = (error ? error : ProcessNode(term1));

    return error;
}

/* 81. <arithmetic> -> <term> */
int ReduceArithmeticC(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* term1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(term1));

    return error;
}

/* 82. <term> -> <term> * <factor> */
int ReduceTermA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(term1));
    error = (error ? error : ProcessNode(factor1));

    return error;
}

/* 83. <term> -> <term> / <factor> */
int ReduceTermB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(term1));
    error = (error ? error : ProcessNode(factor1));

    return error;
}

/* 84. <term> -> <term> mod <factor> */
int ReduceTermC(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(term1));
    error = (error ? error : ProcessNode(factor1));

    return error;
}

/* 85. <term> -> <factor> */
int ReduceTermD(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* factor1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(factor1));

    return error;
}

/* 86. <factor> -> - <factor> */
int ReduceFactorA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* factor1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(factor1));

    return error;
}

/* 87. <factor> -> ! <factor> */
int ReduceFactorB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* factor1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(factor1));

    return error;
}

/* 88. <factor> -> * <factor> */
int ReduceFactorC(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* factor1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(factor1));

    return error;
}

/* 89. <factor> -> <final> */
int ReduceFactorD(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* final1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(final1));

    return error;
}

/* 90. <final> -> ( <expr> ) */
int ReduceFinalA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(expr1));

    return error;
}

/* 91. <final> -> <boolean> */
int ReduceFinalB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* boolean1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(boolean1));

    return error;
}

/* 92. <final> -> <object> */
int ReduceFinalC(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* object1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(object1));

    return error;
}

/* 93. <final> -> <reference> */
int ReduceFinalD(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* reference1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(reference1));

    return error;
}

/* 94. <final> -> new <reference> */
int ReduceFinalE(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);
    SYNTAX_TREE* reference1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(reference1));

    return error;
}

/* 95. <final> -> <integer> */
int ReduceFinalF(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* integer1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(integer1));

    return error;
}

/* 96. <final> -> <float> */
int ReduceFinalG(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* float1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(float1));

    return error;
}

/* 97. <final> -> <string> */
int ReduceFinalH(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* string1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(string1));

    return error;
}

/* 98. <reference> -> <l-value> */
int ReduceReferenceA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* l_value1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(l_value1));

    return error;
}

/* 99. <reference> -> this */
int ReduceReferenceB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);

    int error = 0;

    return error;
}

/* 100. <reference> -> <reference> ( ) */
int ReduceReferenceC(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* reference1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(reference1));

    return error;
}

/* 101. <reference> -> <reference> ( <arguments> ) */
int ReduceReferenceD(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 4);
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* arguments1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(reference1));
    error = (error ? error : ProcessNode(arguments1));

    return error;
}

/* 102. <arguments> -> <arguments> , <expr> */
int ReduceArgumentsA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* arguments1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(arguments1));
    error = (error ? error : ProcessNode(expr1));

    return error;
}

/* 103. <arguments> -> <expr> */
int ReduceArgumentsB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(expr1));

    return error;
}

/* 104. <object> -> [ ] */
int ReduceObjectA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 2);

    int error = 0;

    return error;
}

/* 105. <object> -> [ <array-init> ] */
int ReduceObjectB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* array_init1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(array_init1));

    return error;
}

/* 106. <object> -> [ <dictionary-init> ] */
int ReduceObjectC(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* dictionary_init1 = node->children[1];

    int error = 0;
    error = (error ? error : ProcessNode(dictionary_init1));

    return error;
}

/* 107. <array-init> -> <array-init> , <expr> */
int ReduceArrayInitA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* array_init1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(array_init1));
    error = (error ? error : ProcessNode(expr1));

    return error;
}

/* 108. <array-init> -> <expr> */
int ReduceArrayInitB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = (error ? error : ProcessNode(expr1));

    return error;
}

/* 109. <dictionary-init> -> <dictionary-init> , <identifier> : <expr> */
int ReduceDictionaryInitA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 5);
    SYNTAX_TREE* dictionary_init1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];
    SYNTAX_TREE* expr1 = node->children[4];

    int error = 0;
    error = (error ? error : ProcessNode(dictionary_init1));
    error = (error ? error : ProcessNode(identifier1));
    error = (error ? error : ProcessNode(expr1));

    return error;
}

/* 110. <dictionary-init> -> <identifier> : <expr> */
int ReduceDictionaryInitB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 3);
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = (error ? error : ProcessNode(identifier1));
    error = (error ? error : ProcessNode(expr1));

    return error;
}

/* 111. <boolean> -> true */
int ReduceBooleanA(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);

    int error = 0;

    return error;
}

/* 112. <boolean> -> false */
int ReduceBooleanB(SYNTAX_TREE* node)
{
    Assert(node->numChildren == 1);

    int error = 0;

    return error;
}

/* reduce one node */
int ProcessNode(SYNTAX_TREE* node)
{
    if (node == NULL || node->production == 0)
        return 1;

    switch (node->production)
    {
        case 0x01: return ReduceProgram(node);
        case 0x02: return ReduceStmtlistA(node);
        case 0x03: return ReduceStmtlistB(node);
        case 0x04: return ReduceIdentifierListA(node);
        case 0x05: return ReduceIdentifierListB(node);
        case 0x06: return ReduceStmtA(node);
        case 0x07: return ReduceStmtB(node);
        case 0x08: return ReduceStmtC(node);
        case 0x09: return ReduceStmtD(node);
        case 0x0A: return ReduceStmtE(node);
        case 0x0B: return ReduceStmtF(node);
        case 0x0C: return ReduceStmtG(node);
        case 0x0D: return ReduceStmtH(node);
        case 0x0E: return ReduceStmtI(node);
        case 0x0F: return ReduceStmtJ(node);
        case 0x10: return ReduceStmtK(node);
        case 0x11: return ReduceStmtL(node);
        case 0x12: return ReduceStmtM(node);
        case 0x13: return ReduceStmtN(node);
        case 0x14: return ReduceStmtO(node);
        case 0x15: return ReduceStmtP(node);
        case 0x16: return ReduceStmtQ(node);
        case 0x17: return ReduceStmtR(node);
        case 0x18: return ReduceStmtS(node);
        case 0x19: return ReduceStmtT(node);
        case 0x1A: return ReduceStmtU(node);
        case 0x1B: return ReduceStmtV(node);
        case 0x1C: return ReduceAssignment(node);
        case 0x1D: return ReduceSelfAssignmentA(node);
        case 0x1E: return ReduceSelfAssignmentB(node);
        case 0x1F: return ReduceSelfAssignmentC(node);
        case 0x20: return ReduceSelfAssignmentD(node);
        case 0x21: return ReduceSelfAssignmentE(node);
        case 0x22: return ReduceSelfAssignmentF(node);
        case 0x23: return ReduceFunctionDef(node);
        case 0x24: return ReduceFunctionDeclA(node);
        case 0x25: return ReduceFunctionDeclB(node);
        case 0x26: return ReduceClass(node);
        case 0x27: return ReduceParametersA(node);
        case 0x28: return ReduceParametersB(node);
        case 0x29: return ReduceParametersC(node);
        case 0x2A: return ReduceParamDeclA(node);
        case 0x2B: return ReduceParamDeclB(node);
        case 0x2C: return ReduceIf(node);
        case 0x2D: return ReduceElseifA(node);
        case 0x2E: return ReduceElseifB(node);
        case 0x2F: return ReduceElseifC(node);
        case 0x30: return ReduceForLoop(node);
        case 0x31: return ReduceStepA(node);
        case 0x32: return ReduceStepB(node);
        case 0x33: return ReduceForEach(node);
        case 0x34: return ReduceWhileLoop(node);
        case 0x35: return ReduceDoWhile(node);
        case 0x36: return ReduceLetBlock(node);
        case 0x37: return ReduceBindingsA(node);
        case 0x38: return ReduceBindingsB(node);
        case 0x39: return ReduceTryBlock(node);
        case 0x3A: return ReduceCatchBlockA(node);
        case 0x3B: return ReduceCatchBlockB(node);
        case 0x3C: return ReduceLValueA(node);
        case 0x3D: return ReduceLValueB(node);
        case 0x3E: return ReduceLValueC(node);
        case 0x3F: return ReduceLValueD(node);
        case 0x40: return ReduceExpr(node);
        case 0x41: return ReduceConditionA(node);
        case 0x42: return ReduceConditionB(node);
        case 0x43: return ReduceConditionC(node);
        case 0x44: return ReduceLogicA(node);
        case 0x45: return ReduceLogicB(node);
        case 0x46: return ReduceComparisonA(node);
        case 0x47: return ReduceComparisonB(node);
        case 0x48: return ReduceComparisonC(node);
        case 0x49: return ReduceComparisonD(node);
        case 0x4A: return ReduceComparisonE(node);
        case 0x4B: return ReduceComparisonF(node);
        case 0x4C: return ReduceComparisonG(node);
        case 0x4D: return ReduceComparisonH(node);
        case 0x4E: return ReduceComparisonI(node);
        case 0x4F: return ReduceArithmeticA(node);
        case 0x50: return ReduceArithmeticB(node);
        case 0x51: return ReduceArithmeticC(node);
        case 0x52: return ReduceTermA(node);
        case 0x53: return ReduceTermB(node);
        case 0x54: return ReduceTermC(node);
        case 0x55: return ReduceTermD(node);
        case 0x56: return ReduceFactorA(node);
        case 0x57: return ReduceFactorB(node);
        case 0x58: return ReduceFactorC(node);
        case 0x59: return ReduceFactorD(node);
        case 0x5A: return ReduceFinalA(node);
        case 0x5B: return ReduceFinalB(node);
        case 0x5C: return ReduceFinalC(node);
        case 0x5D: return ReduceFinalD(node);
        case 0x5E: return ReduceFinalE(node);
        case 0x5F: return ReduceFinalF(node);
        case 0x60: return ReduceFinalG(node);
        case 0x61: return ReduceFinalH(node);
        case 0x62: return ReduceReferenceA(node);
        case 0x63: return ReduceReferenceB(node);
        case 0x64: return ReduceReferenceC(node);
        case 0x65: return ReduceReferenceD(node);
        case 0x66: return ReduceArgumentsA(node);
        case 0x67: return ReduceArgumentsB(node);
        case 0x68: return ReduceObjectA(node);
        case 0x69: return ReduceObjectB(node);
        case 0x6A: return ReduceObjectC(node);
        case 0x6B: return ReduceArrayInitA(node);
        case 0x6C: return ReduceArrayInitB(node);
        case 0x6D: return ReduceDictionaryInitA(node);
        case 0x6E: return ReduceDictionaryInitB(node);
        case 0x6F: return ReduceBooleanA(node);
        case 0x70: return ReduceBooleanB(node);
    default:
        printf("Unknown production %i.\n", node->production);
        return 1;
    }
}
