/* auto-generated compiler stubs */
#include "lr_parser.h"
#include "interpreter.h"

/* type stuff */

float CoerceFloat(VALUE val)
{
    switch (val.type)
    {
    case VAL_NIL:               return 0.0f;
                                break;

    case VAL_PRIMITIVE:         return (float)val.primitive;
                                break;

    case VAL_STRING:            return 0.0f;
                                break;

    case VAL_REFERENCE:         return 0.0f;
                                break;

    case VAL_FUNCTION:          return 0.0f;
                                break;
    
    case VAL_FLOATING_POINT:    return val.floatp;
                                break;

    default:                    return 0.0f;
    }
    return 0.0f;
}


/* production stubs */

/* 1. <program> -> <stmt list> */
int ReduceProgram(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 1;
    SYNTAX_TREE* stmt_list1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(stmt_list1);

    return error;
}

/* 2. <stmt list> -> <stmt list> <stmt> */
int ReduceStmtListA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 2;
    SYNTAX_TREE* stmt_list1 = node->children[0];
    SYNTAX_TREE* stmt1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(stmt_list1);
    
    if (returning == 0 &&
        breaking == 0 &&
        continuing == 0)
    {
        error = error || InterpretNode(stmt1);
    }

    return error;
}

/* 3. <stmt list> -> */
int ReduceStmtListB(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 3;

    int error = 0;

    return error;
}

/* 4. <stmt> -> import <identifier> */
int ReduceStmtA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 4;
    //SYNTAX_TREE* identifier1 = node->children[1];

    int error = 0;
    //error = error || InterpretNode(identifier1);

    /* import library */
    // change scope of [namespace] to global
    gLastExpression.type = VAL_NIL;

    return error;
}

/* 5. <stmt> -> call <reference> */
int ReduceStmtB(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 5;
    SYNTAX_TREE* reference1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(reference1);

    // make a function call without parameters or return values

    return error;
}

/* 6. <stmt> -> <endl> */
int ReduceStmtC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 4;

    int error = 0;

    return error;
}

/* 7. <stmt> -> <expr> <endl> */
int ReduceStmtD(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 5;
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(expr1);

    return error;
}

/* 8. <stmt> -> <assignment> <endl> */
int ReduceStmtE(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 6;
    SYNTAX_TREE* assignment1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(assignment1);

    return error;
}

/* 9. <stmt> -> <function def> <endl> */
int ReduceStmtF(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 7;
    SYNTAX_TREE* function_def1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(function_def1);

    return error;
}

/* 10. <stmt> -> <if> <endl> */
int ReduceStmtG(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 8;
    SYNTAX_TREE* if1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(if1);

    return error;
}

/* 11. <stmt> -> <if else> <endl> */
int ReduceStmtH(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 9;
    SYNTAX_TREE* if_else1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(if_else1);

    return error;
}

/* 12. <stmt> -> <for loop> <endl> */
int ReduceStmtI(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 10;
    SYNTAX_TREE* for_loop1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(for_loop1);

    return error;
}

/* 13. <stmt> -> <while loop> <endl> */
int ReduceStmtJ(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 11;
    SYNTAX_TREE* while_loop1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(while_loop1);

    return error;
}

/* 14. <stmt> -> return <expr> <endl> */
int ReduceStmtK(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 12;
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(expr1);

    returning = 1;

    return error;
}

/* 15. <stmt> -> break <endl> */
int ReduceStmtL(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 13;

    int error = 0;

    breaking = 1;

    return error;
}

/* 16. <stmt> -> continue <endl> */
int ReduceStmtM(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 14;

    int error = 0;
    
    continuing = 1;

    return error;
}

/* 15. <function def> -> function <identifier> <parameters> <endl> <stmt list> end */
int ReduceFunctionDef(SYNTAX_TREE* node)
{
    if (node->numChildren != 6) return 15;
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* parameters1 = node->children[2];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;

    gParameterListing = NULL;
    error = error || InterpretNode(parameters1);

    // FUNCTIONS
    VALUE record;
    record.type = VAL_FUNCTION;
    record.function = (FUNCTION*)ALLOCATE(sizeof(FUNCTION));
    record.function->parameters = gParameterListing; // ??
    record.function->body = stmt_list1;
	record.function->closure = gCurrentContext;
    record.function->built_in = 0;
    record.function->functor = NULL;
    StoreRecord(identifier1->string, record, gCurrentContext);

    return error;
}

/* 16. <parameters> -> */
int ReduceParametersA(SYNTAX_TREE* node)
{
    if (node->numChildren != 0) return 16;

    int error = 0;

    return error;
}

/* 17. <parameters> -> ( ) */
int ReduceParametersB(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 17;

    int error = 0;

    return error;
}

/* 18. <parameters> -> ( <param decl> ) */
int ReduceParametersC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 18;
    SYNTAX_TREE* param_decl1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(param_decl1);

    return error;
}

