/*
    Duck Programming Language
    Interpreter Productions
*/

#include "lr_parser.h"
#include "interpreter.h"
#include "arithmetic.h"
#include "memory.h"
#include "garbage.h"

/* production stubs */

// MakeTemporary
// IncrementReferences(VALUE*)
// InvalidateExpr(VALUE*)
// AddObjectPool(VALUE) 
// RemoveObjectPool(VALUE)

void PushReturnStack(VALUE* return_value)
{
//    IncrementReferences(return_value);
}

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
             //   InvalidateExpr(&gLastExpression);
                if ((++gc_collect_count) == GC_COLLECT_LIMIT)
                {
                    gc_collect_count = 0;
                    CallGCTraceRoot(gGlobalContext, gLastExpression);
                    //CallGCTraceRoot(gCurrentContext, gLastExpression);
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
/* 4. <stmt> -> import <identifier> */
int ReduceStmtA(SYNTAX_TREE* node)
{
    int error = 0;
    //printf("@import %s\n", node->children[1]->string);

    /* import library */
    // change scope of [namespace] to global
    VALUE library = GetRecord(node->children[1]->string, gCurrentContext);
    //RemoveRecord(node->children[1]->string, gCurrentContext);
    
    if (library.type == VAL_REFERENCE)
    {
        CONTEXT* namespace = library.data.reference;
        PAIR* iterator = namespace->list;
        while (iterator)
        {
            StoreRecord(iterator->identifier, iterator->value, gGlobalContext);
            iterator = iterator->next;
        }
        //DEALLOC(library.data.reference);
    }

    // InvalidateExpr(&gLastExpression);

    return error;
}

/* 5. <stmt> -> call <reference> */
/* 6. <stmt> -> <endl> */
/* 7. <stmt> -> <expr> <endl> */
/* 8. <stmt> -> <assignment> <endl> */
/* 9. <stmt> -> <function def> <endl> */
/* 10. <stmt> -> <if> <endl> */
/* 11. <stmt> -> <for loop> <endl> */
/* 12. <stmt> -> <while loop> <endl> */
/* 13. <stmt> -> return <expr> <endl> */
int ReduceStmtJ(SYNTAX_TREE* node)
{
    SYNTAX_TREE* expr1 = node->children[1];

    int error = 0;
    error = InterpretNode(expr1);

    PushReturnStack(&gLastExpression);

    returning = 1;

    return error;
}

/* 14. <stmt> -> break <endl> */
int ReduceStmtK(SYNTAX_TREE* node)
{
    int error = 0;
    
    breaking = 1;
    
    return error;
}

/* 15. <stmt> -> continue <endl> */
int ReduceStmtL(SYNTAX_TREE* node)
{
    int error = 0;
    
    continuing = 1;
    
    return error;
}

/* 16. <function def> -> function <identifier> <parameters> <endl> <stmt list> end */
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

	    /* record.data.function->closure = gCurrentContext; */
        /* if (gCurrentContext->ref_count > 0) {
            gCurrentContext->ref_count++;
        } */

        record.data.function->closure = gCurrentContext;
        //record.data.function->ref_count = 1;
        record.data.function->built_in = 0;
        record.data.function->functor = NULL;
        record.data.function->fn_name = identifier1->string;
        
        //printf("storing: %s in %p\n", identifier1->string, gCurrentContext);
        StoreRecord(identifier1->string, record, gCurrentContext);
        GCAddFunction(record.data.function, &gGCManager);
        //AddObjectPool(record);

        //gLastExpression = record;
    }
    return error;
}

/* 17. <parameters> -> */
/* 18. <parameters> -> ( ) */
/* 19. <parameters> -> ( <param decl> ) */
/* 20. <param decl> -> <identifier> */
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

/* 21. <param decl> -> <param decl> , <identifier> */
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

/* 22. <if> -> if <condition> then <endl> <stmt list> <else if> */
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
            //InvalidateExpr(&gLastExpression);
            error = InterpretNode(stmt_list1);
        } else {
            //InvalidateExpr(&gLastExpression);
            error = InterpretNode(else_if1);
        }
    }

    return error;
}

