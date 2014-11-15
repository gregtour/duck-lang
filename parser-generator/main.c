// LR Parser

#define malloc malloc
#include <stdlib.h>
#include "lr_parser.h"
//#include "generated_parser.h"
//#include "java_parser.h"

// memory tracker
#ifdef _MEM_TRACKING
int gTotalMemoryUsage = 0;
int gMallocCalls = 0;
int gFreeCalls = 0;

#ifdef malloc
#undef malloc
#endif

#ifdef free
#undef free
#endif

void* MallocTrackMemory(size_t size)
{
    gTotalMemoryUsage += (int)size; // gTotalMemoryUsage + size;
    gMallocCalls++;
    return malloc(size);
}

void FreeTrackMemory(void* data)
{
    free(data);
    gFreeCalls++;
    return;
}

#ifndef malloc
#define malloc      MallocTrackMemory
#endif

#ifndef free
#define free        FreeTrackMemory
#endif

void PrintMemoryUsage()
{
    int b = gTotalMemoryUsage % 1000;
    int kb = (gTotalMemoryUsage / 1000) % 1000;
    int mb = (gTotalMemoryUsage / 1000000) % 1000;
    if (mb) {
        printf("Total memory usage: %i.%i mb\n", mb, kb);
    } else {
        printf("Total memory usage: %i.%i kb\n", kb, b);
    }

    printf("%i calls to malloc() with %i calls to free()\n", 
        gMallocCalls, 
        gFreeCalls);
}
#endif // _MEM_TRACKING

int ParserGenerator(const char* language,
                    const char* compiler)
{
    GRAMMAR_TABLE grammar;
    LR_TABLE      parser;
    int           error;

    printf("\n");

    // load grammar
    error = LoadGrammar(language, &grammar);
    if (error)
    {
        printf("Error loading context free grammar file\n");
        FreeGrammarTable(&grammar);
        PrintMemoryUsage();
        return 1;
    }
    PrintGrammar(grammar);

    // build parse tables
    error = BuildLRParser(grammar, &parser);
    if (error)
    {
        printf("Error building canonical LR parse tables.\n");
        FreeGrammarTable(&grammar);
        FreeLRParser(&parser);
        PrintMemoryUsage();
        return 2;
    }
    PrintLRParser(parser, grammar);
    
    error = SaveLRParser(compiler, parser, grammar);
    if (error)
    {
        printf("Failed to generate parser.\n");
        FreeGrammarTable(&grammar);
        FreeLRParser(&parser);
        return 3;
    }
    
    printf("Successfully generated parser!\n");
    FreeGrammarTable(&grammar);
    FreeLRParser(&parser);
    PrintMemoryUsage();
    return 0;
}

int TestParser(const char* language,
               const char* program)
{
    GRAMMAR_TABLE grammar;
    LR_TABLE      parser;
    L_TOKEN*      lexing;
    SYNTAX_TREE*  ast;
    char*         buffer;
    int           error;

    printf("\n");

    // load grammar
    error = LoadGrammar(language, &grammar);
    if (error)
    {
        printf("Error loading context free grammar file\n");
        FreeGrammarTable(&grammar);
        PrintMemoryUsage();
        return 1;
    }
    PrintGrammar(grammar);

    // build parse tables
    error = BuildLRParser(grammar, &parser);
    if (error)
    {
        printf("Error building canonical LR parse tables.\n");
        FreeGrammarTable(&grammar);
        FreeLRParser(&parser);
        PrintMemoryUsage();
        return 2;
    }
    PrintLRParser(parser, grammar);

    // lex source
    buffer = 0;
    lexing = LexSource(program, &buffer, grammar);
    if (lexing == NULL)
    {
        printf("Error lexing source or empty source file.\n");
        FreeGrammarTable(&grammar);
        FreeLRParser(&parser);
        FreeLexing(lexing, buffer);
        PrintMemoryUsage();
        return 3;
    }
    PrintLexing(lexing);

    // parse source
    ast = ParseSource(lexing, parser, grammar);
    if (ast == NULL)
    {
        printf("Error parsing source.\n");
        FreeGrammarTable(&grammar);
        FreeLRParser(&parser);
        FreeLexing(lexing, buffer);
        //FreeParseTree(parseTree);
        PrintMemoryUsage();
        return 4;
    }
    PrintParseTree(ast, grammar);

    printf("Success.\n");
    FreeGrammarTable(&grammar);
    FreeLRParser(&parser);
    FreeLexing(lexing, buffer);
    FreeParseTree(ast);
    PrintMemoryUsage();
    getchar();
    return 0;
}

// compiler frontend
int main(int argc, char** argv)
{
    int           error;

    //if (argc < 2) {
    //    printf("./lrparser grammar [-o output] [-t test]");
    //}
    
    //TestParser("grammar.txt", "output/duck_syntax");
    ParserGenerator("grammar.txt", "output/duck");
    getchar();
    return 0;
}

