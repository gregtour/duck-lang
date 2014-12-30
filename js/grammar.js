var K_TOKEN = (256*32);
var K_SYMBOL = (256*16);

var gSymbolRoot = 0;
var gSymbolGoal = K_SYMBOL + 1;
var gSymbolEpsilon = K_TOKEN + 1;
var gSymbolEOF = K_TOKEN + 2;
var gSymbolEndLine = K_TOKEN + 3;
var gSymbolInteger = K_TOKEN + 4;
var gSymbolFloat = K_TOKEN + 5;
var gSymbolString = K_TOKEN + 6;
var gSymbolIdentifier = K_TOKEN + 7;

var DUCK_GRAMMAR = "<program> ::= <stmt list>\n" +
    "<stmt list> ::= <stmt> <stmt list>\n" +
    "<stmt list> ::= <epsilon>\n" +
    "<stmt> ::= import <identifier> <endl>\n" +
    "<stmt> ::= call <reference> <endl>\n" +
    "<stmt> ::= <endl>\n" +
    "<stmt> ::= <expr> <endl>\n" +
    "<stmt> ::= <assignment> <endl>\n" +
    "<stmt> ::= <function def> <endl>\n" +
    "<stmt> ::= <if> <endl>\n" +
    "<stmt> ::= <for loop> <endl>\n" +
    "<stmt> ::= <while loop> <endl>\n" +
    "<stmt> ::= return <expr> <endl>\n" +
    "<stmt> ::= break <endl>\n" +
    "<stmt> ::= continue <endl>\n" +
    "<function def> ::= function <identifier> <parameters> <endl> <stmt list> end\n" +
    "<parameters> ::= <epsilon>\n" +
    "<parameters> ::= ( )\n" +
    "<parameters> ::= (<param decl>)\n" +
    "<param decl> ::= <identifier>\n" +
    "<param decl> ::= <param decl>, <identifier>\n" +
    "<if> ::= if <condition> then <endl> <stmt list> <else if>\n" +
    "<else if> ::= else <endl> <stmt list> end\n" +
    "<else if> ::= else <if>\n" +
    "<for loop> ::= for <identifier> = <arithmetic> to <arithmetic> do <endl> <stmt list> loop\n" +
    "<while loop> ::= while <condition> do <endl> <stmt list> loop\n" +
    "<assignment> ::= <l-value> = <assignment>\n" +
    "<assignment> ::= <l-value> = <condition>\n" +
    "<l-value> ::= <identifier>\n" +
    "<l-value> ::= ( <l-value> )\n" +
    "<l-value> ::= <reference> . <identifier>\n" +
    "<l-value> ::= <reference> [ <expr> ]\n" +
    "<expr> ::= <condition>\n" +
    "<condition> ::= <condition> and <logic>\n" +
    "<condition> ::= <condition> or <logic>\n" +
    "<condition> ::= <condition> nor <logic>\n" +
    "<condition> ::= <condition> xor <logic>\n" +
    "<condition> ::= <logic>\n" +
    "<logic> ::= not <comparison>\n" +
    "<logic> ::= <comparison>\n" +
    "<comparison> ::= <comparison> == <arithmetic>\n" +
    "<comparison> ::= <comparison> != <arithmetic>\n" +
    "<comparison> ::= <comparison> \\< <arithmetic>\n" +
    "<comparison> ::= <comparison> > <arithmetic>\n" +
    "<comparison> ::= <comparison> \\<= <arithmetic>\n" +
    "<comparison> ::= <comparison> >= <arithmetic>\n" +
    "<comparison> ::= <arithmetic>\n" +
    "<arithmetic> ::= <arithmetic> + <term>\n" +
    "<arithmetic> ::= <arithmetic> - <term>\n" +
    "<arithmetic> ::= <arithmetic> & <term>\n" +
    "<arithmetic> ::= <arithmetic> | <term>\n" +
    "<arithmetic> ::= <term>\n" +
    "<term> ::= <term> * <factor>\n" +
    "<term> ::= <term> / <factor>\n" +
    "<term> ::= <factor>\n" +
    "<factor> ::= -<factor>\n" +
    "<factor> ::= !<factor>\n" +
    "<factor> ::= <final>\n" +
    "<final> ::= ( <expr> )\n" +
    "<final> ::= <boolean>\n" +
    "<final> ::= <integer>\n" +
    "<final> ::= <float>\n" +
    "<final> ::= <string>\n" +
    "<final> ::= <object>\n" +
    "<final> ::= <reference>\n" +
    "<reference> ::= <l-value>\n" +
    "<reference> ::= <reference> ( )\n" +
    "<reference> ::= <reference> ( <arguments> )\n" +
    "<arguments> ::= <arguments>, <expr>\n" +
    "<arguments> ::= <expr>\n" +
    "<object> ::= [ ]\n" +
    "<object> ::= [ <array init> ]\n" +
    "<object> ::= [ <dictionary init> ]\n" +
    "<array init> ::= <array init>, <expr>\n" +
    "<array init> ::= <expr>\n" +
    "<dictionary init> ::= <dictionary init>, <identifier> : <expr>\n" +
    "<dictionary init> ::= <identifier> : <expr>\n" +
    "<else if> ::= end\n" +
    "<boolean> ::= true\n" +
    "<boolean> ::= false\n";

