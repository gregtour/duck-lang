/* Duck Programming Language Standard Library */

#include "stdduck.h"
#include "interpreter.h"
#include "memory.h"

/* printing functions */
void PrintValue(VALUE value)
{
    switch (value.type)
    {
        case VAL_PRIMITIVE: printf("%i", value.data.primitive); break;
        case VAL_FLOATING_POINT: printf("%g", value.data.floatp); break;
        case VAL_STRING: printf("%s", value.data.string); break;
        case VAL_REFERENCE: PrintObject(value.data.reference); break;
        case VAL_FUNCTION: PrintFunction(value.data.function); break;
        case VAL_DICTIONARY: PrintDictionary(value.data.dictionary); break;
        default:
        case VAL_NIL: printf("[NIL]"); break;
    }
}

void PrintFunction(FUNCTION* function)
{
    printf("function(");
    PAIR* itr = function->parameters;
    while (itr)
    {
        printf("%s", itr->identifier);
        if (itr->next)
            printf(", ");
        itr = itr->next;
    }
    printf(")");
}

void PrintObject(CONTEXT* context)
{
    printf("[");
    PAIR* list = context->list;
    while (list)
    {
        PrintValue(list->value);

        if (list->next)
            printf(", ");
        list = list->next;
    }
    printf("]");
}

void PrintDictionary(HASH_TABLE* dictionary)
{
    int i, size;
    size = dictionary->size;
    printf("[");
    for (i = 0; i < dictionary->capacity; i++)
    {
        if (dictionary->table[i].key.type != VAL_NIL)
        {
            size--;
            PrintValue(dictionary->table[i].key);
            printf(": ");
            PrintValue(dictionary->table[i].value);
            if (size) printf(", ");
        }
    }
    printf("]");
}

/* TODO: Implement or come up with another scheme to manage strings. */
void ReallocStringsRef(CONTEXT* context) { return; }
void ReallocStringsFunc(FUNCTION* func) { return; }
void ReallocStringsDict(HASH_TABLE* table) { return; }

/* sanitize strings */
VALUE ReallocStrings(VALUE value)
{
    int   size;
    char* copy;
    switch (value.type)
    {
        case VAL_STRING:
            size = strlen(value.data.string);
            copy = (char*)ALLOCATE(sizeof(char) * (size+1));
            sprintf(copy, "%s", value.data.string);
            value.data.string = copy;
            return value;
        case VAL_REFERENCE: 
            ReallocStringsRef(value.data.reference);
            return value;
        case VAL_FUNCTION: 
            ReallocStringsFunc(value.data.function);
            return value;
        case VAL_DICTIONARY: 
            ReallocStringsDict(value.data.dictionary);
            return value;
        case VAL_PRIMITIVE:
        case VAL_FLOATING_POINT:
        case VAL_NIL: 
        default:
            break;
    }
    return value;
}

/* eval(source) */
int DuckEval(int argument_count)
{
    L_TOKEN*      lexing;
    SYNTAX_TREE*  ast;
    char*         buffer;
    int           error = 0;

    VALUE argument = GetRecord("source", gCurrentContext);

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;

    CONTEXT* currentContext;
    currentContext = gCurrentContext;

//  if (gCurrentContext->parent) gCurrentContext = gCurrentContext->parent;
    gCurrentContext = gGlobalContext;

    if (argument.type == VAL_STRING) 
    {
        lexing = LexSourceBuffer(argument.data.string, &buffer, CONTEXT_FREE_GRAMMAR);
        if (lexing == NULL) {
            printf("Error lexing source or empty source string.\n");
            FreeLexing(lexing, buffer);
            return 1;
        }
        ast = ParseSource(lexing, PARSE_TABLE, CONTEXT_FREE_GRAMMAR);
        if (ast == NULL) {
            printf("Error parsing source.\n");
            FreeLexing(lexing, buffer);
            return 1;
        }
        error = InterpretNode(ast);
        if (error)
        {
            printf("Error %i.\n", error);
            FreeLexing(lexing, buffer);
            FreeParseTree(ast);
            return 1;
        }

        /* sanitize gLastExpression for use in program */
        gLastExpression = ReallocStrings(gLastExpression);

        /* free lexing and parse tree */
        FreeLexing(lexing, buffer);
        FreeParseTree(ast);
    }

    gCurrentContext = currentContext;
    return error;
}

/* duck.print(arg1), duck.println(arg1) */
int DuckPrint(int argument_count)
{
    int error = 0;
    VALUE argument = GetRecord("output", gCurrentContext);
    
    PrintValue(argument);
    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    printf("\n");

    return error;
}

/* duck.prompt(message) */
int DuckPrompt(int argument_count)
{
    int error = 0;

    // optional message prompt
    VALUE opt_message = GetRecord("message", gCurrentContext);
    if (opt_message.type != VAL_NIL) {
        PrintValue(opt_message);
    }

    // get string
    char* buffer = (char*)ALLOCATE(sizeof(char)*128);
    fgets(buffer, 127, stdin);
    buffer[127] = '\0';

    // remove trailing newline
    int len = strlen(buffer);
    if (len && buffer[len-1] == '\n') buffer[len-1] = '\0';

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

/* quit() */
int DuckQuit(int argument_count)
{
    int error = 0;

    halting = 1;
    
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.type = 0;

    return error;
}

/* bind the duck standard library */
void BindStandardLibrary()
{
    VALUE duckStdLib = LinkNamespace("duck");

    VALUE print = CreateFunction(DuckPrint);
    AddParameter(print, "output");
    
    LinkFunction(duckStdLib, "print", print);
    LinkFunction(duckStdLib, "println", print);

    VALUE prompt = CreateFunction(DuckPrompt);
    AddParameter(prompt, "message");
    LinkFunction(duckStdLib, "prompt", prompt);

    LinkConstString(duckStdLib, "newline", "\n");

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

    VALUE evalFun = CreateFunction(DuckEval);
    AddParameter(evalFun, "source");
    LinkFunction(root, "eval", evalFun);

    VALUE duckQuit = CreateFunction(DuckQuit);
    LinkFunction(root, "quit", duckQuit);
}

