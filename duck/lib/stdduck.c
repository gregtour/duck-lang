/* Duck Programming Language Standard Library */

#include "stdduck.h"
#include "interpreter.h"
#include "memory.h"
#include "garbage.h"
#include <time.h>
#include <string.h>

#ifdef WIN32
#undef CLOSURE
#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#endif

HASH_TABLE* duck_print_records = NULL;

unsigned int start_t = 0;

/* to string function declarations */
void PrintString(char** dest, unsigned int* size, const char* text);
void PrintValueString(char** dest, unsigned int* size, VALUE value);
void PrintFunctionString(char** dest, unsigned int* size, FUNCTION* function);
void PrintObjectString(char** dest, unsigned int* size, CLOSURE* context);
void PrintDictionaryString(char** string, unsigned int* size, HASH_TABLE* dictionary);


/* printing functions */
void PrintValue(VALUE value)
{
    switch (value.type)
    {
        case VAL_PRIMITIVE: 
//#ifdef WIN32
//            printf("%l64i", value.data.primitive); 
//#else
            printf("%lli", value.data.primitive); 
//#endif
            break;
        case VAL_FLOATING_POINT: 
            if (_SUPPORTS_80BIT_FLOATING_POINT)
            {
                printf("%.18Lg", value.data.floatp);
                break;
            } else {
                printf("%.16Lg", value.data.floatp); 
                break;
            }
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
    if (function) {
        if (function->fn_name) {
            printf("%s(", function->fn_name);
        } else {
            printf("function(");
        }
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
}

void PrintObject(CLOSURE* context)
{
    VALUE key;

    key.type = VAL_REFERENCE;
    key.data.reference = context;

    // check for recursion
    if (HashGet(key, duck_print_records).type != VAL_NIL) {
        printf("...");
        return;
    } else {
        VALUE value;
        value.type = VAL_PRIMITIVE;
        value.data.primitive = 1;
        HashStore(key, value, duck_print_records);
    }

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
    unsigned int i, size;
    size = dictionary->size;

    VALUE key;
    key.type = VAL_DICTIONARY;
    key.data.dictionary = dictionary;

    // check for recursion
    if (HashGet(key, duck_print_records).type != VAL_NIL) {
        printf("...");
        return;
    } else {
        VALUE value;
        value.type = VAL_PRIMITIVE;
        value.data.primitive = 1;
        HashStore(key, value, duck_print_records);
    }

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


/* ToString functions */

void PrintString(char** dest, unsigned int* size, const char* text)
{
    unsigned int necessary_space;
    unsigned int len;

    len = strlen(*dest);
    necessary_space = len + strlen(text) + 1;
    if (necessary_space > *size)
    {
        *size = *size * 2;
        *dest = (char*)realloc(*dest, *size);
    }

    sprintf(*dest + len, "%s", text);
}

void PrintValueString(char** dest, unsigned int* size, VALUE value)
{
    char buffer[128];
    switch (value.type)
    {
    case VAL_PRIMITIVE: 
        //#ifdef WIN32
        //            printf("%l64i", value.data.primitive); 
        //#else
        sprintf(buffer, "%lli", value.data.primitive); 
        PrintString(dest, size, buffer);
        //#endif
        break;
    case VAL_FLOATING_POINT: 
        if (_SUPPORTS_80BIT_FLOATING_POINT)
        {
            sprintf(buffer, "%.18Lg", value.data.floatp);
            break;
        } else {
            sprintf(buffer, "%.16Lg", value.data.floatp); 
            break;
        }
    case VAL_STRING: PrintString(dest, size, value.data.string); break;
    case VAL_REFERENCE: PrintObjectString(dest, size, value.data.reference); break;
    case VAL_FUNCTION: PrintFunctionString(dest, size, value.data.function); break;
    case VAL_DICTIONARY: PrintDictionaryString(dest, size, value.data.dictionary); break;
    default:
    case VAL_NIL: printf("[NIL]"); break;
    }
}

void PrintFunctionString(char** dest, unsigned int* size, FUNCTION* function)
{
    if (function) {
        if (function->fn_name) {
            PrintString(dest, size, function->fn_name);
            PrintString(dest, size, "(");
        } else {
            PrintString(dest, size, "function(");
        }
        PAIR* itr = function->parameters;
        while (itr)
        {
            PrintString(dest, size, itr->identifier);
            if (itr->next) {
                PrintString(dest, size, ", ");
            }
            itr = itr->next;
        }
        PrintString(dest, size, ")");
    }
}

void PrintObjectString(char** dest, unsigned int* size, CLOSURE* context)
{
    VALUE key;

    key.type = VAL_REFERENCE;
    key.data.reference = context;

    // check for recursion
    if (HashGet(key, duck_print_records).type != VAL_NIL) {
        PrintString(dest, size, "...");
        return;
    } else {
        VALUE value;
        value.type = VAL_PRIMITIVE;
        value.data.primitive = 1;
        HashStore(key, value, duck_print_records);
    }

    PrintString(dest, size, "[");
    PAIR* list = context->list;
    while (list)
    {
        PrintValueString(dest, size, list->value);

        if (list->next) {
            PrintString(dest, size, ", ");
        }
        list = list->next;
    }
    PrintString(dest, size, "]");
}


void PrintDictionaryString(char** string, unsigned int* size, HASH_TABLE* dictionary)
{
    VALUE key;
    unsigned int i, dictionary_size;
    dictionary_size = dictionary->size;
    key.type = VAL_DICTIONARY;
    key.data.dictionary = dictionary;

    // check for recursion
    if (HashGet(key, duck_print_records).type != VAL_NIL) {
        PrintString(string, size, "...");
        return;
    } else {
        VALUE value;
        value.type = VAL_PRIMITIVE;
        value.data.primitive = 1;
        HashStore(key, value, duck_print_records);
    }

    PrintString(string, size, "[");
    for (i = 0; i < dictionary->capacity; i++)
    {
        if (dictionary->table[i].key.type != VAL_NIL)
        {
            dictionary_size--;
            PrintValueString(string, size, dictionary->table[i].key);
            PrintString(string, size, ": ");
            PrintValueString(string, size, dictionary->table[i].value);
            if (dictionary_size) { PrintString(string, size, ", "); }
        }
    }
    PrintString(string, size, "]");
}


char* ToString(VALUE value)
{
    char* string;
    unsigned int size;

    duck_print_records = CreateHashTable();

    size = 512;
    string = (char*)malloc(size * sizeof(char));
    sprintf(string, "");

     PrintValueString(&string, &size, value);

    FreeHashTable(duck_print_records);
    duck_print_records = NULL;

    return string;
}



/* parses(source) -> boolean */
int DuckParses(int argument_count, void* data)
{
    L_TOKEN*      lexing;
    char*         buffer;
    int           error = 0;

    VALUE argument = GetRecord("source", gCurrentContext);

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = 0;

    if (argument.type == VAL_STRING) 
    {
        lexing = LexSourceBuffer(argument.data.string, &buffer, CONTEXT_FREE_GRAMMAR);
        if (lexing == NULL) 
        {
            gLastExpression.data.primitive = -1;
            FreeLexing(lexing, buffer);
            //return 1;
            return 0;
        }
        gLastExpression.data.primitive = ParseSucceeds(lexing, PARSE_TABLE, CONTEXT_FREE_GRAMMAR);
        if (gLastExpression.data.primitive == 0) {
            FreeLexing(lexing, buffer);
            return 0;
        }

        /* free lexing */
        FreeLexing(lexing, buffer);
    }

    return error;
}

/* eval(source) */
int DuckEval(int argument_count, void* data)
{
    L_TOKEN*      lexing;
    SYNTAX_TREE*  ast;
    char*         buffer;
    int           error = 0;

    VALUE argument = GetRecord("source", gCurrentContext);

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;

    CLOSURE* currentContext;
    currentContext = gCurrentContext;

    int prev_line_error = line_error;
    SYNTAX_TREE* prev_failed_production = failed_production;

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

        /* ReduceProgramAST(&ast); */
        error = InterpretNode(ast);

        if (error)
        {
            printf("%s\n", ErrorMessage(error));
            PrintStackTrace();
            FreeLexing(lexing, buffer);
            FreeParseTree(ast);

            ClearCallStack(&gStackTrace);

            line_error = prev_line_error;
            failed_production = prev_failed_production;

            return 1;
        }

        /* sanitize last expression for use in program */
        //gLastExpression = ReallocStrings(gLastExpression);

        /* free lexing and parse tree */
        //FreeLexing(lexing, buffer);
        //FreeParseTree(ast);
        GCAddLexing(lexing, buffer);
        GCAddParseTree(ast);
    }

    gCurrentContext = currentContext;
    return error;
}

/* duck.print(output) */
int DuckPrint(int argument_count, void* data)
{
    int error = 0;
    VALUE argument = GetRecord("output", gCurrentContext);
    
    duck_print_records = CreateHashTable();

    PrintValue(argument);

    FreeHashTable(duck_print_records);
    duck_print_records = NULL;

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;

    return error;
}

/* duck.println(output) */
int DuckPrintLn(int argument_count, void* data)
{
    int error = 0;
    VALUE argument = GetRecord("output", gCurrentContext);
    
    duck_print_records = CreateHashTable();

    PrintValue(argument);

    FreeHashTable(duck_print_records);
    duck_print_records = NULL;

    gLastExpression.type = VAL_NIL;
    gLastExpression.data.primitive = 0;
    printf("\n");
    
    return error;
}

/* duck.prompt(message) */
int DuckPrompt(int argument_count, void* data)
{
    int error = 0;

    // optional message prompt
    VALUE opt_message = GetRecord("message", gCurrentContext);
    if (opt_message.type != VAL_NIL) {
        PrintValue(opt_message);
    }

    // get string
    char* buffer = (char*)ALLOCATE(sizeof(char)*256);
    char* result = fgets(buffer, 255, stdin);

    // check for result
    if (result)
    {
        buffer[255] = '\0';

        // remove trailing newline
        int len = strlen(buffer);
        if (len && buffer[len-1] == '\n') buffer[len-1] = '\0';

        gLastExpression.type = VAL_STRING;
        gLastExpression.data.string = buffer;
        gLastExpression.const_string = 1;
    }
    else
    {
        // null result
        gLastExpression.type = VAL_NIL;
        gLastExpression.data.primitive = 0;

        error = 1;
    }

    return error;
}

/* Type(object) */
int DuckType(int argument_count, void* data)
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
int DuckInt(int argument_count, void* data)
{
    int error = 0;

    VALUE argument = GetRecord("value", gCurrentContext);

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = TypeInt(argument);
    
    return error;
}

/* float(value) */
int DuckFloat(int argument_count, void* data)
{
    int error = 0;

    VALUE argument = GetRecord("value", gCurrentContext);

    gLastExpression.type = VAL_FLOATING_POINT;
    gLastExpression.data.floatp = TypeFloat(argument);
    
    return error;
}

/* len(array) */
int DuckLength(int argument_count, void* data)
{
    int error = 0;

    VALUE argument = GetRecord("array", gCurrentContext);

    if (argument.type == VAL_REFERENCE)
    {
        long int count = 0;
        CLOSURE* reference;
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
    else if (argument.type == VAL_STRING)
    {
        gLastExpression.type = VAL_PRIMITIVE;
        gLastExpression.data.primitive = strlen(gLastExpression.data.string);
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
int DuckQuit(int argument_count, void* data)
{
    int error = 0;

    halting = 1;
    
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.type = 0;

    return error;
}

/* float time() */
int DuckTime(int argument_count, void* data)
{
    int error = 0;

#ifndef WIN32
    struct timespec ctime;
    long double time;

    clock_gettime(CLOCK_MONOTONIC, &ctime);
    time = ctime.tv_sec + ctime.tv_nsec / 1000000000.0;

    gLastExpression.type = VAL_FLOATING_POINT;
    gLastExpression.data.floatp = time;
#else
    unsigned int cur_t;
    long double time;

    cur_t = GetTickCount();
    time = (cur_t - start_t) / 1000.0;

    gLastExpression.type = VAL_FLOATING_POINT;
    gLastExpression.data.floatp = time;
#endif

    return error;
}

/* bind the duck standard library */
void BindStandardLibrary()
{
    VALUE duckStdLib = LinkNamespace("duck");

    VALUE print = CreateFunction(DuckPrint);
    AddParameter(print, "output");
    LinkFunction(duckStdLib, "print", print);

    VALUE println = CreateFunction(DuckPrintLn);
    AddParameter(println, "output");
    LinkFunction(duckStdLib, "println", println);

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

    VALUE float_c = CreateFunction(DuckFloat);
    AddParameter(float_c, "value");
    LinkFunction(root, "float", float_c);

    VALUE length = CreateFunction(DuckLength);
    AddParameter(length, "array");
    LinkFunction(root, "len", length);

    VALUE type = CreateFunction(DuckType);
    AddParameter(type, "object");
    LinkFunction(root, "Type", type);

    VALUE evalFunc = CreateFunction(DuckEval);
    AddParameter(evalFunc, "source");
    LinkFunction(root, "eval", evalFunc);

    VALUE parsesFunc = CreateFunction(DuckParses);
    AddParameter(parsesFunc, "source");
    LinkFunction(duckStdLib, "parses", parsesFunc);

    VALUE duckQuit = CreateFunction(DuckQuit);
    LinkFunction(root, "quit", duckQuit);
    BindStringLibrary();

    VALUE time = CreateFunction(DuckTime);
    LinkFunction(root, "time", time);

#ifdef WIN32
    start_t = GetTickCount();
#endif
}

int StringSplit(int argument_count, void* data)
{
    int error = 0;

    VALUE argument = GetRecord("string", gCurrentContext);

    if (argument.type == VAL_STRING) 
    {
        const char* data = argument.data.string;
        unsigned int length = strlen(data);
        unsigned int index;

        HASH_TABLE* dictionary = CreateHashTable();
        GCAddDictionary(dictionary, &gGCManager);

        for (index = 0; index < length; index++)
        {
            VALUE key;
            VALUE expr;

            key.type = VAL_PRIMITIVE;
            key.data.primitive = index;
            
            expr.type = VAL_STRING;
            expr.const_string = 0;
            char* char_string = (char*)ALLOC(sizeof(char) * 2);
            GCAddString(char_string, &gGCManager);
            char_string[0] = data[index];
            char_string[1] = '\0';
            expr.data.string = char_string;

            HashStore(key, expr, dictionary);
        }

        gLastExpression.type = VAL_DICTIONARY;
        gLastExpression.data.dictionary = dictionary;
    } else {
        gLastExpression.type = VAL_NIL;
        gLastExpression.data.primitive = 0;
    }

    return error;
}

void BindStringLibrary()
{
    VALUE stringLib = LinkNamespace("string");
    
    VALUE split = CreateFunction(StringSplit);
    AddParameter(split, "string");
    LinkFunction(stringLib, "split", split);
}

