/* grammar.c */

#include "lr_parser.h"


// globals
int gSymbolRoot       = 0;
int gSymbolGoal       = K_SYMBOL + 1;
int gSymbolEpsilon    = K_TOKEN + 1;
int gSymbolEOF        = K_TOKEN + 2;
int gSymbolEndLine    = K_TOKEN + 3;
int gSymbolInteger    = K_TOKEN + 4;
int gSymbolFloat      = K_TOKEN + 5;
int gSymbolString     = K_TOKEN + 6;
int gSymbolIdentifier = K_TOKEN + 7;

// grammar table functions
char* GetElement(int i, GRAMMAR_TABLE grammar)
{
    char* search;
    char* end;
    int   index;

    if (i & K_SYMBOL) {
        search = grammar.symbols;
        end = grammar.symbols + SYMBOL_BUFFER_SIZE;
        i ^= K_SYMBOL;
    } else if (i & K_TOKEN) {
        search = grammar.tokens;
        end = grammar.tokens + TOKEN_BUFFER_SIZE;
        i ^= K_TOKEN;
    } else {
        return 0;
    }

    index = 1;
    while (index < i &&
           search < end)
    {
        while (search[0] != 0 && search != end)
            search++;
        search++;
        index++;
    }

    if (search < end)
        return search;
    return 0;
}

RULE* GetRule(int lhs, int n, GRAMMAR_TABLE grammar)
{
    int r;
    for (r = 0; r < grammar.numRules; r++)
    {
        if (grammar.rules[r].lhs == lhs) {
            if (n == 0)
                return grammar.rules + r;
            n--;
        }
    }
    return NULL;
}

int AddSymbol(char*          string,
              int            len,
              GRAMMAR_TABLE* grammar)
{
    int   j;
    char* search = grammar->symbols;
    char* end = grammar->symbols + SYMBOL_BUFFER_SIZE;
    int   index = 1;
    while (index <= grammar->numSymbols &&
           search < end)
    {
        for (j = 0; j < len; j++)
        {
            if (string[j] != search[j])
                break;
        }
        if (j == len && search[j] == 0)
        {
            return index | K_SYMBOL;
        }
        while (search[0] != 0 && search != end)
            search++;
        search++;
        index++;
    }

    if (search < end)
    {
        for (j = 0; j < len && search < end; j++)
        {
            search[0] = string[j];
            search++;
        }
        search[0] = 0;
        grammar->numSymbols++;
        return index | K_SYMBOL;
    }

    return 0;
}

int AddToken(char*           string,
              int            len,
              GRAMMAR_TABLE* grammar)
{
    int   j;
    char* search = grammar->tokens;
    char* end = grammar->tokens + TOKEN_BUFFER_SIZE;
    int   index = 1;
    while (index <= grammar->numTokens &&
           search < end)
    {
        for (j = 0; j < len; j++)
        {
            if (string[j] == '\\') j++;
            if (string[j] != search[j])
                break;
        }
        if (j == len && search[j] == 0)
        {
            return index | K_TOKEN;
        }
        while (search[0] != 0 && search != end)
            search++;
        search++;
        index++;
    }

    if (search < end)
    {
        for (j = 0; j < len && search < end; j++)
        {
            if (string[j] == '\\') j++;
            search[0] = string[j];
            search++;
        }
        search[0] = 0;
        grammar->numTokens++;
        return index | K_TOKEN;
    }

    return 0;
}

int FindToken(char*          string,
              int            len,
              GRAMMAR_TABLE  grammar)
{
    int   j;
    char* search = grammar.tokens;
    char* end = grammar.tokens + TOKEN_BUFFER_SIZE;
    int   index = 1;
    while (index <= grammar.numTokens &&
           search < end)
    {
        for (j = 0; j < len; j++)
        {
            if (string[j] == '\\') j++;
#ifdef CASE_SENSITIVE_KEYWORDS
            if (string[j] != search[j])
                break;
#else
            if (toupper(string[j]) != toupper(search[j]))
                break;
#endif
        }
        if (j == len && search[j] == 0)
        {
            return index | K_TOKEN;
        }
        while (search[0] != 0 && search != end)
            search++;
        search++;
        index++;
    }

    return 0;
}

