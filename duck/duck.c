/*
    Duck Programming Language
    Interpreter Productions
*/
// TODO: Rewrite in continuation passing style

#include "lr_parser.h"
#include "interpreter.h"
#include "arithmetic.h"
#include "memory.h"
#include "garbage.h"


/* 1. <program> -> <stmt list> */
int ReduceProgram(SYNTAX_TREE* node)
{
    SYNTAX_TREE* stmt_list1 = node->children[0];

    int error = 0;
    error = InterpretNode(stmt_list1);

    return error;
}

/* 2. <stmt list> -> <stmt> <stmt list> */
int ReduceStmtListA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* stmt1 = node->children[0];
    SYNTAX_TREE* stmt_list1 = node->children[1];

    int error = 0;
    if (halting == 0) {
        while (node->numChildren) 
        {
            if (returning == 0 &&
                breaking == 0 &&
                continuing == 0 &&
                error == 0 &&
                halting == 0)
            {
                error = InterpretNode(node->children[0]);
            } else {
                if (halting) {
                    returning = 1;
                    breaking = 1;
                }
                return error;
            }
            
            if (error == 0 && returning == 0)
            {
                if ((++gc_inst_count) == GC_COLLECT_LIMIT)
                {
                    gc_inst_count = 0;
                    gc_collect_count++;

                    CallGCTraceRoot(gGlobalContext, gLastExpression);
                }
            }
            
            node = node->children[1];
        }
    } else {
        returning = 1;
        breaking = 1;
    }
    return error;
}

/* 3. <stmt list> -> */
int ReduceStmtListB(SYNTAX_TREE* node)
{
    return 0;
}

/* 4. <identifier list> -> <identifier> , <identifier list> */
int ReduceIdentifierListA(SYNTAX_TREE* node)
{
    return 0;
}

/* 5. <identifier list> -> <identifier> */
int ReduceIdentifierListB(SYNTAX_TREE* node)
{
    return 0;
}

/* 6. <opt endl> -> <endl> */
int ReduceOptEndlA(SYNTAX_TREE* node)
{
    return 0;
}

/* 7. <opt endl> -> */
int ReduceOptEndlB(SYNTAX_TREE* node)
{
    return 0;
}

/* 8. <stmt> -> import <identifier list> <endl> */
int ReduceStmtA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier_list1 = node->children[1];

    int error = 0;

    while (identifier_list1)
    {
        SYNTAX_TREE* identifier1 = identifier_list1->children[0];

        /* import library */
        // change scope of [NameSpace] to global
        VALUE library = GetRecord(identifier1->string, gCurrentContext);
        
        if (library.type == VAL_REFERENCE)
        {
            CLOSURE* NameSpace = library.data.reference;
            PAIR* iterator = NameSpace->list;
            while (iterator)
            {
                StoreRecord(iterator->identifier, iterator->value, gGlobalContext);
                iterator = iterator->next;
            }
        }

        if (identifier_list1->numChildren == 3)
        {
            identifier_list1 = identifier_list1->children[2];
        }
        else
        {
            identifier_list1 = NULL;
        }
    }

    return error;
}

/* 9. <stmt> -> include <string> */
int ReduceStmtB(SYNTAX_TREE* node)
{
/*  if (node->numChildren != 2) return 9;
    SYNTAX_TREE* string1 = node->children[1];

    int error = 0;
    error = error || CompileNode(string1);

    return error; */
//  TODO: Should include the src of <string> by evaluating
//  the contents of a file
    return 0;
}


/* 10. <stmt> -> <endl> */
int ReduceStmtC(SYNTAX_TREE* node)
{
    int error = 0;

    return error;
}

/* 11. <stmt> -> <expr> <endl> */
int ReduceStmtD(SYNTAX_TREE* node)
{
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = InterpretNode(expr1);

    return error;
}

/* 12. <stmt> -> <assignment> <endl> */
int ReduceStmtE(SYNTAX_TREE* node)
{
    SYNTAX_TREE* assignment1 = node->children[0];

    int error = 0;
    error = InterpretNode(assignment1);

    return error;
}

/* 13. <stmt> -> <self assignment> <endl> */
int ReduceStmtF(SYNTAX_TREE* node)
{
    SYNTAX_TREE* self_assignment1 = node->children[0];

    int error = 0;
    error = InterpretNode(self_assignment1);

    return error;
}

/* 14. <stmt> -> <function def> <endl> */
int ReduceStmtG(SYNTAX_TREE* node)
{
    SYNTAX_TREE* function_def1 = node->children[0];

    int error = 0;
    error = InterpretNode(function_def1);

    return error;
}

/* 15. <stmt> -> <if> <endl> */
int ReduceStmtH(SYNTAX_TREE* node)
{
    SYNTAX_TREE* if1 = node->children[0];

    int error = 0;
    error = InterpretNode(if1);

    return error;
}

/* 16. <stmt> -> <for loop> <endl> */
int ReduceStmtI(SYNTAX_TREE* node)
{
    SYNTAX_TREE* for_loop1 = node->children[0];

    int error = 0;
    error = InterpretNode(for_loop1);

    return error;
}

/* 17. <stmt> -> <while loop> <endl> */
int ReduceStmtJ(SYNTAX_TREE* node)
{
    SYNTAX_TREE* while_loop1 = node->children[0];

    int error = 0;
    error = InterpretNode(while_loop1);

    return error;
}

/* 18. <stmt> -> <for each> <endl> */
int ReduceStmtK(SYNTAX_TREE* node)
{
    SYNTAX_TREE* for_each1 = node->children[0];

    int error = 0;
    error = InterpretNode(for_each1);

    return error;
}

/* 19. <stmt> -> <let block> <endl> */
int ReduceStmtL(SYNTAX_TREE* node)
{
    SYNTAX_TREE* let_block1 = node->children[0];

    int error = 0;
    error = InterpretNode(let_block1);

    return error;
}

/* 20. <stmt> -> <try block> <endl> */
int ReduceStmtM(SYNTAX_TREE* node)
{
    SYNTAX_TREE* try_block1 = node->children[0];

    int error = 0;
    error = InterpretNode(try_block1);

    return error;
}

