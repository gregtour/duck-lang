#include "interpreter.h"

int main(int argc, char* argv[])
{
    const char*   program;
    L_TOKEN*      lexing;
    SYNTAX_TREE*  ast;
    char*         buffer;
    int           error;

    if (argc > 1)
        program = argv[1];
    else {
#ifdef _GDUCK
        printf("Usage: gduck program.src\n");
#else
        printf("Usage: duck program.src\n");
#endif
        return 1;
    }

    //printf("%s\n", program);
    // lex source

    buffer = 0;
    lexing = LexSource(program, &buffer, CONTEXT_FREE_GRAMMAR);
    if (lexing == NULL)
    {
        printf("Error lexing source or empty source file.\n");
        FreeLexing(lexing, buffer);
        getchar();
        return 1;
    }
    //PrintLexing(lexing);

    // parse source
    ast = ParseSource(lexing, PARSE_TABLE, CONTEXT_FREE_GRAMMAR);
    if (ast == NULL)
    {
        printf("Error parsing source.\n");
        FreeLexing(lexing, buffer);
        getchar();
        return 1;
    }
    //PrintParseTree(ast, CONTEXT_FREE_GRAMMAR);

    // compile source
    //printf("Running...\n");
    error = Interpret(ast);
    if (error)
    {
        printf("Error %i.\n", error);
        FreeLexing(lexing, buffer);
        FreeParseTree(ast);
        getchar();
        return 1;
    }

    //printf("Done.\n");
    //getchar();

    // clean up
    FreeEnvironment();
    FreeLexing(lexing, buffer);
    FreeParseTree(ast);

#ifdef _MEM_TRACKING
    PrintMemoryUsage();
#endif // _MEM_TRACKING
    return 0;
}