/* 23. <else if> -> else <endl> <stmt list> end */
/* 24. <else if> -> else <if> */
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
    //IncrementReferences(&start);
    if (error == 0) {
        error = InterpretNode(arithmetic2);
        end = gLastExpression;
        //IncrementReferences(&end);
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
        error = 25;
        breaking = 0;
        return error;
    }

    //InvalidateExpr(&start);
    //InvalidateExpr(&end);
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
           && EvaluatesTrue(gLastExpression)
           && error == 0
           && breaking == 0)
    {
        //InvalidateExpr(&gLastExpression);

        error = InterpretNode(stmt_list1);
        if (error == 0) {
            error = InterpretNode(condition1);
        }
        continuing = 0;
    }

    //InvalidateExpr(&gLastExpression);
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

    //IncrementReferences(&expr);
    
    //VALUE oldval = GetRecord(gLValueIdentifier, gLValueContext);
    if (array_indexing)
    {
        VALUE previous = HashGet(gLValueIndex, gLValueDictionary);
        //InvalidateExpr(&previous);
        HashStore(gLValueIndex, expr, gLValueDictionary);
        array_indexing = 0;
    }
    else
    {
        VALUE previous = GetRecord(gLValueIdentifier, gLValueContext);
        //InvalidateExpr(&previous);

        if (gLValueIndex.type == VAL_STRING &&
            gLValueIndex.const_string == 0)
        {
            gLValueIndex = CopyString(gLValueIndex);
        }

        StoreRecord(gLValueIdentifier, expr, gLValueContext);
    }

    //InvalidateExpr(oldval);
    //gLastExpression = MakeTemporary(expr);

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

    //IncrementReferences(&expr);
    
    //VALUE oldval = GetRecord(gLValueIdentifier, gLValueContext);
    if (array_indexing)
    {
        VALUE previous = HashGet(gLValueIndex, gLValueDictionary);
        //InvalidateExpr(&previous);
        
        if (gLValueIndex.type == VAL_STRING &&
            gLValueIndex.const_string == 0)
        {
            gLValueIndex = CopyString(gLValueIndex);
        }

        HashStore(gLValueIndex, expr, gLValueDictionary);
        array_indexing = 0;
    }
    else
    {
        VALUE previous = GetRecord(gLValueIdentifier, gLValueContext);
        //InvalidateExpr(&previous);
        StoreRecord(gLValueIdentifier, expr, gLValueContext);
    }

    //InvalidateExpr(oldval);
    //gLastExpression = MakeTemporary(expr);

    return error;
}

/* 29. <l-value> -> <identifier> */
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

/* 30. <l-value> -> ( <l-value> ) */
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
        error = 31;
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
        failed_production = node;
    }

    return error;
}

/* 33. <expr> -> <condition> */
/* 34. <condition> -> <condition> and <logic> */
int ReduceConditionA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* condition1 = node->children[0];
    SYNTAX_TREE* logic1 = node->children[2];

    int error = 0;
    error = InterpretNode(condition1);
    VALUE condition = gLastExpression;
    if (error) return error;

    /* AND */
    if (EvaluatesTrue(condition)) {
        //InvalidateExpr(&gLastExpression);

        error = InterpretNode(logic1);
        /* fall-through */

        if (error) return error;
    } else {
        //InvalidateExpr(&gLastExpression);
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 0;
    }

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

    if (EvaluatesTrue(condition)) {
        gLastExpression = condition;
        return error;
    }

    //InvalidateExpr(&gLastExpression);
    error = InterpretNode(logic1);
    VALUE logic = gLastExpression;
    if (error) return error;

    /* OR */
    gLastExpression = logic;

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

    if (EvaluatesTrue(condition)) {
        //InvalidateExpr(&gLastExpression);
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 0;
        return error;
    }

    error = InterpretNode(logic1);
    VALUE logic = gLastExpression;
    if (error) return error;

    /* NOR */
    if (EvaluatesTrue(logic)) {
        //InvalidateExpr(&gLastExpression);
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 0;
        return error;
    }
    else
    {
        //InvalidateExpr(&gLastExpression);
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = 1;
        return error;
    }

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
    
    /* XOR */
    gLastExpression = LogicXOR(condition, logic);
    /*InvalidateExpr(&condition); ????
    InvalidateExpr(&logic);*/

    return error;
}