/* 21. <stmt> -> return <expr> <endl> */
int ReduceStmtN(SYNTAX_TREE* node)
{
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = InterpretNode(expr1);

    returning = 1;
    continuing = 0;

    return error;
}

/* 22. <stmt> -> break <endl> */
int ReduceStmtO(SYNTAX_TREE* node)
{
    int error = 0;
    
    breaking = 1;
    
    return error;
}

/* 23. <stmt> -> continue <endl> */
int ReduceStmtP(SYNTAX_TREE* node)
{
    int error = 0;
    
    continuing = 1;
    
    return error;
}

/* 24. <stmt> -> throw <expr> <endl> */
int ReduceStmtQ(SYNTAX_TREE* node)
{
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = InterpretNode(expr1);

    // TODO: Implement exception handling

    return error;
}

/* 25. <stmt> -> <object def> <endl> */
int ReduceStmtR(SYNTAX_TREE* node)
{
    SYNTAX_TREE* object_def1 = node->children[0];

    int error = 0;
    error = InterpretNode(object_def1);

    return error;
}

/* 26. <assignment> -> <l-value> = <assignment> */
int ReduceAssignmentA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* assignment1 = node->children[2];

    int error = 0;
    error = InterpretNode(assignment1);
    VALUE expr = gLastExpression;
    if (error) return error;
    error = InterpretNode(l_value1);
    if (error) return error;

    if (array_indexing)
    {
        if (gLValueDictionary)
        {
            VALUE previous = HashGet(gLValueIndex, gLValueDictionary);
            HashStore(gLValueIndex, expr, gLValueDictionary);
            array_indexing = 0;
        } else {
            if (!gLValueStringReference.const_string &&
                expr.type == VAL_STRING)
            {
                int len, index;

                len = strlen(gLValueStringReference.data.string);
                index = gLValueIndex.data.primitive;

                if (index < len)
                {
                    //gLValueStringReference.data.string[index] = expr.data.string[0];
                }
            }
            array_indexing = 0;
        }
    }
    else
    {
        VALUE previous = GetRecord(gLValueIdentifier, gLValueContext);

        if (gLValueIndex.type == VAL_STRING &&
            gLValueIndex.const_string == 0)
        {
            gLValueIndex = CopyString(gLValueIndex);
        }

        StoreRecord(gLValueIdentifier, expr, gLValueContext);
    }

    gLastExpression = expr;

    return error;
}

/* 27. <assignment> -> <l-value> = <condition> */
int ReduceAssignmentB(SYNTAX_TREE* node)

{
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* condition1 = node->children[2];

    int error = 0;
    error = InterpretNode(condition1);
    VALUE expr = gLastExpression;
    if (error) return error;
    error = InterpretNode(l_value1);
    if (error) return error;
    
    if (array_indexing)
    {
        if (gLValueDictionary)
        {
            VALUE previous = HashGet(gLValueIndex, gLValueDictionary);
        
            if (gLValueIndex.type == VAL_STRING &&
                gLValueIndex.const_string == 0)
            {
                gLValueIndex = CopyString(gLValueIndex);
            }

            HashStore(gLValueIndex, expr, gLValueDictionary);
            array_indexing = 0;
        } else {
            if (!gLValueStringReference.const_string &&
                expr.type == VAL_STRING)
            {
                int len, index;

                len = strlen(gLValueStringReference.data.string);
                index = gLValueIndex.data.primitive;

                if (index < len)
                {
                    //gLValueStringReference.data.string[index] = expr.data.string[0];
                }
            }
            array_indexing = 0;
        }
    }
    else
    {
        VALUE previous = GetRecord(gLValueIdentifier, gLValueContext);
        StoreRecord(gLValueIdentifier, expr, gLValueContext);
    }

    gLastExpression = expr;

    return error;
}

/* 28. <self assignment> -> <l-value> += <arithmetic> */
int ReduceSelfAssignmentA(SYNTAX_TREE* node)
{
    // TODO: Implement plus equals
    return 28;
}

/* 29. <self assignment> -> <l-value> -= <arithmetic> */
int ReduceSelfAssignmentB(SYNTAX_TREE* node)
{
    // TODO: Implement minus equals
    return 29;
}

/* 30. <self assignment> -> <l-value> *= <arithmetic> */
int ReduceSelfAssignmentC(SYNTAX_TREE* node)
{
    // TODO: Implement times equals
    return 30;
}

/* 31. <self assignment> -> <l-value> /= <arithmetic> */
int ReduceSelfAssignmentD(SYNTAX_TREE* node)
{
    // TODO: Implement divide equals
    return 31;
}

/* 32. <function def> -> function <identifier> <parameters> <endl> <stmt list> end */
int ReduceFunctionDef(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* parameters1 = node->children[2];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;

    gParameterListing = NULL;
    error = InterpretNode(parameters1);

    // FUNCTIONS
    VALUE record;
    if (error == 0)
    {
        record.type = VAL_FUNCTION;
        record.data.function = (FUNCTION*)ALLOC(sizeof(FUNCTION));
        record.data.function->parameters = gParameterListing; // ??
        record.data.function->body = stmt_list1;

        record.data.function->closure = gCurrentContext;

        record.data.function->built_in = 0;
        record.data.function->functor = NULL;
        record.data.function->fn_name = identifier1->string;
        record.data.function->func_data = NULL;
        
        StoreRecord(identifier1->string, record, gCurrentContext);
        GCAddFunction(record.data.function, &gGCManager);
    }
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
    SYNTAX_TREE* param_decl1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(param_decl1);

    return error;
}

/* 36. <param decl> -> <identifier> */
int ReduceParamDeclA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;

    gParameterListing = (PAIR*)ALLOC(sizeof(PAIR));
    gParameterListing->identifier = identifier1->string;
    gParameterListing->value.type = VAL_NIL;
    gParameterListing->next = NULL;

    return error;
}

/* 37. <param decl> -> <param decl> , <identifier> */
int ReduceParamDeclB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* param_decl1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];

    int error = 0;
    error = InterpretNode(param_decl1);

    PAIR* last = gParameterListing;
    while (last->next)
    {
        last = last->next;

    }
    
    last->next = (PAIR*)ALLOC(sizeof(PAIR));
    last->next->identifier = identifier1->string;
    last->next->value.type = VAL_NIL;
    last->next->next = NULL;

    return error;
}

