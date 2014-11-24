/* auto-generated compiler stubs */
#include "lr_parser.h"
#include "interpreter.h"
#include "memory.h"

/* type stuff */

double TypeFloat(VALUE value)
{
    if (value.type == VAL_PRIMITIVE) {
        return (double)value.data.primitive;
    } else if (value.type == VAL_FLOATING_POINT) {
        return value.data.floatp;
    } else if (value.type == VAL_STRING) {
        return atof(value.data.string);
    } else {
        return 0.0;
    }
}

int TypeInt(VALUE value)
{
    if (value.type == VAL_PRIMITIVE) {
        return value.data.primitive;
    } else if (value.type == VAL_FLOATING_POINT) {
        return (int)value.data.floatp;
    } else if (value.type == VAL_STRING) {
        return atoi(value.data.string);
    } else {
        return 0;
    }
}


/* production stubs */

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
        while (node->numChildren) {
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

            node = node->children[1];
        }

        //error = error || InterpretNode(stmt_list1);
    } else {
        returning = 1;
        breaking = 1;
    }
    return error;
}

/* 3. <stmt list> -> */
int ReduceStmtListB(SYNTAX_TREE* node)
{
    int error = 0;

    return error;
}

/* 4. <stmt> -> import <identifier> */
int ReduceStmtA(SYNTAX_TREE* node)
{
    int error = 0;
    //printf("@import %s\n", node->children[1]->string);

    /* import library */
    // change scope of [namespace] to global
    VALUE library = GetRecord(node->children[1]->string, gCurrentContext);
    if (library.type == VAL_REFERENCE)
    {
        CONTEXT* namespace = library.data.reference;
        PAIR* iterator = namespace->list;
        while (iterator)
        {
            StoreRecord(iterator->identifier, iterator->value, gGlobalContext);
            iterator = iterator->next;
        }
    }

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;

    return error;
}

/* 5. <stmt> -> call <reference> */
int ReduceStmtB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* reference1 = node->children[1];

    int error = 0;
    error = InterpretNode(reference1);
	VALUE function = gLastExpression;
    
    if (function.type == VAL_FUNCTION
        && error == 0)
    {
        // create new context
        CONTEXT* current = gCurrentContext;
        gCurrentContext = (CONTEXT*)ALLOC(sizeof(CONTEXT));
        gCurrentContext->list = NULL;
        gCurrentContext->ref_count = 1;
        gCurrentContext->parent = function.data.function->closure;
        CONTEXT* func_context = gCurrentContext;
        
        if (function.data.function->built_in) {
            error = function.data.function->functor(0);
        } else {
            error = InterpretNode(function.data.function->body);
        }

        // free calling context
        func_context->ref_count--;
        if (func_context->ref_count == 0)
            FreeContext(func_context);
        
        // return with same context
        gCurrentContext = current;
        returning = 0;
    }
    else
    {
        error = 12345;
    }

    return error;
}

/* 6. <stmt> -> <endl> */
int ReduceStmtC(SYNTAX_TREE* node)
{
    int error = 0;

    return error;
}

/* 7. <stmt> -> <expr> <endl> */
int ReduceStmtD(SYNTAX_TREE* node)
{
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = InterpretNode(expr1);

    return error;
}

/* 8. <stmt> -> <assignment> <endl> */
int ReduceStmtE(SYNTAX_TREE* node)
{
    SYNTAX_TREE* assignment1 = node->children[0];

    int error = 0;
    error = InterpretNode(assignment1);

    return error;
}

/* 9. <stmt> -> <function def> <endl> */
int ReduceStmtF(SYNTAX_TREE* node)
{
    SYNTAX_TREE* function_def1 = node->children[0];

    int error = 0;
    error = InterpretNode(function_def1);

    return error;
}

/* 10. <stmt> -> <if> <endl> */
int ReduceStmtG(SYNTAX_TREE* node)
{
    SYNTAX_TREE* if1 = node->children[0];

    int error = 0;
    error = InterpretNode(if1);

    if (returning == 0) 
    {
        gLastExpression.type = VAL_NIL;
        gLastExpression.data.primitive = 0;
    }

    return error;
}

/* 11. <stmt> -> <if else> <endl> */
int ReduceStmtH(SYNTAX_TREE* node)
{
    SYNTAX_TREE* if_else1 = node->children[0];

    int error = 0;
    error = InterpretNode(if_else1);

    if (returning == 0) 
    {
        gLastExpression.type = VAL_NIL;
        gLastExpression.data.primitive = 0;
    }

    return error;
}

/* 12. <stmt> -> <for loop> <endl> */
int ReduceStmtI(SYNTAX_TREE* node)
{
    SYNTAX_TREE* for_loop1 = node->children[0];

    int error = 0;
    error = InterpretNode(for_loop1);

    if (returning == 0) 
    {
        gLastExpression.type = VAL_NIL;
        gLastExpression.data.primitive = 0;
    }

    return error;
}

/* 13. <stmt> -> <while loop> <endl> */
int ReduceStmtJ(SYNTAX_TREE* node)
{
    SYNTAX_TREE* while_loop1 = node->children[0];

    int error = 0;
    error = InterpretNode(while_loop1);

    if (returning == 0) 
    {
        gLastExpression.type = VAL_NIL;
        gLastExpression.data.primitive = 0;
    }

    return error;
}

/* 14. <stmt> -> return <expr> <endl> */
int ReduceStmtK(SYNTAX_TREE* node)
{
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = InterpretNode(expr1);

    returning = 1;

    return error;
}

/* 15. <stmt> -> break <endl> */
int ReduceStmtL(SYNTAX_TREE* node)
{
    int error = 0;

    breaking = 1;

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;

    return error;
}

