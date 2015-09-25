/*
    Duck Programming Language - unittest.c

    Automated Unit Testing - Loads programs and their expected output from a 
    given file and checks the results against the expected output.

    Single line C-style comments are allowed.

    The beginning of a program is marked by '@test' followed by the name.

    The end of the program and beginning of output is marked by '@output'.

    And the end of output is delineated by '@end'.

Ex:
    @test simple-test
    duck.println(1 + duck.newline + 2 + duck.newline + (1+2))
    @output
    1
    2
    3
    @end
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>

#ifdef WIN32
#include <WinSock2.h>
#include <io.h>

#define STDOUT_FILENO 1
#define pipe _pipe
#else
#include <unistd.h>
#endif

#include "main.h"
#include "interpreter.h"

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
    else if (error == -1)
        return "Out of time.";
    else if (error == 2)
        return "Lexing error.";
    else if (error == 3)
        return "Parse error.";
    else
        return "Unspecified error.";
}


typedef struct TEST_PROGRAM
{
    const char* name;
    const char* input;
    const char* output;
    struct TEST_PROGRAM* 
        nexttest;
    int passed;
} TEST_PROGRAM;


int ExecuteProgram(const char* input)
{
    L_TOKEN*      lexing;
    SYNTAX_TREE*  ast;
    char*         buffer;
    int           error;

    // lex source
    buffer = 0;
    lexing = LexSourceBuffer(input, &buffer, CONTEXT_FREE_GRAMMAR);
    if (lexing == NULL) {
        return 2;
    }

    // parse source
    ast = ParseSource(lexing, PARSE_TABLE, CONTEXT_FREE_GRAMMAR);
    if (ast == NULL)
    {
        FreeLexing(lexing, buffer);
        return 3;
    }

    // interpret program
    error = Interpret(ast);
    if (error)
    {
        PrintStackTrace();
        FreeEnvironment();
        FreeLexing(lexing, buffer);
        FreeParseTree(ast);
        return error;
    }

    FreeEnvironment();
    FreeLexing(lexing, buffer);
    FreeParseTree(ast);

    return 0;
}

int RunTest(TEST_PROGRAM* program, char** destbuffer, int* size)
{
    const int BUFFER_SIZE = 256;
    int saved_stdout;
    int out_pipe[2];
    int runtimeError;
    int length;
    int scanning;
    int buffersize;

    *destbuffer = NULL;
    *size = 0;
    if (program == NULL) return 0;

    // Redirect standard output to our pipe
#ifdef WIN32
    saved_stdout = _dup(STDOUT_FILENO);
    pipe(out_pipe /**/, 12000, O_BINARY /**/);
    _dup2(out_pipe[1], STDOUT_FILENO);
    _close(out_pipe[1]);
#else
    saved_stdout = dup(STDOUT_FILENO);
    pipe(out_pipe);
    dup2(out_pipe[1], STDOUT_FILENO);
    close(out_pipe[1]);
#endif

    // Run the program to get its output
    printf("@");
    runtimeError = ExecuteProgram(program->input);
    printf("#");
    fflush(stdout);

    // Extract the program to a buffer
    *destbuffer = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    buffersize = BUFFER_SIZE + 1;

    scanning = 1;
    length = 0;
    // Scan until reaching the end of output token
    while (scanning)
    {
        int iterator;
        iterator = length;
        length = length + read(out_pipe[0], *destbuffer + length, BUFFER_SIZE);

        for (; iterator < length; iterator++)
        {
            if ((*destbuffer)[iterator] == '#') scanning = 0;
        }

        if (scanning)
        {
            buffersize += BUFFER_SIZE;
            *destbuffer = (char*)realloc(*destbuffer, buffersize);
        }
    }
    (*destbuffer)[length] = 0;
    (*size) = length;

    // Resume normal standard output
    dup2(saved_stdout, STDOUT_FILENO);
    fflush(stdout);

    return runtimeError;
}

int RunTests(TEST_PROGRAM* testSuite)
{
    char* buffer;
    int error;
    int failures = 0;
    int size;
    int outputlen;

    while (testSuite)
    {
        printf("%s [", testSuite->name);
        fflush(stdout);
        error = RunTest(testSuite, &buffer, &size);

        if (error != 0) {
            printf("fail]: %s\n", ErrorMessage(error));
            failures++;
        } else {
            if (buffer[0] != '@') {
                printf("fail]: Could not capture output.\n");
                failures++;
            } else {
                int matches = 1;
                int i, j;

                // compare outputs
                outputlen = strlen(testSuite->output);
                for (i = 1, j = 0;
                     i < size && j < outputlen;
                     i++, j++)
                {
                    if (buffer[i] != testSuite->output[j])
                    {
                        matches = 0;
                    }
                }

                if (buffer[i] != '#') matches = 0;

                if (matches) {
                    printf("pass]\n");
                } else {
                    printf("fail]:\n");
                    for (i = 0; i < size; i++) {
                        if (buffer[i] == '#') {
                            buffer[i] = 0;
                            break;
                        }
                    }
                    printf("%s\n", buffer+1);
                    failures++;
                }
            }
        }

        if (buffer) { free(buffer); }
        testSuite = testSuite->nexttest;
    }

    return failures;
}