/* 38. <if> -> if <condition> then <endl> <stmt list> <else if> */
int ReduceIf(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];
    SYNTAX_TREE* else_if1 = node->children[5];

    int error = 0;
    error = InterpretNode(condition1);
    if (error == 0) {
        if (EvaluatesTrue(gLastExpression))
        {
            error = InterpretNode(stmt_list1);
        } else {
            error = InterpretNode(else_if1);
        }
    }

    return error;
}

/* 39. <else if> -> else <endl> <stmt list> end */
int ReduceElseIfA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* stmt_list1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(stmt_list1);

    return error;
}

/* 40. <else if> -> else <if> */
int ReduceElseIfB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* if1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(if1);

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
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* arithmetic1 = node->children[3];
    SYNTAX_TREE* arithmetic2 = node->children[5];
    SYNTAX_TREE* stmt_list1 = node->children[8];
    
    VALUE start, end;
    const char* id = identifier1->string;

    int error = 0;
    start.type = VAL_NIL;
    end.type = VAL_NIL;

    error = InterpretNode(arithmetic1);
    start = gLastExpression;
    
    if (error == 0) {
        error = InterpretNode(arithmetic2);
        end = gLastExpression;
    }

    if (start.type == VAL_FLOATING_POINT
       && end.type == VAL_FLOATING_POINT)
    {
        while (start.type == VAL_FLOATING_POINT
               && end.type == VAL_FLOATING_POINT
               && start.data.floatp <= end.data.floatp
               && error == 0
               && breaking == 0
               && returning == 0)
        {
            StoreRecord(id, start, gCurrentContext);
            error = InterpretNode(stmt_list1);
            if (breaking == 0)
            {
                continuing = 0;
                start.data.floatp = start.data.floatp + 1.0;
            }
        }
    }
    else if (start.type == VAL_PRIMITIVE
                && end.type == VAL_PRIMITIVE)
    {
        while (start.type == VAL_PRIMITIVE
               && end.type == VAL_PRIMITIVE
               && start.data.primitive <= end.data.primitive
               && error == 0
               && breaking == 0
               && returning == 0)
        {
            StoreRecord(id, start, gCurrentContext);
            error = InterpretNode(stmt_list1);
            if (breaking == 0)
            {
                continuing = 0;
                start.data.primitive++;
            }
        }
    }
    else
    {
        error = 42;
        breaking = 0;
        return error;
    }

    breaking = 0;

    return error;
}

/* 43. <for loop> -> for <identifier> = <arithmetic> to <arithmetic> step <arithmetic> do <endl> <stmt list> loop */
int ReduceForLoopB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* arithmetic1 = node->children[3];
    SYNTAX_TREE* arithmetic2 = node->children[5];
    SYNTAX_TREE* arithmetic3 = node->children[7];
    SYNTAX_TREE* stmt_list1 = node->children[10];

    
    VALUE start, end, step;
    const char* id = identifier1->string;

    int error = 0;
    start.type = VAL_NIL;
    end.type = VAL_NIL;

    error = InterpretNode(arithmetic1);
    start = gLastExpression;
    
    if (error == 0) {
        error = InterpretNode(arithmetic2);
        end = gLastExpression;
    }

    if (error == 0) {
        error = InterpretNode(arithmetic3);
        step = gLastExpression;
    }

    if (start.type == VAL_FLOATING_POINT
       && end.type == VAL_FLOATING_POINT
       && step.type == VAL_FLOATING_POINT)
    {
        while (start.type == VAL_FLOATING_POINT
               && end.type == VAL_FLOATING_POINT
               && start.data.floatp <= end.data.floatp
               && error == 0
               && breaking == 0
               && returning == 0)
        {
            StoreRecord(id, start, gCurrentContext);
            error = InterpretNode(stmt_list1);
            if (breaking == 0)
            {
                continuing = 0;
                start.data.floatp = start.data.floatp + step.data.floatp;
            }
        }
    }
    else if (start.type == VAL_PRIMITIVE
                && end.type == VAL_PRIMITIVE
                && step.type == VAL_PRIMITIVE)
    {
        while (start.type == VAL_PRIMITIVE
               && end.type == VAL_PRIMITIVE
               && start.data.primitive <= end.data.primitive
               && error == 0
               && breaking == 0
               && returning == 0)
        {
            StoreRecord(id, start, gCurrentContext);
            error = InterpretNode(stmt_list1);
            if (breaking == 0)
            {
                continuing = 0;
                start.data.primitive = start.data.primitive + step.data.primitive;
            }
        }
    }
    else
    {
        error = 43;
        breaking = 0;
        return error;
    }

    breaking = 0;

    return error;
}

/* 44. <for each> -> for <identifier> in <expr> do <endl> <stmt list> loop */
int ReduceForEach(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* expr1 = node->children[3];
    SYNTAX_TREE* stmt_list1 = node->children[6];

    int error = 0;
/*  error = error || CompileNode(identifier1);
    error = error || CompileNode(expr1);
    error = error || CompileNode(stmt_list1); */
//  TODO: Implement for-each loop

    return error;
}

/* 45. <while loop> -> while <condition> do <endl> <stmt list> loop */
int ReduceWhileLoop(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;
    error = InterpretNode(condition1);
    while (gLastExpression.type != VAL_NIL
           && EvaluatesTrue(gLastExpression)
           && error == 0
           && breaking == 0
           && returning == 0)
    {
        error = InterpretNode(stmt_list1);
        if (error == 0 && returning == 0) {
            error = InterpretNode(condition1);
        }
        continuing = 0;
    }

    breaking = 0;

    return error;
}

/* 46. <let block> -> let <bindings> begin <endl> <stmt list> end */
int ReduceLetBlock(SYNTAX_TREE* node)
{
    SYNTAX_TREE* bindings1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;
    error = InterpretNode(bindings1);
    if (error == 0)
    {
        error = InterpretNode(stmt_list1);
    }
    else
    {
        error = 46;
    }

    // TODO: Implement let expressions

    return error;
}

