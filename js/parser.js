/* grammar */
var K_TOKEN = (256*32);
var K_SYMBOL = (256*16);

/* grammar tokens & symbols */
function FindToken(text) 
{
    // case insensitive
    text = text.toLowerCase();

    // delimit text
    for (i = 0; i < GRAMMAR.tokens.length; i++) {
        if (GRAMMAR.tokens[i] == text) {
            return (i+1);
        }
    }

    return 0;
}

/* built in tokens */
var gSymbolEOF = FindToken("<$>");
var gSymbolEndLine = FindToken("<endl>");
var gSymbolInteger = FindToken("<integer>");
var gSymbolFloat = FindToken("<float>");
var gSymbolString = FindToken("<string>");
var gSymbolIdentifier = FindToken("<identifier>");


/* parser */
var ACTION_ERROR = 0;
var ACTION_SHIFT = 1;
var ACTION_REDUCE = 2;
var ACTION_ACCEPT = 3;
var TOKEN_L_TOKEN = 1;
var TOKEN_SYNTAX_TREE = 2;

/* table indexing */
function ActionTable(state, token) 
{
    var action = {};
    action.type = ACTION_ERROR;
    action.value = 0;

    if (token & K_TOKEN) token -= K_TOKEN;
    if (state >= 0 && state < PARSER.numStates &&
        token > 0 && token <= PARSER.numTokens)
    {
        var index = (state * PARSER.numTokens + token - 1);
        action = PARSER.ACTION_TABLE[index] || action;
    }

    return action;
}

function GotoTable(state, symbol) 
{
    var nextState = -1;
    if (symbol & K_SYMBOL) symbol = symbol ^ K_SYMBOL;
    if (state >= 0 && state < PARSER.numStates
        && symbol > 0 && symbol <= PARSER.numSymbols)
    {
        var index = state * PARSER.numSymbols + symbol - 1;
        nextState = PARSER.GOTO_TABLE[index];

        if (nextState === undefined || nextState === null) {
            nextState = -1;
        }
    }

    return nextState;
}


/* parse stack */
var gParseStack;
var gParseTop;

function StackPushState(state) 
{ 
    gParseStack.push({
        "token": undefined,
        "type": 0,
        "state": state
    });
}

function StackPushToken(token) 
{ 
    gParseStack.push({
        "token": token,
        "type": TOKEN_L_TOKEN,
        "state": -1
    });
}

function StackPushTree(tree) 
{ 
    gParseStack.push({
        "token": tree,
        "type": TOKEN_SYNTAX_TREE,
        "state": -1
    });
}

function StackPeek() 
{
    if (gParseStack.length) {
        return gParseStack[gParseStack.length - 1];
    }
    else {
        return {"token": undefined, "type": ACTION_ERROR, "state": -1};
    }
}

function StackPop() 
{
    if (gParseStack.length) 
    {
        var element = gParseStack.pop();
        return element;
    }
    else {
        return {"token": undefined, "type": ACTION_ERROR, "state": -1};
    }
}

/* error messages */
function PrintErrorInput(input)
{
    var i;
    if (input) {
        program.output("Syntax error on line " + (input.line+1) + ":");
        if (input.string) {
            program.output(input.string);
        } else {
            program.output(JSON.stringify(input));
            /*var token = input.token;
            if (token & K_TOKEN) token = token ^ K_TOKEN;
            program.output(GRAMMAR.tokens[token]);*/
        }
    }
}

/* parse source */
function ParseSource(lexing)
{
    var AST = {};
    var cur = 0;
    gParseStack = [];
    StackPushState(0);

    // loop forever
    for (;;) {
        var s = StackPeek();
        var lexeme = lexing[cur];

        //program.output("S:" + JSON.stringify(s) + ", L: " + JSON.stringify(lexeme));

        // get the state off of the top of the stack
        if (s.token || s.state == -1 || s.state >= PARSER.numStates)
        {
            program.output("Parse error: invalid state on top of the stack.");
            return 0;
        }
        if (cur >= lexing.length) {
            program.output("Parse error: unexpected end of input.");
            return 0;
        }
        // find the action table entry for the state and input
        var action = ActionTable(s.state, lexeme.token);
        // perform the parse action
        if (action.type == ACTION_SHIFT)
        {
            // push a then s' on top of the stack;
            StackPushToken(lexeme);
            StackPushState(action.value);
            // advance ip to the next input symbol
            cur++;
        }
        else if (action.type == ACTION_REDUCE)
        {
            var rhs, length, node, ruleNum, lhs;

            if (action.value < 0 || action.value >= GRAMMAR.numRules)
            {
                program.output("Parse error: invalid production for reduce action.");
                PrintErrorInput(lexeme);
                return 0;
            }

            ruleNum = action.value;
            length = GRAMMAR.ruleLen[ruleNum];
            lhs = GRAMMAR.ruleSymbol[ruleNum];

            // pop 2*|B| symbols off of the stack
            node = {};
            node.token = lhs;
            //node.token = "SYMBOL";
            node.rule = action.value;
            node.string = "";
            node.len = 0;
            node.line = 0;
            node.child = [];
            node.numChildren = length;

            for (rhs = 0; rhs < length; rhs++) {
                node.child.push(0);
            }

            for (rhs = 0; rhs < length; rhs++)
            {
                var state = StackPop();
                var symbol = StackPop();
                if (symbol.token === undefined)
                {
                    program.output("Parse error: expected token.");
                    PrintErrorInput(lexeme);
                    return 0;
                }

                var child = length - rhs - 1;
                if (symbol.type == TOKEN_L_TOKEN) {
                    var token = symbol.token;
                    node.child[child] = {};
                    node.child[child].token = token.token;
                    node.child[child].rule = 0;
                    node.child[child].string = token.string;
                    node.child[child].line = token.line;
                    node.child[child].child = [];
                    node.child[child].numChildren = 0;
                }
                else if (symbol.type == TOKEN_SYNTAX_TREE) {
                    node.child[child] = symbol.token;
                }
                else {
                    program.output("Parse error: expected token object.");
                    PrintErrorInput(lexeme);
                }
            }
            if (length > 0) {
                node.line = node.child[0].line;
            }

            // let s' be the state now on top of the stack;
            s = StackPeek();
            if (s.token || s.state == -1 || s.state >= PARSER.numStates)
            {
                program.output("Parse error: expected state on top of the stack.");
                PrintErrorInput(lexeme);
                return 0;
            }

            // push A then goto[s', A] on top of the stack;
            if (lhs == 1) {
                AST = node;
            }

            program.output("Reducing: " + ruleNum + " (" + lhs + ")");

            StackPushTree(node);
            StackPushState(GotoTable(s.state, lhs));
        }
        else if (action.type == ACTION_ACCEPT)
        {
            // accept
            break;
        }
        else
        {
            if (lexeme.token == gSymbolEOF) {
                successful = 0;
                program.output("Unexpected end of input.");
            } else {
                program.output("Parse error: illegal action type.");
                PrintErrorInput(lexeme);
            }
            return 0;
        }
    }
   
    // free the stack
    while (gParseStack.length) {
        StackPop();
    }
    
    // no errors
    return AST;
}