// main(args) accepts test cases to run 
int main(int argc, char* argv[])
{
    FILE* input;
    char* buffer = 0;
    char* bufferRn = 0;
    TEST_PROGRAM* testsuite = NULL;
    TEST_PROGRAM* tail = NULL;
    unsigned int   size;
    unsigned int   read;
    unsigned int   index = 0;
    unsigned int   count;
    unsigned int   parsed;
    unsigned int   testcount;
    int   result = 1;

    // must include unit test file argument
    if (argc != 2)
    {   
        printf("Please provide an argument for the unit test file.\n");
#ifdef WIN32
        getchar();
#endif
        return -1;  
    }

    input = fopen(argv[1], "rb");
    if (input == 0) {
        // file must exit
        printf("Could not open unit tests.\n");
#ifdef WIN32
        getchar();
#endif
        return 1;
    }
    fseek(input, 0, SEEK_END);
    size = ftell(input);
    rewind(input);
    bufferRn = (char*)malloc(size+1);
    read = fread(bufferRn, 1, size, input);
    bufferRn[size] = 0;
    fclose(input);

    // remove \r
    buffer = (char*)malloc(size+1);
    for (index = 0, count = 0; index < size; index++)
    {
        if (bufferRn[index] != '\r')
            buffer[count++] = bufferRn[index];
    }
    size = count;
    free(bufferRn);
    
    if (size == 0) {
        // file must not be empty
        printf("Unable to read input file.\n");
#ifdef WIN32
        getchar();
#endif
        return 1;
    }


    index = 0;
    parsed = 0;
    testcount = 0;
    // parse tests
    while (index < size)
    {
        if (buffer[index] == '@')
        {
            if (index + strlen("@test ") < size
                && buffer[index+1] == 't'
                && buffer[index+2] == 'e'
                && buffer[index+3] == 's'
                && buffer[index+4] == 't'
                && buffer[index+5] == ' ')
            {
                // new testcase
                TEST_PROGRAM* program = (TEST_PROGRAM*)malloc(sizeof(TEST_PROGRAM));
                testcount++;
                program->nexttest = NULL;
                program->passed = 0;

                if (testsuite == NULL) { 
                    testsuite = program; 
                    tail = program;
                } else {
                    tail->nexttest = program;
                    tail = program;
                }

                index += 6;
                if (index < size) {
                    program->name = buffer + index;
                } else {
                    program->name = "";
                    goto end_test;
                }

                // capture program source
                while (index < size && buffer[index] != '\n') index++;
                if (index == size) { goto end_test; }
                buffer[index] = '\0';
                program->input = buffer + index + 1;

                // capture output
                while (index < size && buffer[index] != '@') index++;
                if (index == size) { goto end_test; }
                if (index + 7 >= size) { goto end_test; }
                if (buffer[index+1] != 'o' ||
                    buffer[index+2] != 'u' ||
                    buffer[index+3] != 't' ||
                    buffer[index+4] != 'p' ||
                    buffer[index+5] != 'u' ||
                    buffer[index+6] != 't')
                { goto end_test; }
                buffer[index] = '\0';

                while (index < size && buffer[index] != '\n') index++;
                if (index == size || index == size - 1) { goto end_test; }
                buffer[index] = '\0';
                program->output = buffer + index + 1;
                
                // terminate at @end
                while (index < size && buffer[index] != '@') index++;
                if (index == size) { goto end_test; }
                if (index + 4 > size) { goto end_test; }

                if (buffer[index+1] != 'e' ||
                    buffer[index+2] != 'n' ||
                    buffer[index+3] != 'd')
                { goto end_test; }

                buffer[index] = '\0';
                index += 4;
            }
        }
        else if (buffer[index] == '/' && buffer[index+1] == '/')
        {
            while (index < size && buffer[index] != '\n')
                index++;
        }
        index++;
    }

    parsed = 1;
    if (testcount > 1) {
        printf("Running %i tests...\n\n", testcount);
    } else if (testcount == 1) {
        printf("Running %i test...\n\n", testcount);
    }
    result = RunTests(testsuite);

end_test:

    if (parsed == 0) {
        printf("Incorrectly formatted test cases.\n");
        result = -1;
    } else {
        if (result > 0) {
            printf("\n%i/%i tests passed.\n\n", testcount - result, testcount);
        } else {
            printf("\nAll passed!\n\n");
        }
    }

    while (testsuite) 
    {
        TEST_PROGRAM* next = testsuite->nexttest;
        free(testsuite);
        testsuite = next;
    }

    free(buffer);

#ifdef _MEM_TRACKING
    PrintMemoryUsage();
#endif

    if (result == 0 && CheckMemoryUsage() != 0)
    {
        printf("\nTest failed due to memory leak!\n");
        result = 1;
    }

    fflush(stdout);
#ifdef WIN32
    getchar();
#endif
    return result;
}