/* 16. <stmt> -> continue <endl> */
int ReduceStmtM(SYNTAX_TREE* node)
{
    int error = 0;
    
    continuing = 1;

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;

    return error;
}

/* 17. <function def> -> function <identifier> <parameters> <endl> <stmt list> end */
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
        if (gCurrentContext->ref_count > 0) {
            gCurrentContext->ref_count++;
        }
        record.data.function->ref_count = 1;
        record.data.function->built_in = 0;
        record.data.function->functor = NULL;
        StoreRecord(identifier1->string, record, gCurrentContext);

        gLastExpression = record;
    }
    return error;
}

/* 18. <parameters> -> */
int ReduceParametersA(SYNTAX_TREE* node)
{
    return 0;
}

/* 19. <parameters> -> ( ) */
int ReduceParametersB(SYNTAX_TREE* node)
{
    return 0;
}

/* 20. <parameters> -> ( <param decl> ) */
int ReduceParametersC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* param_decl1 = node->children[1];

    int error = 0;
    error = InterpretNode(param_decl1);

    return error;
}

/* 21. <param decl> -> <identifier> */
int ReduceParamDeclA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;

    gParameterListing = (PAIR*)ALLOCATE(sizeof(PAIR));
    gParameterListing->identifier = identifier1->string;
    gParameterListing->value.type = VAL_NIL;
    gParameterListing->next = NULL;

    return error;
}

/* 22. <param decl> -> <param decl> , <identifier> */
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
    
    last->next = (PAIR*)ALLOCATE(sizeof(PAIR));
    last->next->identifier = identifier1->string;
    last->next->value.type = VAL_NIL;
    last->next->next = NULL;

    return error;
}

/* 23. <if> -> if <condition> then <endl> <stmt list> end */
int ReduceIf(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;
    error = InterpretNode(condition1);
    if (error == 0) {
        if ((gLastExpression.type == VAL_PRIMITIVE
                && gLastExpression.data.primitive)
            || (gLastExpression.type != VAL_PRIMITIVE
                && gLastExpression.type != VAL_NIL))
        {
            error = InterpretNode(stmt_list1);
        }
    }

    return error;
}

/* 24. <if else> -> if <condition> then <endl> <stmt list> else <endl> <stmt list> end */
int ReduceIfElse(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];
    SYNTAX_TREE* stmt_list2 = node->children[7];

    int error = 0;
    error = InterpretNode(condition1);
    if (error == 0) {
        if ((gLastExpression.type == VAL_PRIMITIVE
                && gLastExpression.data.primitive)
            || (gLastExpression.type != VAL_PRIMITIVE
                && gLastExpression.type != VAL_NIL))
        {
            error = InterpretNode(stmt_list1);
        }
        else
        {
            error = InterpretNode(stmt_list2);
        }
    }

    return error;
}

/* 25. <for loop> -> for <identifier> = <arithmetic> to <arithmetic> do <endl> <stmt list> loop */
int ReduceForLoop(SYNTAX_TREE* node)
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
               && breaking == 0)
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
               && breaking == 0)
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
        printf("Error: Illegal for loop operands.\n");
    }
    breaking = 0;

    return error;
}

/* 26. <while loop> -> while <condition> do <endl> <stmt list> loop */
int ReduceWhileLoop(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;
    error = InterpretNode(condition1);
    while (gLastExpression.type != VAL_NIL
           && (gLastExpression.data.primitive ||
               gLastExpression.type != VAL_PRIMITIVE)
           && error == 0
           && breaking == 0)
    {
        error = InterpretNode(stmt_list1);
        if (error == 0) {
            error = InterpretNode(condition1);
        }
        continuing = 0;
    }
    breaking = 0;

    return error;
}

/* 27. <assignment> -> <l-value> = <assignment> */
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
    
    //VALUE oldval = GetRecord(gLValueIdentifier, gLValueContext);
    if (array_indexing)
    {
        HashStore(gLValueIndex, expr, gLValueDictionary);
        array_indexing = 0;
    }
    else
    {
        StoreRecord(gLValueIdentifier, expr, gLValueContext);
    }
/*  if (expr.type == VAL_REFERENCE)
    {
        if (expr.data.reference->ref_count >= 0) {
            expr.data.reference->ref_count++;
        }
    }
    else if (expr.type == VAL_FUNCTION)
    {
        if (expr.data.function->ref_count >= 0) {
            expr.data.function->ref_count++;
            if (expr.data.function->closure &&
                expr.data.function->closure->ref_count >= 0)
            {
                expr.data.function->closure->ref_count++;
            }
        }
    }*/

    //InvalidateExpr(oldval);
    gLastExpression = expr;

    return error;
}

/* 28. <assignment> -> <l-value> = <condition> */
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
    
    //VALUE oldval = GetRecord(gLValueIdentifier, gLValueContext);
    if (array_indexing)
    {
        HashStore(gLValueIndex, expr, gLValueDictionary);
//        printf("Storing (%i,%i) @ (%i,%i)\n", expr.type, expr.data.primitive, gLValueIndex.type, gLValueIndex.data.primitive);
        array_indexing = 0;
    }
    else
    {
        StoreRecord(gLValueIdentifier, expr, gLValueContext);
    }
/*  if (expr.type == VAL_REFERENCE)
    {
        if (expr.data.reference->ref_count >= 0) {
            expr.data.reference->ref_count++;
        }
    }
    else if (expr.type == VAL_FUNCTION)
    {
        if (expr.data.function->ref_count > 0) {
            expr.data.function->ref_count++;
            if (expr.data.function->closure &&
                expr.data.function->closure->ref_count >= 0)
            {
                expr.data.function->closure->ref_count++;
            }
        }
    }*/

    //InvalidateExpr(oldval);
    gLastExpression = expr;

    return error;
}