/* 47. <bindings> -> <identifier> = <expr> , <bindings> */
int ReduceBindingsA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];
    SYNTAX_TREE* bindings1 = node->children[4];

    int error = 0;
    error = InterpretNode(expr1);
    if (error == 0)
    {
        error = InterpretNode(bindings1);
    }

    return error;
}

/* 48. <bindings> -> <identifier> = <expr> */
int ReduceBindingsB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = InterpretNode(expr1);

    return error;
}

/* 49. <try block> -> try <endl> <stmt list> <catch block> complete */
int ReduceTryBlock(SYNTAX_TREE* node)
{
    SYNTAX_TREE* stmt_list1 = node->children[2];
    SYNTAX_TREE* catch_block1 = node->children[3];

    int error = 0;
    error = InterpretNode(stmt_list1);
    if (error != 0)
    {
        error = InterpretNode(catch_block1);
    }

    // TODO: Implement exceptions, try-catch blocks

    return error;
}

/* 50. <catch block> -> catch <identifier> <endl> <stmt list> */
int ReduceCatchBlockA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[3];

    int error = 0;
    error = error || InterpretNode(stmt_list1);

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
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* object_body1 = node->children[3];

    int error = 0;

    error = InterpretNode(object_body1);

    // TODO: Implement classes and objects

    return error;
}

/* 53. <object body> -> static <identifier> <endl> <object body> */
int ReduceObjectBodyA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* object_body1 = node->children[3];

    int error = 0;

    // TODO: Implement static class members

    error = InterpretNode(object_body1);

    return error;
}

/* 54. <object body> -> static <identifier> = <expr> <endl> <object body> */
int ReduceObjectBodyB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* expr1 = node->children[3];
    SYNTAX_TREE* object_body1 = node->children[5];

    int error = 0;

    // TODO: Implement static class members with default values

    error = InterpretNode(object_body1);

    return error;
}

/* 55. <object body> -> <stmt> <object body> */
int ReduceObjectBodyC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* stmt1 = node->children[0];
    SYNTAX_TREE* object_body1 = node->children[1];

    int error = 0;

    // TODO: Implement classes and objects

    error = InterpretNode(object_body1);

    return error;
}

/* 56. <object body> -> operator [ ] ( <identifier> ) <endl> <stmt list> end <endl> <object body> */
int ReduceObjectBodyD(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[4];
    SYNTAX_TREE* stmt_list1 = node->children[7];
    SYNTAX_TREE* object_body1 = node->children[10];

    int error = 0;

    // TODO: Implement operator overloading on the [] operator

    error = InterpretNode(object_body1);

    return error;
}

/* 57. <object body> -> operator + ( <identifier> , <identifier> ) <endl> <stmt list> end <endl> <object body> */
int ReduceObjectBodyE(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[3];
    SYNTAX_TREE* identifier2 = node->children[5];
    SYNTAX_TREE* stmt_list1 = node->children[8];
    SYNTAX_TREE* object_body1 = node->children[11];

    int error = 0;

    // TODO: Implement operator overloading on the + operator

    error = InterpretNode(object_body1);

    return error;
}

/* 58. <object body> -> operator - ( <identifier> , <identifier> ) <endl> <stmt list> end <endl> <object body> */
int ReduceObjectBodyF(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[3];
    SYNTAX_TREE* identifier2 = node->children[5];
    SYNTAX_TREE* stmt_list1 = node->children[8];
    SYNTAX_TREE* object_body1 = node->children[11];

    int error = 0;

    // TODO: Implement operator overloading on the - operator

    error = InterpretNode(object_body1);

    return error;
}

/* 59. <object body> -> operator * ( <identifier> , <identifier> ) <endl> <stmt list> end <endl> <object body> */
int ReduceObjectBodyG(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[3];
    SYNTAX_TREE* identifier2 = node->children[5];
    SYNTAX_TREE* stmt_list1 = node->children[8];
    SYNTAX_TREE* object_body1 = node->children[11];

    int error = 0;

    // TODO: Implement operator overloading on the * operator

    error = InterpretNode(object_body1);

    return error;
}

/* 60. <object body> -> operator / ( <identifier> , <identifier> ) <endl> <stmt list> end <endl> <object body> */
int ReduceObjectBodyH(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[3];
    SYNTAX_TREE* identifier2 = node->children[5];
    SYNTAX_TREE* stmt_list1 = node->children[8];
    SYNTAX_TREE* object_body1 = node->children[11];

    int error = 0;

    // TODO: Implement operator overloading on the division operator

    error = InterpretNode(object_body1);

    return error;
}

/* 61. <object body> -> static <function def> <endl> <object body> */
int ReduceObjectBodyI(SYNTAX_TREE* node)
{
    SYNTAX_TREE* function_def1 = node->children[1];
    SYNTAX_TREE* object_body1 = node->children[3];

    int error = 0;

    // TODO: Implement static methods for classes

    error = InterpretNode(object_body1);

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
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;

    array_indexing = 0;
    gLValueIdentifier = identifier1->string;
    gLValueContext = gCurrentContext;
    gLValueIndex.type = VAL_NIL;
    gLValueIndex.data.primitive = 0;
    gLValueDictionary = NULL;

    return error;
}

/* 64. <l-value> -> ( <l-value> ) */
int ReduceLValueB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* l_value1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(l_value1);

    return error;
}

/* 65. <l-value> -> <reference> . <identifier> */
int ReduceLValueC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];

    int error = 0;
    error = InterpretNode(reference1);
    if (error) return error;

    if (gLastExpression.type == VAL_REFERENCE)
    {
        array_indexing = 0;
        gLValueIdentifier = identifier1->string;
        gLValueContext = gLastExpression.data.reference;
        gLValueIndex.type = VAL_NIL;
        gLValueIndex.data.primitive = 0;
        gLValueDictionary = NULL;
    }
    else if (gLastExpression.type == VAL_DICTIONARY)
    {
        // error ?
//        error = 1;
        array_indexing = 1;
        gLValueIndex.type = VAL_STRING;
        gLValueIndex.data.string = identifier1->string;
        gLValueIndex.const_string = 1;
        gLValueDictionary = gLastExpression.data.dictionary;
        gLValueIdentifier = NULL;
        gLValueContext = NULL;
    }
    else
    {
        error = 65;
        array_indexing = 0;
        gLValueIdentifier = NULL;
        gLValueContext = NULL;
        gLValueIndex.type = VAL_NIL;
        gLValueIndex.data.primitive = 0;
        gLValueDictionary = NULL;
        failed_production = node;
    }

    return error;
}

