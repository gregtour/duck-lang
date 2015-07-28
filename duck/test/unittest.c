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


int RunTest(const char* input)
{
    L_TOKEN*      lexing;
    SYNTAX_TREE*  ast;
    char*         buffer;
    int           error;

    // lex source
    buffer = 0;
    lexing = LexSourceBuffer(input, &buffer, CONTEXT_FREE_GRAMMAR);
    if (lexing == NULL) {
        return 1;
    }

    // parse source
    ast = ParseSource(lexing, PARSE_TABLE, CONTEXT_FREE_GRAMMAR);
    if (ast == NULL)
    {
        FreeLexing(lexing, buffer);
        return 1;
    }

    // interpret program
    error = Interpret(ast);
    if (error)
    {
        PrintStackTrace();
        FreeEnvironment();
        FreeLexing(lexing, buffer);
        FreeParseTree(ast);
        return 1;
    }

    FreeEnvironment();
    FreeLexing(lexing, buffer);
    FreeParseTree(ast);

    return 0;
}

int RunTests(TEST_PROGRAM* testSuite)
{
    int saved_stdout;
    int out_pipe[2];
    char* buffer;
    char* output;
    int bufferSize;
    int numRead;
    int iterator;
    int errors = 0;
    int pass;

    if (testSuite == NULL) return 0;

    saved_stdout = dup(STDOUT_FILENO);
#ifdef WIN32
    pipe(out_pipe /**/, 12000, O_BINARY /**/);
#else
    pipe(out_pipe);
#endif
    dup2(out_pipe[1], STDOUT_FILENO);
    close(out_pipe[1]);

    //int flags = fcntl(out_pipe[0], F_GETFL, 0);
    //fcntl(out_pipe[0], F_SETFL, flags | O_NONBLOCK);
    while (testSuite)
    {
        testSuite->passed = 1;
        printf("@");
        pass = RunTest(testSuite->input);
        fflush(stdout);

        bufferSize = strlen(testSuite->output);
        buffer = (char*)malloc(sizeof(char) * (bufferSize + 13));

        numRead = read(out_pipe[0], buffer, bufferSize + 10);
        buffer[numRead] = '\0';

        iterator = 0;
        while (iterator < numRead && buffer[iterator] != '@')
        {
            iterator++;
        }
        output = buffer + iterator + 1;
        numRead = numRead - iterator - 1;

        if (numRead > bufferSize) {
            errors++;
            testSuite->passed = 0;
        } else {
            for (iterator = 0; iterator < bufferSize; iterator++)
            {
                // compare output to testcase output
                if ((output[iterator] != testSuite->output[iterator]
                    && testSuite->output[iterator] != '\r'
                    && testSuite->output[iterator] != '\n') ||
                    (testSuite->output[iterator] != '\n' &&
                     iterator > numRead))
                {
                    errors++;
                    testSuite->passed = 0;
                    break;
                }
            }
        }

        if (testSuite->passed && pass != 0)
        {
            errors++;
            testSuite->passed = 0;
        }
        
        free(buffer);
        testSuite = testSuite->nexttest;
    }

    dup2(saved_stdout, STDOUT_FILENO);
    fflush(stdout);

    return errors;
}


// main(args) accepts testcase to run 
int main(int argc, char* argv[])
{
    FILE* input;
    char* buffer = 0;
    char* bufferRn = 0;
    TEST_PROGRAM* testsuite = NULL;
    TEST_PROGRAM* tail = NULL;
    int   size;
    int   read;
    int   result = 1;
    int   index = 0;
    int   count;

    // must include unit test file argument
    if (argc != 2)
    {   return -1;  }

    input = fopen(argv[1], "rb");
    if (input == 0) {
        // file must exit
        printf("Could not open unit tests.\n");
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
        return 1;
    }

    index = 0;
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
                    program->name = '\0';
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

    result = RunTests(testsuite);

end_test:

    if (result > 0) {
        printf("%i failed:\n", result);
    } else {
        printf("All passed!\n");
    }

    while (testsuite) 
    {
        TEST_PROGRAM* next = testsuite->nexttest;

        if (testsuite->passed != 1) {
            printf("%s failed.\n", testsuite->name);
        }
        free(testsuite);
        testsuite = next;
    }

    free(buffer);
    fflush(stdout);
#ifdef WIN32
    getchar();
#endif
    return result;
}