// grammar table memory management
void FreeGrammarTable(GRAMMAR_TABLE* table)
{
    int i;

    free(table->symbols);
    free(table->tokens);
    table->numSymbols = 0;
    table->numTokens = 0;

    for (i = 0; i < table->numRules; i++)
    {
        free(table->rules[i].rhs);
    }
    free(table->rules);
    table->numRules = 0;
}

/* load context free grammar */

int LoadGrammar(const char*    file,
                GRAMMAR_TABLE* table)
{
    FILE* input;
    char* buffer;
    int   size;
    int   i, r, start, end;
    int   rhs, symbol, token;
    int   read, line, col;

    // initialize table
    table->numSymbols = 0;
    table->symbols = (char*)malloc(SYMBOL_BUFFER_SIZE);
    table->symbols[SYMBOL_BUFFER_SIZE - 1] = 0;
    table->numTokens = 0;
    table->tokens = (char*)malloc(TOKEN_BUFFER_SIZE);
    table->tokens[TOKEN_BUFFER_SIZE - 1] = 0;
    table->numRules = 0;
    table->rules = 0;

    // add built in symbols
    gSymbolRoot       = 0;
    gSymbolGoal       = K_SYMBOL + table->numSymbols + 1;
    gSymbolEpsilon    = AddToken("<epsilon>", 9, table);
    gSymbolEOF        = AddToken("<$>", 3, table);
    gSymbolEndLine    = AddToken("<endl>", 6, table);
    gSymbolInteger    = AddToken("<integer>", 9, table);
    gSymbolFloat      = AddToken("<float>", 7, table);
    gSymbolString     = AddToken("<string>", 8, table);
    gSymbolIdentifier = AddToken("<identifier>", 12, table);

    // read grammar file
    printf("Loading context free grammar from %s...\n", file);
    input = fopen(file, "rb");
    if (input == 0) {
        printf("Could not open grammar file.\n");
        return 1;
    }
    fseek(input, 0, SEEK_END);
    size = ftell(input);
    rewind(input);
    buffer = (char*)malloc(size+2);
    read = fread(buffer, 1, size, input);
    buffer[size] = '\n';
    buffer[size+1] = 0;
    fclose(input);
    
    printf("Read %i of %i bytes.\n", read, size);

    if (size == 0) {
        printf("Unable to read grammar rules.\n");
        return 1;
    }

    // count rules
    table->numRules = 0; col = 0;
    for (i = 0; i < size; i++)
    {
        // don't count comments or new lines
        if (col == 0 &&
            (buffer[i] == ';' || buffer[i] == '\r' || buffer[i] == '\n'))
        {
            while (i < size && buffer[i] != '\n')
                i++;
            continue;
        }
        col++;
        if (buffer[i] == '\r') buffer[i] = 0;
        else if (buffer[i] == '\n') { table->numRules++; col = 0; }
    }
    printf("Loaded %i grammar rules.\n", table->numRules);
    table->numRules++;

    // S' -> S
    table->rules = (RULE*)malloc(sizeof(RULE) * table->numRules);
    table->rules[0].lhs = gSymbolRoot;
    table->rules[0].rhs = (int*)malloc(sizeof(int) * RULE_RHS_SIZE);
    table->rules[0].rhs[0] = gSymbolGoal;
    table->rules[0].rhs[1] = 0;
    table->rules[0].rhsLength = 1;

    // parse rules
    start = 0; end = 0; line = 0;
    for (r = 1; r < table->numRules; r++)
    {
        // skip comments or blank lines
        while (start < size &&
                (buffer[start] == ';' || buffer[start] == '\n'
                 || buffer[start] == 0))
        {
            while (start < symbol && buffer[start] != '\n')
                start++;
            start++;
            line++;
        }
        // left hand symbol
        while (start < size && buffer[start] != '<')
            start++;
        end = start;
        while (start < size && buffer[end] != '>')
            end++;
        symbol = AddSymbol(&buffer[start], end - start + 1, table);
        if (symbol == 0) {
            printf("Could not identify left hand symbol in rule %i ", r+1);
            printf("on line %i.\n", line);
            return 1;
        }
        table->rules[r].lhs = symbol;
        start = end + 1;

        // ::= operator
        while (start < size - 2)
        {
            if (buffer[start] == ':' &&
                buffer[start+1] == ':' &&
                buffer[start+2] == '=')
            {
                break;
            }
            start++;
        }
        start = start + 3;

        // right hand side
        table->rules[r].rhs = (int*)malloc(sizeof(int) * RULE_RHS_SIZE);
        rhs = 0;
        while (start < size &&
               buffer[start] != '\n' &&
               buffer[start] != 0 &&
               rhs < RULE_RHS_SIZE)
        {
            if (buffer[start] == '<')
            {
                // symbol
                end = start;
                while (buffer[end] != '>' &&
                       end < size)
                {
                    end++;
                }

                symbol = FindToken(&buffer[start], end - start + 1, *table);
                if (symbol == 0)
                    symbol = AddSymbol(&buffer[start], end - start + 1, table);
                if (symbol == 0)
                {
                    printf("Could not identify right hand symbol in rule %i ", r+1);
                    printf("on line %i.\n", line);
                    return 1;
                }
                table->rules[r].rhs[rhs] = symbol;
                rhs++;
                start = end + 1;
            }
            else if (buffer[start] != ' ')
            {
                // token
                end = start;
                while (buffer[end] != ' ' &&
                      (buffer[end] != '<' ||
                       buffer[end-1] == '\\') &&
                       buffer[end] != '\n' &&
                       buffer[end] != 0 &&
                       end < size)
                {
                    end++;
                }

                token = AddToken(&buffer[start], end - start, table);
                if (token == 0)
                {
                    printf("Could not identify right hand token in rule %i ", r+1);
                    printf("on line %i.\n", line);
                    return 1;
                }
                table->rules[r].rhs[rhs] = token;
                rhs++;
                start = end;
            }
            else
            {
                // whitespace
                start++;
            }
        }
        table->rules[r].rhs[rhs] = 0;
        table->rules[r].rhsLength = rhs;
        if (rhs == 0) {
            printf("Rule %i on line %i has no right hand side.\n", r, line);
            return 1;
        } else if (rhs == RULE_RHS_SIZE) {
            printf("Rule %i on line %i may be too long.\n", r, line);
        }
    }

    if (gSymbolGoal == 0)
    {
        printf("Grammar is missing a goal symbol.\n");
        return 1;
    }

    printf("Parsed %i of %i rules.\n\n", r, table->numRules);

    free(buffer);
    return 0;
}

