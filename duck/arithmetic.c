/*
    Duck Arithmetic
    Basic Math and Logic
*/

#include <math.h>
#include "types.h"
#include "arithmetic.h"
#include "memory.h"
#include "garbage.h"
#include "lib/stdduck.h"

/* truth */
int EvaluatesTrue(VALUE value)
{
    return ((value.type == VAL_PRIMITIVE &&
             value.data.primitive) ||
            (value.type == VAL_FLOATING_POINT &&
             fabs(value.data.floatp) > DOUBLE_EPSILON) ||
            (value.type == VAL_STRING ||
             value.type == VAL_REFERENCE ||
             value.type == VAL_FUNCTION ||
             value.type == VAL_DICTIONARY));
}

/* true */
VALUE TrueValue()
{
    VALUE truth;
    truth.type = VAL_PRIMITIVE;
    truth.data.primitive = 1;
    return truth;
}

/* false */
VALUE FalseValue()
{
    VALUE truth;
    truth.type = VAL_PRIMITIVE;
    truth.data.primitive = 0;
    return truth;
}

/* string concatenation */
VALUE Concat(VALUE a, VALUE b)
{
    VALUE value;
    char* string_a = NULL;
    char* string_b = NULL;
    char buffer1[32];
    char buffer2[32];
    int length;
    char* new_string;
    char* temp1 = NULL;
    char* temp2 = NULL;

    // coerce string for first term
    if (a.type == VAL_STRING) {
        string_a = (char*)a.data.string;
    } else {
        if (a.type == VAL_PRIMITIVE) {
//#ifdef WIN32
//            sprintf(buffer1, "%l64i", a.data.primitive);
//#else
            sprintf(buffer1, "%lli", a.data.primitive);
//#endif
            string_a = buffer1;
        } else if (a.type == VAL_FLOATING_POINT) {
if (_SUPPORTS_80BIT_FLOATING_POINT) {
            sprintf(buffer1, "%.18Lg", a.data.floatp);
} else {
            sprintf(buffer1, "%.16Lg", a.data.floatp);
}
            string_a = buffer1;
        }
        // VAL_REFERENCE
        // VAL_FUNCTION
        // VAL_DICTIONARY
        else {
            //sprintf(buffer1, "null");
            temp1 = ToString(a);
            string_a = temp1;
        }
    }

    // coerce string for second term
    if (b.type == VAL_STRING) {
        string_b = (char*)b.data.string;
    } else {
        if (b.type == VAL_PRIMITIVE) {
//#ifdef WIN32
//            sprintf(buffer2, "%l64i", b.data.primitive);
//#else
            sprintf(buffer2, "%lli", b.data.primitive);
//#endif
            string_b = buffer2;
        } else if (b.type == VAL_FLOATING_POINT) {
if (_SUPPORTS_80BIT_FLOATING_POINT) {
            sprintf(buffer2, "%.18Lg", b.data.floatp);
} else {
            sprintf(buffer2, "%.16Lg", b.data.floatp);
}
            string_b = buffer2;
        }
        // VAL_REFERENCE
        // VAL_FUNCTION
        // VAL_DICTIONARY
        else {
            //sprintf(buffer2, "null");
            temp2 = ToString(b);
            string_b = temp2;
        }
    }

    // concat strings
    length = strlen(string_a) + strlen(string_b) + 1;
    new_string = (char*)ALLOC(sizeof(char) * length);

    GCAddString(new_string, &gGCManager);

    sprintf(new_string, "%s%s", string_a, string_b);
    //printf("concat: '%s'\n", new_string);
    value.type = VAL_STRING;
    value.data.string = new_string;
    value.const_string = 0;

    if (temp1) { free(temp1); }
    if (temp2) { free(temp2); }

    return value;
}

/* addition */
VALUE Add(VALUE a, VALUE b)
{
    VALUE result;
    result.type = VAL_NIL;
    result.data.primitive = 0;

    if (a.type == VAL_FLOATING_POINT ||
        b.type == VAL_FLOATING_POINT)
    {
        result.type = VAL_FLOATING_POINT;
        result.data.floatp = TypeFloat(a) + TypeFloat(b);
    }
    else if (a.type == VAL_PRIMITIVE ||
             b.type == VAL_PRIMITIVE)
    {
        result.type = VAL_PRIMITIVE;
        result.data.primitive = TypeInt(a) + TypeInt(b);
    }

    return result;
}

/* subtraction */
VALUE Subtract(VALUE a, VALUE b)
{
    VALUE result;
    result.type = VAL_NIL;
    result.data.primitive = 0;

    if (a.type == VAL_FLOATING_POINT ||
        b.type == VAL_FLOATING_POINT)
    {
        result.type = VAL_FLOATING_POINT;
        result.data.floatp = TypeFloat(a) - TypeFloat(b);
    }
    else if (a.type == VAL_PRIMITIVE ||
             b.type == VAL_PRIMITIVE)
    {
        result.type = VAL_PRIMITIVE;
        result.data.primitive = TypeInt(a) - TypeInt(b);
    }

    return result;
}

