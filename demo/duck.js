/*
    Duck Programming Language
    JavaScript Implementation
*/

var halting = 0;
var returning = 0;
var breaking = 0;
var continuing = 0;

var VAL_NIL = 0;
var VAL_PRIMITIVE = 1;
var VAL_STRING = 2;
var VAL_REFERENCE = 3;
var VAL_FUNCTION = 4;
var VAL_FLOATING_POINT = 5;

var DOUBLE_EPSILON = (1.0E-12);

var gParameterListing = [];
var gGlobalContext = {};
var gCurrentContext = {};
var gLastExpression;

var gLValueIdentifier;
var gLValueContext;
var gDictionaryInit;
var gArrayIndex;
var gArrayInit;

function GetRecord(id, context) 
{ 
    while (context) {
        for (var j = 0; j < context.list.length; j++)
        {
            if (context.list[j].identifier == id)
                return context.list[j].value;
        }
        context = context.parent;
    }
    return {type: VAL_NIL};
}

function StoreRecord(id, value, context) 
{
    var top = context;
    while (context) {
        for (var j = 0; j < context.list.length; j++)
        {
            if (context.list[j].identifier == id) {
                context.list[j].value = value;
                return;
            }
        }
        context = context.parent;
    }
    top.list.push({"identifier": id, "value": value});
    return;
}

var gArgumentEvaluation;

/* 1. <program> -> <stmt list> */
function ReduceProgram(node)
{
    if (node.numChildren != 1) return 1;
    var stmt_list1 = node.children[0];

    var error = 0;
    error = InterpretNode(stmt_list1);

    return error;
}

/* 2. <stmt list> -> <stmt> <stmt list> */
function ReduceStmtListA(node)
{
    if (node.numChildren != 2) return 2;
    var stmt1 = node.children[0];
    var stmt_list1 = node.children[1];

    var error = 0;
    if (halting == 0) {
        while (node.numChildren) {
            if (returning == 0 &&
                breaking == 0 &&
                continuing == 0 &&
                error == 0 &&
                halting == 0)
            {
                error = InterpretNode(node.children[0]);
            } else {
                if (halting) {
                    returning = 1;
                    breaking = 1;
                }
                return error;
            }

            if (error == 0 && returning == 0)
            {
            }

            node = node.children[1];
        }
    } else {
        returning = 1;
        breaking = 1;
    }
    return error;   
}

/* 3. <stmt list> -> */
function ReduceStmtListB(node)
{
    if (node.numChildren != 0) return 3;

    var error = 0;

    return error;
}

/* 4. <stmt> -> import <identifier> <endl> */
function ReduceStmtA(node)
{
    if (node.numChildren != 3) return 4;
    var identifier1 = node.children[1];
    var error = 0;

    var library = GetRecord(identifier1.string, gCurrentContext);

    if (library.type == VAL_REFERENCE) {
        var namespace = library.reference;
        var iterator = 0;
        while (iterator < namespace.list.length) {
            StoreRecord(namespace.list[iterator].identifier, 
                namespace.list[iterator].value, 
                gGlobalContext);
            iterator++;
        }
    }

    return error;
}

/* 5. <stmt> -> call <reference> <endl> */
function ReduceStmtB(node)
{
    if (node.numChildren != 3) return 5;
    var reference1 = node.children[1];

    var error = 0;
    error = InterpretNode(reference1);

    return error;
}

/* 6. <stmt> -> <endl> */
function ReduceStmtC(node)
{
    if (node.numChildren != 1) return 6;

    var error = 0;

    return error;
}

/* 7. <stmt> -> <expr> <endl> */
function ReduceStmtD(node)
{
    if (node.numChildren != 2) return 7;
    var expr1 = node.children[0];

    var error = 0;
    error = InterpretNode(expr1);

    return error;
}

/* 8. <stmt> -> <assignment> <endl> */
function ReduceStmtE(node)
{
    if (node.numChildren != 2) return 8;
    var assignment1 = node.children[0];

    var error = 0;
    error = InterpretNode(assignment1);

    return error;
}

/* 9. <stmt> -> <function def> <endl> */
function ReduceStmtF(node)
{
    if (node.numChildren != 2) return 9;
    var function_def1 = node.children[0];

    var error = 0;
    error = InterpretNode(function_def1);

    return error;
}

/* 10. <stmt> -> <if> <endl> */
function ReduceStmtG(node)
{
    if (node.numChildren != 2) return 10;
    var if1 = node.children[0];

    var error = 0;
    error = InterpretNode(if1);
    
    if (!returning) {
      gLastExpression = {type: VAL_NIL, primitive: 0};
    }

    return error;
}

/* 11. <stmt> -> <for loop> <endl> */
function ReduceStmtH(node)
{
    if (node.numChildren != 2) return 11;
    var for_loop1 = node.children[0];

    var error = 0;
    error = InterpretNode(for_loop1);
    
    if (!returning) {
      gLastExpression = {type: VAL_NIL, primitive: 0};
    }

    return error;
}

