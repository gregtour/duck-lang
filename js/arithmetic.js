/* arithmetic.js */

function EvaluatesTrue(value)
{
    return ((value.type == VAL_PRIMITIVE &&
             value.primitive) ||
            (value.type == VAL_FLOATING_POINT &&
             Math.abs(value.floatp) > DOUBLE_EPSILON) ||
            (value.type == VAL_STRING ||
             value.type == VAL_REFERENCE ||
             value.type == VAL_FUNCTION));
}

function CoerceString(val)
{
    var string = "";
    if (val.type == VAL_FLOATING_POINT) {
        return val.floatp + "";
    } else if (val.type == VAL_PRIMITIVE) {
        return val.primitive + "";
    } else if (val.type == VAL_STRING) {
        return val.string;
    } else if (val.type == VAL_REFERENCE) {
        return "reference";
    } else if (val.type == VAL_FUNCTION) {
        return "function";
    } else if (val.type == VAL_NIL) {
        return "nill";
    } else {
        return "unknown type";
    }
}

function CoerceInt(val)
{
    if (val.type == VAL_FLOATING_POINT) {
        return parseInt(val.floatp);
    } else if (val.type == VAL_PRIMITIVE) {
        return val.primitive;
    } else if (val.type == VAL_STRING) {
        return parseInt(val.string);
    } else if (val.type == VAL_REFERENCE ||
               val.type == VAL_FUNCTION ||
               val.type == VAL_NIL)
    {
        return 0;
    } else {
        return 0;
    }
}

function CoerceFloat(val)
{
    if (val.type == VAL_FLOATING_POINT) {
        return val.floatp;
    } else if (val.type == VAL_PRIMITIVE) {
        return parseFloat(val.primitive);
    } else if (val.type == VAL_STRING) {
        return parseFloat(val.string);
    } else if (val.type == VAL_REFERENCE ||
               val.type == VAL_FUNCTION ||
               val.type == VAL_NIL)
    {
        return 0.0;
    } else {
        return 0.0;
    }
}


function Concat(a, b)
{
    var value = {};
    value.type = VAL_STRING;
    value.string = CoerceString(a) + CoerceString(b);
    return value;
}

function Add(a, b)
{
    if (a.type == VAL_FLOATING_POINT ||
        b.type == VAL_FLOATING_POINT)
    {
        return {type: VAL_FLOATING_POINT, 
              floatp: CoerceFloat(a) + CoerceFloat(b)};
    }
    else if (a.type == VAL_PRIMITIVE ||
             b.type == VAL_PRIMITIVE)
    {
        return {type: VAL_PRIMITIVE,
           primitive: CoerceInt(a) + CoerceInt(b)};
    }
    else
    {
        return {type: VAL_NIL};
    }
}

function Subtract(a, b)
{
    if (a.type == VAL_FLOATING_POINT ||
        b.type == VAL_FLOATING_POINT)
    {
        return {type: VAL_FLOATING_POINT, 
              floatp: CoerceFloat(a) - CoerceFloat(b)};
    }
    else if (a.type == VAL_PRIMITIVE ||
             b.type == VAL_PRIMITIVE)
    {
        return {type: VAL_PRIMITIVE,
           primitive: CoerceInt(a) - CoerceInt(b)};
    }
    else
    {
        return {type: VAL_NIL};
    }
}

function Multiply(a, b)
{
    if (a.type == VAL_FLOATING_POINT ||
        b.type == VAL_FLOATING_POINT)
    {
        return {type: VAL_FLOATING_POINT, 
              floatp: CoerceFloat(a) * CoerceFloat(b)};
    }
    else if (a.type == VAL_PRIMITIVE ||
             b.type == VAL_PRIMITIVE)
    {
        return {type: VAL_PRIMITIVE,
           primitive: CoerceInt(a) * CoerceInt(b)};
    }
    else
    {
        return {type: VAL_NIL};
    }
}

function Divide(a, b)
{
    if (a.type == VAL_FLOATING_POINT ||
        b.type == VAL_FLOATING_POINT)
    {
        var divisor = CoerceFloat(b);
        if (divisor != 0.0) {
            return {type: VAL_FLOATING_POINT, 
                  floatp: CoerceFloat(a) / CoerceFloat(b)};
        } else {
            return {type: VAL_NIL};
        }
    }
    else if (a.type == VAL_PRIMITIVE ||
             b.type == VAL_PRIMITIVE)
    {
        var divisor = CoerceInt(b);
        if (divisor != 0) {
            return {type: VAL_PRIMITIVE,
               primitive: CoerceInt(a) / CoerceInt(b)};
        } else {
            return {type: VAL_NIL};
        }
    }
    else
    {
        return {type: VAL_NIL};
    }
}

function CompareLessThan(a, b)
{
    var result = {};
    result.type = VAL_PRIMITIVE;
    result.primitive = 0;

    if (a.type == VAL_PRIMITIVE && b.type == VAL_PRIMITIVE) {
        result.primitive = (a.primitive < b.primitive);
    }
    else if (a.type == VAL_FLOATING_POINT || b.type == VAL_FLOATING_POINT)
    {
        result.primitive = (CoerceFloat(a) < CoerceFloat(b));
    }
    else if (a.type == VAL_STRING && b.type == VAL_STRING)
    {
        result.primitive = (a.string < b.string);
    }
    else {
        result.type = VAL_NIL;
        result.primitive = 0;
    }
    return result;
}


function CompareGreaterThan(a, b)
{
    var result = {};
    result.type = VAL_PRIMITIVE;
    result.primitive = 0;

    if (a.type == VAL_PRIMITIVE && b.type == VAL_PRIMITIVE) {
        result.primitive = (a.primitive > b.primitive);
    }
    else if (a.type == VAL_FLOATING_POINT || b.type == VAL_FLOATING_POINT)
    {
        result.primitive = (CoerceFloat(a) > CoerceFloat(b));
    }
    else if (a.type == VAL_STRING && b.type == VAL_STRING)
    {
        result.primitive = (a.string > b.string);
    }
    else {
        result.type = VAL_NIL;
        result.primitive = 0;
    }
    return result;
}

function CompareLessThanOrEqual(a, b)
{
    var result = {};
    result.type = VAL_PRIMITIVE;
    result.primitive = 0;

    if (a.type == VAL_PRIMITIVE && b.type == VAL_PRIMITIVE) {
        result.primitive = (a.primitive <= b.primitive);
    }
    else if (a.type == VAL_FLOATING_POINT || b.type == VAL_FLOATING_POINT)
    {
        result.primitive = (CoerceFloat(a) <= CoerceFloat(b));
    }
    else if (a.type == VAL_STRING && b.type == VAL_STRING)
    {
        result.primitive = (a.string <= b.string);
    }
    else {
        result.type = VAL_NIL;
        result.primitive = 0;
    }
    return result;
}

function CompareGreaterThanOrEqual(a, b)
{
    var result = {};
    result.type = VAL_PRIMITIVE;
    result.primitive = 0;

    if (a.type == VAL_PRIMITIVE && b.type == VAL_PRIMITIVE) {
        result.primitive = (a.primitive >= b.primitive);
    }
    else if (a.type == VAL_FLOATING_POINT || b.type == VAL_FLOATING_POINT)
    {
        result.primitive = (CoerceFloat(a) >= CoerceFloat(b));
    }
    else if (a.type == VAL_STRING && b.type == VAL_STRING)
    {
        result.primitive = (a.string >= b.string);
    }
    else {
        result.type = VAL_NIL;
        result.primitive = 0;
    }
    return result;
}

