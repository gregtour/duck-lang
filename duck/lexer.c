/* lexer.c */

#include "lr_parser.h"


// lexer list functions
void LexAddBlock(L_TOKEN** start,
                 L_TOKEN** end,
                 L_TOKEN*  next)
{
    if (next) {
        if (next->string)
        {
            // use null terminated strings
            char* buffer = (char*)malloc(sizeof(char) * (next->length + 1));
            int i;
#ifdef CASE_SENSITIVE
            for (i = 0; i < next->length; i++)
                buffer[i] = next->string[i];
#else
            if (next->token == gSymbolIdentifier) {
                for (i = 0; i < next->length; i++)
                    buffer[i] = tolower(next->string[i]);
            } else {
                for (i = 0; i < next->length; i++)
                    buffer[i] = next->string[i];
            }
#endif
            buffer[i] = '\0';
            next->string = buffer;
        }

        if (*start)
            (*end)->next = next;
        else
            *start = next;
        *end = next;
    }
}

// lexer token constructors
L_TOKEN* EOFSYMBOL(int line)
{
    L_TOKEN* block = (L_TOKEN*)malloc(sizeof(L_TOKEN));

    // end of file
    block->token = gSymbolEOF;
    block->string = 0;
    block->length = 0;
    block->line = line;
    block->next = 0;

    return block;
}

L_TOKEN* NEWLINE(int line)
{
    L_TOKEN* block = (L_TOKEN*)malloc(sizeof(L_TOKEN));

    // end line
    block->token = gSymbolEndLine;
    block->string = 0;
    block->length = 0;
    block->line = line;
    block->next = 0;

    return block;
}

L_TOKEN* INTEGER(char* source,
                 int   start,
                 int   end,
                 int   line)
{
    L_TOKEN* block = (L_TOKEN*)malloc(sizeof(L_TOKEN));

    // number
    block->token = gSymbolInteger;
    block->string = source + start;
    block->length = end - start;
    block->line = line;
    block->next = 0;

    return block;
}

L_TOKEN* FLOAT(char* source,
               int   start,
               int   end,
               int   line)
{
    L_TOKEN* block = (L_TOKEN*)malloc(sizeof(L_TOKEN));
    
    // floating-point number
    block->token = gSymbolFloat;
    block->string = source + start;
    block->length = end - start;
    block->line = line;
    block->next = 0;

    return block;
}

L_TOKEN* STRING(char*         source,
                int           start,
                int           end,
                int           line)
{
    L_TOKEN* block = (L_TOKEN*)malloc(sizeof(L_TOKEN));

    // string
    block->token = gSymbolString;
    block->string = source + start + 1;
    block->length = end - start - 2;
    block->line = line;
    block->next = 0;

    return block;
}

L_TOKEN* TOKEN(char*          source,
               int            start,
               int            end,
               int            line,
               GRAMMAR_TABLE  grammar)
{
    int token;
    L_TOKEN* block = (L_TOKEN*)malloc(sizeof(L_TOKEN));

    token = FindToken(&source[start], end - start, grammar);
    if (token) {
        // token
        block->token = token;
        block->string = source + start;
        block->length = end - start;
        block->line = line;
        block->next = 0;
    } else {
        // identifier
        free(block);
        block = NULL;
        printf("Syntax error on line %i, ", line+1);
        printf("Error, illegal identifier: ");
        while (start < end)
            printf("0x%X", source[start++]);
        printf("\n");
    }

    return block;
}

L_TOKEN* IDENTIFIER(char*          source,
                    int            start,
                    int            end,
                    int            line,
                    GRAMMAR_TABLE  grammar)
{
    int token;
    L_TOKEN* block = (L_TOKEN*)malloc(sizeof(L_TOKEN));

    token = FindToken(&source[start], end - start, grammar);
    if (token) {
        // token
        block->token = token;
        block->string = source + start;
        block->length = end - start;
        block->line = line;
        block->next = 0;
    } else {
        // identifier
        block->token = gSymbolIdentifier;
        block->string = source + start;
        block->length = end - start;
        block->line = line;
        block->next = 0;
    }

    return block;
}

