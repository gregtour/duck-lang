/* auto-generated compiler stubs */
#include "lr_parser.h"
#include "interpreter.h"
#include "duck.h"


#ifndef _DEBUG
#define Assert(x)                   ;
#define AssertS(x,message)           ;
/*#define CompilerError(message)       ;*/
#else
/* AssertS(0, message) */
extern void CLAssert(unsigned int condition, const char* message, const char* source, int lineNumber);
#define Assert(x)                   CLAssert((int)(x), NULL, __FILE__, __LINE__);
#define AssertS(x, message)         CLAssert((int)(x), (message), __FILE__, __LINE__);
#endif


#ifdef _DEBUG
void CLAssert(unsigned int condition, const char* message, const char* source, int lineNumber)
{
	if (!condition)
	{
		printf("\nAssert failed %s:%i.\n", source, lineNumber);
		if (message) { printf("Error: %s\n\n", message); }
		getchar();
		exit(0);
	}
}
#endif


/* production stubs */

/* 1. <program> -> <stmtlist> */
int ReduceProgram(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* stmtlist1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(stmtlist1));

	return error;
}

/* 2. <stmtlist> -> <stmt> <stmtlist> */
int ReduceStmtlistA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* stmt1 = node->children[0];
	SYNTAX_TREE* stmtlist1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(stmt1));
	error = (error ? error : InterpretNode(stmtlist1));

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
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(identifier_list1));

	return error;
}

/* 5. <identifier-list> -> <identifier> */
int ReduceIdentifierListB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* identifier1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));

	return error;
}

/* 6. <stmt> -> import <identifier-list> <endl> */
int ReduceStmtA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* identifier_list1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(identifier_list1));

	return error;
}

/* 7. <stmt> -> require <identifier-list> <endl> */
int ReduceStmtB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* identifier_list1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(identifier_list1));

	return error;
}

/* 8. <stmt> -> include <string> <endl> */
int ReduceStmtC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* string1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(string1));

	return error;
}

/* 9. <stmt> -> <expr> <endl> */
int ReduceStmtD(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* expr1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(expr1));

	return error;
}

/* 10. <stmt> -> <endl> */
int ReduceStmtE(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);

	int error = 0;

	return error;
}

/* 11. <stmt> -> global <identifier-list> */
int ReduceStmtF(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* identifier_list1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(identifier_list1));

	return error;
}

/* 12. <stmt> -> local <identifier-list> */
int ReduceStmtG(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* identifier_list1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(identifier_list1));

	return error;
}

/* 13. <stmt> -> <assignment> <endl> */
int ReduceStmtH(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* assignment1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(assignment1));

	return error;
}

/* 14. <stmt> -> global <assignment> <endl> */
int ReduceStmtI(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* assignment1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(assignment1));

	return error;
}

/* 15. <stmt> -> local <assignment> <endl> */
int ReduceStmtJ(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* assignment1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(assignment1));

	return error;
}

/* 16. <stmt> -> static <assignment> <endl> */
int ReduceStmtK(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* assignment1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(assignment1));

	return error;
}

/* 17. <stmt> -> <self-assignment> <endl> */
int ReduceStmtL(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* self_assignment1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(self_assignment1));

	return error;
}

/* 18. <stmt> -> <function-def> <endl> */
int ReduceStmtM(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* function_def1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(function_def1));

	return error;
}

/* 19. <stmt> -> global <function-def> <endl> */
int ReduceStmtN(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* function_def1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(function_def1));

	return error;
}

/* 20. <stmt> -> local <function-def> <endl> */
int ReduceStmtO(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* function_def1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(function_def1));

	return error;
}

/* 21. <stmt> -> static <function-def> <endl> */
int ReduceStmtP(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* function_def1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(function_def1));

	return error;
}

/* 22. <stmt> -> <if> <endl> */
int ReduceStmtQ(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* if1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(if1));

	return error;
}

/* 23. <stmt> -> <for-loop> <endl> */
int ReduceStmtR(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* for_loop1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(for_loop1));

	return error;
}

/* 24. <stmt> -> <for-each> <endl> */
int ReduceStmtS(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* for_each1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(for_each1));

	return error;
}

/* 25. <stmt> -> <while-loop> <endl> */
int ReduceStmtT(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* while_loop1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(while_loop1));

	return error;
}

/* 26. <stmt> -> <do-while> <endl> */
int ReduceStmtU(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* do_while1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(do_while1));

	return error;
}

