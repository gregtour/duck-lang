/* type stuff */

#include "types.h"

/* cast to float */
long double TypeFloat(VALUE value)
{
    if (value.type == VAL_PRIMITIVE) {
        return (long double)value.data.primitive;
    } else if (value.type == VAL_FLOATING_POINT) {
        return value.data.floatp;
    } else if (value.type == VAL_STRING) {
        return atof(value.data.string);
    } else {
        return 0.0;
    }
}

/* cast to int */
int64 TypeInt(VALUE value)
{
    if (value.type == VAL_PRIMITIVE) {
        return value.data.primitive;
    } else if (value.type == VAL_FLOATING_POINT) {
        return (int64)value.data.floatp;
    } else if (value.type == VAL_STRING) {
        return atoi(value.data.string);
    } else {
        return 0;
    }
}

/* returns whether type is a dynamic type */
int IsDynamic(VALUE type)
{
    if (type.type == VAL_PRIMITIVE ||
        type.type == VAL_FLOATING_POINT ||
        type.type == VAL_NIL)
    {
        return 0;
    }
    else if (type.type == VAL_STRING ||
             type.type == VAL_FUNCTION ||
             type.type == VAL_REFERENCE ||
             type.type == VAL_DICTIONARY)
    {
        return 1;
    }

    return 0;
}

/* make a dynamic copy */
VALUE CopyString(VALUE string)
{
    VALUE copy;
    if (string.type == VAL_STRING)
    {
        copy.type = VAL_STRING;
        printf("copying: '%s'\n", string.data.string);
        copy.data.string = (char*)malloc(strlen(string.data.string)+1);
        sprintf((char*)copy.data.string, "%s", string.data.string);
        copy.const_string = 0;
    }
    else
    {
        copy.type = VAL_NIL;
        copy.data.primitive = 0;
    }
    return copy;
}