/* 29. <l-value> -> <identifier> */
int ReduceLValueA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;

    gLValueIdentifier = identifier1->string;
    gLValueContext = gCurrentContext;
    gLValueIndex.type = VAL_NIL;
    gLValueIndex.data.primitive = 0;
    gLValueDictionary = NULL;
    array_indexing = 0;

    return error;
}

/* 30. <l-value> -> ( <l-value> ) */
int ReduceLValueB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* l_value1 = node->children[1];

    int error = 0;
    error = InterpretNode(l_value1);

    return error;
}

/* 31. <l-value> -> <reference> . <identifier> */
int ReduceLValueC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];

    int error = 0;
    error = InterpretNode(reference1);
    if (error) return error;

    if (gLastExpression.type == VAL_REFERENCE)
    {
        gLValueIdentifier = identifier1->string;
        gLValueContext = gLastExpression.data.reference;
        gLValueIndex.type = VAL_NIL;
        gLValueIndex.data.primitive = 0;
        gLValueDictionary = NULL;
        array_indexing = 0;
    }
    else if (gLastExpression.type == VAL_DICTIONARY)
    {
        // error ?
//        error = 1;
        gLValueIndex.type = VAL_STRING;
        gLValueIndex.data.string = identifier1->string;
        gLValueDictionary = gLastExpression.data.dictionary;
        gLValueIdentifier = NULL;
        gLValueContext = NULL;
        array_indexing = 1;
    }
    else
    {
        error = 31;
        gLValueIdentifier = NULL;
        gLValueContext = NULL;
        gLValueIndex.type = VAL_NIL;
        gLValueIndex.data.primitive = 0;
        gLValueDictionary = NULL;
        array_indexing = 0;
    }

    return error;
}

/* 32. <l-value> -> <reference> [ <expr> ] */
int ReduceLValueD(SYNTAX_TREE* node)
{
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = InterpretNode(reference1);
    VALUE reference = gLastExpression;
    if (error) return error;
    error = InterpretNode(expr1);
    VALUE index = gLastExpression;
    if (error) return error;
    
    if (reference.type == VAL_REFERENCE &&
        (index.type == VAL_STRING || index.type == VAL_PRIMITIVE))
    {
        if (index.type == VAL_PRIMITIVE)
        {
            char* string = (char*)ALLOCATE(sizeof(char) * 16);
            sprintf(string, "%i", index.data.primitive);
            index.type = VAL_STRING;
            index.data.string = string;
        }
        else if (index.type == VAL_FLOATING_POINT)
        {
            char* string = (char*)ALLOCATE(sizeof(char) * 16);
            sprintf(string, "%x", (unsigned int)index.data.floatp);
            index.type = VAL_STRING;
            index.data.string = string;
        }

        gLValueIdentifier = index.data.string;
        gLValueContext = reference.data.reference;
        gLValueIndex.type = VAL_NIL;
        gLValueIndex.data.primitive = 0;
        gLValueDictionary = NULL;
        array_indexing = 0;
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
        error = 32;
        gLValueIdentifier = NULL;
        gLValueContext = NULL;
        gLValueIndex.type = VAL_NIL;
        gLValueIndex.data.primitive = 0;
        gLValueDictionary = NULL;
        array_indexing = 0;
    }

    return error;
}

/* 33. <expr> -> <condition> */
int ReduceExpr(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[0];

    int error = 0;
    error = InterpretNode(condition1);

    return error;
}

/* 34. <condition> -> <condition> and <logic> */
int ReduceConditionA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = InterpretNode(condition1);
    VALUE condition = gLastExpression;
    if (error) return error;
    error = InterpretNode(logic1);
    VALUE logic = gLastExpression;
    if (error) return error;

    int truths = 0;
    if (condition.type == VAL_PRIMITIVE)
    {
        if (condition.data.primitive)
            truths++;
    }
    else if (condition.type != VAL_NIL)
    {
        truths++;
    }

    if (logic.type == VAL_PRIMITIVE)
    {
        if (logic.data.primitive)
            truths++;
    }
    else if (logic.type != VAL_NIL)
    {
        truths++;
    }

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = (truths == 2) ? 1 : 0;

    return error;
}

/* 35. <condition> -> <condition> or <logic> */
int ReduceConditionB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = InterpretNode(condition1);
    VALUE condition = gLastExpression;
    if (error) return error;
    error = InterpretNode(logic1);
    VALUE logic = gLastExpression;
    if (error) return error;

    int truths = 0;
    if (condition.type == VAL_PRIMITIVE)
    {
        if (condition.data.primitive)
            truths++;
    }
    else if (condition.type != VAL_NIL)
    {
        truths++;
    }

    if (logic.type == VAL_PRIMITIVE)
    {
        if (logic.data.primitive)
            truths++;
    }
    else if (logic.type != VAL_NIL)
    {
        truths++;
    }

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = (truths > 0) ? 1 : 0;

    return error;
}

/* 36. <condition> -> <condition> nor <logic> */
int ReduceConditionC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = InterpretNode(condition1);
    VALUE condition = gLastExpression;
    if (error) return error;
    error = InterpretNode(logic1);
    VALUE logic = gLastExpression;
    if (error) return error;

    int truths = 0;
    if (condition.type == VAL_PRIMITIVE)
    {
        if (condition.data.primitive)
            truths++;
    }
    else if (condition.type != VAL_NIL)
    {
        truths++;
    }

    if (logic.type == VAL_PRIMITIVE)
    {
        if (logic.data.primitive)
            truths++;
    }
    else if (logic.type != VAL_NIL)
    {
        truths++;
    }

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = (truths == 0) ? 1 : 0;

    return error;
}

