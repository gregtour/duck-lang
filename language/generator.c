/* generator.c */

#include "lr_parser.h"


#define gRuleNameBufferLength       24
char gRuleNameBuffer[gRuleNameBufferLength];

const char* RuleName(int r, GRAMMAR_TABLE grammar)
{
    const char* name;
    int i, j;
    int capitalize = 1;
    int index, count;

    name = GetElement(grammar.rules[r].lhs, grammar);
    for (j = 0, i = 0; name[j]; j++)
    {
        if (i == gRuleNameBufferLength - 3) break;
        if (name[j] != '<' && name[j] != '>')
        {
            if (isAlpha(name[j]))
            {
                if (capitalize &&
                    name[j] <= 'z' && name[j] >= 'a')
                {
                    gRuleNameBuffer[i++] = name[j] - 'a' + 'A';
                }
                else
                {
                    gRuleNameBuffer[i++] = name[j];
                }
                capitalize = 0;
            }
            else if (isNumeric(name[j]))
            {
                gRuleNameBuffer[i++] = name[j];
                capitalize = 1;
            }
            else
            {
                capitalize = 1;
            }
        }
    }
    
    count = 0;
    for (j = 0; j < grammar.numRules; j++)
    {
        if (grammar.rules[j].lhs == grammar.rules[r].lhs)
            count++;
        if (j == r)
            index = count;
    }
    
    if (count > 1)
    {
        gRuleNameBuffer[i++] = 'A' + ((index-1) % 26);
        index = (index - 1) / 26;
        if (index) gRuleNameBuffer[i++] = 'A' + ((index-1) % 26);
    }
    gRuleNameBuffer[i] = '\0';
    return gRuleNameBuffer;
}

/* define constants for language symbols */
void SaveDefines(FILE* file, GRAMMAR_TABLE grammar)
{
    int i, j;
    const char* name;
    
    // symbols
    fprintf(file, "/* symbol constants */\n");
    for (i = 1; i <= grammar.numSymbols; i++)
    {
        fprintf(file, "#define SYMBOL_");
        name = GetElement(i | K_SYMBOL, grammar);
        for (j = 0; name[j]; j++)
        {
            if (name[j] != '<' && name[j] != '>')
            {
                if (isAlpha(name[j]))
                {
                    if (name[j] <= 'z' && name[j] >= 'a')
                        fprintf(file, "%c", name[j] - 'a' + 'A');
                    else
                        fprintf(file, "%c", name[j]);
                }
                else if (isNumeric(name[j]))
                {
                    fprintf(file, "%c", name[j]);
                }
                else
                {
                    fprintf(file, "_");
                }
            }
        }
        
        while (j++ < 27) fprintf(file, " ");
        fprintf(file, "0x%.4X", i | K_SYMBOL);
        fprintf(file, "\n");
    }
    fprintf(file, "\n\n");
}