/* 38. <condition> -> <logic> */
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
        //InvalidateExpr(&gLastExpression);
        gLastExpression.type = VAL_NIL;
        gLastExpression.data.primitive = 0;
    }

    return error;
}

/* 40. <logic> -> <comparison> */
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

    /* EQUAL */
    gLastExpression = CompareEquality(comparison, arithmetic);
    //InvalidateExpr(&comparison);
    //InvalidateExpr(&arithmetic);

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
    
    /* NOT EQUAL */
    gLastExpression = CompareInequality(comparison, arithmetic);
    //InvalidateExpr(&comparison);
    //InvalidateExpr(&arithmetic);

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

    /* LESS THAN */
    gLastExpression = CompareLessThan(comparison, arithmetic);
    //InvalidateExpr(&comparison);
    //InvalidateExpr(&arithmetic);

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

    /* GREATER THAN */
    gLastExpression = CompareGreaterThan(comparison, arithmetic);
    //InvalidateExpr(&comparison);
    //InvalidateExpr(&arithmetic);

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

    /* LESS-THAN-OR-EQUAL */
    gLastExpression = CompareLessThanOrEqual(comparison, arithmetic);
    //InvalidateExpr(&comparison);
    //InvalidateExpr(&arithmetic);

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
    
    /* GREATER-THAN-OR-EQUAL */
    gLastExpression = CompareGreaterThanOrEqual(comparison, arithmetic);
    //InvalidateExpr(&comparison);
    //InvalidateExpr(&arithmetic);

    return error;
}

/* 47. <comparison> -> <arithmetic> */
/* 48. <arithmetic> -> <arithmetic> + <term> */
int ReduceArithmeticA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* arithmetic1 = node->children[0];
    SYNTAX_TREE* term1 = node->children[2];

    int error = 0;
    error = InterpretNode(arithmetic1);
    VALUE arithmetic = gLastExpression;
    gLastExpression.type = VAL_NIL;
    if (error) return error;
    error = InterpretNode(term1);
    VALUE term = gLastExpression;
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

    //InvalidateExpr(&arithmetic);
    //InvalidateExpr(&term);

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

    /* subtract */
    gLastExpression = Subtract(arithmetic, term);

    //InvalidateExpr(&arithmetic);
    //InvalidateExpr(&term);

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

    /* binary & */
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

    //InvalidateExpr(&arithmetic);
    //InvalidateExpr(&term);

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
    
    /* binary | */
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

    //InvalidateExpr(&arithmetic);
    //InvalidateExpr(&term);

    return error;
}

/* 52. <arithmetic> -> <term> */
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

    /* multiplication */
    gLastExpression = Multiply(term, factor);

    //InvalidateExpr(&term);
    //InvalidateExpr(&factor);

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
    
    /* division */
    gLastExpression = Divide(term, factor);

    //InvalidateExpr(&term);
    //InvalidateExpr(&factor);

    return error;
}

/* 55. <term> -> <factor> */
/* 56. <factor> -> - <factor> */
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
        //InvalidateExpr(&gLastExpression);
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
        //InvalidateExpr(&gLastExpression);
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 58. <factor> -> <final> */
/* 59. <final> -> ( <expr> ) */
/* 60. <final> -> <boolean> */
/* 61. <final> -> <integer> */
int ReduceFinalC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* integer1 = node->children[0];

    int error = 0;

    //InvalidateExpr(&gLastExpression);    

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = atoi(integer1->string);

    return error;
}

/* 62. <final> -> <float> */
int ReduceFinalD(SYNTAX_TREE* node)
{
    SYNTAX_TREE* float1 = node->children[0];
    
    int error = 0;

    //InvalidateExpr(&gLastExpression);    

    gLastExpression.type = VAL_FLOATING_POINT;
    gLastExpression.data.floatp = atof(float1->string);
    
    return error;
}