/* 19. <param decl> -> <identifier> */
int ReduceParamDeclA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 19;
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;

    gParameterListing = (PAIR*)ALLOCATE(sizeof(PAIR));
    gParameterListing->identifier = identifier1->string;
    gParameterListing->value.type = VAL_NIL;
    gParameterListing->next = NULL;

    return error;
}

/* 20. <param decl> -> <param decl> , <identifier> */
int ReduceParamDeclB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 20;
    SYNTAX_TREE* param_decl1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(param_decl1);

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

/* 21. <if> -> if <condition> then <endl> <stmt list> end */
int ReduceIf(SYNTAX_TREE* node)
{
    if (node->numChildren != 6) return 21;
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;
    error = error || InterpretNode(condition1);
    if ((gLastExpression.type == VAL_PRIMITIVE
            && gLastExpression.primitive)
    || (gLastExpression.type != VAL_PRIMITIVE
            && gLastExpression.type != VAL_NIL))
    {
        error = error || InterpretNode(stmt_list1);
    }

    return error;
}

/* 22. <if else> -> if <condition> then <endl> <stmt list> else <endl> <stmt list> end */
int ReduceIfElse(SYNTAX_TREE* node)
{
    if (node->numChildren != 9) return 22;
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];
    SYNTAX_TREE* stmt_list2 = node->children[7];

    int error = 0;
    error = error || InterpretNode(condition1);
    if ((gLastExpression.type == VAL_PRIMITIVE
            && gLastExpression.primitive)
    || (gLastExpression.type != VAL_PRIMITIVE
            && gLastExpression.type != VAL_NIL))
    {
        error = error || InterpretNode(stmt_list1);
    }
    else
    {
        error = error || InterpretNode(stmt_list2);
    }

    return error;
}

/* 23. <for loop> -> for <identifier> = <arithmetic> to <arithmetic> do <endl> <stmt list> loop */
int ReduceForLoop(SYNTAX_TREE* node)
{
    if (node->numChildren != 10) return 23;
    SYNTAX_TREE* identifier1 = node->children[1];
    SYNTAX_TREE* arithmetic1 = node->children[3];
    SYNTAX_TREE* arithmetic2 = node->children[5];
    SYNTAX_TREE* stmt_list1 = node->children[8];
    
    VALUE start, end;
    const char* id = identifier1->string;

    int error = 0;

    error = error || InterpretNode(arithmetic1);
    start = gLastExpression;
    error = error || InterpretNode(arithmetic2);
    end = gLastExpression;

    if (start.type == VAL_FLOATING_POINT
       && end.type == VAL_FLOATING_POINT)
    {
        while (start.type == VAL_FLOATING_POINT
               && end.type == VAL_FLOATING_POINT
               && start.floatp <= end.floatp
               && error == 0
               && breaking == 0)
        {
            StoreRecord(id, start, gCurrentContext);
            error = error || InterpretNode(stmt_list1);
            if (breaking == 0)
            {
                continuing = 0;
                start.floatp = start.floatp + 1.0f;
            }
        }
    }
    else if (start.type == VAL_PRIMITIVE
                && end.type == VAL_PRIMITIVE)
    {
        while (start.type == VAL_PRIMITIVE
               && end.type == VAL_PRIMITIVE
               && start.primitive <= end.primitive
               && error == 0
               && breaking == 0)
        {
            StoreRecord(id, start, gCurrentContext);
            error = error || InterpretNode(stmt_list1);
            if (breaking == 0)
            {
                continuing = 0;
                start.primitive++;
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

/* 24. <while loop> -> while <condition> do <endl> <stmt list> loop */
int ReduceWhileLoop(SYNTAX_TREE* node)
{
    if (node->numChildren != 6) return 24;
    SYNTAX_TREE* condition1 = node->children[1];
    SYNTAX_TREE* stmt_list1 = node->children[4];

    int error = 0;
    error = error || InterpretNode(condition1);
    while (gLastExpression.type != VAL_NIL
           && (gLastExpression.primitive ||
               gLastExpression.type != VAL_PRIMITIVE)
           && error == 0
           && breaking == 0)
    {
        error = error || InterpretNode(stmt_list1);
        error = error || InterpretNode(condition1);
        continuing = 0;
    }
    breaking = 0;

    return error;
}

/* 25. <assignment> -> <l-value> = <assignment> */
int ReduceAssignmentA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 25;
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* assignment1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(assignment1);
    VALUE expr = gLastExpression;
    error = error || InterpretNode(l_value1);
    
    StoreRecord(gLValueIdentifier, expr, gLValueContext);

    return error;
}

/* 26. <assignment> -> <l-value> = <condition> */
int ReduceAssignmentB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 26;
    SYNTAX_TREE* l_value1 = node->children[0];
    SYNTAX_TREE* condition1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(condition1);
    VALUE expr = gLastExpression;
    error = error || InterpretNode(l_value1);
    
    StoreRecord(gLValueIdentifier, expr, gLValueContext);

    return error;
}

/* 27. <l-value> -> <identifier> */
int ReduceLValueA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 27;
    SYNTAX_TREE* identifier1 = node->children[0];

    int error = 0;

    gLValueIdentifier = identifier1->string;
    gLValueContext = gCurrentContext;

    return error;
}

/* 28. <l-value> -> ( <l-value> ) */
int ReduceLValueB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 28;
    SYNTAX_TREE* l_value1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(l_value1);

    return error;
}