/* 37. <condition> -> <condition> xor <logic> */
int ReduceConditionD(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = InterpretNode(condition1);
    VALUE condition = gLastExpression;
    if (error) return error;
    error = InterpretNode(logic1);
    VALUE logic = gLastExpression;
    if (error) return error;
    
    int truths = 0;
    if (condition.type == VAL_PRIMITIVE)
    {
        if (condition.data.primitive)
            truths++;
    }
    else if (condition.type != VAL_NIL)
    {
        truths++;
    }
    
    if (logic.type == VAL_PRIMITIVE)
    {
        if (logic.data.primitive)
            truths++;
    }
    else if (logic.type != VAL_NIL)
    {
        truths++;
    }
    
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = (truths == 1) ? 1 : 0;

    return error;
}

/* 38. <condition> -> <logic> */
int ReduceConditionE(SYNTAX_TREE* node)
{
    SYNTAX_TREE* logic1 = node->children[0];

    int error = 0;
    error = InterpretNode(logic1);

    return error;
}

/* 39. <logic> -> not <comparison> */
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
    }

    return error;
}

/* 40. <logic> -> <comparison> */
int ReduceLogicB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];

    int error = 0;
    error = InterpretNode(comparison1);

    return error;
}

/* 41. <comparison> -> <comparison> == <arithmetic> */
int ReduceComparisonA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = InterpretNode(comparison1);
    VALUE comparison = gLastExpression;
    if (error) return error;
    error = InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    if (error) return error;

    if (comparison.type == arithmetic.type)
    {
        if (comparison.type == VAL_PRIMITIVE)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = (comparison.data.primitive == arithmetic.data.primitive);
        }
        else if (comparison.type == VAL_FLOATING_POINT)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = (comparison.data.floatp == arithmetic.data.floatp);
        }
        else if (comparison.type == VAL_STRING)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = strcmp(comparison.data.string, arithmetic.data.string) ? 0 : 1;
        }
        else if (comparison.type == VAL_REFERENCE)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = (comparison.data.reference == arithmetic.data.reference);
        }
        else if (comparison.type == VAL_FUNCTION)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = (comparison.data.function == arithmetic.data.function);
        }
        else if (comparison.type == VAL_DICTIONARY)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = (comparison.data.dictionary == arithmetic.data.dictionary);
        }
        else
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = 1;
        }
    }
    else
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 0;
    }
    
    gLastExpression.data.primitive = gLastExpression.data.primitive ? 1 : 0;

    return error;
}

/* 42. <comparison> -> <comparison> != <arithmetic> */
int ReduceComparisonB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = InterpretNode(comparison1);
    VALUE comparison = gLastExpression;
    if (error) return error;
    error = InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    if (error) return error;
    
    if (comparison.type == arithmetic.type)
    {
        if (comparison.type == VAL_PRIMITIVE)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = (comparison.data.primitive != arithmetic.data.primitive);
        }
        else if (comparison.type == VAL_FLOATING_POINT)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = (comparison.data.floatp != arithmetic.data.floatp);
        }
        else if (comparison.type == VAL_STRING)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = strcmp(comparison.data.string, arithmetic.data.string) ? 1 : 0;
        }
        else if (comparison.type == VAL_REFERENCE)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = (comparison.data.reference != arithmetic.data.reference);
        }
        else if (comparison.type == VAL_FUNCTION)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = (comparison.data.function != arithmetic.data.function);
        }
        else
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = 0;
        }
    }
    else
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 1;
    }

    return error;
}

/* 43. <comparison> -> <comparison> < <arithmetic> */
int ReduceComparisonC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = InterpretNode(comparison1);
    VALUE comparison = gLastExpression;
    if (error) return error;
    error = InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    if (error) return error;

    if (comparison.type == VAL_PRIMITIVE && arithmetic.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = comparison.data.primitive < arithmetic.data.primitive;
    }
    else if (comparison.type == VAL_FLOATING_POINT || arithmetic.type == VAL_FLOATING_POINT)
    {
        double a = TypeFloat(comparison);
        double b = TypeFloat(arithmetic);
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = a < b;
    }
    else
    {
        // string comparison
        gLastExpression.data.primitive = VAL_NIL;
    }
    
    gLastExpression.data.primitive = gLastExpression.data.primitive ? 1 : 0;

    return error;
}

/* 44. <comparison> -> <comparison> > <arithmetic> */
int ReduceComparisonD(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = InterpretNode(comparison1);
    VALUE comparison = gLastExpression;
    if (error) return error;
    error = InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    if (error) return error;

    if (comparison.type == VAL_PRIMITIVE && arithmetic.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 
            (comparison.data.primitive > arithmetic.data.primitive);
    }
    else if (comparison.type == VAL_FLOATING_POINT || arithmetic.type == VAL_FLOATING_POINT)
    {
        double a = TypeFloat(comparison);
        double b = TypeFloat(arithmetic);
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = a > b;
    }
    else
    {
        // string comparison
        gLastExpression.type = VAL_NIL;
    }
    
    gLastExpression.data.primitive = gLastExpression.data.primitive ? 1 : 0;

    return error;
}

/* 45. <comparison> -> <comparison> <= <arithmetic> */
int ReduceComparisonE(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = InterpretNode(comparison1);
    VALUE comparison = gLastExpression;
    if (error) return error;
    error = InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    if (error) return error;

    if (comparison.type == VAL_PRIMITIVE && arithmetic.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 
            (comparison.data.primitive <= arithmetic.data.primitive);
    }
    else if (comparison.type == VAL_FLOATING_POINT || arithmetic.type == VAL_FLOATING_POINT)
    {
        double a = TypeFloat(comparison);
        double b = TypeFloat(arithmetic);
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = a <= b;
    }
    else
    {
        // string comparison
        gLastExpression.type = VAL_NIL;
    }
    
    gLastExpression.data.primitive = gLastExpression.data.primitive ? 1 : 0;

    return error;
}