/* 63. <final> -> <string> */
int ReduceFinalE(SYNTAX_TREE* node)
{
    SYNTAX_TREE* string1 = node->children[0];
    
    int error = 0;

    //InvalidateExpr(&gLastExpression);
    
    /*char* working_string;
    // realloc strings
    gLastExpression.type = VAL_STRING;
    working_string = (char*)ALLOC(strlen(string1->string)+1);
    sprintf(working_string, "%s", string1->string);
    printf("copy: '%s'\n", working_string);
    gLastExpression.data.string = working_string;
    gLastExpression.const_string = 0;
d
    IncrementReferences(&gLastExpression);*/

    gLastExpression.type = VAL_STRING;
    gLastExpression.data.string = string1->string;
    gLastExpression.const_string = 1;

    //gLastExpression.data.string = string1->string;
    
    return error;
}

/* 64. <final> -> <object> */
/* 65. <final> -> <reference> */
/* 66. <reference> -> <l-value> */
int ReduceReferenceA(SYNTAX_TREE* node)
{
    SYNTAX_TREE* l_value1 = node->children[0];

    int error = 0;
    error = InterpretNode(l_value1);
    
    if (array_indexing)
    {
        gLastExpression = HashGet(gLValueIndex, gLValueDictionary);
        //IncrementReferences(&gLastExpression);
        //gLastExpression = MakeTemporary(gLastExpression);
        array_indexing = 0;
    }
    else
    {
        gLastExpression = GetRecord(gLValueIdentifier, gLValueContext);
        //IncrementReferences(&gLastExpression);
        //gLastExpression = MakeTemporary(gLastExpression);
    }

    return error;
}
#if 1
/* function call */
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
        CONTEXT* func_context = (CONTEXT*)ALLOC(sizeof(CONTEXT));
        func_context->list = NULL;
        func_context->parent = function.data.function->closure;
        CONTEXT* current = gCurrentContext;
        gCurrentContext = func_context;

        PushExecutionStack(current);
        GCAddContext(func_context, &gGCManager);

        // store params
        
        // call function
        if (function.data.function->built_in) {
            error = function.data.function->functor(0);
            //gLastExpression = MakeTemporary(gLastExpression);
        } else {
            error = InterpretNode(function.data.function->body);
            //gLastExpression = MakeTemporary(gLastExpression);
        }

        // check for error
        if (error) {
            PushCallStack(&gStackTrace, function.data.function/*->fn_name*/);
        } else {
/*            // clear function closure
            PAIR *itr, *itr_next;
            itr = func_context->list;
            while (itr) {
                itr_next = itr->next;
                InvalidateExpr(&itr->value);
                DEALLOC(itr);
                itr = itr_next;
            }
            DEALLOC(func_context); */
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

/* function call with params */
int ReduceReferenceC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* reference1 = node->children[0];
    SYNTAX_TREE* arguments1 = node->children[2];
    int argument_count;

    int error = 0;

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
        CONTEXT* func_context = (CONTEXT*)ALLOC(sizeof(CONTEXT));
        func_context->list = NULL;
        func_context->parent = function.data.function->closure;
        CONTEXT* current = gCurrentContext;
        gCurrentContext = func_context;

        PushExecutionStack(current);
        GCAddContext(func_context, &gGCManager);

        // store params
        // store arguments in the function's closure
		PAIR* last = NULL;
        PAIR* arg_next;
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
            error = function.data.function->functor(0);
            //gLastExpression = MakeTemporary(gLastExpression);
        } else {
            error = InterpretNode(function.data.function->body);
            //gLastExpression = MakeTemporary(gLastExpression);
        }

        // check for error
        if (error) {
            PushCallStack(&gStackTrace, function.data.function/*->fn_name*/);
        } else {
        /*
            // clear function closure
            PAIR *itr, *itr_next;
            itr = func_context->list;
            while (itr) {
                itr_next = itr->next;
                InvalidateExpr(&itr->value);
                DEALLOC(itr);
                itr = itr_next;
            }
            DEALLOC(func_context);*/
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
#endif
#if 0
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
        //gCurrentContext->ref_count = 1;
        gCurrentContext->parent = function.data.function->closure;
        CONTEXT* func_context = gCurrentContext;
        
        if (function.data.function->built_in) {
            error = function.data.function->functor(0);
            gLastExpression = MakeTemporary(gLastExpression);
        } else {
            error = InterpretNode(function.data.function->body);
            gLastExpression = MakeTemporary(gLastExpression);
        }

        if (error) {
            PushCallStack(&gStackTrace, function.data.function/*->fn_name*/);
        } else {
            PAIR *itr, *itr_next;
            itr = func_context->list;
            while (itr) {
                itr_next = itr->next;
                InvalidateExpr(&itr->value);
                DEALLOC(itr);
                itr = itr_next;
            }

            DEALLOC(func_context);
        }

        // return with same context
        gCurrentContext = current;
        returning = 0;
    }
    else
    {
        error = 12345;
        failed_production = node;
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
        gCurrentContext = (CONTEXT*)ALLOC(sizeof(CONTEXT));
        gCurrentContext->list = NULL;
        //gCurrentContext->ref_count = 1;
        gCurrentContext->parent = function.data.function->closure;
        CONTEXT* func_context = gCurrentContext;
        
        // store arguments in the function's closure
		PAIR* last = NULL;
        PAIR* arg_next;
        while (param && arg)
        {
            gLastExpression.type = VAL_NIL;
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

            arg_next = arg->next;
            DEALLOC(arg);
			param = param->next;
			arg = arg_next;
        }
        //arg = gArgumentEvaluation;

        //return_value_exists = 0;
        if (error == 0) 
        {
            if (function.data.function->built_in)
            {
                error = function.data.function->functor(argument_count);
                //gLastExpression = MakeTemporary(gLastExpression);
            } else {        
                error = InterpretNode(function.data.function->body);
                //gLastExpression = MakeTemporary(gLastExpression);
            }
        }

        if (error) {
            PushCallStack(&gStackTrace, function.data.function/*->fn_name*/);
        } else {
            /* invalidate function parameters */
            /* todo:   check for first-class functions
                       referencing this closure, to
                       delay deallocating */
            PAIR *itr, *next_itr;
            itr = func_context->list;
            while (itr) {
                next_itr = itr->next;
                InvalidateExpr(&itr->value);
                DEALLOC(itr);
                itr = next_itr;
            }

            DEALLOC(func_context);
        }

        // return with same context
        gCurrentContext = current;
        returning = 0;
    }
    else
    {
        error = 12345;
        failed_production = node;
    }

    return error;
}
#endif

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

    //InvalidateExpr(&gLastExpression);

    gLastExpression.type = VAL_DICTIONARY;
    gLastExpression.data.dictionary = CreateHashTable();
    GCAddDictionary(gLastExpression.data.dictionary, &gGCManager);
    gLastExpression.data.dictionary->ref_count = 1;

    return error;
}