/* 27. <stmt> -> <let-block> <endl> */
int ReduceStmtV(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* let_block1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(let_block1));

	return error;
}

/* 28. <stmt> -> <try-block> <endl> */
int ReduceStmtW(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* try_block1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(try_block1));

	return error;
}

/* 29. <stmt> -> <class> <endl> */
int ReduceStmtX(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* class1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(class1));

	return error;
}

/* 30. <stmt> -> return <endl> */
int ReduceStmtY(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);

	int error = 0;

	return error;
}

/* 31. <stmt> -> return <expr> <endl> */
int ReduceStmtZ(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* expr1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(expr1));

	return error;
}

/* 32. <stmt> -> break <endl> */
int ReduceStmtAA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);

	int error = 0;

	return error;
}

/* 33. <stmt> -> continue <endl> */
int ReduceStmtBA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);

	int error = 0;

	return error;
}

/* 34. <stmt> -> throw <expr> <endl> */
int ReduceStmtCA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* expr1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(expr1));

	return error;
}

/* 35. <stmt> -> call , cc <reference> <endl> */
int ReduceStmtDA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 5);
	SYNTAX_TREE* reference1 = node->children[3];

	int error = 0;
	error = (error ? error : InterpretNode(reference1));

	return error;
}

/* 36. <assignment> -> <l-value> = <condition> */
int ReduceAssignment(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* l_value1 = node->children[0];
	SYNTAX_TREE* condition1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(l_value1));
	error = (error ? error : InterpretNode(condition1));

	return error;
}

/* 37. <self-assignment> -> <l-value> ++ */
int ReduceSelfAssignmentA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* l_value1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(l_value1));

	return error;
}

/* 38. <self-assignment> -> <l-value> -- */
int ReduceSelfAssignmentB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* l_value1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(l_value1));

	return error;
}

/* 39. <self-assignment> -> <l-value> += <arithmetic> */
int ReduceSelfAssignmentC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* l_value1 = node->children[0];
	SYNTAX_TREE* arithmetic1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(l_value1));
	error = (error ? error : InterpretNode(arithmetic1));

	return error;
}

/* 40. <self-assignment> -> <l-value> -= <arithmetic> */
int ReduceSelfAssignmentD(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* l_value1 = node->children[0];
	SYNTAX_TREE* arithmetic1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(l_value1));
	error = (error ? error : InterpretNode(arithmetic1));

	return error;
}

/* 41. <self-assignment> -> <l-value> *= <arithmetic> */
int ReduceSelfAssignmentE(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* l_value1 = node->children[0];
	SYNTAX_TREE* arithmetic1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(l_value1));
	error = (error ? error : InterpretNode(arithmetic1));

	return error;
}

/* 42. <self-assignment> -> <l-value> /= <arithmetic> */
int ReduceSelfAssignmentF(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* l_value1 = node->children[0];
	SYNTAX_TREE* arithmetic1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(l_value1));
	error = (error ? error : InterpretNode(arithmetic1));

	return error;
}

/* 43. <function-def> -> func <function-decl> */
int ReduceFunctionDef(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* function_decl1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(function_decl1));

	return error;
}

/* 44. <function-decl> -> <identifier> <parameters> <endl> <stmtlist> end */
int ReduceFunctionDeclA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 5);
	SYNTAX_TREE* identifier1 = node->children[0];
	SYNTAX_TREE* parameters1 = node->children[1];
	SYNTAX_TREE* stmtlist1 = node->children[3];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(parameters1));
	error = (error ? error : InterpretNode(stmtlist1));

	return error;
}

/* 45. <function-decl> -> <string> <parameters> <endl> <stmtlist> end */
int ReduceFunctionDeclB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 5);
	SYNTAX_TREE* string1 = node->children[0];
	SYNTAX_TREE* parameters1 = node->children[1];
	SYNTAX_TREE* stmtlist1 = node->children[3];

	int error = 0;
	error = (error ? error : InterpretNode(string1));
	error = (error ? error : InterpretNode(parameters1));
	error = (error ? error : InterpretNode(stmtlist1));

	return error;
}