/* 12. <stmt> -> <while loop> <endl> */
function ReduceStmtI(node)
{
    if (node.numChildren != 2) return 12;
    var while_loop1 = node.children[0];

    var error = 0;
    error = InterpretNode(while_loop1);
    
    if (!returning) {
      gLastExpression = {type: VAL_NIL, primitive: 0};
    }

    return error;
}

/* 13. <stmt> -> return <expr> <endl> */
function ReduceStmtJ(node)
{
    if (node.numChildren != 3) return 13;
    var expr1 = node.children[1];

    var error = 0;
    if (error) return error;
    error = InterpretNode(expr1);

    returning = true;
    continuing = false;

    return error;
}

/* 14. <stmt> -> break <endl> */
function ReduceStmtK(node)
{
    if (node.numChildren != 2) return 14;

    var error = 0;

    breaking = true;
    
    gLastExpression = {type: VAL_NIL, primitive: 0};

    return error;
}

/* 15. <stmt> -> continue <endl> */
function ReduceStmtL(node)
{
    if (node.numChildren != 2) return 15;

    var error = 0;

    continuing = true;
    
    gLastExpression = {type: VAL_NIL, primitive: 0};

    return error;
}

/* 16. <function def> -> function <identifier> <parameters> <endl> <stmt list> end */
function ReduceFunctionDef(node)
{
    if (node.numChildren != 6) return 16;
    var identifier1 = node.children[1];
    var parameters1 = node.children[2];
    var stmt_list1 = node.children[4];

    var error = 0;

    gParameterListing = [];

    error = InterpretNode(parameters1);
    if (error == 0)
    {
        var record = {};
        record.type = VAL_FUNCTION;
        record.func = {};
        record.func.parameters = gParameterListing;
        record.func.body = stmt_list1;
        record.func.closure = gCurrentContext;
        record.func.built_in = 0;
        record.func.functor = undefined;
        record.func.fn_name = identifier1.string;

        StoreRecord(identifier1.string, record, gCurrentContext);
        gLastExpression = record;
    }
    return error;
}

/* 17. <parameters> -> */
function ReduceParametersA(node)
{
    if (node.numChildren != 0) return 17;

    var error = 0;

    return error;
}

/* 18. <parameters> -> ( ) */
function ReduceParametersB(node)
{
    if (node.numChildren != 2) return 18;

    var error = 0;

    return error;
}

/* 19. <parameters> -> ( <param decl> ) */
function ReduceParametersC(node)
{
    if (node.numChildren != 3) return 19;
    var param_decl1 = node.children[1];

    var error = 0;
    if (error) return error;
    error = InterpretNode(param_decl1);

    return error;
}

/* 20. <param decl> -> <identifier> */
function ReduceParamDeclA(node)
{
    if (node.numChildren != 1) return 20;
    var identifier1 = node.children[0];

    var error = 0;

    gParameterListing.push(identifier1.string);

    return error;
}

/* 21. <param decl> -> <param decl> , <identifier> */
function ReduceParamDeclB(node)
{
    if (node.numChildren != 3) return 21;
    var param_decl1 = node.children[0];
    var identifier1 = node.children[2];

    var error = 0;
    error = InterpretNode(param_decl1);
    if (error) return error;

    gParameterListing.push(identifier1.string);

    return error;
}

/* 22. <if> -> if <condition> then <endl> <stmt list> <else if> */
function ReduceIf(node)
{
    if (node.numChildren != 6) return 22;
    var condition1 = node.children[1];
    var stmt_list1 = node.children[4];
    var else_if1 = node.children[5];

    var error = 0;
    error = InterpretNode(condition1);
    if (error) return error;

    if (EvaluatesTrue(gLastExpression))
    {
        error = InterpretNode(stmt_list1);
    } else {
        error = InterpretNode(else_if1);
    }

    return error;
}

/* 23. <else if> -> else <endl> <stmt list> end */
function ReduceElseIfA(node)
{
    if (node.numChildren != 4) return 23;
    var stmt_list1 = node.children[2];

    var error = 0;

    error = InterpretNode(stmt_list1);

    return error;
}

/* 24. <else if> -> else <if> */
function ReduceElseIfB(node)
{
    if (node.numChildren != 2) return 24;
    var if1 = node.children[1];

    var error = 0;

    error = InterpretNode(if1);

    return error;
}

/* 25. <for loop> -> for <identifier> = <arithmetic> to <arithmetic> do <endl> <stmt list> loop */
function ReduceForLoop(node)
{
    if (node.numChildren != 10) return 25;
    var identifier1 = node.children[1];
    var arithmetic1 = node.children[3];
    var arithmetic2 = node.children[5];
    var stmt_list1 = node.children[8];

    var error = 0;

    var start, end;
    var id = identifier1.string;
    
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
                && start.floatp <= end.floatp
                && error == 0
                && breaking == 0
                && returning == 0)
        {
            StoreRecord(id, start, gCurrentContext);
            error = InterpretNode(stmt_list1);
            if (breaking == 0)
            {
                continuing = 0;
                start.floatp = start.floatp + 1.0;
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
                && breaking == 0
                && returning == 0)
        {
            StoreRecord(id, start, gCurrentContext);
            error = InterpretNode(stmt_list1);
            if (breaking == 0)
            {
                continuing = 0;
                start.primitive++;
            }
        }

    }
    else
    {
        error = 25;
        breaking = 0;
        return error;
    }

    breaking = 0;

    return error;
}