/* 72. <object> -> [ <array init> ] */
int ReduceObjectB(SYNTAX_TREE* node)
{
    SYNTAX_TREE* array_init1 = node->children[1];

    int error = 0;
    error = InterpretNode(array_init1);

    //InvalidateExpr(&gLastExpression);
    
    gLastExpression.type = VAL_DICTIONARY;
    gLastExpression.data.dictionary = gDictionaryInit;
    GCAddDictionary(gDictionaryInit, &gGCManager);
    gLastExpression.data.dictionary->ref_count = 1;

    return error;
}

/* 73. <object> -> [ <dictionary init> ] */
int ReduceObjectC(SYNTAX_TREE* node)
{
    SYNTAX_TREE* dictionary_init1 = node->children[1];

    int error = 0;
    error = InterpretNode(dictionary_init1);
    
    //InvalidateExpr(&gLastExpression);

    gLastExpression.type = VAL_DICTIONARY;
    gLastExpression.data.dictionary = gDictionaryInit;
    GCAddDictionary(gDictionaryInit, &gGCManager);
    gLastExpression.data.dictionary->ref_count = 1;


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

    //IncrementReferences(&expr);
    
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

    //IncrementReferences(&expr);
    
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

    //IncrementReferences(&expr);

    VALUE key;
    key.type = VAL_STRING;
    key.data.string = identifier1->string;
    key.const_string = 1;

    VALUE dupe = HashGet(key, dictionary);
    if (dupe.type != VAL_NIL) 
    {
        error = 76;
        return error;
    }

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

    //IncrementReferences(&expr);

    gDictionaryInit = CreateHashTable();

    VALUE key;
    key.type = VAL_STRING;
    key.data.string = identifier1->string;
    key.const_string = 1;

    HashStore(key, expr, gDictionaryInit);

    return error;
}