// lexer delimiter functions
int isAlpha(char c)
{
    return (('a' <= c && c <= 'z') ||
            ('A' <= c && c <= 'Z'));
}

int isNumeric(char c)
{
    return ('0' <= c && c <= '9');
}

int isSpace(char c)
{
    return (c == ' ' ||
            c == '\t' ||
            c == '\r' ||
            c == '\n');
}

int isGlyph(char c)
{
    return (!isAlpha(c) &&
            !isNumeric(c) &&
            !isSpace(c));
}

/* lex a source file for a program */
L_TOKEN* LexSource(const char*    file,
                   char**         stripped,
                   GRAMMAR_TABLE  table)
{
    FILE* input;
    char* buffer;
    int   size;
    int   read;
    L_TOKEN* result;

    // read source file
    input = fopen(file, "rb");
    if (input == 0) {
        printf("Could not open source file.\n");
        return 0;
    }
    fseek(input, 0, SEEK_END);
    size = ftell(input);
    rewind(input);
    buffer = (char*)malloc(size+1);
    read = fread(buffer, 1, size, input);
    buffer[size] = 0;
    fclose(input);
    
    if (size == 0) {
        printf("Unable to read source file.\n");
        return 0;
    }

    // lex source file
    result = LexSourceBuffer(buffer, 
                             stripped, 
                             table);
    free(buffer);
    return result;
}