/* save the binary data of a grammar file to a header */
void SaveGrammar(FILE* file, GRAMMAR_TABLE grammar)
{
    int i, j, length;
    
    // count symbols
    j = grammar.numSymbols;
    length = 0;
    for (i = 0; i < SYMBOL_BUFFER_SIZE; i++)
    {
        length++;
        if (grammar.symbols[i] == 0) {
            j--;
            if (j == 0) break;
        }
    }
    
    // symbols
    fprintf(file, "/* Grammar Symbols */\n");
    fprintf(file, "char GRAMMAR_SYMBOLS[%i] =\n",
        length);
    fprintf(file, "    \"");
    
    j = grammar.numSymbols;
    for (i = 0; i < SYMBOL_BUFFER_SIZE; i++)
    {
        if (grammar.symbols[i])
            fprintf(file, "%c", grammar.symbols[i]);
        else
        {
            fprintf(file, "\\0");
            fprintf(file, "\"");
            j--;
            if (j) {
                fprintf(file, "\n    \"");
            }
            else
            {
                break;
            }
        }
    }
    fprintf(file, ";\n");
    fprintf(file, "\n");
    
    // count tokens
    j = grammar.numTokens;
    length = 0;
    for (i = 0; i < SYMBOL_BUFFER_SIZE; i++)
    {
        length++;
        if (grammar.tokens[i] == 0) {
            j--;
            if (j == 0) break;
        }
    }
    
    // tokens
    fprintf(file, "/* Grammar Tokens */\n");
    fprintf(file, "char GRAMMAR_TOKENS[%i] =\n",
        length);
    fprintf(file, "    \"");
    j = grammar.numTokens;
    for (i = 0; i < TOKEN_BUFFER_SIZE; i++)
    {
        if (grammar.tokens[i])
            fprintf(file, "%c", grammar.tokens[i]);
        else
        {
            fprintf(file, "\\0");
            fprintf(file, "\"");
            j--;
            if (j) {
                fprintf(file, "\n    \"");
            }
            else
            {
                break;
            }
        }
    }
    fprintf(file, ";\n");
    fprintf(file, "\n\n");
    
    // rules
    fprintf(file, "/* Rule Right Hand Sides */\n");
    for (i = 0; i < grammar.numRules; i++)
    {
        fprintf(file, "int RULE_%i_RHS[] = ", i);
        fprintf(file, "{");
        fprintf(file, "");
        for (j = 0; j < RULE_RHS_SIZE; j++)
        {
            fprintf(file, "%i, ", grammar.rules[i].rhs[j]);
            if (grammar.rules[i].rhs[j] == 0) break;
        }
        fprintf(file, "};\n");
    }
    fprintf(file, "\n");
    
    fprintf(file, "/* CFG Productions */\n");
    fprintf(file, "RULE GRAMMAR_RULES[%i] =\n",
        grammar.numRules);
    fprintf(file, "{\n");
    for (i = 0; i < grammar.numRules; i++)
    {
        fprintf(file, "    %i, %i, RULE_%i_RHS,\n",
            grammar.rules[i].lhs,
            grammar.rules[i].rhsLength,
            i);
    }
    fprintf(file, "};\n");
    fprintf(file, "\n");

    // CFG struct
    fprintf(file, "/* Context Free Grammar */\n");
    fprintf(file, "GRAMMAR_TABLE CONTEXT_FREE_GRAMMAR =\n");
    fprintf(file, "{\n");
    fprintf(file, "    %i, GRAMMAR_SYMBOLS,\n", grammar.numSymbols);
    fprintf(file, "    %i, GRAMMAR_TOKENS,\n", grammar.numTokens);
    fprintf(file, "    %i, GRAMMAR_RULES,\n", grammar.numRules);
    fprintf(file, "};\n");
    fprintf(file, "\n\n");
}

/* save the binary data of an slr parse table to a header file*/
void SaveParser(FILE* file, LR_TABLE parser)
{
    int i;
    
    // goto table
#ifdef _SLR
    fprintf(file, "/* SLR GOTO table */\n");
#endif
#ifdef _LR1
    fprintf(file, "/* LR(1) GOTO table */\n");
#endif
    fprintf(file, "int GOTO_TABLE[%i] =\n",
        parser.numStates * parser.numSymbols);
    fprintf(file, "{");
    for (i = 0; i < parser.numStates * parser.numSymbols; i++)
    {
        if ((i%16) == 0)
        {
            fprintf(file, "\n    ");
        }
        fprintf(file, "%i, ",
            parser.gotoTable[i]);
    }

    fprintf(file, "\n};\n");
    fprintf(file, "\n\n");

    // action table
#ifdef _SLR
    fprintf(file, "/* SLR ACTION table */\n");
#endif
#ifdef _LR1
    fprintf(file, "/* LR(1) ACTION table */\n");
#endif
    fprintf(file, "ACTION ACTION_TABLE[%i] =\n",
        parser.numStates * parser.numTokens);
    fprintf(file, "{");
    for (i = 0; i < parser.numStates * parser.numTokens; i++)
    {
        if ((i%8) == 0)
        {
            fprintf(file, "\n    ");
        }
        fprintf(file, "%i, %i, ",
            parser.actionTable[i].type,
            parser.actionTable[i].value);
    }
    fprintf(file, "\n};\n");
    fprintf(file, "\n\n");

    // LR_TABLE object
#ifdef _SLR
    fprintf(file, "/* SLR parse table struct */\n");
#endif
#ifdef _LR1
    fprintf(file, "/* LR(1) parse table struct */\n");
#endif
    fprintf(file, "LR_TABLE PARSE_TABLE =\n");
    fprintf(file, "{\n");
    fprintf(file, "    %i, %i, %i,\n",
        parser.numTokens,
        parser.numSymbols,
        parser.numStates);
    fprintf(file, "    ACTION_TABLE,\n");
    fprintf(file, "    GOTO_TABLE\n");
    fprintf(file, "};\n");
    fprintf(file, "\n");
}

