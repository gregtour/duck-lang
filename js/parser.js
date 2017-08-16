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
        "state": state
    });
}

function StackPushToken(token) 
{ 
    gParseStack.push(token);
}

function StackPushTree(tree) 
{ 
    gParseStack.push(tree);
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
        if (!s.hasOwnProperty('state') || s.state == -1 || s.state >= PARSER.numStates)
        {
            program.output("Parse error: invalid state on top of the stack.");
            return 1;
        }
        if (cur >= lexing.length) {
            program.output("Parse error: unexpected end of input.");
            return 2;
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
            var rhs, length, node, subtree, ruleNum, lhs, trivial, recursive, condense;

            if (action.value < 0 || action.value >= GRAMMAR.numRules)
            {
                program.output("Parse error: invalid production for reduce action.");
                PrintErrorInput(lexeme);
                return 3;
            }

            ruleNum = action.value;
            length = GRAMMAR.ruleLen[ruleNum];
            lhs = GRAMMAR.ruleSymbol[ruleNum];
            trivial = (GRAMMAR.trivialRules.indexOf(ruleNum) >= 0);

            node = {
                "rule": ruleNum,
                "symbol": lhs,
                "child": []
//              "line": lineNum
            }

            // trivial rules are popped then pushed back
            if (trivial) {
                var state = StackPop();
                subtree = StackPop();
                node.child = subtree.child;
            }
            else {
                // pop 2*|B| symbols off of the stack
                for (rhs = 0; rhs < length; rhs++) {
                    node.child.push(null);
                }
                for (rhs = 0; rhs < length; rhs++)
                {
                    var state = StackPop();
                    var symbolOrToken = StackPop();

                    // check the reduced child element
                    if (symbolOrToken.hasOwnProperty('symbol')) 
                    {
                        // symbol logic
                        var symbol = symbolOrToken;
                    } 
                    else if (symbolOrToken.hasOwnProperty('token')) 
                    {
                        // token logic
                        var token = symbolOrToken;
                    }
                    else
                    {
                        // error
                        program.output("Parse error: expected token.");
                        PrintErrorInput(lexeme);
                        return 4;
                    }

                    var num = length - rhs - 1;
                    node.child[num] = symbolOrToken;
                }

                // track parser line error
            }


            // let s' be the state now on top of the stack;
            s = StackPeek();
            //if (s.token || s.state == -1 || s.state >= PARSER.numStates)
            if (!s.hasOwnProperty('state') || s.state == -1 || s.state >= PARSER.numStates)
            {
                program.output("Parse error: expected state on top of the stack.");
                PrintErrorInput(lexeme);
                return 6;
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
                return 8;
            } else {
                program.output("Parse error: illegal action type.");
                PrintErrorInput(lexeme);
                return 9;
            }
        }
    }
   
    // free the stack
    while (gParseStack.length) {
        StackPop();
    }
    
    // no errors
    return AST;
}