/* 46. <class> -> class <identifier> <opt-extends> <parameters> <endl> <stmtlist> end */
int ReduceClass(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 7);
	SYNTAX_TREE* identifier1 = node->children[1];
	SYNTAX_TREE* opt_extends1 = node->children[2];
	SYNTAX_TREE* parameters1 = node->children[3];
	SYNTAX_TREE* stmtlist1 = node->children[5];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(opt_extends1));
	error = (error ? error : InterpretNode(parameters1));
	error = (error ? error : InterpretNode(stmtlist1));

	return error;
}

/* 47. <parameters> -> ( ) */
int ReduceParametersA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);

	int error = 0;

	return error;
}

/* 48. <parameters> -> ( <param-decl> ) */
int ReduceParametersB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* param_decl1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(param_decl1));

	return error;
}

/* 49. <parameters> -> */
int ReduceParametersC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 0);

	int error = 0;

	return error;
}

/* 50. <param-decl> -> <identifier> */
int ReduceParamDeclA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* identifier1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));

	return error;
}

/* 51. <param-decl> -> <identifier> , <param-decl> */
int ReduceParamDeclB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* identifier1 = node->children[0];
	SYNTAX_TREE* param_decl1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(param_decl1));

	return error;
}

/* 52. <opt-extends> -> : <identifier-list> */
int ReduceOptExtendsA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* identifier_list1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(identifier_list1));

	return error;
}

/* 53. <opt-extends> -> */
int ReduceOptExtendsB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 0);

	int error = 0;

	return error;
}

/* 54. <if> -> if <condition> then <endl> <stmtlist> <elseif> */
int ReduceIf(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 6);
	SYNTAX_TREE* condition1 = node->children[1];
	SYNTAX_TREE* stmtlist1 = node->children[4];
	SYNTAX_TREE* elseif1 = node->children[5];

	int error = 0;
	error = (error ? error : InterpretNode(condition1));
	error = (error ? error : InterpretNode(stmtlist1));
	error = (error ? error : InterpretNode(elseif1));

	return error;
}

/* 55. <elseif> -> else <endl> <stmtlist> endif */
int ReduceElseifA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 4);
	SYNTAX_TREE* stmtlist1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(stmtlist1));

	return error;
}

/* 56. <elseif> -> else <if> */
int ReduceElseifB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* if1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(if1));

	return error;
}

/* 57. <elseif> -> endif */
int ReduceElseifC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);

	int error = 0;

	return error;
}

/* 58. <for-loop> -> for <identifier> = <arithmetic> to <arithmetic> <step> */
int ReduceForLoop(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 7);
	SYNTAX_TREE* identifier1 = node->children[1];
	SYNTAX_TREE* arithmetic1 = node->children[3];
	SYNTAX_TREE* arithmetic2 = node->children[5];
	SYNTAX_TREE* step1 = node->children[6];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(arithmetic1));
	error = (error ? error : InterpretNode(arithmetic2));
	error = (error ? error : InterpretNode(step1));

	return error;
}

/* 59. <step> -> step <arithmetic> do <endl> <stmtlist> loop */
int ReduceStepA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 6);
	SYNTAX_TREE* arithmetic1 = node->children[1];
	SYNTAX_TREE* stmtlist1 = node->children[4];

	int error = 0;
	error = (error ? error : InterpretNode(arithmetic1));
	error = (error ? error : InterpretNode(stmtlist1));

	return error;
}

/* 60. <step> -> do <endl> <stmtlist> loop */
int ReduceStepB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 4);
	SYNTAX_TREE* stmtlist1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(stmtlist1));

	return error;
}

/* 61. <for-each> -> for <identifier> in <expr> do <endl> <stmtlist> loop */
int ReduceForEach(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 8);
	SYNTAX_TREE* identifier1 = node->children[1];
	SYNTAX_TREE* expr1 = node->children[3];
	SYNTAX_TREE* stmtlist1 = node->children[6];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(expr1));
	error = (error ? error : InterpretNode(stmtlist1));

	return error;
}

/* 62. <while-loop> -> while <condition> do <endl> <stmtlist> loop */
int ReduceWhileLoop(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 6);
	SYNTAX_TREE* condition1 = node->children[1];
	SYNTAX_TREE* stmtlist1 = node->children[4];

	int error = 0;
	error = (error ? error : InterpretNode(condition1));
	error = (error ? error : InterpretNode(stmtlist1));

	return error;
}

/* 63. <do-while> -> do <endl> <stmtlist> loop while <condition> */
int ReduceDoWhile(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 6);
	SYNTAX_TREE* stmtlist1 = node->children[2];
	SYNTAX_TREE* condition1 = node->children[5];

	int error = 0;
	error = (error ? error : InterpretNode(stmtlist1));
	error = (error ? error : InterpretNode(condition1));

	return error;
}

