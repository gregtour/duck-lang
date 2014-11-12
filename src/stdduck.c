/* Duck Programming Language Standard Library */

#include "stdduck.h"
#include "interpreter.h"

/* duck.print(arg1), duck.println(arg1) */
int DuckPrint(int argument_count)
{
    int error = 0;
    VALUE argument = GetRecord("arg1", gCurrentContext);
    
    if (argument.type == VAL_PRIMITIVE)
    {
        printf("%i", argument.primitive);
    }
    else if (argument.type == VAL_FLOATING_POINT)
    {
        printf("%g", argument.floatp);
    }
    else if (argument.type == VAL_STRING)
    {
        printf("%s", argument.string);
    }
    else if (argument.type == VAL_REFERENCE)
    {
        PrintObject(argument.reference);
    }
    else if (argument.type == VAL_FUNCTION)
    {
        printf("f(");
        PAIR* list = argument.function->parameters;
        while (list)
        {
            printf("%s", list->identifier);
            if (list->next)
                printf(", ");
            list = list->next;
        }
        printf(")");
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
//    VALUE argument = GetRecord("arg1", gCurrentContext);

    int error = 0;

    char* buffer = (char*)ALLOCATE(sizeof(char)*128);
    fgets(buffer, 128, stdin);

    gLastExpression.type = VAL_STRING;
    gLastExpression.string = buffer;

    return error;
}

void BindStandardLibrary()
{
    VALUE duckStdLib = LinkNamespace("duck");

    VALUE print = CreateFunction(DuckPrint);
    AddParameter(print, "arg1");
    
    LinkFunction(duckStdLib, "print", print);
    LinkFunction(duckStdLib, "println", print);

    VALUE prompt = CreateFunction(DuckPrompt);
    LinkFunction(duckStdLib, "prompt", prompt);
}