void SaveProductions(FILE*         file,
                     LR_TABLE      parser,
                     GRAMMAR_TABLE grammar)
{
    RULE rule;
    int r, rhs;
    const char* name;
    int j, count, index;

    fprintf(file, "/* production stubs */\n\n");
    for (r = 1; r < grammar.numRules; r++)
    {
        rule = grammar.rules[r];

        fprintf(file, "/* ");
        fprintf(file, "%i. ", r);
        fprintf(file, "%s -> ", GetElement(rule.lhs, grammar));
        for (rhs = 0; rhs < rule.rhsLength; rhs++)
        {
            fprintf(file, "%s ", GetElement(rule.rhs[rhs], grammar));
        }
        fprintf(file, "*/\n");
        
        fprintf(file, "int Reduce%s(SYNTAX_TREE* node)\n",
            RuleName(r, grammar));
        fprintf(file, "{\n");
        fprintf(file, "    if (node->numChildren != %i) return %i;\n",
            rule.rhsLength, r);
        for (rhs = 0; rhs < rule.rhsLength; rhs++)
        {
            int symbol = rule.rhs[rhs];
            if (symbol & K_SYMBOL ||
                symbol == gSymbolInteger ||
                symbol == gSymbolFloat ||
                symbol == gSymbolString ||
                symbol == gSymbolIdentifier)
            {
                fprintf(file, "    SYNTAX_TREE* ");
                
                name = GetElement(symbol, grammar);
                for (j = 0; name[j]; j++)
                {
                    if (name[j] != '<' && name[j] != '>')
                    {
                        if (isAlpha(name[j]) || isNumeric(name[j]))
                            fprintf(file, "%c", name[j]);
                        else
                            fprintf(file, "_");
                    }
                }
                
                count = 0;
                for (j = 0; j < rule.rhsLength; j++)
                {
                    if (rule.rhs[j] == symbol)
                        count++;
                    if (j == rhs)
                        index = count;
                }
                
                fprintf(file, "%i", index);
                
                fprintf(file, " = ");
                fprintf(file, "node->children[%i];\n", rhs);
            }
        }
        
        fprintf(file, "\n");
        fprintf(file, "    int error = 0;\n");
        for (rhs = 0; rhs < rule.rhsLength; rhs++)
        {
            int symbol = rule.rhs[rhs];
            if (symbol & K_SYMBOL ||
                symbol == gSymbolInteger ||
                symbol == gSymbolFloat ||
                symbol == gSymbolString ||
                symbol == gSymbolIdentifier)
            {
                fprintf(file, "    error = error || CompileNode(");

                name = GetElement(symbol, grammar);
                for (j = 0; name[j]; j++)
                {
                    if (name[j] != '<' && name[j] != '>')
                    {
                        if (isAlpha(name[j]) || isNumeric(name[j]))
                            fprintf(file, "%c", name[j]);
                        else
                            fprintf(file, "_");
                    }
                }

                count = 0;
                for (j = 0; j < rule.rhsLength; j++)
                {
                    if (rule.rhs[j] == symbol)
                        count++;
                    if (j == rhs)
                        index = count;
                }

                fprintf(file, "%i", index);
                fprintf(file, ");\n");
            }
        }
        
        fprintf(file, "\n");
        fprintf(file, "    return error;\n");
        fprintf(file, "}\n");

        fprintf(file, "\n");
    }
}