/* 66. <l-value> -> <reference> [ <expr> ] */
int ReduceLValueD(SYNTAX_TREE* node)
{
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    VALUE reference;
    VALUE index;

    int error = 0;
    error = InterpretNode(reference1);
    reference = gLastExpression;
    if (error) return error;
    error = InterpretNode(expr1);
    index = gLastExpression;
    if (error) return error;
    
    if (reference.type == VAL_REFERENCE &&
        (index.type == VAL_STRING || index.type == VAL_PRIMITIVE))
    {
        if (index.type == VAL_PRIMITIVE ||
            index.type == VAL_FLOATING_POINT)
        {
            VALUE ns;
            ns.type = VAL_STRING;
            ns.data.string = "";
            index = Concat(index, ns);
        }

        gLValueIdentifier = index.data.string;
        gLValueContext = reference.data.reference;
        gLValueIndex.type = VAL_NIL;
        gLValueIndex.data.primitive = 0;
        gLValueDictionary = NULL;
        array_indexing = 0;
    }
    else if (reference.type == VAL_STRING &&
             index.type == VAL_PRIMITIVE)
    {
        gLValueStringReference = reference;
        gLValueIndex = index;
        gLValueDictionary = NULL;
        gLValueIdentifier = NULL;
        array_indexing = 1;
    }
    else if (reference.type == VAL_DICTIONARY)
    {
        gLValueIndex = index;
        gLValueDictionary = reference.data.dictionary;
        gLValueIdentifier = NULL;
        gLValueContext = NULL;
        array_indexing = 1;
    }
    else
    {
        error = 66;
        gLValueIdentifier = NULL;
        gLValueContext = NULL;
        gLValueIndex.type = VAL_NIL;
        gLValueIndex.data.primitive = 0;
        gLValueDictionary = NULL;
        array_indexing = 0;
        failed_production = node;
    }

    return error;
}

/* 67. <l-value> -> this */
int ReduceLValueE(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 67;

    int error = 0;

    // TODO: Implement local pointers

    return error;
}

/* 68. <expr> -> <condition> */
int ReduceExpr(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[0];

    int error = 0;
    error = InterpretNode(condition1);

    return error;
}

/* 69. <condition> -> <condition> and <logic> */
int ReduceConditionA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    VALUE condition;

    int error = 0;
    error = InterpretNode(condition1);
    condition = gLastExpression;
    if (error) return error;

    /* AND */
    if (EvaluatesTrue(condition)) {

        error = InterpretNode(logic1);

        /* fall-through */

        if (error) return error;
    } else {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 0;
    }

    return error;
}

/* 70. <condition> -> <condition> or <logic> */
int ReduceConditionB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    VALUE condition;
    VALUE logic;

    int error = 0;
    error = InterpretNode(condition1);
    condition = gLastExpression;
    if (error) return error;

    if (EvaluatesTrue(condition)) {
        gLastExpression = condition;
        return error;
    }

    error = InterpretNode(logic1);
    logic = gLastExpression;
    if (error) return error;

    /* OR */
    gLastExpression = logic;

    return error;
}

/* 71. <condition> -> <logic> */
int ReduceConditionC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* logic1 = node->children[0];

    int error = 0;
    error = InterpretNode(logic1);

    return error;
}

/* 72. <logic> -> not <comparison> */
int ReduceLogicA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[1];

    int error = 0;
    error = InterpretNode(comparison1);
    
    if (gLastExpression.type == VAL_PRIMITIVE)
    {
        gLastExpression.data.primitive = gLastExpression.data.primitive ? 0 : 1;
    }
    else if (gLastExpression.type == VAL_NIL)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 1;
    }
    else
    {
        // opposite of string, function, reference or nil is nil
        gLastExpression.type = VAL_NIL;
        gLastExpression.data.primitive = 0;
    }

    return error;
}

/* 73. <logic> -> <comparison> */
int ReduceLogicB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];

    int error = 0;
    error = InterpretNode(comparison1);

    return error;
}

/* 74. <comparison> -> <comparison> == <arithmetic> */
int ReduceComparisonA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    VALUE comparison;
    VALUE arithmetic;

    int error = 0;
    error = InterpretNode(comparison1);
    comparison = gLastExpression;
    if (error) return error;
    error = InterpretNode(arithmetic1);
    arithmetic = gLastExpression;
    if (error) return error;

    /* EQUAL */
    gLastExpression = CompareEquality(comparison, arithmetic);
    
    return error;
}

/* 75. <comparison> -> <comparison> != <arithmetic> */
int ReduceComparisonB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    VALUE comparison;
    VALUE arithmetic;

    int error = 0;
    error = InterpretNode(comparison1);
    comparison = gLastExpression;
    if (error) return error;
    error = InterpretNode(arithmetic1);
    arithmetic = gLastExpression;
    if (error) return error;
    
    /* NOT EQUAL */
    gLastExpression = CompareInequality(comparison, arithmetic);

    return error;
}

/* 76. <comparison> -> <comparison> < <arithmetic> */
int ReduceComparisonC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    VALUE comparison;
    VALUE arithmetic;

    int error = 0;
    error = InterpretNode(comparison1);
    comparison = gLastExpression;
    if (error) return error;
    error = InterpretNode(arithmetic1);
    arithmetic = gLastExpression;
    if (error) return error;

    /* LESS THAN */
    gLastExpression = CompareLessThan(comparison, arithmetic);

    return error;
}