function AddToken(string, table)
{
    var index = 1;
    var i;
    for (i = 0; i < table.numTokens; i++, index++)
    {
        if (table.tokens[i] == string) {
            return (index | K_TOKEN);
        }
    }

    table.tokens.push(string);
    table.numTokens = table.tokens.length;
    return (index | K_TOKEN);
}

function FindToken(string, table)
{
    var index = 1;
    var i;
    for (i = 0; i < table.numTokens; i++, index++)
    {
        if (table.tokens[i] == string) {
            return (index | K_TOKEN);
        }
    }
    
    return 0;
}

function AddSymbol(string, table)
{
    var index = 1;
    var i;
    for (i = 0; i < table.numSymbols; i++, index++)
    {
        if (table.symbols[i] == string) {
            return (index | K_SYMBOL);
        }
    }

    table.symbols.push(string);
    table.numSymbols = table.symbols.length;
    return (index | K_SYMBOL);
}

function GetElement(token, table)
{
    if (token & K_TOKEN) {
        token = token ^ K_TOKEN;
        if (token < table.tokens.length && token >= 0)
            return table.tokens[token];
        else
            return "null";
    } else if (token & K_SYMBOL) {
        token = token ^ K_SYMBOL;
        if (token < table.symbols.length && token >= 0)
            return table.symbols[token];
        else
            return "null";
    }
    return "null";
}