/* 64. <let-block> -> let <bindings> begin <endl> <stmtlist> end */
int ReduceLetBlock(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 6);
	SYNTAX_TREE* bindings1 = node->children[1];
	SYNTAX_TREE* stmtlist1 = node->children[4];

	int error = 0;
	error = (error ? error : InterpretNode(bindings1));
	error = (error ? error : InterpretNode(stmtlist1));

	return error;
}

/* 65. <bindings> -> <identifier> = <expr> , <bindings> */
int ReduceBindingsA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 5);
	SYNTAX_TREE* identifier1 = node->children[0];
	SYNTAX_TREE* expr1 = node->children[2];
	SYNTAX_TREE* bindings1 = node->children[4];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(expr1));
	error = (error ? error : InterpretNode(bindings1));

	return error;
}

/* 66. <bindings> -> <identifier> = <expr> , <endl> <bindings> */
int ReduceBindingsB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 6);
	SYNTAX_TREE* identifier1 = node->children[0];
	SYNTAX_TREE* expr1 = node->children[2];
	SYNTAX_TREE* bindings1 = node->children[5];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(expr1));
	error = (error ? error : InterpretNode(bindings1));

	return error;
}

/* 67. <bindings> -> <identifier> = <expr> */
int ReduceBindingsC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* identifier1 = node->children[0];
	SYNTAX_TREE* expr1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(expr1));

	return error;
}

/* 68. <bindings> -> <identifier> = <expr> <endl> */
int ReduceBindingsD(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 4);
	SYNTAX_TREE* identifier1 = node->children[0];
	SYNTAX_TREE* expr1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(expr1));

	return error;
}

/* 69. <try-block> -> try <endl> <stmtlist> <catch-block> */
int ReduceTryBlock(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 4);
	SYNTAX_TREE* stmtlist1 = node->children[2];
	SYNTAX_TREE* catch_block1 = node->children[3];

	int error = 0;
	error = (error ? error : InterpretNode(stmtlist1));
	error = (error ? error : InterpretNode(catch_block1));

	return error;
}

/* 70. <catch-block> -> catch <l-value> <endl> <stmtlist> done */
int ReduceCatchBlockA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 5);
	SYNTAX_TREE* l_value1 = node->children[1];
	SYNTAX_TREE* stmtlist1 = node->children[3];

	int error = 0;
	error = (error ? error : InterpretNode(l_value1));
	error = (error ? error : InterpretNode(stmtlist1));

	return error;
}

/* 71. <catch-block> -> done */
int ReduceCatchBlockB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);

	int error = 0;

	return error;
}

/* 72. <l-value> -> <identifier> */
int ReduceLValueA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* identifier1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));

	return error;
}

/* 73. <l-value> -> ( <l-value> ) */
int ReduceLValueB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* l_value1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(l_value1));

	return error;
}

/* 74. <l-value> -> <reference> . <identifier> */
int ReduceLValueC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* reference1 = node->children[0];
	SYNTAX_TREE* identifier1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(reference1));
	error = (error ? error : InterpretNode(identifier1));

	return error;
}

/* 75. <l-value> -> <reference> [ <expr> ] */
int ReduceLValueD(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 4);
	SYNTAX_TREE* reference1 = node->children[0];
	SYNTAX_TREE* expr1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(reference1));
	error = (error ? error : InterpretNode(expr1));

	return error;
}

/* 76. <expr> -> <condition> */
int ReduceExpr(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* condition1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(condition1));

	return error;
}

/* 77. <condition> -> <condition> and <logic> */
int ReduceConditionA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* condition1 = node->children[0];
	SYNTAX_TREE* logic1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(condition1));
	error = (error ? error : InterpretNode(logic1));

	return error;
}

/* 78. <condition> -> <condition> or <logic> */
int ReduceConditionB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* condition1 = node->children[0];
	SYNTAX_TREE* logic1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(condition1));
	error = (error ? error : InterpretNode(logic1));

	return error;
}

/* 79. <condition> -> <logic> */
int ReduceConditionC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* logic1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(logic1));

	return error;
}

/* 80. <logic> -> not <comparison> */
int ReduceLogicA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* comparison1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(comparison1));

	return error;
}

/* 81. <logic> -> <comparison> */
int ReduceLogicB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* comparison1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(comparison1));

	return error;
}