// binary loading
int LoadGrammar(const char* file, GRAMMAR_TABLE* table);
int LoadGrammarBinary(const char* file, GRAMMAR_TABLE* table);

// testing
void PrintGrammar(GRAMMAR_TABLE table)
{
    int i, j, token;
    printf("Grammar Table\n");
    printf("-------------\n");

    // symbols
    printf("SYMBOLS\n");
    j = 0;
    for (i = 0; i < table.numSymbols; i++)
    {
        printf("%i. '%s'\n", i+1, &table.symbols[j]);
        j = j + strlen(&table.symbols[j]) + 1;
    }

    // tokens
    printf("TOKENS\n");
    j = 0;
    for (i = 0; i < table.numTokens; i++)
    {
        printf("%i. '%s'\n", i+1, &table.tokens[j]);
        j = j + strlen(&table.tokens[j]) + 1;
    }

    // rules
    printf("RULES\n");
    for (i = 0; i < table.numRules; i++)
    {
        printf("%i. S%i ::= ", i+1, table.rules[i].lhs & K_VALUE);
        j = 0;
        token = table.rules[i].rhs[0];
        while (token != 0)
        {
            if (token & K_SYMBOL)
            {
                token ^= K_SYMBOL;
                printf("S");
            }
            else if (table.rules[i].rhs[j] & K_TOKEN)
            {
                token ^= K_TOKEN;
                printf("T");
            }
            printf("%i ", token);
            j++;
            token = table.rules[i].rhs[j];
        }
        printf("\n");
    }
    printf("\n");
}