/* 77. <comparison> -> <comparison> > <arithmetic> */
int ReduceComparisonD(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    VALUE comparison;
    VALUE arithmetic;

    int error = 0;
    error = InterpretNode(comparison1);
    comparison = gLastExpression;
    if (error) return error;
    error = InterpretNode(arithmetic1);
    arithmetic = gLastExpression;
    if (error) return error;

    /* GREATER THAN */
    gLastExpression = CompareGreaterThan(comparison, arithmetic);

    return error;
}

/* 78. <comparison> -> <comparison> <= <arithmetic> */
int ReduceComparisonE(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    VALUE comparison;
    VALUE arithmetic;

    int error = 0;
    error = InterpretNode(comparison1);
    comparison = gLastExpression;
    if (error) return error;
    error = InterpretNode(arithmetic1);
    arithmetic = gLastExpression;
    if (error) return error;

    /* LESS-THAN-OR-EQUAL */
    gLastExpression = CompareLessThanOrEqual(comparison, arithmetic);

    return error;
}

/* 79. <comparison> -> <comparison> >= <arithmetic> */
int ReduceComparisonF(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    VALUE comparison;
    VALUE arithmetic;

    int error = 0;
    error = InterpretNode(comparison1);
    comparison = gLastExpression;
    if (error) return error;
    error = InterpretNode(arithmetic1);
    arithmetic = gLastExpression;
    if (error) return error;
    
    /* GREATER-THAN-OR-EQUAL */
    gLastExpression = CompareGreaterThanOrEqual(comparison, arithmetic);

    return error;
}

/* 80. <comparison> -> <comparison> is <arithmetic> */
int ReduceComparisonG(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    VALUE comparison;
    VALUE arithmetic;

    int error = 0;
    error = InterpretNode(comparison1);
    comparison = gLastExpression;
    if (error) return error;
    error = InterpretNode(arithmetic1);
    arithmetic = gLastExpression;
    if (error) return error;

    /* EQUAL */
    gLastExpression = CompareEquality(comparison, arithmetic);

    // XX: Check equality?

    return error;
}

/* 81. <comparison> -> <arithmetic> */
int ReduceComparisonH(SYNTAX_TREE* node)
{
    SYNTAX_TREE* arithmetic1 = node->children[0];

    int error = 0;
    error = InterpretNode(arithmetic1);

    return error;
}

/* 82. <arithmetic> -> <arithmetic> + <term> */
int ReduceArithmeticA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    VALUE arithmetic;
    VALUE term;

    int error = 0;
    error = InterpretNode(arithmetic1);
    arithmetic = gLastExpression;
    gLastExpression.type = VAL_NIL;
    if (error) return error;
    error = InterpretNode(term1);
    term = gLastExpression;
    if (error) return error;

    /* add */
    if (arithmetic.type == VAL_STRING || term.type == VAL_STRING)
    {
        gLastExpression = Concat(arithmetic, term);
    }
    else
    {
        gLastExpression = Add(arithmetic, term);
    }

    // TODO: Implement operator overloaded addition

    return error;
}

/* 83. <arithmetic> -> <arithmetic> - <term> */
int ReduceArithmeticB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    VALUE arithmetic;
    VALUE term;

    int error = 0;
    error = InterpretNode(arithmetic1);
    arithmetic = gLastExpression;
    if (error) return error;
    error = InterpretNode(term1);
    term = gLastExpression;
    if (error) return error;

    /* subtract */
    gLastExpression = Subtract(arithmetic, term);

    // TODO: Implement operator overloaded subtraction

    return error;
}

/* 84. <arithmetic> -> <term> */
int ReduceArithmeticC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* term1 = node->children[0];

    int error = 0;
    error = InterpretNode(term1);

    return error;
}

/* 85. <term> -> <term> * <factor> */
int ReduceTermA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    VALUE term;
    VALUE factor;

    int error = 0;
    error = InterpretNode(term1);
    term = gLastExpression;
    if (error) return error;
    error = InterpretNode(factor1);
    factor = gLastExpression;
    if (error) return error;

    /* multiplication */
    gLastExpression = Multiply(term, factor);

    return error;
}

/* 86. <term> -> <term> / <factor> */
int ReduceTermB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    VALUE term;
    VALUE factor;

    int error = 0;
    error = InterpretNode(term1);
    term = gLastExpression;
    if (error) return error;
    error = InterpretNode(factor1);
    factor = gLastExpression;
    if (error) return error;
    
    /* division */
    gLastExpression = Divide(term, factor);

    return error;
}

/* 87. <term> -> <term> mod <factor> */
int ReduceTermC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    VALUE term;
    VALUE factor;

    int error = 0;
    error = InterpretNode(term1);
    term = gLastExpression;
    if (error) return error;
    error = InterpretNode(factor1);
    factor = gLastExpression;
    if (error) return error;
    
    /* modulus */
    gLastExpression = Modulus(term, factor);

    return error;
}

/* 88. <term> -> <factor> */
int ReduceTermD(SYNTAX_TREE* node)
{
    SYNTAX_TREE* factor1 = node->children[0];

    int error = 0;
    error = InterpretNode(factor1);

    return error;
}

/* 89. <factor> -> - <factor> */
int ReduceFactorA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* factor1 = node->children[1];

    int error = 0;
    error = InterpretNode(factor1);
    
    /* negate */
    if (gLastExpression.type == VAL_PRIMITIVE)
    {
        gLastExpression.data.primitive = -gLastExpression.data.primitive;
    }
    else if (gLastExpression.type == VAL_FLOATING_POINT)
    {
        gLastExpression.data.floatp = -gLastExpression.data.floatp;
    }
    else
    {
        // opposite of string, function, reference or nil is nil
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 90. <factor> -> ! <factor> */
int ReduceFactorB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* factor1 = node->children[1];

    int error = 0;
    error = InterpretNode(factor1);
    
    /* Not */
    if (gLastExpression.type == VAL_PRIMITIVE)
    {
        gLastExpression.data.primitive = !gLastExpression.data.primitive;
    }
    else if (gLastExpression.type == VAL_NIL)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 1;
    }
    else
    {
        // opposite of string, function, reference or nil is nil
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 91. <factor> -> <final> */
int ReduceFactorC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* final1 = node->children[0];

    int error = 0;
    error = InterpretNode(final1);

    return error;
}