/* 82. <comparison> -> <comparison> == <arithmetic> */
int ReduceComparisonA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* comparison1 = node->children[0];
	SYNTAX_TREE* arithmetic1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(comparison1));
	error = (error ? error : InterpretNode(arithmetic1));

	return error;
}

/* 83. <comparison> -> <comparison> != <arithmetic> */
int ReduceComparisonB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* comparison1 = node->children[0];
	SYNTAX_TREE* arithmetic1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(comparison1));
	error = (error ? error : InterpretNode(arithmetic1));

	return error;
}

/* 84. <comparison> -> <comparison> < <arithmetic> */
int ReduceComparisonC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* comparison1 = node->children[0];
	SYNTAX_TREE* arithmetic1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(comparison1));
	error = (error ? error : InterpretNode(arithmetic1));

	return error;
}

/* 85. <comparison> -> <comparison> > <arithmetic> */
int ReduceComparisonD(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* comparison1 = node->children[0];
	SYNTAX_TREE* arithmetic1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(comparison1));
	error = (error ? error : InterpretNode(arithmetic1));

	return error;
}

/* 86. <comparison> -> <comparison> <= <arithmetic> */
int ReduceComparisonE(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* comparison1 = node->children[0];
	SYNTAX_TREE* arithmetic1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(comparison1));
	error = (error ? error : InterpretNode(arithmetic1));

	return error;
}

/* 87. <comparison> -> <comparison> >= <arithmetic> */
int ReduceComparisonF(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* comparison1 = node->children[0];
	SYNTAX_TREE* arithmetic1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(comparison1));
	error = (error ? error : InterpretNode(arithmetic1));

	return error;
}

/* 88. <comparison> -> <final> is <reference> */
int ReduceComparisonG(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* final1 = node->children[0];
	SYNTAX_TREE* reference1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(final1));
	error = (error ? error : InterpretNode(reference1));

	return error;
}

/* 89. <comparison> -> <final> is not <reference> */
int ReduceComparisonH(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 4);
	SYNTAX_TREE* final1 = node->children[0];
	SYNTAX_TREE* reference1 = node->children[3];

	int error = 0;
	error = (error ? error : InterpretNode(final1));
	error = (error ? error : InterpretNode(reference1));

	return error;
}

/* 90. <comparison> -> <arithmetic> */
int ReduceComparisonI(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* arithmetic1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(arithmetic1));

	return error;
}

/* 91. <arithmetic> -> <arithmetic> + <term> */
int ReduceArithmeticA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* arithmetic1 = node->children[0];
	SYNTAX_TREE* term1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(arithmetic1));
	error = (error ? error : InterpretNode(term1));

	return error;
}

/* 92. <arithmetic> -> <arithmetic> - <term> */
int ReduceArithmeticB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* arithmetic1 = node->children[0];
	SYNTAX_TREE* term1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(arithmetic1));
	error = (error ? error : InterpretNode(term1));

	return error;
}

/* 93. <arithmetic> -> <term> */
int ReduceArithmeticC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* term1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(term1));

	return error;
}

/* 94. <term> -> <term> * <factor> */
int ReduceTermA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* term1 = node->children[0];
	SYNTAX_TREE* factor1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(term1));
	error = (error ? error : InterpretNode(factor1));

	return error;
}

/* 95. <term> -> <term> / <factor> */
int ReduceTermB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* term1 = node->children[0];
	SYNTAX_TREE* factor1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(term1));
	error = (error ? error : InterpretNode(factor1));

	return error;
}

/* 96. <term> -> <term> mod <factor> */
int ReduceTermC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* term1 = node->children[0];
	SYNTAX_TREE* factor1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(term1));
	error = (error ? error : InterpretNode(factor1));

	return error;
}

/* 97. <term> -> <factor> */
int ReduceTermD(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* factor1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(factor1));

	return error;
}

/* 98. <factor> -> - <factor> */
int ReduceFactorA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* factor1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(factor1));

	return error;
}

/* 99. <factor> -> ! <factor> */
int ReduceFactorB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* factor1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(factor1));

	return error;
}

/* 100. <factor> -> * <factor> */
int ReduceFactorC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* factor1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(factor1));

	return error;
}

/* 101. <factor> -> & <factor> */
int ReduceFactorD(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* factor1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(factor1));

	return error;
}