/* 46. <comparison> -> <comparison> >= <arithmetic> */
int ReduceComparisonF(SYNTAX_TREE* node)
{
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = InterpretNode(comparison1);
    VALUE comparison = gLastExpression;
    if (error) return error;
    error = InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    if (error) return error;
    
    if (comparison.type == VAL_PRIMITIVE && arithmetic.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = comparison.data.primitive >= arithmetic.data.primitive;
    }
    else if (comparison.type == VAL_FLOATING_POINT || arithmetic.type == VAL_FLOATING_POINT)
    {
        double a = TypeFloat(comparison);
        double b = TypeFloat(arithmetic);
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = (a >= b);
    }
    else
    {
        // string comparison
        gLastExpression.type = VAL_NIL;
    }
    
    gLastExpression.data.primitive = gLastExpression.data.primitive ? 1 : 0;

    return error;
}

/* 47. <comparison> -> <arithmetic> */
int ReduceComparisonG(SYNTAX_TREE* node)
{
    SYNTAX_TREE* arithmetic1 = node->children[0];

    int error = 0;
    error = InterpretNode(arithmetic1);

    return error;
}

/* 48. <arithmetic> -> <arithmetic> + <term> */
int ReduceArithmeticA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    if (error) return error;
    error = InterpretNode(term1);
    VALUE term = gLastExpression;
    if (error) return error;

    if (arithmetic.type == VAL_PRIMITIVE && term.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = arithmetic.data.primitive + term.data.primitive;
    }
    else if (arithmetic.type == VAL_PRIMITIVE && term.type == VAL_FLOATING_POINT)
    {

        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.data.floatp = (double)arithmetic.data.primitive + term.data.floatp;
    }
    else if (arithmetic.type == VAL_FLOATING_POINT && term.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.data.floatp = arithmetic.data.floatp + (double)term.data.primitive;
    }
    else if (arithmetic.type == VAL_FLOATING_POINT && term.type == VAL_FLOATING_POINT)
    {
        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.data.floatp = arithmetic.data.floatp + term.data.floatp;
    }
    else if (arithmetic.type == VAL_STRING || term.type == VAL_STRING)
    {
        gLastExpression.type = VAL_STRING;
        if (arithmetic.type != VAL_STRING)
        {
            if (arithmetic.type == VAL_PRIMITIVE)
            {
                char* string = (char*)ALLOCATE(sizeof(char) * 16);
                sprintf(string, "%i", arithmetic.data.primitive);
                arithmetic.type = VAL_STRING;
                arithmetic.data.string = string;
            }
            else if (arithmetic.type == VAL_FLOATING_POINT)
            {
                char* string = (char*)ALLOCATE(sizeof(char) * 16);
                sprintf(string, "%g", arithmetic.data.floatp);
                arithmetic.type = VAL_STRING;
                arithmetic.data.string = string;
            }
            else if (arithmetic.type == VAL_REFERENCE)
            {
                arithmetic.type = VAL_STRING;
                arithmetic.data.string = "[OBJECT REFERENCE]";
            }
            else if (arithmetic.type == VAL_FUNCTION)
            {
                arithmetic.type = VAL_STRING;
                arithmetic.data.string = "[FUNCTION]";
            }
            else if (arithmetic.type == VAL_DICTIONARY)
            {
                arithmetic.type = VAL_STRING;
                arithmetic.data.string = "[DICTIONARY]";
            }
            else if (arithmetic.type == VAL_NIL)
            {
                arithmetic.type = VAL_STRING;
                arithmetic.data.string = "[NIL]";
            }
            else
            {
                arithmetic.type = VAL_STRING;
                arithmetic.data.string = "[UNKNOWN]";
            }
        }
        
        if (term.type != VAL_STRING)
        {
            if (term.type == VAL_PRIMITIVE)
            {
                char* string = (char*)ALLOCATE(sizeof(char) * 16);
                sprintf(string, "%i", term.data.primitive);
                term.type = VAL_STRING;
                term.data.string = string;
            }
            else if (term.type == VAL_FLOATING_POINT)
            {
                char* string = (char*)ALLOCATE(sizeof(char) * 16);
                sprintf(string, "%g", term.data.floatp);
                term.type = VAL_STRING;
                term.data.string = string;
            }
            else if (term.type == VAL_REFERENCE)
            {
                term.type = VAL_STRING;
                term.data.string = "[OBJECT REFERENCE]";
            }
            else if (term.type == VAL_FUNCTION)
            {
                term.type = VAL_STRING;
                term.data.string = "[FUNCTION]";
            }
            else if (term.type == VAL_DICTIONARY)
            {
                term.type = VAL_STRING;
                term.data.string = "[DICTIONARY]";
            }
            else if (term.type == VAL_NIL)
            {
                term.type = VAL_STRING;
                term.data.string = "[NIL]";
            }
            else
            {
                term.type = VAL_STRING;
                term.data.string = "[UNKNOWN]";
            }
        }
        
        int length = strlen(arithmetic.data.string) + strlen(term.data.string) + 1;
        char* string = (char*)ALLOCATE(sizeof(char) * length);
        sprintf(string, "%s%s", arithmetic.data.string, term.data.string);
        gLastExpression.data.string = string;
    }
    else
    {
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 49. <arithmetic> -> <arithmetic> - <term> */
int ReduceArithmeticB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    if (error) return error;
    error = InterpretNode(term1);
    VALUE term = gLastExpression;
    if (error) return error;

    if (arithmetic.type == VAL_PRIMITIVE && term.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = arithmetic.data.primitive - term.data.primitive;
    }
    else if (arithmetic.type == VAL_FLOATING_POINT || term.type == VAL_FLOATING_POINT)
    {
        if (arithmetic.type == VAL_FLOATING_POINT && term.type == VAL_FLOATING_POINT)
        {
            gLastExpression.type = VAL_FLOATING_POINT;
            gLastExpression.data.floatp = arithmetic.data.floatp - term.data.floatp;
        }
        else if (arithmetic.type == VAL_FLOATING_POINT && term.type == VAL_PRIMITIVE)
        {
            gLastExpression.type = VAL_FLOATING_POINT;
            gLastExpression.data.floatp = arithmetic.data.floatp - (double)term.data.primitive;
        }
        else if (arithmetic.type == VAL_PRIMITIVE && term.type == VAL_FLOATING_POINT)
        {
            gLastExpression.type = VAL_FLOATING_POINT;
            gLastExpression.data.floatp = (double)arithmetic.data.primitive - term.data.floatp;
        }
        else
        {
            gLastExpression.type = VAL_NIL;
        }
    }
    else
    {
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 50. <arithmetic> -> <arithmetic> & <term> */
int ReduceArithmeticC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    if (error) return error;
    error = InterpretNode(term1);
    VALUE term = gLastExpression;
    if (error) return error;

    if (arithmetic.type == VAL_PRIMITIVE && term.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 
            (arithmetic.data.primitive & term.data.primitive);
    }
    else
    {
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 51. <arithmetic> -> <arithmetic> | <term> */
int ReduceArithmeticD(SYNTAX_TREE* node)
{
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    if (error) return error;
    error = InterpretNode(term1);
    VALUE term = gLastExpression;
    if (error) return error;
    
    if (arithmetic.type == VAL_PRIMITIVE && term.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 
            (arithmetic.data.primitive | term.data.primitive);
    }
    else
    {
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 52. <arithmetic> -> <term> */
int ReduceArithmeticE(SYNTAX_TREE* node)
{
    SYNTAX_TREE* term1 = node->children[0];

    int error = 0;
    error = InterpretNode(term1);

    return error;
}

/* 53. <term> -> <term> * <factor> */
int ReduceTermA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    int error = 0;
    error = InterpretNode(term1);
    VALUE term = gLastExpression;
    if (error) return error;
    error = InterpretNode(factor1);
    VALUE factor = gLastExpression;
    if (error) return error;

    if (term.type == VAL_PRIMITIVE && factor.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 
            (term.data.primitive * factor.data.primitive);
    }
    else if (term.type == VAL_FLOATING_POINT || factor.type == VAL_FLOATING_POINT)
    {
        double a = TypeFloat(term);
        double b = TypeFloat(factor);
        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.data.floatp = (a * b);
    }
    else
    {
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 54. <term> -> <term> / <factor> */
int ReduceTermB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    int error = 0;
    error = InterpretNode(term1);
    VALUE term = gLastExpression;
    if (error) return error;
    error = InterpretNode(factor1);
    VALUE factor = gLastExpression;
    if (error) return error;
    
    if (term.type == VAL_PRIMITIVE && factor.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = term.data.primitive / factor.data.primitive;
    }
    else if (term.type == VAL_FLOATING_POINT && factor.type == VAL_FLOATING_POINT)
    {
        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.data.floatp = term.data.floatp / factor.data.floatp;
    }
    else if (term.type == VAL_FLOATING_POINT && factor.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.data.floatp = term.data.floatp / (double)factor.data.primitive;
    }
    else if (term.type == VAL_PRIMITIVE && factor.type == VAL_FLOATING_POINT)
    {
        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.data.floatp = (double)term.data.primitive / factor.data.floatp;
    }
    else
    {
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 55. <term> -> <factor> */
int ReduceTermC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* factor1 = node->children[0];

    int error = 0;
    error = InterpretNode(factor1);

    return error;
}

/* 56. <factor> -> - <factor> */
int ReduceFactorA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* factor1 = node->children[1];

    int error = 0;
    error = InterpretNode(factor1);
    
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

/* 57. <factor> -> ! <factor> */
int ReduceFactorB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* factor1 = node->children[1];

    int error = 0;
    error = InterpretNode(factor1);
    
    if (gLastExpression.type == VAL_PRIMITIVE)
    {
        gLastExpression.data.primitive = !gLastExpression.data.primitive;
    }
    else
    {
        // opposite of string, function, reference or nil is nil
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 58. <factor> -> <final> */
int ReduceFactorC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* final1 = node->children[0];

    int error = 0;
    error = InterpretNode(final1);

    return error;
}

/* 59. <final> -> ( <expr> ) */
int ReduceFinalA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = InterpretNode(expr1);

    return error;
}

/* 60. <final> -> <boolean> */
int ReduceFinalB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* boolean1 = node->children[0];

    int error = 0;
    error = InterpretNode(boolean1);

    return error;
}

/* 61. <final> -> <integer> */
int ReduceFinalC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* integer1 = node->children[0];

    int error = 0;
    
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = atoi(integer1->string);

    return error;
}

/* 62. <final> -> <float> */
int ReduceFinalD(SYNTAX_TREE* node)
{
    SYNTAX_TREE* float1 = node->children[0];
    
    int error = 0;
    
    gLastExpression.type = VAL_FLOATING_POINT;
    gLastExpression.data.floatp = atof(float1->string);
    
    return error;
}

/* 63. <final> -> <string> */
int ReduceFinalE(SYNTAX_TREE* node)
{
    SYNTAX_TREE* string1 = node->children[0];
    
    int error = 0;
    
    gLastExpression.type = VAL_STRING;
    gLastExpression.data.string = string1->string;
    
    return error;
}

/* 64. <final> -> <object> */
int ReduceFinalF(SYNTAX_TREE* node)
{
    SYNTAX_TREE* object1 = node->children[0];

    int error = 0;
    error = InterpretNode(object1);

    return error;
}

/* 65. <final> -> <reference> */
int ReduceFinalG(SYNTAX_TREE* node)
{
    SYNTAX_TREE* reference1 = node->children[0];

    int error = 0;
    error = InterpretNode(reference1);

    return error;
}

/* 66. <reference> -> <l-value> */
int ReduceReferenceA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* l_value1 = node->children[0];

    int error = 0;
    error = InterpretNode(l_value1);
    
    if (array_indexing)
    {
        //gLastExpression = GetRecord(gLValueIdentifier, gLValueContext);
        //printf("Retrieving (%i,%i) from (%i,%i)\n", gLastExpression.type, gLastExpression.data.primitive, gLValueIndex.type, gLValueIndex.data.primitive);
        gLastExpression = HashGet(gLValueIndex, gLValueDictionary);
        array_indexing = 0;
    }
    else
    {
        gLastExpression = GetRecord(gLValueIdentifier, gLValueContext);
    }

    return error;
}

/* 67. <reference> -> <reference> ( ) */
// function application
int ReduceReferenceB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* reference1 = node->children[0];

    int error = 0;
    
    error = InterpretNode(reference1);
	VALUE function = gLastExpression;
    if (error) return error;
    
    if (function.type == VAL_FUNCTION)
    {
        // create new context
        CONTEXT* current = gCurrentContext;
        gCurrentContext = (CONTEXT*)ALLOC(sizeof(CONTEXT));
        gCurrentContext->list = NULL;
        gCurrentContext->ref_count = 1;
        gCurrentContext->parent = function.data.function->closure;
        CONTEXT* func_context = gCurrentContext;
        
        if (function.data.function->built_in) {
            error = function.data.function->functor(0);
        } else {
            error = InterpretNode(function.data.function->body);
        }

      // remove calling context
        func_context->ref_count--;
        if (func_context->ref_count == 0)
        {
            //FreeContext(func_context);
        }

        // return with same context
        gCurrentContext = current;
        returning = 0;
    }
    else
    {
        error = 12345;
    }

    return error;
}

/* 68. <reference> -> <reference> ( <arguments> ) */
// function application
int ReduceReferenceC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* arguments1 = node->children[2];

    int error = 0;
    int argument_count = 0;
    error = InterpretNode(reference1);
	VALUE function = gLastExpression;
    if (error) return error;

    if (function.type == VAL_FUNCTION)
    {
        // evaluate arguments
        error = InterpretNode(arguments1);
        PAIR* param = function.data.function->parameters;
        PAIR* arg = gArgumentEvaluation;

        // create new context
        CONTEXT* current = gCurrentContext;
        //gCurrentContext = (CONTEXT*)ALLOCATE(sizeof(CONTEXT));
        gCurrentContext = (CONTEXT*)ALLOC(sizeof(CONTEXT));
        gCurrentContext->list = NULL;
        gCurrentContext->ref_count = 1;
        gCurrentContext->parent = function.data.function->closure;
        CONTEXT* func_context = gCurrentContext;
        
        // store arguments in the function's closure
		PAIR* last = NULL;
        while (param && arg)
        {
            //StoreRecord(param->identifier, arg->value, gCurrentContext);
			if (last)
			{
				//last->next = (PAIR*)ALLOCATE(sizeof(PAIR));
                last->next = (PAIR*)ALLOC(sizeof(PAIR));
				last = last->next;
			}
			else
			{
				//gCurrentContext->list = last = (PAIR*)ALLOCATE(sizeof(PAIR));
                gCurrentContext->list = last = (PAIR*)ALLOC(sizeof(PAIR));
			}

			last->identifier = param->identifier;
			last->value = arg->value;
			last->next = NULL;

            argument_count++;            

			param = param->next;
			arg = arg->next;
        }
        arg = gArgumentEvaluation;

        //return_value_exists = 0;
        if (error == 0) 
        {
            if (function.data.function->built_in)
            {
                error = function.data.function->functor(argument_count);
            } else {        
                error = InterpretNode(function.data.function->body);
            }
        }

      // remove calling context
        // remove evaluated arguments
/*      while (arg) {
            PAIR* next;
            next = arg->next;
            DEALLOC((void*)arg);
            arg = next;
        }*/
        // remove function closure
        func_context->ref_count--;
        if (func_context->ref_count == 0)
        {
            //FreeContext(func_context);
        }

        // return with same context
        gCurrentContext = current;
        returning = 0;
    }
    else
    {
        error = 12345;
    }

    return error;
}