/* multiplication */
VALUE Multiply(VALUE a, VALUE b)
{
    VALUE result;
    result.type = VAL_NIL;
    result.data.primitive = 0;

    if (a.type == VAL_FLOATING_POINT ||
        b.type == VAL_FLOATING_POINT)
    {
        result.type = VAL_FLOATING_POINT;
        result.data.floatp = TypeFloat(a) * TypeFloat(b);
    }
    else if (a.type == VAL_PRIMITIVE ||
             b.type == VAL_PRIMITIVE)
    {
        result.type = VAL_PRIMITIVE;
        result.data.primitive = TypeInt(a) * TypeInt(b);
    }

    return result;
}

/* division */
VALUE Divide(VALUE a, VALUE b)
{
    VALUE result;
    result.type = VAL_NIL;
    result.data.primitive = 0;

    if (a.type == VAL_FLOATING_POINT ||
        b.type == VAL_FLOATING_POINT)
    {
        long double divisor = TypeFloat(b);
    
        result.type = VAL_FLOATING_POINT;
        if (divisor != 0.0) {
            result.data.floatp = TypeFloat(a) / divisor;
        } else {
            result.type = VAL_NIL;
            result.data.primitive = 0;
        }
    }
    else if (a.type == VAL_PRIMITIVE ||
             b.type == VAL_PRIMITIVE)
    {
        int64 divisor = TypeInt(b);

        result.type = VAL_PRIMITIVE;
        if (divisor != 0) {
            result.data.primitive = TypeInt(a) / divisor;
        } else {
            result.type = VAL_NIL;
            result.data.primitive = 0;
        }
    }

    return result;
}

/* modulo */
VALUE Modulus(VALUE a, VALUE b)
{
    VALUE result;
    int64 base;
    result.type = VAL_NIL;
    result.data.primitive = 0;

    base = TypeInt(b);

    if (base != 0) {
        result.type = VAL_PRIMITIVE;
        result.data.primitive = TypeInt(a) % base;
    }

    return result;
}

/* equality */
VALUE CompareEquality(VALUE a, VALUE b)
{
    VALUE value;

    if ((a.type == VAL_FLOATING_POINT && b.type == VAL_PRIMITIVE) ||
        (a.type == VAL_PRIMITIVE && b.type == VAL_FLOATING_POINT))
    {
        long double a_val, b_val;
        a_val = TypeFloat(a);
        b_val = TypeFloat(b);
        a.type = b.type = 
            VAL_FLOATING_POINT;
        a.data.floatp = a_val;
        b.data.floatp = b_val;
    }

    if (a.type == b.type) 
    {
        value.type = VAL_PRIMITIVE;
        switch (a.type) 
        {
            case VAL_PRIMITIVE: 
                value.data.primitive = (a.data.primitive == b.data.primitive);
                break;
            case VAL_FLOATING_POINT:
                //value.data.primitive = (a.data.floatp == b.data.floatp);
                value.data.primitive = (fabs(a.data.floatp - b.data.floatp) 
                        < DOUBLE_EPSILON);
                break;
            case VAL_STRING:
                value.data.primitive = strcmp(a.data.string, b.data.string) 
                        ? 0 : 1;
                break;
            case VAL_REFERENCE:
                value.data.primitive = (a.data.reference == b.data.reference);
                break;
            case VAL_FUNCTION:
                value.data.primitive = (a.data.function == b.data.function);
                break;
            case VAL_DICTIONARY:
                value.data.primitive = (a.data.dictionary == b.data.dictionary);
                break;
        }
    } 
    else 
    {
        value.type = VAL_PRIMITIVE;
        value.data.primitive = 0;
    }

    return value;
}

/* inequality */
VALUE CompareInequality(VALUE a, VALUE b)
{
    VALUE result = CompareEquality(a, b);
    result.type = VAL_PRIMITIVE;
    result.data.primitive = (result.data.primitive ? 0 : 1);
    return result;
}

/* and */
VALUE LogicAND(VALUE a, VALUE b)
{
    if (EvaluatesTrue(a) && EvaluatesTrue(b))
        return b;
    else {
        VALUE value_false;
        value_false.type = VAL_PRIMITIVE;
        value_false.data.primitive = 0;
        return value_false;
    }
}

/* or */
VALUE LogicOR(VALUE a, VALUE b)
{
    if (EvaluatesTrue(a))
        return a;
    else if (EvaluatesTrue(b))
        return b;
    else {
        VALUE value_false;
        value_false.type = VAL_PRIMITIVE;
        value_false.data.primitive = 0;
        return value_false;
    }
}

/* nor */
VALUE LogicNOR(VALUE a, VALUE b)
{
    if (EvaluatesTrue(a))
    {
        VALUE value_false;
        value_false.type = VAL_PRIMITIVE;
        value_false.data.primitive = 0;
        return value_false;
    }
    else if (EvaluatesTrue(b))
    {
        VALUE value_false;
        value_false.type = VAL_PRIMITIVE;
        value_false.data.primitive = 0;
        return value_false;
    }
    else
    {
        VALUE value_true;
        value_true.type = VAL_PRIMITIVE;
        value_true.data.primitive = 1;
        return value_true;
    }
}