/* lex a source buffer for a program */
L_TOKEN* LexSourceBuffer(const char*    source_buffer,
                         char**         stripped,
                         GRAMMAR_TABLE  table)
{
    const char* buffer;
    char*       format;
    int*        lineNumbers;
    int         line;
    int         size;
    int         i, j;
    int         a, b;

    L_TOKEN* start = NULL;
    L_TOKEN* end = NULL;

    buffer = source_buffer;
    size = strlen(buffer);
    
    // count lines
    lineNumbers = (int*)malloc((size+1)*sizeof(int));
    line = 0;
    for (i = 0; i <= size; i++)
    {
        lineNumbers[i] = line;
        if (buffer[i] == '\n')

            line++;
    }

    // strip clean
    format = (char*)malloc(size+1);
    j = 0;
    for (i = 0; i < size; i++)
    {
        if (buffer[i] == '/' &&
            buffer[i+1] == '/')
        {
            // inline comments
            while (i < size && buffer[i] != '\n') i++;
            i--;
        }
        else if (buffer[i] == '/' &&
                 buffer[i+1] == '*')
        {
            // multiline comments
            i++; i++;
            while (i < size - 1 &&
                   (buffer[i] != '*' ||
                    buffer[i+1] != '/'))
            {
                i++;
            }
            i++;
        }
#ifdef IGNORE_MACROS
        else if (buffer[i] == '#')
        {
            while (i < size && buffer[i] != '\n') i++;
            i--;
        }
#endif
#ifdef SEMICOLON_COMMENTS
        else if (buffer[i] == ';')
        {
            while (i < size && buffer[i] != '\n') i++;
            i--;
        }
#endif
        else if (isSpace(buffer[i]))
        {
            // whitespace
            format[j] = ' ';
            lineNumbers[j] = lineNumbers[i];

            while (i < size && isSpace(buffer[i]))
            {
                if (buffer[i] == '\n') {
                    format[j] = '\n';
                    lineNumbers[j] = lineNumbers[i];
                }
                i++;
            }
            i--;
            j++;
        }
        else if (buffer[i] == '"' ||
                 buffer[i] == '\'')
        {
            char quote = buffer[i];
            // string
            format[j++] = buffer[i++];
            while (i < size - 1 && buffer[i] != quote)
            {
                if (buffer[i] == '\\')
                {
                    lineNumbers[j] = lineNumbers[i];
                    format[j++] = buffer[i++];
                }
                lineNumbers[j] = lineNumbers[i];
                format[j++] = buffer[i++];
            }
            lineNumbers[j] = lineNumbers[i];
            format[j++] = buffer[i];
        }
        else
        {
            // character
            lineNumbers[j] = lineNumbers[i];
            format[j] = buffer[i];
            j++;
        }
    }
    
    format[j] = 0;
    size = j;

    // lex
    // printf("Lexing...\n\n");

    for (i = 0; i < size; i++)
    {
        line = lineNumbers[i];
        if (isAlpha(format[i]))
        {
            a = i;
            // alpha
            while (i < size &&
                   (isAlpha(format[i]) ||
                    isNumeric(format[i]) ||
                    format[i] == '_'))
            {
                i++;
            }
            b = i;
            LexAddBlock(&start, &end, IDENTIFIER(format,
                                                 a,
                                                 b,
                                                 line,
                                                 table));
            i--;
        }
        else if (isNumeric(format[i]))
        {
            // numeric
            a = i;
            while (i < size &&
                   isNumeric(format[i]))
            {
                i++;
            }
            if (format[i] == '.') {
                i++;
                while (i < size &&
                       isNumeric(format[i]))
                {
                    i++;
                }
                b = i;
                LexAddBlock(&start, &end, FLOAT(format,
                                                a,
                                                b,
                                                line));
                i--;
            } else {
                b = i;
                LexAddBlock(&start, &end, INTEGER(format,
                                                  a,
                                                  b,
                                                  line));
                i--;
            }
        }
        else if (format[i] == '"' ||
                 format[i] == '\'')
        {
            char delimiter = format[i];
            // string
            a = i++;
            while (i < size &&
                   format[i] != delimiter)
            {
                i++;
            }
            b = i++;
            LexAddBlock(&start, &end, STRING(format,
                                             a,
                                             b+1,
                                             line));
            i--;
        }
        else if (isGlyph(format[i]))
        {
            a = i; b = 0;
            // symbol
            while (i < size &&
                   isGlyph(format[i]))
            {
                i++;
                if (FindToken(&format[a], i - a, table))
                    b = i;
            }
            b = b ? b : i;
            LexAddBlock(&start, &end, TOKEN(format,
                                            a,
                                            b,
                                            line,
                                            table));
            i = b - 1;
        }
        else if (format[i] == '\n')
        {
#ifdef LEX_NEWLINES
            // end line
            LexAddBlock(&start, &end, NEWLINE(line));
#endif
        }
        else if (format[i] == ' ')
        {
            // whitespace
        }
        else
        {
            // ?
            PrintLexing(start);
            printf("Syntax error on line %i: ", line+1);
            printf("Illegal token %i.\n", format[i]);
            FreeLexing(start, format);
            *stripped = 0;
            return NULL;
        }
    }
    
#ifdef LEX_NEWLINES
    // add newline to the end
    LexAddBlock(&start, &end, NEWLINE(line));
#endif
    
    // add $ to the end
    LexAddBlock(&start, &end, EOFSYMBOL(line));

    free(lineNumbers);
    *stripped = format;
    return start;
}

// lexer memory management
void FreeLexing(L_TOKEN* lexing,
                char*    buffer)
{
    L_TOKEN* block;

    while (lexing)
    {
        block = lexing;
        lexing = lexing->next;
        if (block->string) {
            free(block->string);
        }
        free(block);
    }

    if (buffer) free(buffer);
}

// testing
void PrintLexing(L_TOKEN* lexing)
{
    int i;
    printf("NUMBER  STRING\n");
    printf("--------------\n");
    
    while (lexing)
    {
        printf("0x%.4X  ", lexing->token);
        for (i = 0; i < lexing->length; i++)
            printf("%c", lexing->string[i]);
        printf("\n");
        lexing = lexing->next;
    }
    
    printf("\n");
}

