/* Duck Programming Language Standard Library */

#include "stdduck.h"
#include "interpreter.h"
#include "memory.h"

/* duck.print(arg1), duck.println(arg1) */
int DuckPrint(int argument_count)
{
    int error = 0;
    VALUE argument = GetRecord("output", gCurrentContext);
    
    if (argument.type == VAL_PRIMITIVE)
    {
        printf("%i", argument.data.primitive);
    }
    else if (argument.type == VAL_FLOATING_POINT)
    {
        printf("%g", argument.data.floatp);
    }
    else if (argument.type == VAL_STRING)
    {
        printf("%s", argument.data.string);
    }
    else if (argument.type == VAL_REFERENCE)
    {
        PrintObject(argument.data.reference);
    }
    else if (argument.type == VAL_FUNCTION)
    {
        printf("f(");
        PAIR* list = argument.data.function->parameters;
        while (list)
        {
            printf("%s", list->identifier);
            if (list->next)
                printf(", ");
            list = list->next;
        }
        printf(")");
    }
    else if (argument.type == VAL_DICTIONARY)
    {
        printf("Dictionary Object");
    }
    else
    {
        printf("[NIL]");
    }
    
    gLastExpression.type = VAL_NIL;
    printf("\n");

    return error;
}

/* duck.prompt([NIL]) */
int DuckPrompt(int argument_count)
{
    int error = 0;

    char* buffer = (char*)ALLOCATE(sizeof(char)*128);
    fgets(buffer, 128, stdin);

    gLastExpression.type = VAL_STRING;
    gLastExpression.data.string = buffer;

    return error;
}

/* Type(object) */
int DuckType(int argument_count)
{
    int error = 0;

    VALUE argument = GetRecord("object", gCurrentContext);

    gLastExpression.type = VAL_STRING;
    switch (argument.type)
    {
        case VAL_NIL: gLastExpression.data.string = "NIL"; break;
        case VAL_PRIMITIVE: gLastExpression.data.string = "INT"; break;
        case VAL_FLOATING_POINT: gLastExpression.data.string = "FLOAT"; break;
        case VAL_STRING: gLastExpression.data.string = "STRING"; break;
        case VAL_REFERENCE: gLastExpression.data.string = "REFERENCE"; break;
        case VAL_FUNCTION: gLastExpression.data.string = "FUNCTION"; break;
        case VAL_DICTIONARY: gLastExpression.data.string = "DICTIONARY"; break;
        default: gLastExpression.data.string = "UNKNOWN";
    }

    return error;
}

/* int(value) */
int DuckInt(int argument_count)
{
    int error = 0;

    VALUE argument = GetRecord("value", gCurrentContext);

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = TypeInt(argument);
    
    return error;
}

/* len(array) */
int DuckLength(int argument_count)
{
    int error = 0;

    VALUE argument = GetRecord("array", gCurrentContext);

    if (argument.type == VAL_REFERENCE)
    {
        int count = 0;
        CONTEXT* reference;
        PAIR* iterator;

        reference = argument.data.reference;
        iterator = reference->list;
        while (iterator)
        {
            count++;
            iterator = iterator->next;
        }

        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = count;
    }
    else if (argument.type == VAL_DICTIONARY)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = argument.data.dictionary->size;
    }
    else 
    {
        if (argument.type != VAL_NIL) {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = 1;
        } else {
            gLastExpression.type = VAL_PRIMITIVE;
            gLastExpression.data.primitive = 0;
        }
    }

    return error;
}

void BindStandardLibrary()
{
    VALUE duckStdLib = LinkNamespace("duck");

    VALUE print = CreateFunction(DuckPrint);
    AddParameter(print, "output");
    
    LinkFunction(duckStdLib, "print", print);
    LinkFunction(duckStdLib, "println", print);

    VALUE prompt = CreateFunction(DuckPrompt);
    LinkFunction(duckStdLib, "prompt", prompt);

    VALUE root;
    root.type = VAL_REFERENCE;
    root.data.reference = gGlobalContext;

    VALUE int_c = CreateFunction(DuckInt);
    AddParameter(int_c, "value");
    LinkFunction(root, "int", int_c);

    VALUE length = CreateFunction(DuckLength);
    AddParameter(length, "array");
    LinkFunction(root, "len", length);

    VALUE type = CreateFunction(DuckType);
    AddParameter(type, "object");
    LinkFunction(root, "Type", type);
}