function LoadGrammar(input)
{
    var table = {};
    table.numSymbols = 0;
    table.symbols = [];
    table.numTokens = 0;
    table.tokens = [];
    table.numRules = 0;
    table.rules = [];

    // built-in symbols
    gSymbolRoot = 0;
    gSymbolGoal = K_SYMBOL + table.numSymbols + 1;
    gSymbolEpsilon = AddToken("<epsilon>", table);
    gSymbolEOF = AddToken("<$>", table);
    gSymbolEndLine = AddToken("<endl>", table);
    gSymbolInteger = AddToken("<integer>", table);
    gSymbolFloat = AddToken("<float>", table);
    gSymbolString = AddToken("<string>", table);
    gSymbolIdentifier = AddToken("<identifier>", table);

    var buffer = input;

    // count rules
    var col;
    var size;
    var i, r, start, end;
    var rhs, symbol, token;
    var read, line;
    table.numRules = 0; col = 0;
    size = input.length;
    for (i = 0; i < size; i++) {
        if (col == 0 &&
            (buffer.charAt(i) == ';' || buffer.charAt(i) == '\r' ||
                buffer.charAt(i) == '\n'))
        {
            while (i < size && buffer.charAt(i) != '\n')
                i++;
            continue;
        }
        col++;
        if (buffer.charAt(i) == '\r') { } //buffer[i] = 0;//
        else if (buffer.charAt(i) == '\n') { table.numRules++; col = 0; }
    }
    table.numRules++;

    // parse rules
    start = 0; end = 0; line = 0;
    // S' -> S
    table.rules.push([]);
    table.rules[0].lhs = gSymbolRoot;
    table.rules[0].rhs = [];
    table.rules[0].rhs.push(gSymbolGoal);
    table.rules[0].rhsLength = 1;
    for (r = 1; r < table.numRules; r++) {
        table.rules.push([]);
        // skip blank / commented lines
        while (start < size &&
                (buffer.charAt(start) == ';' || buffer.charAt(start) == '\n'
                    || buffer.charAt(start) == '\r'))
        {
            while (start < symbol && buffer.charAt(start) != '\n')
                start++;
            start++;
            line++;
        }
        // left hand symbol
        while (start < size && buffer.charAt(start) != '<')
            start++;
        end = start;
        while (start < size && buffer.charAt(end) != '>')
            end++;
        symbol = AddSymbol(buffer.substr(start, end - start + 1), table);
        if (symbol == 0) {
            console.log("Could not identify left hand symbol in rule " + (r+1) + " on line " + line + ".");
            return 1;
        }
        table.rules[r].lhs = symbol;
        start = end + 1;

        // ::= operator
        while (start < size - 2) {
            if (buffer.charAt(start) == ':' &&
                buffer.charAt(start+1) == ':' &&
                buffer.charAt(start+2) == '=')
            {
                break;
            }
            start++;
        }
        start = start + 3;

        // right hand side
        table.rules[r].rhs = [];
        rhs = 0;
        while (start < size &&
                buffer.charAt(start) != '\n' &&
                buffer.charAt(start) != '\r'
//               && rhs < RULE_RHS_SIZE)
                )
        {
            if (buffer.charAt(start) == '<')
            {
                // symbol
                end = start;
                while (buffer.charAt(end) != '>' &&
                        end < size)
                {
                    end++;
                }

                symbol = FindToken(buffer.substr(start, end - start + 1), table);
                if (symbol == 0)
                    symbol = AddSymbol(buffer.substr(start, end - start + 1), table);
                if (symbol == 0)
                {
                    console.log("Could not identify right hand symbol in rule " + (r+1) + " on line " + line + ".");
                    return 1;
                }
                table.rules[r].rhs.push(symbol);
                rhs++;
                start = end + 1;
            }
            else if (buffer.charAt(start) != ' ')
            {
                end = start;
                while (buffer.charAt(end) != ' ' &&
                        (buffer.charAt(end) != '<' ||
                         buffer.charAt(end-1) == '\\') &&
                        buffer.charAt(end) != '\n' &&
                        buffer.charAt(end) != '\r' &&
                        end < size)
                {
                    end++;
                }

                token = AddToken(buffer.substr(start, end - start), table);
                if (token == 0)
                {
                    console.log("Could not identify right token in rule " + (r+1) + " on line " + line + ".");
                    return 1;
                }
                table.rules[r].rhs.push(token);
                rhs++;
                start = end;
            }
            else
            {
                // whitespace
                start++;
            }
        }

        // table.rules[r].rhs.push(0);
        table.rules[r].rhsLength = rhs;
        if (rhs == 0) {
            console.log("Rule " + (r+1) + " on line " + line + " has no right hand side.");
            return 1;
        }
    }

    if (gSymbolGoal == 0) {
        console.log("Grammar is missing a goal symbol.");
        return 1;
    }

    /* remove epsilons */
    var j;
    for (j = 0; j < table.numRules; j++)
    {
        if (table.rules[j].rhsLength && table.rules[j].rhs[0] == gSymbolEpsilon)
            table.rules[j].rhsLength = 0;
    }
        
    console.log("Parsed " + r + " of " + table.numRules + " rules.");
    table.FindToken = function (t) { return FindToken(t, table); };
    table.GetElement = function (t) { return GetElement(t, table); };
    return table;
}