/* 69. <arguments> -> <arguments> , <expr> */
int ReduceArgumentsA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* arguments1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = InterpretNode(arguments1);
    
    PAIR* arguments = gArgumentEvaluation;
    
    error = error ? error : InterpretNode(expr1);
    
    PAIR* list = arguments;
    while (list->next)
        list = list->next;
    list->next = (PAIR*)ALLOC(sizeof(PAIR));
    list->next->identifier = NULL;
    list->next->value = gLastExpression;
    list->next->next = NULL;

    
    gArgumentEvaluation = arguments;

    return error;
}

/* 70. <arguments> -> <expr> */
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

/* 71. <object> -> [ ] */
int ReduceObjectA(SYNTAX_TREE* node)
{
    int error = 0;
    
/*   gLastExpression.type = VAL_REFERENCE;
    gLastExpression.data.reference = (CONTEXT*)ALLOC(sizeof(CONTEXT));
    gLastExpression.data.reference->parent = NULL;
    gLastExpression.data.reference->list = NULL;
    gLastExpression.data.reference->ref_count = 0; */

    gLastExpression.type = VAL_DICTIONARY;
    gLastExpression.data.dictionary = CreateHashTable();

    return error;
}

/* 72. <object> -> [ <array init> ] */
int ReduceObjectB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* array_init1 = node->children[1];

    int error = 0;
    error = InterpretNode(array_init1);
    