/* 29. <l-value> -> <reference> . <identifier> */
int ReduceLValueC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 29;
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(reference1);

    if (gLastExpression.type == VAL_REFERENCE)
    {
        gLValueIdentifier = identifier1->string;
        gLValueContext = gLastExpression.reference;
    }
    else
    {
        gLValueIdentifier = NULL;
        gLValueContext = NULL;
    }

    return error;
}

/* 30. <l-value> -> <reference> [ <expr> ] */
int ReduceLValueD(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 30;
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(reference1);
    VALUE reference = gLastExpression;
    error = error || InterpretNode(expr1);
    VALUE index = gLastExpression;
    
    if (reference.type == VAL_REFERENCE &&
        (index.type == VAL_STRING || index.type == VAL_PRIMITIVE))
    {
        if (index.type == VAL_PRIMITIVE)
        {
            char* string = (char*)ALLOCATE(sizeof(char) * 16);
            sprintf(string, "%i", index.primitive);
            index.type = VAL_STRING;
            index.string = string;
        }
        else if (index.type == VAL_FLOATING_POINT)
        {
            char* string = (char*)ALLOCATE(sizeof(char) * 16);
            sprintf(string, "%x", (unsigned int)index.floatp);
            index.type = VAL_STRING;
            index.string = string;
        }

        gLValueIdentifier = index.string;
        gLValueContext = reference.reference;
    }
    else
    {
        gLValueIdentifier = NULL;
        gLValueContext = NULL;
    }

    return error;
}

/* 31. <expr> -> <condition> */
int ReduceExpr(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 31;
    SYNTAX_TREE* condition1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(condition1);

    return error;
}

/* 32. <condition> -> <condition> and <logic> */
int ReduceConditionA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 32;
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(condition1);
    VALUE condition = gLastExpression;
    error = error || InterpretNode(logic1);
    VALUE logic = gLastExpression;

    int truths = 0;
    if (condition.type == VAL_PRIMITIVE)
    {
        if (condition.primitive)
            truths++;
    }
    else if (condition.type != VAL_NIL)
    {
        truths++;
    }

    if (logic.type == VAL_PRIMITIVE)
    {
        if (logic.primitive)
            truths++;
    }
    else if (logic.type != VAL_NIL)
    {
        truths++;
    }

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.primitive = (truths == 2) ? 1 : 0;

    return error;
}

/* 33. <condition> -> <condition> or <logic> */
int ReduceConditionB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 33;
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(condition1);
    VALUE condition = gLastExpression;
    error = error || InterpretNode(logic1);
    VALUE logic = gLastExpression;

    int truths = 0;
    if (condition.type == VAL_PRIMITIVE)
    {
        if (condition.primitive)
            truths++;
    }
    else if (condition.type != VAL_NIL)
    {
        truths++;
    }

    if (logic.type == VAL_PRIMITIVE)
    {
        if (logic.primitive)
            truths++;
    }
    else if (logic.type != VAL_NIL)
    {
        truths++;
    }

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.primitive = (truths > 0) ? 1 : 0;

    return error;
}

/* 34. <condition> -> <condition> nor <logic> */
int ReduceConditionC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 34;
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(condition1);
    VALUE condition = gLastExpression;
    error = error || InterpretNode(logic1);
    VALUE logic = gLastExpression;

    int truths = 0;
    if (condition.type == VAL_PRIMITIVE)
    {
        if (condition.primitive)
            truths++;
    }
    else if (condition.type != VAL_NIL)
    {
        truths++;
    }

    if (logic.type == VAL_PRIMITIVE)
    {
        if (logic.primitive)
            truths++;
    }
    else if (logic.type != VAL_NIL)
    {
        truths++;
    }

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.primitive = (truths == 0) ? 1 : 0;

    return error;
}

/* 35. <condition> -> <condition> xor <logic> */
int ReduceConditionD(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 35;
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(condition1);
    VALUE condition = gLastExpression;
    error = error || InterpretNode(logic1);
    VALUE logic = gLastExpression;
    
    int truths = 0;
    if (condition.type == VAL_PRIMITIVE)
    {
        if (condition.primitive)
            truths++;
    }
    else if (condition.type != VAL_NIL)
    {
        truths++;
    }
    
    if (logic.type == VAL_PRIMITIVE)
    {
        if (logic.primitive)
            truths++;
    }
    else if (logic.type != VAL_NIL)
    {
        truths++;
    }
    
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.primitive = (truths == 1) ? 1 : 0;

    return error;
}

/* 36. <condition> -> <logic> */
int ReduceConditionE(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 36;
    SYNTAX_TREE* logic1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(logic1);

    return error;
}