/* 26. <while loop> -> while <condition> do <endl> <stmt list> loop */
function ReduceWhileLoop(node)
{
    if (node.numChildren != 6) return 26;
    var condition1 = node.children[1];
    var stmt_list1 = node.children[4];

    var error = 0;
    error = InterpretNode(condition1);
    while (EvaluatesTrue(gLastExpression)
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

/* 27. <assignment> -> <l-value> = <assignment> */
function ReduceAssignmentA(node)
{
    if (node.numChildren != 3) return 27;
    var l_value1 = node.children[0];
    var assignment1 = node.children[2];

    var error = 0;

    error = InterpretNode(assignment1);
    var expr = gLastExpression;

    if (error) return error;
    error = InterpretNode(l_value1);
    
    if (error == 0)
    {
        StoreRecord(gLValueIdentifier, expr, gLValueContext);
    }        

    gLastExpression = expr;

    return error;
}

/* 28. <assignment> -> <l-value> = <condition> */
function ReduceAssignmentB(node)
{
    if (node.numChildren != 3) return 28;
    var l_value1 = node.children[0];
    var condition1 = node.children[2];

    var error = 0;

    error = InterpretNode(condition1);
    var expr = gLastExpression;

    if (error) return error;
    error = InterpretNode(l_value1);
    
    if (error == 0)
    {
        StoreRecord(gLValueIdentifier, expr, gLValueContext);
    }        

    gLastExpression = expr;


    return error;
}

/* 29. <l-value> -> <identifier> */
function ReduceLValueA(node)
{
    if (node.numChildren != 1) return 29;
    var identifier1 = node.children[0];

    var error = 0;

    gLValueIdentifier = identifier1.string;
    gLValueContext = gCurrentContext;

    return error;
}

/* 30. <l-value> -> ( <l-value> ) */
function ReduceLValueB(node)
{
    if (node.numChildren != 3) return 30;
    var l_value1 = node.children[1];

    var error = 0;

    error = InterpretNode(l_value1);

    return error;
}

/* 31. <l-value> -> <reference> . <identifier> */
function ReduceLValueC(node)
{
    if (node.numChildren != 3) return 31;
    var reference1 = node.children[0];
    var identifier1 = node.children[2];

    var error = 0;
    error = InterpretNode(reference1);
    if (error) return error;

    if (gLastExpression.type == VAL_REFERENCE)
    {
        gLValueIdentifier = identifier1.string;
        gLValueContext = gLastExpression.reference;
    }
    else
    {
        error = 31;
        failed_production = node;
    }

    return error;
}

/* 32. <l-value> -> <reference> [ <expr> ] */
function ReduceLValueD(node)
{
    if (node.numChildren != 4) return 32;
    var reference1 = node.children[0];
    var expr1 = node.children[2];

    var error = 0;
    
    error = InterpretNode(reference1);
    var reference = gLastExpression;
    if (error) return error;
    
    error = InterpretNode(expr1);
    var index = gLastExpression;
    if (error) return error;

    if (reference.type == VAL_REFERENCE &&
        (index.type == VAL_STRING || index.type == VAL_PRIMITIVE))
    {
        var string;
        if (index.type == VAL_PRIMITIVE) {
            string = index.primitive + "";
        } else {
            string = index.string;
        }
        gLValueIdentifier = string;
        gLValueContext = reference.reference;
    }
/*  else if (reference.type == VAL_DICTIONARY)
    {

    } */
    else
    {
        error = 32;
        failed_production = node;
    }

    return error;
}

/* 33. <expr> -> <condition> */
function ReduceExpr(node)
{
    if (node.numChildren != 1) return 33;
    var condition1 = node.children[0];

    var error = 0;
    error = InterpretNode(condition1);

    return error;
}

/* 34. <condition> -> <condition> and <logic> */
function ReduceConditionA(node)
{
    if (node.numChildren != 3) return 34;
    var condition1 = node.children[0];
    var logic1 = node.children[2];

    var error = 0;
    error = InterpretNode(condition1);
    if (error) return error;

    if (EvaluatesTrue(gLastExpression)) {
        /* fall through */
        error = InterpretNode(logic1);
        return error;
    }
    else
    {
        gLastExpression = {type: VAL_PRIMITIVE,
                           primitive: 0};
    }

    return error;
}

/* 35. <condition> -> <condition> or <logic> */
function ReduceConditionB(node)
{
    if (node.numChildren != 3) return 35;
    var condition1 = node.children[0];
    var logic1 = node.children[2];

    var error = 0;
    error = InterpretNode(condition1);
    if (error) return error;

    if (EvaluatesTrue(gLastExpression)) 
    {
        return error;
    }
       
    error = InterpretNode(logic1);

    return error;
}

/* 36. <condition> -> <condition> nor <logic> */
function ReduceConditionC(node)
{
    if (node.numChildren != 3) return 36;
    var condition1 = node.children[0];
    var logic1 = node.children[2];

    var error = 0;
    error = InterpretNode(condition1);
    if (error) return error;

    if (EvaluatesTrue(gLastExpression))
    {
        gLastExpression = {type: VAL_PRIMITIVE,
                           primitive: 0};
        return error;
    }
    error = InterpretNode(logic1);
    if (error) return error;

    if (EvaluatesTrue(gLastExpression))
    {
        gLastExpression = {type: VAL_PRIMITIVE,
                           primitive: 0};
        return 0;
    }
    else
    {
        gLastExpression = {type: VAL_PRIMITIVE,
                           primitive: 1};
    }

    return error;
}

/* 37. <condition> -> <condition> xor <logic> */
function ReduceConditionD(node)
{
    if (node.numChildren != 3) return 37;
    var condition1 = node.children[0];
    var logic1 = node.children[2];

    var error = 0;

    error = InterpretNode(condition1);
    if (error) return error;
    var condition = gLastExpression;

    error = InterpretNode(logic1);
    if (error) return error;
    var logic = gLastExpression;

    if (EvaluatesTrue(condition) &&
        !EvaluatesTrue(logic))
    {
        gLastExpression = condition;
        return error;
    }
    else if (EvaluatesTrue(logic) &&
            !EvaluatesTrue(condition))
    {
        gLastExpression = logic;
        return error;
    }
    else
    {
        gLastExpression = {type: VAL_PRIMITIVE,
                           primitive: 0};
    }

    return error;
}

/* 38. <condition> -> <logic> */
function ReduceConditionE(node)
{
    if (node.numChildren != 1) return 38;
    var logic1 = node.children[0];

    var error = 0;
    error = InterpretNode(logic1);

    return error;
}

/* 39. <logic> -> not <comparison> */
function ReduceLogicA(node)
{
    if (node.numChildren != 2) return 39;
    var comparison1 = node.children[1];

    var error = 0;

    error = InterpretNode(comparison1);
    if (error) return error;

    if (gLastExpression.type == VAL_PRIMITIVE)
    {
        gLastExpression.primitive = (gLastExpression.primitive ? 0 : 1);
    }
    else if (gLastExpression.type == VAL_NIL)
    {
        gLastExpression = {type: VAL_PRIMITIVE, primitive: 1};
    }
    else
    {
        gLastExpression = {type: VAL_NIL, primitive: 0};
    }

    return error;
}

/* 40. <logic> -> <comparison> */
function ReduceLogicB(node)
{
    if (node.numChildren != 1) return 40;
    var comparison1 = node.children[0];

    var error = 0;
    error = InterpretNode(comparison1);

    return error;
}

/* 41. <comparison> -> <comparison> == <arithmetic> */
function ReduceComparisonA(node)
{
    if (node.numChildren != 3) return 41;
    var comparison1 = node.children[0];
    var arithmetic1 = node.children[2];

    var error = 0;
    error = InterpretNode(comparison1);
    if (error) return error;
    var comparison = gLastExpression;

    error = InterpretNode(arithmetic1);
    if (error) return error;
    var arithmetic = gLastExpression;

    if (comparison.type == arithmetic.type)
    {
        gLastExpression = {type: VAL_PRIMITIVE, primitive: 0};
        if (comparison.type == VAL_PRIMITIVE)
        {
            gLastExpression.primitive = 
                (comparison.primitive == arithmetic.primitive);
        }
        else if (comparison.type == VAL_FLOATING_POINT)
        {
            gLastExpression.primitive = 
                (comparison.floatp == arithmetic.floatp);
        }
        else if (comparison.type == VAL_STRING)
        {
            gLastExpression.primitive = 
                (comparison.string == arithmetic.string);
        }
        else if (comparison.type == VAL_REFERENCE)
        {
            gLastExpression.primitive = 
                (comparison.reference == arithmetic.reference);
        }
        else if (comparison.type == VAL_FUNCTION)
        {
            gLastExpression.primitive = 
                (comparison.func == arithmetic.func);
        }
        else if (comparison.type == VAL_NIL)
        {
            gLastExpression.primitive = 1;
        }
        else
        {
            program.output("Unknown type.");
            return 41;
        }
    }
    else
    {
        gLastExpression = {type: VAL_PRIMITIVE, primitive: 0};
    }

    return error;
}

/* 42. <comparison> -> <comparison> != <arithmetic> */
function ReduceComparisonB(node)
{
    if (node.numChildren != 3) return 42;
    var comparison1 = node.children[0];
    var arithmetic1 = node.children[2];

    var error = 0;

    error = InterpretNode(comparison1);
    if (error) return error;
    var comparison = gLastExpression;

    error = InterpretNode(arithmetic1);
    if (error) return error;
    var arithmetic = gLastExpression;

    if (comparison.type == arithmetic.type)
    {
        gLastExpression = {type: VAL_PRIMITIVE, primitive: 0};
        if (comparison.type == VAL_PRIMITIVE)
        {
            gLastExpression.primitive = 
                (comparison.primitive == arithmetic.primitive);
        }
        else if (comparison.type == VAL_FLOATING_POINT)
        {
            gLastExpression.primitive = 
                (comparison.floatp == arithmetic.floatp);
        }
        else if (comparison.type == VAL_STRING)
        {
            gLastExpression.primitive = 
                (comparison.string == arithmetic.string);
        }
        else if (comparison.type == VAL_REFERENCE)
        {
            gLastExpression.primitive = 
                (comparison.reference == arithmetic.reference);
        }
        else if (comparison.type == VAL_FUNCTION)
        {
            gLastExpression.primitive = 
                (comparison.func == arithmetic.func);
        }
        else if (comparison.type == VAL_NIL)
        {
            gLastExpression.primitive = 1;
        }
        else
        {
            program.output("Unknown type.");
            return 41;
        }
    }
    else
    {
        gLastExpression = {type: VAL_PRIMITIVE, primitive: 0};
    }

    gLastExpression.primitive = gLastExpression.primitive ? 0 : 1;

    return error;
}

/* 43. <comparison> -> <comparison> < <arithmetic> */
function ReduceComparisonC(node)
{
    if (node.numChildren != 3) return 43;
    var comparison1 = node.children[0];
    var arithmetic1 = node.children[2];

    var error = 0;

    error = InterpretNode(comparison1);
    var comparison = gLastExpression;
    if (error) return error;

    error = InterpretNode(arithmetic1);
    var arithmetic = gLastExpression;
    if (error) return error;

    gLastExpression = CompareLessThan(comparison, arithmetic);

    return error;
}

/* 44. <comparison> -> <comparison> > <arithmetic> */
function ReduceComparisonD(node)
{
    if (node.numChildren != 3) return 44;
    var comparison1 = node.children[0];
    var arithmetic1 = node.children[2];

    var error = 0;

    error = InterpretNode(comparison1);
    var comparison = gLastExpression;
    if (error) return error;

    error = InterpretNode(arithmetic1);
    var arithmetic = gLastExpression;
    if (error) return error;

    gLastExpression = CompareGreaterThan(comparison, arithmetic);

    return error;
}

/* 45. <comparison> -> <comparison> <= <arithmetic> */
function ReduceComparisonE(node)
{
    if (node.numChildren != 3) return 45;
    var comparison1 = node.children[0];
    var arithmetic1 = node.children[2];

    var error = 0;

    error = InterpretNode(comparison1);
    var comparison = gLastExpression;
    if (error) return error;

    error = InterpretNode(arithmetic1);
    var arithmetic = gLastExpression;
    if (error) return error;

    gLastExpression = CompareLessThanOrEqual(comparison, arithmetic);

    return error;
}

/* 46. <comparison> -> <comparison> >= <arithmetic> */
function ReduceComparisonF(node)
{
    if (node.numChildren != 3) return 46;
    var comparison1 = node.children[0];
    var arithmetic1 = node.children[2];

    var error = 0;

    error = InterpretNode(comparison1);
    var comparison = gLastExpression;
    if (error) return error;

    error = InterpretNode(arithmetic1);
    var arithmetic = gLastExpression;
    if (error) return error;

    gLastExpression = CompareGreaterThanOrEqual(comparison, arithmetic);

    return error;
}

/* 47. <comparison> -> <arithmetic> */
function ReduceComparisonG(node)
{
    if (node.numChildren != 1) return 47;
    var arithmetic1 = node.children[0];

    var error = 0;
    error = InterpretNode(arithmetic1);

    return error;
}

/* 48. <arithmetic> -> <arithmetic> + <term> */
function ReduceArithmeticA(node)
{
    if (node.numChildren != 3) return 48;
    var arithmetic1 = node.children[0];
    var term1 = node.children[2];

    var error = 0;

    error = InterpretNode(arithmetic1);
    if (error) return error;
    var arithmetic = gLastExpression;

    error = InterpretNode(term1);
    if (error) return error;
    var term = gLastExpression;    

    if (arithmetic.type == VAL_STRING || term.type == VAL_STRING)
    {
        gLastExpression = Concat(arithmetic, term);
    }
    else
    {
        gLastExpression = Add(arithmetic, term);
    }

    return error;
}

/* 49. <arithmetic> -> <arithmetic> - <term> */
function ReduceArithmeticB(node)
{
    if (node.numChildren != 3) return 49;
    var arithmetic1 = node.children[0];
    var term1 = node.children[2];

    var error = 0;

    error = InterpretNode(arithmetic1);
    if (error) return error;
    var arithmetic = gLastExpression;

    error = InterpretNode(term1);
    if (error) return error;
    var term = gLastExpression;    

    gLastExpression = Subtract(arithmetic, term);

    return error;
}

/* 50. <arithmetic> -> <arithmetic> & <term> */
function ReduceArithmeticC(node)
{
    return 50;
}

/* 51. <arithmetic> -> <arithmetic> | <term> */
function ReduceArithmeticD(node)
{
    return 51;
}

/* 52. <arithmetic> -> <term> */
function ReduceArithmeticE(node)
{
    if (node.numChildren != 1) return 52;
    var term1 = node.children[0];

    var error = 0;
    error = InterpretNode(term1);

    return error;
}

/* 53. <term> -> <term> * <factor> */
function ReduceTermA(node)
{
    if (node.numChildren != 3) return 53;
    var term1 = node.children[0];
    var factor1 = node.children[2];

    var error = 0;

    error = InterpretNode(term1);
    if (error) return error;
    var term = gLastExpression;

    error = InterpretNode(factor1);
    if (error) return error;
    var factor = gLastExpression;

    /* multiplication */
    gLastExpression = Multiply(term, factor);

    return error;
}

/* 54. <term> -> <term> / <factor> */
function ReduceTermB(node)
{
    if (node.numChildren != 3) return 54;
    var term1 = node.children[0];
    var factor1 = node.children[2];

    var error = 0;

    error = InterpretNode(term1);
    if (error) return error;
    var term = gLastExpression;

    error = InterpretNode(factor1);
    if (error) return error;
    var factor = gLastExpression;

    /* division */
    gLastExpression = Divide(term, factor);

    return error;
}

/* 55. <term> -> <factor> */
function ReduceTermC(node)
{
    if (node.numChildren != 1) return 55;
    var factor1 = node.children[0];

    var error = 0;
    error = InterpretNode(factor1);

    return error;
}

/* 56. <factor> -> - <factor> */
function ReduceFactorA(node)
{
    if (node.numChildren != 2) return 56;
    var factor1 = node.children[1];

    var error = 0;

    error = InterpretNode(factor1);
    if (error) return error;

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
        gLastExpression.type = VAL_NIL;
    }

    return error;
}

/* 57. <factor> -> ! <factor> */
function ReduceFactorB(node)
{
    if (node.numChildren != 2) return 57;
    var factor1 = node.children[1];

    var error = 0;

    error = InterpretNode(factor1);
    if (error) return error;

    if (gLastExpression.type == VAL_PRIMITIVE)
    {
        gLastExpression.primitive = (gLastExpression.primitive ? 0 : 1);
    }
    else if (gLastExpression.type == VAL_NIL)
    {
        gLastExpression = {type: VAL_PRIMITIVE, primitive: 1};
    }
    else
    {
        gLastExpression = {type: VAL_NIL, primitive: 0};
    }

    return error;
}

/* 58. <factor> -> <final> */
function ReduceFactorC(node)
{
    if (node.numChildren != 1) return 58;
    var final1 = node.children[0];

    var error = 0;
    error = InterpretNode(final1);

    return error;
}

/* 59. <final> -> ( <expr> ) */
function ReduceFinalA(node)
{
    if (node.numChildren != 3) return 59;
    var expr1 = node.children[1];

    var error = 0;
    if (error) return error;
    error = InterpretNode(expr1);

    return error;
}

/* 60. <final> -> <boolean> */
function ReduceFinalB(node)
{
    if (node.numChildren != 1) return 60;
    var boolean1 = node.children[0];

    var error = 0;
    error = InterpretNode(boolean1);

    return error;
}

/* 61. <final> -> <integer> */
function ReduceFinalC(node)
{
    if (node.numChildren != 1) return 61;
    var integer1 = node.children[0];

    var error = 0;

    gLastExpression = {};
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.primitive = parseInt(integer1.string);

    return error;
}

/* 62. <final> -> <float> */
function ReduceFinalD(node)
{
    if (node.numChildren != 1) return 62;
    var float1 = node.children[0];

    var error = 0;

    gLastExpression = {};
    gLastExpression.type = VAL_FLOATING_POINT;
    gLastExpression.floatp = parseFloat(float1.string);

    return error;
}

/* 63. <final> -> <string> */
function ReduceFinalE(node)
{
    if (node.numChildren != 1) return 63;
    var string1 = node.children[0];

    var error = 0;

    gLastExpression = {};
    gLastExpression.type = VAL_STRING;
    gLastExpression.string = string1.string;

    return error;
}

/* 64. <final> -> <object> */
function ReduceFinalF(node)
{
    if (node.numChildren != 1) return 64;
    var object1 = node.children[0];

    var error = 0;
    error = InterpretNode(object1);

    return error;
}

/* 65. <final> -> <reference> */
function ReduceFinalG(node)
{
    if (node.numChildren != 1) return 65;
    var reference1 = node.children[0];

    var error = 0;
    error = InterpretNode(reference1);

    return error;
}

/* 66. <reference> -> <l-value> */
function ReduceReferenceA(node)
{
    if (node.numChildren != 1) return 66;
    var l_value1 = node.children[0];

    var error = 0;
    error = InterpretNode(l_value1);

    gLastExpression = GetRecord(gLValueIdentifier, gLValueContext);

    return error;
}

/* 67. <reference> -> <reference> ( ) */
function ReduceReferenceB(node)
{
    if (node.numChildren != 3) return 67;
    var reference1 = node.children[0];

    var error = 0;

    error = InterpretNode(reference1);
    if (error) return error;
    var func = gLastExpression;

    if (func.type == VAL_FUNCTION)
    {
        var func_context = {};
        func_context.list = [];
        func_context.parent = func.func.closure;
        var current = gCurrentContext;
        gCurrentContext = func_context;

        if (func.func.built_in) {
            error = func.func.functor(0);
        } else {
            error = InterpretNode(func.func.body);
        }

        // check for error
        if (error) {
            // push error callstack
        } else {
        }

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
function ReduceReferenceC(node)
{
    if (node.numChildren != 4) return 68;
    var reference1 = node.children[0];
    var arguments1 = node.children[2];

    var error = 0;

    error = InterpretNode(reference1);
    if (error) return error;
    var func = gLastExpression;

    if (func.type == VAL_FUNCTION)
    {
        // evaluate arguments
        error = InterpretNode(arguments1);
        var param = func.func.parameters;
        var arg = gArgumentEvaluation;

        if (error) return error;
    
        // create new context
        var func_context = {};
        func_context.list = [];
        func_context.parent = func.func.closure;
        var current = gCurrentContext;
        gCurrentContext = func_context;

        // store params
        var i = 0;
        for (; i < param.length && i < arg.length; i++)
        {
            func_context.list.push({"identifier": param[i], "value": arg[i]});
        }

        // call function
        if (func.func.built_in) {
            error = func.func.functor(0);
        } else {
            error = InterpretNode(func.func.body);
        }

        // check for error
        if (error) {
            // push call stack for error
        } else {
        }

        // return with same context
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

/* 69. <arguments> -> <arguments> , <expr> */
function ReduceArgumentsA(node)
{
    if (node.numChildren != 3) return 69;
    var arguments1 = node.children[0];
    var expr1 = node.children[2];

    var error = 0;
    error = InterpretNode(arguments1);
    if (error) return error;
    
    arguments = gArgumentEvaluation;

    error = InterpretNode(expr1);
    
    arguments.push(gLastExpression);
    
    gArgumentEvaluation = arguments;

    return error;
}

/* 70. <arguments> -> <expr> */
function ReduceArgumentsB(node)
{
    if (node.numChildren != 1) return 70;
    var expr1 = node.children[0];

    var error = 0;
    error = InterpretNode(expr1);
    if (error) return error;

    gArgumentEvaluation = [];
    gArgumentEvaluation.push(gLastExpression);

    return error;
}

/* 71. <object> -> [ ] */
function ReduceObjectA(node)
{
    if (node.numChildren != 2) return 71;

    var error = 0;

    gLastExpression = {};
    gLastExpression.type = VAL_REFERENCE;
    gLastExpression.reference = {};
    gLastExpression.reference.parent = undefined;
    gLastExpression.reference.list = [];

    return error;
}

/* 72. <object> -> [ <array init> ] */
function ReduceObjectB(node)
{
    if (node.numChildren != 3) return 72;
    var array_init1 = node.children[1];

    var error = 0;
    if (error) return error;
    error = InterpretNode(array_init1);

    gLastExpression = {};
    gLastExpression.type = VAL_REFERENCE;
    gLastExpression.reference = gArrayInit;

    return error;
}

/* 73. <object> -> [ <dictionary init> ] */
function ReduceObjectC(node)
{
    if (node.numChildren != 3) return 73;
    var dictionary_init1 = node.children[1];

    var error = 0;
    if (error) return error;
    error = InterpretNode(dictionary_init1);

    gLastExpression = {};
    gLastExpression.type = VAL_REFERENCE;
    gLastExpression.reference = gDictionaryInit;

    return error;
}

/* 74. <array init> -> <array init> , <expr> */
function ReduceArrayInitA(node)
{
    if (node.numChildren != 3) return 74;
    var array_init1 = node.children[0];
    var expr1 = node.children[2];

    var error = 0;
    error = InterpretNode(array_init1);
    if (error) return error;

    var nIndex = (gArrayIndex+1);
    var nArray = gArrayInit;

    error = InterpretNode(expr1);
    if (error) return error;

    nArray.list.push({
        "identifier": nIndex + "",
        "value": gLastExpression
    });

    gArrayIndex = nIndex;
    gArrayInit = nArray;

    return error;
}

/* 75. <array init> -> <expr> */
function ReduceArrayInitB(node)
{
    if (node.numChildren != 1) return 75;
    var expr1 = node.children[0];

    var error = 0;
    error = InterpretNode(expr1);
    if (error) return error;

    gArrayInit = {};
    gArrayInit.parent = undefined;
    gArrayInit.list = [];

    gArrayIndex = 0;

    gArrayInit.list.push({
        "identifier": gArrayIndex + "", 
        "value": gLastExpression
    });

    return error;
}

/* 76. <dictionary init> -> <dictionary init> , <identifier> : <expr> */
function ReduceDictionaryInitA(node)
{
    if (node.numChildren != 5) return 76;
    var dictionary_init1 = node.children[0];
    var identifier1 = node.children[2];
    var expr1 = node.children[4];

    var error = 0;
    error = InterpretNode(dictionary_init1);
    if (error) return error;    

    var nDict = gDictionaryInit;

    error = InterpretNode(expr1);
    if (error) return error;

    nDict.list.push({
        "identifier": identifier1.string,
        "value": gLastExpression
    });

    gDictionaryInit = nDict;

    return error;
}

/* 77. <dictionary init> -> <identifier> : <expr> */
function ReduceDictionaryInitB(node)
{
    if (node.numChildren != 3) return 77;
    var identifier1 = node.children[0];
    var expr1 = node.children[2];

    var error = 0;
    error = InterpretNode(expr1);

    gDictionaryInit = {};
    gDictionaryInit.parent = undefined;
    gDictionaryInit.list = [];

    gDictionaryInit.list.push({
        "identifier": identifier1.string,
        "value": gLastExpression
    });

    return error;
}

/* 78. <else if> -> end */
function ReduceElseIfC(node)
{
    if (node.numChildren != 1) return 78;

    var error = 0;

    return error;
}

/* 79. <boolean> -> true */
function ReduceBooleanA(node)
{
    if (node.numChildren != 1) return 79;

    var error = 0;

    gLastExpression = {};
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.primitive = 1;

    return error;
}

/* 80. <boolean> -> false */
function ReduceBooleanB(node)
{
    if (node.numChildren != 1) return 80;

    var error = 0;

    gLastExpression = {};
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.primitive = 0;

    return error;
}

/* reduce one node */
function InterpretNode(node)
{
    if (node === undefined || node.production == 0)
        return -1;

    switch (node.production)
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
        case 0x10: return ReduceFunctionDef(node);
        case 0x11: return ReduceParametersA(node);
        case 0x12: return ReduceParametersB(node);
        case 0x13: return ReduceParametersC(node);
        case 0x14: return ReduceParamDeclA(node);
        case 0x15: return ReduceParamDeclB(node);
        case 0x16: return ReduceIf(node);
        case 0x17: return ReduceElseIfA(node);
        case 0x18: return ReduceElseIfB(node);
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
        case 0x4E: return ReduceElseIfC(node);
        case 0x4F: return ReduceBooleanA(node);
        case 0x50: return ReduceBooleanB(node);
    default:
        program.output("Unknown production " + node.production);
//        return -1;
        return 0;
    }
}


function InterpretProgram(syntax_tree, use_existing_environment) 
{
    halting = 0;
    returning = 0;
    breaking = 0;
    continuing = 0;

    if (use_existing_environment === undefined || !use_existing_environment)
    {
      gGlobalContext = {"parent": undefined, list: []};
    }
    gCurrentContext = gGlobalContext;
    gLastExpression = {type: VAL_NIL, primitive: 0};
    gParameterListing = undefined;

    gLValueIdentifier = "";
    gLValueContext = undefined;

    gDictionaryInit = undefined;
    gArrayIndex = 0;
    gArrayInit = undefined;
    gArgumentEvaluation = undefined;

    failed_production = undefined;
    line_error = -1;

    if (use_existing_environment === undefined || !use_existing_environment)
    {
      BindStandardLibrary();
    }

//    BindMathLibrary();
//    BindRandLibrary();
//    BindAdditionalLibraries();

    var error = InterpretNode(syntax_tree);

    //if (error) alert("Error: " + error);
    if (error) { /*program.output("Error: " + error);*/ 
        if (error == 12345)
        {
            program.output("Reference error.\n");
        }
        else
        {
            program.output("Error " + error + ".\n");
        }
    }
    return gLastExpression;
}

var duck_grammar;
function StartUpDuckRuntime()
{
  duck_grammar = LoadGrammar(DUCK_GRAMMAR);
  // ...
}

function TestParse(source)
{
  var lexing = LexSource(source, duck_grammar);
  if (lexing) {
      return ParseSucceeds(lexing, PARSE_TABLE, duck_grammar);
  } else {
      return -1;
  }
}

var runcount = 0;
function RunAndPrintValue(source)
{
  var lexing = LexSource(source, duck_grammar);
  if (lexing) {
    var parsing = ParseSource(lexing, PARSE_TABLE, duck_grammar);
    if (parsing) {
      var expr = InterpretProgram(parsing, (runcount > 0));
      runcount++;
      if (expr !== undefined && expr.type != VAL_NIL)
      {
        if (expr.type == VAL_STRING) {
            program.output(">> " + expr.string);
        } else if (expr.type == VAL_PRIMITIVE) {
            program.output(">> " + expr.primitive + "");
        } else if (expr.type == VAL_FLOATING_POINT) {
            program.output(">> " + expr.floatp + "");
        } else if (expr.type == VAL_FUNCTION) {
            program.output(">> " + "function");
        } else if (expr.type == VAL_REFERENCE) {
            program.output(">> " + "reference");
        } else {
            program.output(">> " + "unknown");
        }
        program.output("");
      }
    } else {
      program.output("Error, parsing source.");
    }
  } else {
      program.output("Error, lexing source code.");
  }
}

function Interpret(source_code)
{
    var grammar = LoadGrammar(DUCK_GRAMMAR);
    if (grammar) {
        var lexing = LexSource(source_code, grammar);
        if (lexing) {
            var parsing = ParseSource(lexing, PARSE_TABLE, grammar);
            if (parsing) {
//                alert(JSON.stringify(parsing));
                return InterpretProgram(parsing);
            } else {
                program.output("Error, parsing source.");
            }
        } else {
            program.output("Error, lexing source code.");
        }
    } else {
        program.output("Error, loading programming language grammar.");
    }
}