/* 78. <else if> -> end */
/* 79. <boolean> -> true */
int ReduceBooleanA(SYNTAX_TREE* node)
{
    int error = 0;
    
    //InvalidateExpr(&gLastExpression);

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = 1;

    return error;
}

/* 80. <boolean> -> false */
int ReduceBooleanB(SYNTAX_TREE* node)
{
    int error = 0;

    //InvalidateExpr(&gLastExpression);
    
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

    switch (node->production)
    {
        case 0x01: return ReduceProgram(node);
        case 0x02: return ReduceStmtListA(node);
        //case 0x03: return ReduceStmtListB(node);
        case 0x04: return ReduceStmtA(node);
        //case 0x05: return ReduceStmtB(node);
        //case 0x06: return ReduceStmtC(node);
        //case 0x07: return ReduceStmtD(node);
        //case 0x08: return ReduceStmtE(node);
        //case 0x09: return ReduceStmtF(node);
        //case 0x0A: return ReduceStmtG(node);
        //case 0x0B: return ReduceStmtH(node);
        //case 0x0C: return ReduceStmtI(node);
        case 0x0D: return ReduceStmtJ(node);
        case 0x0E: return ReduceStmtK(node);
        case 0x0F: return ReduceStmtL(node);
        case 0x10: return ReduceFunctionDef(node);
        //case 0x11: return ReduceParametersA(node);
        //case 0x12: return ReduceParametersB(node);
        //case 0x13: return ReduceParametersC(node);
        case 0x14: return ReduceParamDeclA(node);
        case 0x15: return ReduceParamDeclB(node);
        case 0x16: return ReduceIf(node);
        //case 0x17: return ReduceElseIfA(node);
        //case 0x18: return ReduceElseIfB(node);
        case 0x19: return ReduceForLoop(node);
        case 0x1A: return ReduceWhileLoop(node);
        case 0x1B: return ReduceAssignmentA(node);
        case 0x1C: return ReduceAssignmentB(node);
        case 0x1D: return ReduceLValueA(node);
        //case 0x1E: return ReduceLValueB(node);
        case 0x1F: return ReduceLValueC(node);
        case 0x20: return ReduceLValueD(node);
        //case 0x21: return ReduceExpr(node);
        case 0x22: return ReduceConditionA(node);
        case 0x23: return ReduceConditionB(node);
        case 0x24: return ReduceConditionC(node);
        case 0x25: return ReduceConditionD(node);
        //case 0x26: return ReduceConditionE(node);
        case 0x27: return ReduceLogicA(node);
        //case 0x28: return ReduceLogicB(node);
        case 0x29: return ReduceComparisonA(node);
        case 0x2A: return ReduceComparisonB(node);
        case 0x2B: return ReduceComparisonC(node);
        case 0x2C: return ReduceComparisonD(node);
        case 0x2D: return ReduceComparisonE(node);
        case 0x2E: return ReduceComparisonF(node);
        //case 0x2F: return ReduceComparisonG(node);
        case 0x30: return ReduceArithmeticA(node);
        case 0x31: return ReduceArithmeticB(node);
        case 0x32: return ReduceArithmeticC(node);
        case 0x33: return ReduceArithmeticD(node);
        //case 0x34: return ReduceArithmeticE(node);
        case 0x35: return ReduceTermA(node);
        case 0x36: return ReduceTermB(node);
        //case 0x37: return ReduceTermC(node);
        case 0x38: return ReduceFactorA(node);
        case 0x39: return ReduceFactorB(node);
        //case 0x3A: return ReduceFactorC(node);
        //case 0x3B: return ReduceFinalA(node);
        //case 0x3C: return ReduceFinalB(node);
        case 0x3D: return ReduceFinalC(node);
        case 0x3E: return ReduceFinalD(node);
        case 0x3F: return ReduceFinalE(node);
        //case 0x40: return ReduceFinalF(node);
        //case 0x41: return ReduceFinalG(node);
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
        //case 0x4E: return ReduceElseIfC(node);
        case 0x4F: return ReduceBooleanA(node);
        case 0x50: return ReduceBooleanB(node);
        // empty production
        case 0xFF: return 0;
    default:
        printf("Unknown production %i.\n", node->production);
        return 1;
    }
}