/* 102. <factor> -> <final> */
int ReduceFactorE(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* final1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(final1));

	return error;
}

/* 103. <final> -> ( <expr> ) */
int ReduceFinalA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* expr1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(expr1));

	return error;
}

/* 104. <final> -> <boolean> */
int ReduceFinalB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* boolean1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(boolean1));

	return error;
}

/* 105. <final> -> <object> */
int ReduceFinalC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* object1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(object1));

	return error;
}

/* 106. <final> -> <reference> */
int ReduceFinalD(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* reference1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(reference1));

	return error;
}

/* 107. <final> -> new <reference> */
int ReduceFinalE(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* reference1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(reference1));

	return error;
}

/* 108. <final> -> <integer> */
int ReduceFinalF(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* integer1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(integer1));

	return error;
}

/* 109. <final> -> <float> */
int ReduceFinalG(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* float1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(float1));

	return error;
}

/* 110. <final> -> <string> */
int ReduceFinalH(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* string1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(string1));

	return error;
}

/* 111. <reference> -> <l-value> */
int ReduceReferenceA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* l_value1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(l_value1));

	return error;
}

/* 112. <reference> -> this */
int ReduceReferenceB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);

	int error = 0;

	return error;
}

/* 113. <reference> -> <reference> ( ) */
int ReduceReferenceC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* reference1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(reference1));

	return error;
}

/* 114. <reference> -> <reference> ( <arguments> ) */
int ReduceReferenceD(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 4);
	SYNTAX_TREE* reference1 = node->children[0];
	SYNTAX_TREE* arguments1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(reference1));
	error = (error ? error : InterpretNode(arguments1));

	return error;
}

/* 115. <arguments> -> <arguments> , <expr> */
int ReduceArgumentsA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* arguments1 = node->children[0];
	SYNTAX_TREE* expr1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(arguments1));
	error = (error ? error : InterpretNode(expr1));

	return error;
}

/* 116. <arguments> -> <expr> */
int ReduceArgumentsB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);
	SYNTAX_TREE* expr1 = node->children[0];

	int error = 0;
	error = (error ? error : InterpretNode(expr1));

	return error;
}

/* 117. <object> -> [ ] */
int ReduceObjectA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);

	int error = 0;

	return error;
}

/* 118. <object> -> <endl> [ <array-begin> */
int ReduceObjectB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* array_begin1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(array_begin1));

	return error;
}

/* 119. <object> -> [ <array-begin> */
int ReduceObjectC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* array_begin1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(array_begin1));

	return error;
}

/* 120. <array-begin> -> <endl> <expr> <object-array> */
int ReduceArrayBeginA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* expr1 = node->children[1];
	SYNTAX_TREE* object_array1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(expr1));
	error = (error ? error : InterpretNode(object_array1));

	return error;
}

/* 121. <array-begin> -> <expr> <object-array> */
int ReduceArrayBeginB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* expr1 = node->children[0];
	SYNTAX_TREE* object_array1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(expr1));
	error = (error ? error : InterpretNode(object_array1));

	return error;
}

/* 122. <object-array> -> , <endl> <expr> <object-array> */
int ReduceObjectArrayA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 4);
	SYNTAX_TREE* expr1 = node->children[2];
	SYNTAX_TREE* object_array1 = node->children[3];

	int error = 0;
	error = (error ? error : InterpretNode(expr1));
	error = (error ? error : InterpretNode(object_array1));

	return error;
}

/* 123. <object-array> -> , <expr> <object-array> */
int ReduceObjectArrayB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* expr1 = node->children[1];
	SYNTAX_TREE* object_array1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(expr1));
	error = (error ? error : InterpretNode(object_array1));

	return error;
}

/* 124. <object-array> -> <endl> ] */
int ReduceObjectArrayC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);

	int error = 0;

	return error;
}

/* 125. <object-array> -> ] */
int ReduceObjectArrayD(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);

	int error = 0;

	return error;
}

/* 126. <object> -> <endl> [ <dictionary-begin> */
int ReduceObjectD(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 3);
	SYNTAX_TREE* dictionary_begin1 = node->children[2];

	int error = 0;
	error = (error ? error : InterpretNode(dictionary_begin1));

	return error;
}

/* 127. <object> -> [ <dictionary-begin> */
int ReduceObjectE(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);
	SYNTAX_TREE* dictionary_begin1 = node->children[1];

	int error = 0;
	error = (error ? error : InterpretNode(dictionary_begin1));

	return error;
}