/* 37. <logic> -> not <comparison> */
int ReduceLogicA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 37;
    SYNTAX_TREE* comparison1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(comparison1);
    
    if (gLastExpression.type == VAL_PRIMITIVE)
    {
        gLastExpression.primitive = gLastExpression.primitive ? 0 : 1;
    }
    else if (gLastExpression.type == VAL_NIL)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = 1;
    }
    else
    {

        // opposite of string, function, reference or nil is nil
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 38. <logic> -> <comparison> */
int ReduceLogicB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 38;
    SYNTAX_TREE* comparison1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(comparison1);

    return error;
}

/* 39. <comparison> -> <comparison> == <arithmetic> */
int ReduceComparisonA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 39;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(comparison1);
    VALUE comparison = gLastExpression;
    error = error || InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;

    if (comparison.type == arithmetic.type)
    {
        if (comparison.type == VAL_PRIMITIVE)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.primitive = (comparison.primitive == arithmetic.primitive);
        }
        else if (comparison.type == VAL_FLOATING_POINT)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.primitive = (comparison.floatp == arithmetic.floatp);
        }
        else if (comparison.type == VAL_STRING)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.primitive = strcmp(comparison.string, arithmetic.string) ? 0 : 1;
        }
        else if (comparison.type == VAL_REFERENCE)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.primitive = (comparison.reference == arithmetic.reference);
        }
        else if (comparison.type == VAL_FUNCTION)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.primitive = (comparison.function == arithmetic.function);
        }
        else
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.primitive = 1;
        }
    }
    else
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = 0;
    }
    
    gLastExpression.primitive = gLastExpression.primitive ? 1 : 0;

    return error;
}

/* 40. <comparison> -> <comparison> != <arithmetic> */
int ReduceComparisonB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 40;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(comparison1);
    VALUE comparison = gLastExpression;
    error = error || InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    
    if (comparison.type == arithmetic.type)
    {
        if (comparison.type == VAL_PRIMITIVE)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.primitive = (comparison.primitive != arithmetic.primitive);
        }
        else if (comparison.type == VAL_FLOATING_POINT)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.primitive = (comparison.floatp != arithmetic.floatp);
        }
        else if (comparison.type == VAL_STRING)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.primitive = strcmp(comparison.string, arithmetic.string) ? 1 : 0;
        }
        else if (comparison.type == VAL_REFERENCE)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.primitive = (comparison.reference != arithmetic.reference);
        }
        else if (comparison.type == VAL_FUNCTION)
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.primitive = (comparison.function != arithmetic.function);
        }
        else
        {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.primitive = 0;
        }
    }
    else
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = 1;
    }

    return error;
}

/* 41. <comparison> -> <comparison> < <arithmetic> */
int ReduceComparisonC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 41;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(comparison1);
    VALUE comparison = gLastExpression;
    error = error || InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;

    if (comparison.type == VAL_PRIMITIVE && arithmetic.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = comparison.primitive < arithmetic.primitive;
    }
    else if (comparison.type == VAL_FLOATING_POINT || arithmetic.type == VAL_FLOATING_POINT)
    {
        float a = CoerceFloat(comparison);
        float b = CoerceFloat(arithmetic);
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = a < b;
    }
    else
    {
        // string comparison
        gLastExpression.primitive = VAL_NIL;
    }
    
    gLastExpression.primitive = gLastExpression.primitive ? 1 : 0;

    return error;
}

/* 42. <comparison> -> <comparison> > <arithmetic> */
int ReduceComparisonD(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 42;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(comparison1);
    VALUE comparison = gLastExpression;
    error = error || InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;

    if (comparison.type == VAL_PRIMITIVE && arithmetic.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = comparison.primitive > arithmetic.primitive;
    }
    else if (comparison.type == VAL_FLOATING_POINT || arithmetic.type == VAL_FLOATING_POINT)
    {
        float a = CoerceFloat(comparison);
        float b = CoerceFloat(arithmetic);
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = a > b;
    }
    else
    {
        // string comparison
        gLastExpression.type = VAL_NIL;
    }
    
    gLastExpression.primitive = gLastExpression.primitive ? 1 : 0;

    return error;
}

/* 43. <comparison> -> <comparison> <= <arithmetic> */
int ReduceComparisonE(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 43;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(comparison1);
    VALUE comparison = gLastExpression;
    error = error || InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;

    if (comparison.type == VAL_PRIMITIVE && arithmetic.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = comparison.primitive <= arithmetic.primitive;
    }
    else if (comparison.type == VAL_FLOATING_POINT || arithmetic.type == VAL_FLOATING_POINT)
    {
        float a = CoerceFloat(comparison);
        float b = CoerceFloat(arithmetic);
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = a <= b;
    }
    else
    {
        // string comparison
        gLastExpression.type = VAL_NIL;
    }
    
    gLastExpression.primitive = gLastExpression.primitive ? 1 : 0;

    return error;
}