/* 92. <final> -> ( <expr> ) */
int ReduceFinalA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = InterpretNode(expr1);

    return error;
}

/* 93. <final> -> <boolean> */
int ReduceFinalB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* boolean1 = node->children[0];

    int error = 0;
    error = InterpretNode(boolean1);

    return error;
}

/* 94. <final> -> <integer> */
int ReduceFinalC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* integer1 = node->children[0];

    int error = 0;

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = atoll(integer1->string);

    return error;
}

/* 95. <final> -> <float> */
int ReduceFinalD(SYNTAX_TREE* node)
{
    SYNTAX_TREE* float1 = node->children[0];
    
    int error = 0;

    gLastExpression.type = VAL_FLOATING_POINT;
    gLastExpression.data.floatp = atof(float1->string);
    
    return error;
}

/* 96. <final> -> <string> */
int ReduceFinalE(SYNTAX_TREE* node)
{
    SYNTAX_TREE* string1 = node->children[0];
    
    int error = 0;

    gLastExpression.type = VAL_STRING;
    gLastExpression.data.string = string1->string;
    gLastExpression.const_string = 1;
    
    return error;
}

/* 97. <final> -> <object> */
int ReduceFinalF(SYNTAX_TREE* node)
{
    SYNTAX_TREE* object1 = node->children[0];

    int error = 0;
    error = InterpretNode(object1);

    return error;
}

/* 98. <final> -> <reference> */
int ReduceFinalG(SYNTAX_TREE* node)
{
    SYNTAX_TREE* reference1 = node->children[0];

    int error = 0;
    error = InterpretNode(reference1);

    return error;
}

/* 99. <reference> -> <l-value> */
int ReduceReferenceA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* l_value1 = node->children[0];
    int len;
    int error = 0;
    char* str;
    int index;
    error = InterpretNode(l_value1);
    
    if (array_indexing)
    {
        if (gLValueDictionary)
        {
            gLastExpression = HashGet(gLValueIndex, gLValueDictionary);
            array_indexing = 0;
        } else {
            gLastExpression.type = VAL_STRING;
            len = strlen(gLValueStringReference.data.string);
            index = gLValueIndex.data.primitive;
            str = (char*)malloc(sizeof(char) * 2);

            if (index >= 0 && index < len) {
                str[0] = gLValueStringReference.data.string[index];
            } else {
                str[0] = '\0';
            }
            str[1] = '\0';
            gLastExpression.data.string = str;

            GCAddString(str, &gGCManager);
            array_indexing = 0;
        }
    }
    else
    {
        gLastExpression = GetRecord(gLValueIdentifier, gLValueContext);
    }

    return error;
}

/* 100. <reference> -> <reference> ( ) */
int ReduceReferenceB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* reference1 = node->children[0];

    VALUE function;

    int error = 0;

    error = InterpretNode(reference1);
    function = gLastExpression;
    if (error) return error;

    if (function.type == VAL_FUNCTION)
    {
        CLOSURE* func_context;
        CLOSURE* current;
    
        // create new context
        func_context = (CLOSURE*)ALLOC(sizeof(CLOSURE));
        func_context->list = NULL;
        func_context->parent = function.data.function->closure;
        
        current = gCurrentContext;
        gCurrentContext = func_context;

        PushExecutionStack(current);
        GCAddContext(func_context, &gGCManager);

        // store params
        
        // call function
        if (function.data.function->built_in) {
            error = function.data.function->functor(0, 0l);
        } else {
            error = InterpretNode(function.data.function->body);
        }

        // check for error
        if (error) {
            PushCallStack(&gStackTrace, function.data.function/*->fn_name*/);
        } else {
        }

        // return with same context
        PopExecutionStack();
        gCurrentContext = current;

        returning = 0;
    }
    else
    {
        // calling non-function
        error = 12345;
        failed_production = node;
    }

    return error;
}

/* 101. <reference> -> <reference> ( <arguments> ) */
int ReduceReferenceC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* arguments1 = node->children[2];
    int argument_count;

    VALUE function;

    int error = 0;

    error = InterpretNode(reference1);
    function = gLastExpression;
    if (error) return error;

    if (function.type == VAL_FUNCTION)
    {
        PAIR* param;
        PAIR* arg;
        PAIR* last;
        PAIR* arg_next;
        CLOSURE* func_context;
        CLOSURE* current;        
       
        // evaluate arguments
        error = InterpretNode(arguments1);
        param = function.data.function->parameters;
        arg = gArgumentEvaluation;

        if (error) return error;

        // create new context
        func_context = (CLOSURE*)ALLOC(sizeof(CLOSURE));
        func_context->list = NULL;
        func_context->parent = function.data.function->closure;
        current = gCurrentContext;
        gCurrentContext = func_context;

        PushExecutionStack(current);
        GCAddContext(func_context, &gGCManager);

        // store params
        // store arguments in the function's closure
        last = NULL;
        arg_next;
        argument_count = 0;
        while (param && arg)
        {
            gLastExpression.type = VAL_NIL;
            if (last)
            {
                last->next = (PAIR*)ALLOC(sizeof(PAIR));
                last = last->next;
            }
            else
            {
                gCurrentContext->list = last = (PAIR*)ALLOC(sizeof(PAIR));
            }

            last->identifier = param->identifier;
            last->value = arg->value;
            last->next = NULL;

            argument_count++;       

            arg_next = arg->next;
            DEALLOC(arg);
            param = param->next;
            arg = arg_next;
        }
        
        // call function
        if (function.data.function->built_in) {
            error = function.data.function->functor(0, 0l);
        } else {
            error = InterpretNode(function.data.function->body);
        }

        // check for error
        if (error) {
            PushCallStack(&gStackTrace, function.data.function/*->fn_name*/);
        } else {
        }

        // return with same context
        PopExecutionStack();
        gCurrentContext = current;
        returning = 0;
    }
    else
    {
        // calling non-function
        error = 12345;
        failed_production = node;
    }

    return error;
}