/* 128. <dictionary-begin> -> <endl> <identifier> : <expr> <object-dictionary> */
int ReduceDictionaryBeginA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 5);
	SYNTAX_TREE* identifier1 = node->children[1];
	SYNTAX_TREE* expr1 = node->children[3];
	SYNTAX_TREE* object_dictionary1 = node->children[4];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(expr1));
	error = (error ? error : InterpretNode(object_dictionary1));

	return error;
}

/* 129. <dictionary-begin> -> <identifier> : <expr> <object-dictionary> */
int ReduceDictionaryBeginB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 4);
	SYNTAX_TREE* identifier1 = node->children[0];
	SYNTAX_TREE* expr1 = node->children[2];
	SYNTAX_TREE* object_dictionary1 = node->children[3];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(expr1));
	error = (error ? error : InterpretNode(object_dictionary1));

	return error;
}

/* 130. <object-dictionary> -> , <endl> <identifier> : <expr> <object-dictionary> */
int ReduceObjectDictionaryA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 6);
	SYNTAX_TREE* identifier1 = node->children[2];
	SYNTAX_TREE* expr1 = node->children[4];
	SYNTAX_TREE* object_dictionary1 = node->children[5];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(expr1));
	error = (error ? error : InterpretNode(object_dictionary1));

	return error;
}

/* 131. <object-dictionary> -> , <identifier> : <expr> <object-dictionary> */
int ReduceObjectDictionaryB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 5);
	SYNTAX_TREE* identifier1 = node->children[1];
	SYNTAX_TREE* expr1 = node->children[3];
	SYNTAX_TREE* object_dictionary1 = node->children[4];

	int error = 0;
	error = (error ? error : InterpretNode(identifier1));
	error = (error ? error : InterpretNode(expr1));
	error = (error ? error : InterpretNode(object_dictionary1));

	return error;
}

/* 132. <object-dictionary> -> <endl> ] */
int ReduceObjectDictionaryC(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 2);

	int error = 0;

	return error;
}

/* 133. <object-dictionary> -> ] */
int ReduceObjectDictionaryD(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);

	int error = 0;

	return error;
}

/* 134. <boolean> -> true */
int ReduceBooleanA(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);

	int error = 0;

	return error;
}

/* 135. <boolean> -> false */
int ReduceBooleanB(SYNTAX_TREE* node)
{
	Assert(node->numChildren == 1);

	int error = 0;

	return error;
}