//    gLastExpression.type = VAL_REFERENCE;
//    gLastExpression.data.reference = gDictionaryInit;
    gLastExpression.type = VAL_DICTIONARY;
    gLastExpression.data.dictionary = gDictionaryInit;

    return error;
}

/* 73. <object> -> [ <dictionary init> ] */
int ReduceObjectC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* dictionary_init1 = node->children[1];

    int error = 0;
    error = InterpretNode(dictionary_init1);
    
//    gLastExpression.type = VAL_REFERENCE;
//    gLastExpression.data.reference = gDictionaryInit;
    gLastExpression.type = VAL_DICTIONARY;
    gLastExpression.data.dictionary = gDictionaryInit;

    return error;
}

/* 74. <array init> -> <array init> , <expr> */
int ReduceArrayInitA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* array_init1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = InterpretNode(array_init1);
    
    //CONTEXT* dictionary = gDictionaryInit;
    HASH_TABLE* dictionary = gDictionaryInit;
    int index = gArrayIndex;
    
    error = error ? error : InterpretNode(expr1);
    VALUE expr = gLastExpression;
    
    // push array gLastExpr
/*   PAIR* list = dictionary->list;
    while (list->next)
        list = list->next;
    list->next = (PAIR*)ALLOC(sizeof(PAIR));
    char* string = (char*)ALLOCATE(sizeof(char)*16);
    sprintf(string, "%i", index++);
    list->next->identifier = string;
    list->next->value = gLastExpression;
    list->next->next = NULL; */

    VALUE key;
    key.type = VAL_PRIMITIVE;
    key.data.primitive = index;
    HashStore(key, expr, dictionary);
    
    //gDictionaryInit = dictionary;
    gArrayIndex = ++index;

    return error;
}