/* 102. <arguments> -> <arguments> , <expr> */
int ReduceArgumentsA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* arguments1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    PAIR* arguments;
    PAIR* list;

    int error = 0;
    error = InterpretNode(arguments1);
    
    arguments = gArgumentEvaluation;
    
    error = error ? error : InterpretNode(expr1);
    
    list = arguments;
    while (list->next) {
        list = list->next;
    }
    list->next = (PAIR*)ALLOC(sizeof(PAIR));
    list->next->identifier = NULL;
    list->next->value = gLastExpression;
    list->next->next = NULL;

    
    gArgumentEvaluation = arguments;

    return error;
}

/* 103. <arguments> -> <expr> */
int ReduceArgumentsB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = InterpretNode(expr1);
    
    gArgumentEvaluation = (PAIR*)ALLOC(sizeof(PAIR));
    gArgumentEvaluation->identifier = NULL;
    gArgumentEvaluation->value = gLastExpression;
    gArgumentEvaluation->next = NULL;

    return error;
}

/* 104. <object> -> [ ] */
int ReduceObjectA(SYNTAX_TREE* node)
{
    int error = 0;

    gLastExpression.type = VAL_DICTIONARY;
    gLastExpression.data.dictionary = CreateHashTable();
    GCAddDictionary(gLastExpression.data.dictionary, &gGCManager);
    gLastExpression.data.dictionary->ref_count = 1;

    return error;
}

/* 105. <object> -> [ <array init> ] */
int ReduceObjectB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* array_init1 = node->children[1];

    int error = 0;
    error = InterpretNode(array_init1);
    
    gLastExpression.type = VAL_DICTIONARY;
    gLastExpression.data.dictionary = gDictionaryInit;
    GCAddDictionary(gDictionaryInit, &gGCManager);
    gLastExpression.data.dictionary->ref_count = 1;

    return error;
}

/* 106. <object> -> [ <dictionary init> ] */
int ReduceObjectC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* dictionary_init1 = node->children[1];

    int error = 0;
    error = InterpretNode(dictionary_init1);

    gLastExpression.type = VAL_DICTIONARY;
    gLastExpression.data.dictionary = gDictionaryInit;
    GCAddDictionary(gDictionaryInit, &gGCManager);
    gLastExpression.data.dictionary->ref_count = 1;

    return error;
}

/* 107. <object> -> { } */
int ReduceObjectD(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 107;

    int error = 0;

    gLastExpression.type = VAL_DICTIONARY;
    gLastExpression.data.dictionary = CreateHashTable();
    GCAddDictionary(gLastExpression.data.dictionary, &gGCManager);
    gLastExpression.data.dictionary->ref_count = 1;

    return error;
}

/* 108. <object> -> { <dictionary init> } */
int ReduceObjectE(SYNTAX_TREE* node)
{
    SYNTAX_TREE* dictionary_init1 = node->children[1];

    int error = 0;
    error = InterpretNode(dictionary_init1);

    gLastExpression.type = VAL_DICTIONARY;
    gLastExpression.data.dictionary = gDictionaryInit;
    GCAddDictionary(gDictionaryInit, &gGCManager);
    gLastExpression.data.dictionary->ref_count = 1;

    return error;
}

/* 109. <object> -> new <identifier> */
int ReduceObjectF(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[1];

    int error = 0;

    // TODO: Implement allocation of new objects

    return error;
}

/* 110. <object> -> new <identifier> ( ) */
int ReduceObjectG(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[1];

    int error = 0;

    // TODO: Implement allocation of new objects through constructor

    return error;
}

/* 111. <object> -> new <identifier> ( <arguments> ) */
int ReduceObjectH(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* arguments1 = node->children[3];

    int error = 0;
    //error = error || CompileNode(arguments1);

    // TODO: Implement allocation of new objects through constructor

    return error;
}

/* 112. <array init> -> <array init> , <expr> */
int ReduceArrayInitA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* array_init1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;

    error = InterpretNode(array_init1);

    HASH_TABLE* dictionary = gDictionaryInit;
    long int index = gArrayIndex;
    
    error = (error ? error : InterpretNode(expr1));
    VALUE expr = gLastExpression;

    VALUE key;
    key.type = VAL_PRIMITIVE;
    key.data.primitive = index;
    HashStore(key, expr, dictionary);
    
    gArrayIndex = ++index;
    gDictionaryInit = dictionary;

    return error;
}

/* 113. <array init> -> <expr> */
int ReduceArrayInitB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = InterpretNode(expr1);
    VALUE expr = gLastExpression;
    
    gDictionaryInit = CreateHashTable();
    gArrayIndex = 0;
    
    VALUE index;
    index.type = VAL_PRIMITIVE;
    index.data.primitive = gArrayIndex;

    HashStore(index, expr, gDictionaryInit);
    gArrayIndex++;

    return error;
}

/* 114. <dictionary init> -> <dictionary init> , <identifier> : <expr> */
int ReduceDictionaryInitA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* dictionary_init1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];
    SYNTAX_TREE* expr1 = node->children[4];

    int error = 0;
    error = InterpretNode(dictionary_init1);

    HASH_TABLE* dictionary = gDictionaryInit;

    error = error ? error : InterpretNode(expr1);
    VALUE expr = gLastExpression;

    VALUE key;
    key.type = VAL_STRING;
    key.data.string = identifier1->string;
    key.const_string = 1;

    VALUE dupe = HashGet(key, dictionary);
    if (dupe.type != VAL_NIL) 
    {
        error = 114;
        return error;
    }

    HashStore(key, expr, dictionary);
    gDictionaryInit = dictionary;

    return error;
}

/* 115. <dictionary init> -> <identifier> : <expr> */
int ReduceDictionaryInitB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = InterpretNode(expr1);
    VALUE expr = gLastExpression;

    gDictionaryInit = CreateHashTable();

    VALUE key;
    key.type = VAL_STRING;
    key.data.string = identifier1->string;
    key.const_string = 1;

    HashStore(key, expr, gDictionaryInit);

    return error;
}

/* 116. <boolean> -> true */
int ReduceBooleanA(SYNTAX_TREE* node)
{
    int error = 0;

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = 1;

    return error;
}

/* 117. <boolean> -> false */
int ReduceBooleanB(SYNTAX_TREE* node)
{
    int error = 0;
    
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = 0;

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