/* reduce one node */
int InterpretNode(SYNTAX_TREE* node)
{
	if (node == NULL || node->production == 0) {
		printf("Null production.\n");
		return 1;
	}

	line_error = node->line;
	failed_production = node;

#ifdef _UNITTEST
	if((++test_inst_count) == TEST_INST_LIMIT)
	{
		halting = 1;
		return -1;
	}
#endif

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
	case 0x1C: return ReduceStmtW(node);
	case 0x1D: return ReduceStmtX(node);
	case 0x1E: return ReduceStmtY(node);
	case 0x1F: return ReduceStmtZ(node);
	case 0x20: return ReduceStmtAA(node);
	case 0x21: return ReduceStmtBA(node);
	case 0x22: return ReduceStmtCA(node);
	case 0x23: return ReduceStmtDA(node);
	case 0x24: return ReduceAssignment(node);
	case 0x25: return ReduceSelfAssignmentA(node);
	case 0x26: return ReduceSelfAssignmentB(node);
	case 0x27: return ReduceSelfAssignmentC(node);
	case 0x28: return ReduceSelfAssignmentD(node);
	case 0x29: return ReduceSelfAssignmentE(node);
	case 0x2A: return ReduceSelfAssignmentF(node);
	case 0x2B: return ReduceFunctionDef(node);
	case 0x2C: return ReduceFunctionDeclA(node);
	case 0x2D: return ReduceFunctionDeclB(node);
	case 0x2E: return ReduceClass(node);
	case 0x2F: return ReduceParametersA(node);
	case 0x30: return ReduceParametersB(node);
	case 0x31: return ReduceParametersC(node);
	case 0x32: return ReduceParamDeclA(node);
	case 0x33: return ReduceParamDeclB(node);
	case 0x34: return ReduceOptExtendsA(node);
	case 0x35: return ReduceOptExtendsB(node);
	case 0x36: return ReduceIf(node);
	case 0x37: return ReduceElseifA(node);
	case 0x38: return ReduceElseifB(node);
	case 0x39: return ReduceElseifC(node);
	case 0x3A: return ReduceForLoop(node);
	case 0x3B: return ReduceStepA(node);
	case 0x3C: return ReduceStepB(node);
	case 0x3D: return ReduceForEach(node);
	case 0x3E: return ReduceWhileLoop(node);
	case 0x3F: return ReduceDoWhile(node);
	case 0x40: return ReduceLetBlock(node);
	case 0x41: return ReduceBindingsA(node);
	case 0x42: return ReduceBindingsB(node);
	case 0x43: return ReduceBindingsC(node);
	case 0x44: return ReduceBindingsD(node);
	case 0x45: return ReduceTryBlock(node);
	case 0x46: return ReduceCatchBlockA(node);
	case 0x47: return ReduceCatchBlockB(node);
	case 0x48: return ReduceLValueA(node);
	case 0x49: return ReduceLValueB(node);
	case 0x4A: return ReduceLValueC(node);
	case 0x4B: return ReduceLValueD(node);
	case 0x4C: return ReduceExpr(node);
	case 0x4D: return ReduceConditionA(node);
	case 0x4E: return ReduceConditionB(node);
	case 0x4F: return ReduceConditionC(node);
	case 0x50: return ReduceLogicA(node);
	case 0x51: return ReduceLogicB(node);
	case 0x52: return ReduceComparisonA(node);
	case 0x53: return ReduceComparisonB(node);
	case 0x54: return ReduceComparisonC(node);
	case 0x55: return ReduceComparisonD(node);
	case 0x56: return ReduceComparisonE(node);
	case 0x57: return ReduceComparisonF(node);
	case 0x58: return ReduceComparisonG(node);
	case 0x59: return ReduceComparisonH(node);
	case 0x5A: return ReduceComparisonI(node);
	case 0x5B: return ReduceArithmeticA(node);
	case 0x5C: return ReduceArithmeticB(node);
	case 0x5D: return ReduceArithmeticC(node);
	case 0x5E: return ReduceTermA(node);
	case 0x5F: return ReduceTermB(node);
	case 0x60: return ReduceTermC(node);
	case 0x61: return ReduceTermD(node);
	case 0x62: return ReduceFactorA(node);
	case 0x63: return ReduceFactorB(node);
	case 0x64: return ReduceFactorC(node);
	case 0x65: return ReduceFactorD(node);
	case 0x66: return ReduceFactorE(node);
	case 0x67: return ReduceFinalA(node);
	case 0x68: return ReduceFinalB(node);
	case 0x69: return ReduceFinalC(node);
	case 0x6A: return ReduceFinalD(node);
	case 0x6B: return ReduceFinalE(node);
	case 0x6C: return ReduceFinalF(node);
	case 0x6D: return ReduceFinalG(node);
	case 0x6E: return ReduceFinalH(node);
	case 0x6F: return ReduceReferenceA(node);
	case 0x70: return ReduceReferenceB(node);
	case 0x71: return ReduceReferenceC(node);
	case 0x72: return ReduceReferenceD(node);
	case 0x73: return ReduceArgumentsA(node);
	case 0x74: return ReduceArgumentsB(node);
	case 0x75: return ReduceObjectA(node);
	case 0x76: return ReduceObjectB(node);
	case 0x77: return ReduceObjectC(node);
	case 0x78: return ReduceArrayBeginA(node);
	case 0x79: return ReduceArrayBeginB(node);
	case 0x7A: return ReduceObjectArrayA(node);
	case 0x7B: return ReduceObjectArrayB(node);
	case 0x7C: return ReduceObjectArrayC(node);
	case 0x7D: return ReduceObjectArrayD(node);
	case 0x7E: return ReduceObjectD(node);
	case 0x7F: return ReduceObjectE(node);
	case 0x80: return ReduceDictionaryBeginA(node);
	case 0x81: return ReduceDictionaryBeginB(node);
	case 0x82: return ReduceObjectDictionaryA(node);
	case 0x83: return ReduceObjectDictionaryB(node);
	case 0x84: return ReduceObjectDictionaryC(node);
	case 0x85: return ReduceObjectDictionaryD(node);
	case 0x86: return ReduceBooleanA(node);
	case 0x87: return ReduceBooleanB(node);
    default:
        printf("Unknown production %i.\n", node->production);
        return 1;
    }
}