/* 44. <comparison> -> <comparison> >= <arithmetic> */
int ReduceComparisonF(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 44;
    SYNTAX_TREE* comparison1 = node->children[0];
    SYNTAX_TREE* arithmetic1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(comparison1);
    VALUE comparison = gLastExpression;
    error = error || InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    
    if (comparison.type == VAL_PRIMITIVE && arithmetic.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = comparison.primitive >= arithmetic.primitive;
    }
    else if (comparison.type == VAL_FLOATING_POINT || arithmetic.type == VAL_FLOATING_POINT)
    {
        float a = CoerceFloat(comparison);
        float b = CoerceFloat(arithmetic);
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = a >= b;
    }
    else
    {
        // string comparison
        gLastExpression.type = VAL_NIL;
    }
    
    gLastExpression.primitive = gLastExpression.primitive ? 1 : 0;

    return error;
}

/* 45. <comparison> -> <arithmetic> */
int ReduceComparisonG(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 45;
    SYNTAX_TREE* arithmetic1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(arithmetic1);

    return error;
}

/* 46. <arithmetic> -> <arithmetic> + <term> */
int ReduceArithmeticA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 46;
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    error = error || InterpretNode(term1);
    VALUE term = gLastExpression;

    if (arithmetic.type == VAL_PRIMITIVE && term.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = arithmetic.primitive + term.primitive;
    }
    else if (arithmetic.type == VAL_PRIMITIVE && term.type == VAL_FLOATING_POINT)
    {
        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.floatp = (float)arithmetic.primitive + term.floatp;
    }
    else if (arithmetic.type == VAL_FLOATING_POINT && term.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.floatp = arithmetic.floatp + (float)term.primitive;
    }
    else if (arithmetic.type == VAL_FLOATING_POINT && term.type == VAL_FLOATING_POINT)
    {
        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.floatp = arithmetic.floatp + term.floatp;
    }
    else if (arithmetic.type == VAL_STRING || term.type == VAL_STRING)
    {
        gLastExpression.type = VAL_STRING;
        if (arithmetic.type != VAL_STRING)
        {
            if (arithmetic.type == VAL_PRIMITIVE)
            {
                char* string = (char*)ALLOCATE(sizeof(char) * 16);
                sprintf(string, "%i", arithmetic.primitive);
                arithmetic.type = VAL_STRING;
                arithmetic.string = string;
            }
            else if (arithmetic.type == VAL_FLOATING_POINT)
            {
                char* string = (char*)ALLOCATE(sizeof(char) * 16);
                sprintf(string, "%g", arithmetic.floatp);
                arithmetic.type = VAL_STRING;
                arithmetic.string = string;
            }
            else if (arithmetic.type == VAL_REFERENCE)
            {
                arithmetic.type = VAL_STRING;
                arithmetic.string = "[OBJECT REFERENCE]";
            }
            else if (arithmetic.type == VAL_FUNCTION)
            {
                arithmetic.type = VAL_STRING;
                arithmetic.string = "[FUNCTION]";
            }
            else
            {
                arithmetic.type = VAL_STRING;
                arithmetic.string = "[NIL]";
            }
        }
        
        if (term.type != VAL_STRING)
        {
            if (term.type == VAL_PRIMITIVE)
            {
                char* string = (char*)ALLOCATE(sizeof(char) * 16);
                sprintf(string, "%i", term.primitive);
                term.type = VAL_STRING;
                term.string = string;
            }
            else if (term.type == VAL_FLOATING_POINT)
            {
                char* string = (char*)ALLOCATE(sizeof(char) * 16);
                sprintf(string, "%g", term.floatp);
                term.type = VAL_STRING;
                term.string = string;
            }
            else if (term.type == VAL_REFERENCE)
            {
                term.type = VAL_STRING;
                term.string = "[OBJECT REFERENCE]";
            }
            else if (term.type == VAL_FUNCTION)
            {
                term.type = VAL_STRING;
                term.string = "[FUNCTION]";
            }
            else
            {
                term.type = VAL_STRING;
                term.string = "[NIL]";
            }
        }
        
        int length = strlen(arithmetic.string) + strlen(term.string) + 1;
        char* string = (char*)ALLOCATE(sizeof(char) * length);
        sprintf(string, "%s%s", arithmetic.string, term.string);
        gLastExpression.string = string;
    }
    else
    {
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 47. <arithmetic> -> <arithmetic> - <term> */
int ReduceArithmeticB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 47;
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    error = error || InterpretNode(term1);
    VALUE term = gLastExpression;

    if (arithmetic.type == VAL_PRIMITIVE && term.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = arithmetic.primitive - term.primitive;
    }
    else if (arithmetic.type == VAL_FLOATING_POINT || term.type == VAL_FLOATING_POINT)
    {
        if (arithmetic.type == VAL_FLOATING_POINT && term.type == VAL_FLOATING_POINT)
        {
            gLastExpression.type = VAL_FLOATING_POINT;
            gLastExpression.floatp = arithmetic.floatp - term.floatp;
        }
        else if (arithmetic.type == VAL_FLOATING_POINT && term.type == VAL_PRIMITIVE)
        {
            gLastExpression.type = VAL_FLOATING_POINT;
            gLastExpression.floatp = arithmetic.floatp - (float)term.primitive;
        }
        else if (arithmetic.type == VAL_PRIMITIVE && term.type == VAL_FLOATING_POINT)
        {
            gLastExpression.type = VAL_FLOATING_POINT;
            gLastExpression.floatp = (float)arithmetic.primitive - term.floatp;
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

/* 48. <arithmetic> -> <arithmetic> & <term> */
int ReduceArithmeticC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 48;
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    error = error || InterpretNode(term1);
    VALUE term = gLastExpression;

    if (arithmetic.type == VAL_PRIMITIVE && term.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = arithmetic.primitive & term.primitive;
    }
    else
    {
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 49. <arithmetic> -> <arithmetic> | <term> */
int ReduceArithmeticD(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 49;
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    error = error || InterpretNode(term1);
    VALUE term = gLastExpression;
    
    if (arithmetic.type == VAL_PRIMITIVE && term.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = arithmetic.primitive | term.primitive;
    }
    else
    {
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 50. <arithmetic> -> <term> */
int ReduceArithmeticE(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 50;
    SYNTAX_TREE* term1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(term1);

    return error;
}

/* 51. <term> -> <term> * <factor> */
int ReduceTermA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 51;
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(term1);
    VALUE term = gLastExpression;
    error = error || InterpretNode(factor1);
    VALUE factor = gLastExpression;

    if (term.type == VAL_PRIMITIVE && factor.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = term.primitive * factor.primitive;
    }
    else if (term.type == VAL_FLOATING_POINT || factor.type == VAL_FLOATING_POINT)
    {
        float a = CoerceFloat(term);
        float b = CoerceFloat(factor);
        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.floatp = (a * b);
    }
    else
    {
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 52. <term> -> <term> / <factor> */
int ReduceTermB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 52;
    SYNTAX_TREE* term1 = node->children[0];
    SYNTAX_TREE* factor1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(term1);
    VALUE term = gLastExpression;
    error = error || InterpretNode(factor1);
    VALUE factor = gLastExpression;
    
    if (term.type == VAL_PRIMITIVE && factor.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.primitive = term.primitive / factor.primitive;
    }
    else if (term.type == VAL_FLOATING_POINT && factor.type == VAL_FLOATING_POINT)
    {
        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.floatp = term.floatp / factor.floatp;
    }
    else if (term.type == VAL_FLOATING_POINT && factor.type == VAL_PRIMITIVE)
    {
        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.floatp = term.floatp / (float)factor.primitive;
    }
    else if (term.type == VAL_PRIMITIVE && factor.type == VAL_FLOATING_POINT)
    {
        gLastExpression.type = VAL_FLOATING_POINT;
        gLastExpression.floatp = (float)term.primitive / factor.floatp;
    }
    else
    {
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 53. <term> -> <factor> */
int ReduceTermC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 53;
    SYNTAX_TREE* factor1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(factor1);

    return error;
}

/* 54. <factor> -> - <factor> */
int ReduceFactorA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 54;
    SYNTAX_TREE* factor1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(factor1);
    
    if (gLastExpression.type == VAL_PRIMITIVE)
    {
        gLastExpression.primitive = -gLastExpression.primitive;
    }
    else if (gLastExpression.type == VAL_FLOATING_POINT)
    {
        gLastExpression.floatp = -gLastExpression.floatp;
    }
    else
    {
        // opposite of string, function, reference or nil is nil
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 55. <factor> -> ! <factor> */
int ReduceFactorB(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 55;
    SYNTAX_TREE* factor1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(factor1);
    
    if (gLastExpression.type == VAL_PRIMITIVE)
    {
        gLastExpression.primitive = !gLastExpression.primitive;
    }
    else
    {
        // opposite of string, function, reference or nil is nil
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 56. <factor> -> <final> */
int ReduceFactorC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 56;
    SYNTAX_TREE* final1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(final1);

    return error;
}

/* 57. <final> -> ( <expr> ) */
int ReduceFinalA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 57;
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(expr1);

    return error;
}

/* 58. <final> -> <boolean> */
int ReduceFinalB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 58;
    SYNTAX_TREE* boolean1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(boolean1);

    return error;
}

/* 59. <final> -> <integer> */
int ReduceFinalC(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 59;
    SYNTAX_TREE* integer1 = node->children[0];

    int error = 0;
    // error = error || InterpretNode(integer1);
    
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.primitive = atoi(integer1->string);

    return error;
}

/* 62. <final> -> <float> */
int ReduceFinalD(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 62;
    SYNTAX_TREE* float1 = node->children[0];

    int error = 0;

    gLastExpression.type = VAL_FLOATING_POINT;
    gLastExpression.floatp = atof(float1->string);

    return error;
}

/* 60. <final> -> <string> */
int ReduceFinalE(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 60;
    SYNTAX_TREE* string1 = node->children[0];

    int error = 0;
    // error = error || InterpretNode(string1);
    
    gLastExpression.type = VAL_STRING;
    gLastExpression.string = string1->string;

    return error;
}

/* 61. <final> -> <object> */
int ReduceFinalF(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 61;
    SYNTAX_TREE* object1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(object1);

    return error;
}

/* 62. <final> -> <reference> */
int ReduceFinalG(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 62;
    SYNTAX_TREE* reference1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(reference1);

    return error;
}

/* 63. <reference> -> <l-value> */
int ReduceReferenceA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 63;
    SYNTAX_TREE* l_value1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(l_value1);
    
    gLastExpression = GetRecord(gLValueIdentifier, gLValueContext);

    return error;
}

/* 64. <reference> -> <reference> ( ) */
// function application
int ReduceReferenceB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 64;
    SYNTAX_TREE* reference1 = node->children[0];

    int error = 0;
    
    error = error || InterpretNode(reference1);
	VALUE function = gLastExpression;
    
    if (function.type == VAL_FUNCTION)
    {
        // create new context
        CONTEXT* current = gCurrentContext;
        gCurrentContext = (CONTEXT*)ALLOCATE(sizeof(CONTEXT));
        gCurrentContext->list = NULL;
        gCurrentContext->parent = function.function->closure;
        
        if (function.function->built_in) {
            error = error || function.function->functor(0);
        } else {
            error = error || InterpretNode(function.function->body);
        }
        
        // return with same context
        gCurrentContext = current;
        returning = 0;
    }
    else
    {
        error = error || 12345;
    }

    return error;
}

/* 65. <reference> -> <reference> ( <arguments> ) */
// function application
int ReduceReferenceC(SYNTAX_TREE* node)
{
    if (node->numChildren != 4) return 65;
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* arguments1 = node->children[2];

    int error = 0;
    int argument_count = 0;
    error = error || InterpretNode(reference1);
	VALUE function = gLastExpression;
	//const char* name = gLValueIdentifier;
	//printf("%s()\n", gLValueIdentifier);

    if (function.type == VAL_FUNCTION)
    {
        // evaluate arguments
        error = error || InterpretNode(arguments1);
        PAIR* param = function.function->parameters;
        PAIR* arg = gArgumentEvaluation;

        // create new context
        CONTEXT* current = gCurrentContext;
        gCurrentContext = (CONTEXT*)ALLOCATE(sizeof(CONTEXT));
        gCurrentContext->list = NULL;
        gCurrentContext->parent = function.function->closure;
        
        // store arguments in the function's closure
		PAIR* last = NULL;
        while (param && arg)
        {
            //StoreRecord(param->identifier, arg->value, gCurrentContext);
			if (last)
			{
				last->next = (PAIR*)ALLOCATE(sizeof(PAIR));
				last = last->next;
			}
			else
			{
				gCurrentContext->list = last = (PAIR*)ALLOCATE(sizeof(PAIR));
			}

			last->identifier = param->identifier;
			last->value = arg->value;
			last->next = NULL;

            argument_count++;            

			param = param->next;
			arg = arg->next;
        }

        if (function.function->built_in)
        {
            error = error || function.function->functor(argument_count);
        } else {        
            error = error || InterpretNode(function.function->body);
        }

        // return with same context
        gCurrentContext = current;
        returning = 0;
    }
    else
    {
        error = error || 12345;
		PrintNode(node);
    }

    return error;
}

/* 66. <arguments> -> <arguments> , <expr> */
int ReduceArgumentsA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 66;
    SYNTAX_TREE* arguments1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(arguments1);
    
    PAIR* arguments = gArgumentEvaluation;
    
    error = error || InterpretNode(expr1);
    
    PAIR* list = arguments;
    while (list->next)
        list = list->next;
    list->next = (PAIR*)ALLOCATE(sizeof(PAIR));
    list->next->identifier = NULL;
    list->next->value = gLastExpression;
    list->next->next = NULL;

    
    gArgumentEvaluation = arguments;

    return error;
}

/* 67. <arguments> -> <expr> */
int ReduceArgumentsB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 67;
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(expr1);
    
    gArgumentEvaluation = (PAIR*)ALLOCATE(sizeof(PAIR));
    gArgumentEvaluation->identifier = NULL;
    gArgumentEvaluation->value = gLastExpression;
    gArgumentEvaluation->next = NULL;

    return error;
}

/* 68. <object> -> [ ] */
int ReduceObjectA(SYNTAX_TREE* node)
{
    if (node->numChildren != 2) return 68;

    int error = 0;
    
    gLastExpression.type = VAL_REFERENCE;
    gLastExpression.reference = (CONTEXT*)ALLOCATE(sizeof(CONTEXT));
    gLastExpression.reference->parent = NULL;
    gLastExpression.reference->list = NULL;

    return error;
}

/* 69. <object> -> [ <array init> ] */
int ReduceObjectB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 69;
    SYNTAX_TREE* array_init1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(array_init1);
    
    gLastExpression.type = VAL_REFERENCE;
    gLastExpression.reference = gDictionaryInit;

    return error;
}

/* 70. <object> -> [ <dictionary init> ] */
int ReduceObjectC(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 70;
    SYNTAX_TREE* dictionary_init1 = node->children[1];

    int error = 0;
    error = error || InterpretNode(dictionary_init1);
    
    gLastExpression.type = VAL_REFERENCE;
    gLastExpression.reference = gDictionaryInit;

    return error;
}

/* 71. <array init> -> <array init> , <expr> */
int ReduceArrayInitA(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 71;
    SYNTAX_TREE* array_init1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(array_init1);
    
    CONTEXT* dictionary = gDictionaryInit;
    int index = gArrayIndex;
    
    error = error || InterpretNode(expr1);
    
    // push array gLastExpr
    PAIR* list = dictionary->list;
    while (list->next)
        list = list->next;
    list->next = (PAIR*)ALLOCATE(sizeof(PAIR));
    char* string = (char*)ALLOCATE(sizeof(char)*16);
    sprintf(string, "%i", index++);
    list->next->identifier = string;
    list->next->value = gLastExpression;
    list->next->next = NULL;
    
    gDictionaryInit = dictionary;
    gArrayIndex = index;

    return error;
}

/* 72. <array init> -> <expr> */
int ReduceArrayInitB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 72;
    SYNTAX_TREE* expr1 = node->children[0];

    int error = 0;
    error = error || InterpretNode(expr1);
    
    // push array gLastExpr
    gDictionaryInit = (CONTEXT*)ALLOCATE(sizeof(CONTEXT));
    gArrayIndex = 0;
    gDictionaryInit->parent = NULL;
    gDictionaryInit->list = (PAIR*)ALLOCATE(sizeof(PAIR));
    char* string = (char*)ALLOCATE(sizeof(char)*16);
    sprintf(string, "%i", gArrayIndex++);
    gDictionaryInit->list->identifier = string;
    gDictionaryInit->list->value = gLastExpression;
    gDictionaryInit->list->next = NULL;

    return error;
}

/* 73. <dictionary init> -> <dictionary init> , <identifier> : <expr> */
int ReduceDictionaryInitA(SYNTAX_TREE* node)
{
    if (node->numChildren != 5) return 73;
    SYNTAX_TREE* dictionary_init1 = node->children[0];
    SYNTAX_TREE* identifier1 = node->children[2];
    SYNTAX_TREE* expr1 = node->children[4];

    int error = 0;
    error = error || InterpretNode(dictionary_init1);

    CONTEXT* dictionary = gDictionaryInit;

    error = error || InterpretNode(expr1);
    
    // push dict[identifier] gLastExpr
    PAIR* list = dictionary->list;
    while (list->next)
        list = list->next;
    list->next = (PAIR*)ALLOCATE(sizeof(PAIR));
    list->next->identifier = identifier1->string;
    list->next->value = gLastExpression;
    list->next->next = NULL;

    gDictionaryInit = dictionary;

    return error;
}

/* 74. <dictionary init> -> <identifier> : <expr> */
int ReduceDictionaryInitB(SYNTAX_TREE* node)
{
    if (node->numChildren != 3) return 74;
    SYNTAX_TREE* identifier1 = node->children[0];
    SYNTAX_TREE* expr1 = node->children[2];

    int error = 0;
    error = error || InterpretNode(expr1);
    
    // push dict[identifier] gLastExpr
    gDictionaryInit = (CONTEXT*)ALLOCATE(sizeof(CONTEXT));
    gDictionaryInit->parent = NULL;
    gDictionaryInit->list = (PAIR*)ALLOCATE(sizeof(PAIR));
    gDictionaryInit->list->identifier = identifier1->string;
    gDictionaryInit->list->value = gLastExpression;
    gDictionaryInit->list->next = NULL;

    return error;
}

/* 75. <boolean> -> true */
int ReduceBooleanA(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 75;

    int error = 0;
    
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.primitive = 1;

    return error;
}

/* 76. <boolean> -> false */
int ReduceBooleanB(SYNTAX_TREE* node)
{
    if (node->numChildren != 1) return 76;

    int error = 0;
    
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.primitive = 0;

    return error;
}

void PrintObject(CONTEXT* context)
{
    printf("[");
    PAIR* list = context->list;
    while (list)
    {
        if (list->value.type == VAL_PRIMITIVE)
        {
            printf("%i", list->value.primitive);
        }
        else if (list->value.type == VAL_STRING)
        {
            printf("'%s'", list->value.string);
        }
        else if (list->value.type == VAL_REFERENCE)
        {
            //printf("[OBJECT REFERENCE]");
            PrintObject(list->value.reference);
        }
        else if (list->value.type == VAL_FUNCTION)
        {
            printf("f(");
            PAIR* itr = list->value.function->parameters;
            while (itr)
            {
                printf("%s", itr->identifier);
                if (itr->next)
                    printf(", ");
                itr = itr->next;
            }
            printf(")");
        }
        else
        {
            printf("[NIL]");
        }

        if (list->next)
            printf(", ");
        list = list->next;
    }
    printf("]");
}


void PrintNode(SYNTAX_TREE* node)
{
    int i;
    for (i = 0; i < node->numChildren; i++)
    {
        PrintNode(node->children[i]);
        if (node->children[i]->string)
        {
            printf("%s", node->children[i]->string);
            printf(" ");
        }
    }
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
    default:
        printf("Unknown production %i.\n", node->production);
        return 1;
    }
}