void SaveCompiler(FILE*         file,
                  LR_TABLE      parser,
                  GRAMMAR_TABLE grammar)
{
    RULE rule;
    int r, rhs;

    fprintf(file, "/* reduce one node */\n");
    fprintf(file, "int CompileNode(SYNTAX_TREE* node)\n");
    fprintf(file, "{\n");
    fprintf(file, "    if (node == NULL || node->production == 0)\n");
    fprintf(file, "        return 1;\n\n");
    fprintf(file, "    switch (node->production)\n");
    fprintf(file, "    {\n");
    
    for (r = 1; r < grammar.numRules; r++)
    {
        fprintf(file, "        ");
        fprintf(file, "case 0x%.2X: return Reduce%s(node);\n", r,
            RuleName(r, grammar));
    }

    fprintf(file, "    default:\n");
    fprintf(file, "        printf(\"Unknown production %%i.\\n\",");
    fprintf(file, " node->production);\n");
    fprintf(file, "        return 1;\n");
    fprintf(file, "    }\n");
    fprintf(file, "}\n");
}

/* save the LR_TABLE to a .C file and generate constants too */
int SaveLRParser(const char*   output,
                 LR_TABLE      parser,
                 GRAMMAR_TABLE grammar)
{
    FILE* file;
    char* header;
    char* tables;
    char* source;
    int length;
    
    if (output == NULL || output[0] == '\0')
    {
        printf("No output file given.\n");
        return 1;
    }
    
    length = strlen(output);
    header = malloc(length + 3);
    tables = malloc(length + 10);
    source = malloc(length + 3);
    
    sprintf(header, "%s.h", output);
    sprintf(tables, "%s_tables.c", output);
    sprintf(source, "%s.c", output);

    // save header file
    file = fopen(header, "w");
    if (file == 0) {
        printf("Could not open header file for output.\n");
        return 1;
    }
    
    fprintf(file, "/* auto-generated lr parse tables */\n");
    fprintf(file, "#ifndef _%s_H\n", output);
    fprintf(file, "#define _%s_H\n", output);
    fprintf(file, "\n");
    fprintf(file, "#include \"lr_parser.h\"\n");
    fprintf(file, "\n\n");
    fprintf(file, "/* main function */\n");
    fprintf(file, "int CompileNode(SYNTAX_TREE* node);\n\n");
    
    SaveDefines(file, grammar);
    SaveGrammar(file, grammar);
    SaveParser(file, parser);
    
    fprintf(file, "#endif // _%s_H\n", output);
    fclose(file);
    
    // save tables to a c file
#if 0
    file = fopen(tables, "w");
    if (file == 0) {
        printf("Could not open table file for output.\n");
        return 1;
    }
    
    SaveGrammar(file, grammar);
    SaveParser(file, parser);
    
    fprintf(file, "");
    fclose(file);
#endif

    // save source file
    file = fopen(source, "w");
    if (file == 0) {
        printf("Could not open source file for output.\n");
        return 1;
    }

    fprintf(file, "/* auto-generated compiler stubs */");
    fprintf(file, "\n");
    fprintf(file, "#include \"lr_parser.h\"\n");
    fprintf(file, "#include \"%s\"\n", header);
    fprintf(file, "\n\n");

    SaveProductions(file, parser, grammar);
    SaveCompiler(file, parser, grammar);
    fclose(file);
    
    free(header);
    free(tables);
    free(source);
    return 0;
}