/* xor */
VALUE LogicXOR(VALUE a, VALUE b)
{
    if (EvaluatesTrue(a) && !EvaluatesTrue(b))
    {
        return a;
    }
    else if (!EvaluatesTrue(a) && EvaluatesTrue(b))
    {
        return b;
    }
    else
    {
        VALUE value_false;
        value_false.type = VAL_PRIMITIVE;
        value_false.data.primitive = 0;
        return value_false;
    }
}

/* less-than */
VALUE CompareLessThan(VALUE a, VALUE b)
{
    VALUE result;

    if (a.type == VAL_PRIMITIVE && b.type == VAL_PRIMITIVE)
    {
        result.type = VAL_PRIMITIVE;
        result.data.primitive = (a.data.primitive < b.data.primitive);
    }
    else if (a.type == VAL_FLOATING_POINT || b.type == VAL_FLOATING_POINT)
    {
        long double afloat = TypeFloat(a);
        long double bfloat = TypeFloat(b);
        result.type = VAL_PRIMITIVE;
        result.data.primitive = (afloat < bfloat);
    }
    else
    {
        if (a.type == VAL_STRING && b.type == VAL_STRING) {
            // string comparison
            result.type = VAL_PRIMITIVE;
            result.data.primitive = (strcmp(a.data.string, b.data.string) < 0);
        } else {
            result.type = VAL_NIL;
            result.data.primitive = 0;
        }
    }
    
    result.data.primitive = result.data.primitive ? 1 : 0;
    return result;
}

/* greater-than */
VALUE CompareGreaterThan(VALUE a, VALUE b)
{
    VALUE result;

    if (a.type == VAL_PRIMITIVE && b.type == VAL_PRIMITIVE)
    {
        result.type = VAL_PRIMITIVE;
        result.data.primitive = 
            (a.data.primitive > b.data.primitive);
    }
    else if (a.type == VAL_FLOATING_POINT || b.type == VAL_FLOATING_POINT)
    {
        long double afloat = TypeFloat(a);
        long double bfloat = TypeFloat(b);
        result.type = VAL_PRIMITIVE;
        result.data.primitive = (afloat > bfloat);
    }
    else
    {
        if (a.type == VAL_STRING && b.type == VAL_STRING) {
            // string comparison
            result.type = VAL_PRIMITIVE;
            result.data.primitive = (strcmp(a.data.string, b.data.string) > 0);
        } else {
            result.type = VAL_NIL;
            result.data.primitive = 0;
        }
    }
    
    result.data.primitive = result.data.primitive ? 1 : 0;
    return result;
}

/* less-than-or-equal */
VALUE CompareLessThanOrEqual(VALUE a, VALUE b)
{
    VALUE result;
    
    if (a.type == VAL_PRIMITIVE && b.type == VAL_PRIMITIVE)
    {
        result.type = VAL_PRIMITIVE;
        result.data.primitive = 
            (a.data.primitive <= b.data.primitive);
    }
    else if (a.type == VAL_FLOATING_POINT || b.type == VAL_FLOATING_POINT)
    {
        long double afloat = TypeFloat(a);
        long double bfloat = TypeFloat(b);
        result.type = VAL_PRIMITIVE;
        result.data.primitive = (afloat <= bfloat);
    }
    else
    {
        if (a.type == VAL_STRING && b.type == VAL_STRING) {
            // string comparison
            result.type = VAL_PRIMITIVE;
            result.data.primitive = (strcmp(a.data.string, b.data.string) <= 0);
        } else {
            result.type = VAL_NIL;
            result.data.primitive = 0;
        }
    }
    
    result.data.primitive = result.data.primitive ? 1 : 0;
    return result;
}

/* greater-than-or-equal */
VALUE CompareGreaterThanOrEqual(VALUE a, VALUE b)
{
    VALUE result;
    
    if (a.type == VAL_PRIMITIVE && b.type == VAL_PRIMITIVE)
    {
        result.type = VAL_PRIMITIVE;
        result.data.primitive = (a.data.primitive >= b.data.primitive);
    }
    else if (a.type == VAL_FLOATING_POINT || b.type == VAL_FLOATING_POINT)
    {
        long double afloat = TypeFloat(a);
        long double bfloat = TypeFloat(b);
        result.type = VAL_PRIMITIVE;
        result.data.primitive = (afloat >= bfloat);
    }
    else
    {
        if (a.type == VAL_STRING && b.type == VAL_STRING) {
            // string comparison
            result.type = VAL_PRIMITIVE;
            result.data.primitive = (strcmp(a.data.string, b.data.string) >= 0);
        } else {
            result.type = VAL_NIL;
            result.data.primitive = 0;
        }
    }
    
    result.data.primitive = result.data.primitive ? 1 : 0;
    return result;
}