/* 75. <array init> -> <expr> */
int ReduceArrayInitB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = InterpretNode(expr1);
    VALUE expr = gLastExpression;
    
    // push array gLastExpr
/*    gDictionaryInit = (CONTEXT*)ALLOC(sizeof(CONTEXT));
    gArrayIndex = 0;
    gDictionaryInit->parent = NULL;
    gDictionaryInit->ref_count = 0;
    gDictionaryInit->list = (PAIR*)ALLOC(sizeof(PAIR));
    char* string = (char*)ALLOCATE(sizeof(char)*16);
    sprintf(string, "%i", gArrayIndex++);
    gDictionaryInit->list->identifier = string;
    gDictionaryInit->list->value = gLastExpression;
    gDictionaryInit->list->next = NULL; */
    
    gDictionaryInit = CreateHashTable();
    gArrayIndex = 0;
    
    VALUE index;
    index.type = VAL_PRIMITIVE;
    index.data.primitive = gArrayIndex;

    HashStore(index, expr, gDictionaryInit);
    gArrayIndex++;

    return error;
}

/* 76. <dictionary init> -> <dictionary init> , <identifier> : <expr> */
int ReduceDictionaryInitA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* dictionary_init1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];
    SYNTAX_TREE* expr1 = node->children[4];

    int error = 0;
    error = InterpretNode(dictionary_init1);

    //CONTEXT* dictionary = gDictionaryInit;
    HASH_TABLE* dictionary = gDictionaryInit;

    error = error ? error : InterpretNode(expr1);
    VALUE expr = gLastExpression;
    
    // push dict[identifier] gLastExpr
/*    PAIR* list = dictionary->list;
    while (list->next)
        list = list->next;
    list->next = (PAIR*)ALLOC(sizeof(PAIR));
    list->next->identifier = identifier1->string;
    list->next->value = gLastExpression;
    list->next->next = NULL; */

    VALUE key;
    key.type = VAL_STRING;
    key.data.string = identifier1->string;

    HashStore(key, expr, dictionary);
//  gDictionaryInit = dictionary;

    return error;
}

/* 77. <dictionary init> -> <identifier> : <expr> */
int ReduceDictionaryInitB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = InterpretNode(expr1);
    VALUE expr = gLastExpression;
    
    // push dict[identifier] gLastExpr
/*    gDictionaryInit = (CONTEXT*)ALLOC(sizeof(CONTEXT));
    gDictionaryInit->parent = NULL;
    gDictionaryInit->ref_count = 0;
    gDictionaryInit->list = (PAIR*)ALLOC(sizeof(PAIR));
    gDictionaryInit->list->identifier = identifier1->string;
    gDictionaryInit->list->value = gLastExpression;
    gDictionaryInit->list->next = NULL; */

    gDictionaryInit = CreateHashTable();

    VALUE key;
    key.type = VAL_STRING;
    key.data.string = identifier1->string;

    HashStore(key, expr, gDictionaryInit);

    return error;
}

/* 78. <boolean> -> true */
int ReduceBooleanA(SYNTAX_TREE* node)
{
    int error = 0;
    
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = 1;

    return error;
}

/* 79. <boolean> -> false */
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
        // empty production
        case 0xFF: return 0;
    default:
        printf("Unknown production %i.\n", node->production);
        return 1;
    }
}

