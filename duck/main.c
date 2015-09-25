/*
    Duck Programming Language - main.c
    Thursday November 20th, 2014 to
        Sunday December 28th, 2014
*/
#include "main.h"
#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char* ErrorMessage(int error)
{
    if (error == 12345)
        return "Error with function call.";
    else if (error == 42)
        return "Illegal for loop operands.";
    else if (error == 43)
        return "Illegal for loop operands.";
    else if (error == 65)
        return "Error using variable as a reference.";
    else if (error == 66)
        return "Error using variable as an array.";
    else if (error == 114)
        return "Error, duplicate object initializer.";
    else if (error == 0)
        return "No error.";
    else if (error == 1)
        return "Error 1.";
    else
        return "Unspecified error.";
}


/* main(args) accepts program file to run */
int main(int argc, char* argv[])
{
    const char*   program = "";
    L_TOKEN*      lexing;
    SYNTAX_TREE*  ast;
    char*         buffer;
    int           error;

    // choose program source
    if (argc > 1) {
        program = argv[1];
        if (strcmp(argv[1], "-h") == 0 ||
            strcmp(argv[1], "-help") == 0 ||
            strcmp(argv[1], "--help") == 0)
        {
#ifdef _GDUCK
        printf("Usage: gduck program.src\n");
#else
        printf("Usage: duck program.src\n");
#endif // _GDUCK
        return 1;
        }
    } 

#ifdef _PROFILING
    // time execution
    struct timespec start, finish;
    long double elapsed;
#endif // _PROFILING

    // lex source
    if (argc > 1) {
        buffer = 0;
        lexing = LexSource(program, &buffer, CONTEXT_FREE_GRAMMAR);
        if (lexing == NULL)
        {
            printf("Error lexing source or empty source file.\n");
            FreeLexing(lexing, buffer);
            getchar();
            return 1;
        }
    } else {
        buffer = 0;
        // built-in read--evaluate--print--loop demo //
        lexing = LexSourceBuffer(demo, &buffer, CONTEXT_FREE_GRAMMAR);
        if (lexing == NULL) {
            printf("Error 1.\n");
            FreeLexing(lexing,buffer);
            getchar();
            return 1;
        }
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

    /* ReduceProgramAST(&ast); */

#ifdef _PROFILING
    clock_gettime(CLOCK_MONOTONIC, &start);
#endif // _PROFILING

    // interpret source and run
    error = Interpret(ast);
    if (error)
    {
        printf("%s\n", ErrorMessage(error));
        //printf("Error %i.\n", ErrorMessage(error));
        PrintStackTrace();
        FreeLexing(lexing, buffer);
        FreeParseTree(ast);
        getchar();
        return 1;
    }

#ifdef _PROFILING
    printf("\n");
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("%i call(s) to the garbage collector.\n", gc_collect_count);
    printf("Time elapsed: %g seconds.\n", elapsed);
#endif // _PROFILING

    // clean up
    FreeEnvironment();
    FreeLexing(lexing, buffer);
    FreeParseTree(ast);

#ifdef _MEM_TRACKING
    PrintMemoryUsage();
#endif // _MEM_TRACKING
    return 0;
}

