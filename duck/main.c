/*
    Duck Programming Language - main.c
    Thursday November 20th, 2014
*/
#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* main(args) accepts program file to run */
int main(int argc, char* argv[])
{
    const char*   program;
    L_TOKEN*      lexing;
    SYNTAX_TREE*  ast;
    char*         buffer;
    int           error;

    // choose program source
    if (argc > 1) {
        program = argv[1];
    } else {
#ifdef _GDUCK
        printf("Usage: gduck program.src\n");
#else
        printf("Usage: duck program.src\n");
#endif
        return 1;
    }

#ifdef _PROFILING
    // time execution
    struct timespec start, finish;
    double elapsed;
#endif

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

    // parse source
    ast = ParseSource(lexing, PARSE_TABLE, CONTEXT_FREE_GRAMMAR);
    if (ast == NULL)
    {
        printf("Error parsing source.\n");
        FreeLexing(lexing, buffer);
        getchar();
        return 1;
    }

#ifdef _PROFILING
    clock_gettime(CLOCK_MONOTONIC, &start);
#endif

    // interpret source and run
    error = Interpret(ast);
    if (error)
    {
        printf("Error %i.\n", error);
        FreeLexing(lexing, buffer);
        FreeParseTree(ast);
        getchar();
        return 1;
    }

#ifdef _PROFILING
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time elapsed: %g\n", elapsed);
#endif

    // clean up
    FreeEnvironment();
    FreeLexing(lexing, buffer);
    FreeParseTree(ast);

#ifdef _MEM_TRACKING
    PrintMemoryUsage();
#endif // _MEM_TRACKING
    return 0;
}

