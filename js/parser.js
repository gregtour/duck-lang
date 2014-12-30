var ACTION_ERROR = 0;
var ACTION_SHIFT = 1;
var ACTION_REDUCE = 2;
var ACTION_ACCEPT = 3;
var TOKEN_L_TOKEN = 1;
var TOKEN_SYNTAX_TREE = 2;

/* table indexing */
// ACTION
function ActionTable(table, state, token) 
{
    var action = {};
    action.type = ACTION_ERROR;
    action.action = 0;
    
    if (token & K_TOKEN) token = token ^ K_TOKEN;
    if (state >= 0 && state < table.numStates &&
        token >0 && token <= table.numTokens)
    {
        action = table.actionTable[state * table.numTokens + token - 1];
    }

    return action;
}

// int
function GotoTable(table, state, symbol) 
{
    var nextState = -1;
    if (symbol & K_SYMBOL)
        symbol = symbol ^ K_SYMBOL;
    
    if (state >= 0 && state < table.numStates
        && symbol > 0 && symbol <= table.numSymbols)
    {
        nextState = table.gotoTable[state * table.numSymbols + symbol - 1];
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
function PrintErrorInput(input, grammar)
{
    var i;
    if (input) {
        console.log("Syntax error on line " + (input.line+1) + ":");
        if (input.string) {
            console.log(input.string);
        } else {
            console.log(grammar.GetElement(input.token));
        }
    }
}

/* attempt parse */
function ParseSucceeds(lexing, parser, grammar)
{
    var cur = 0;
    gParseStack = [];
    StackPushState(0);
    var successful = 0;

    // loop forever
    for (;;) {
        var s = StackPeek();
        if (s.token || s.state == -1 || s.state >= parser.numStates)
        {
            successful = -1;
            break;
        }
        if (cur >= lexing.length) {
            successful = 0;
            break;
        }
        var action = ActionTable(parser, s.state, lexing[cur].token);
        if (action.type == ACTION_SHIFT)
        {
            StackPushToken(lexing[cur]);
            StackPushState(action.action);
            cur++;
        }
        else if (action.type == ACTION_REDUCE)
        {
            var node, r, rhs;
            if (action.action < 0 || action.action >= grammar.numRules)
            {
                successful = -1;
                break;
            }
            r = grammar.rules[action.action];

            for (rhs = 0; rhs < r.rhsLength; rhs++)
            {
                StackPop();
                StackPop();
            }
            s = StackPeek();
            if (s.token || s.state == -1 || s.state >= parser.numStates)
            {
                successful = -1;
                break;
            }
            StackPushTree({});
            StackPushState(GotoTable(parser, s.state, r.lhs));
        }
        else if (action.type == ACTION_ACCEPT)
        {
            successful = 1;
            break;
        }
        else
        {
            if (lexing[cur].token == gSymbolEOF)
                successful = 0;
            else
                successful = -1;
            break;
        }
    }
    while (gParseStack.length)
        StackPop();
    return successful;
}

/* parse source */
/* attempt parse */
function ParseSource(lexing, parser, grammar)
{
    var ast = {};
    var cur = 0;
    gParseStack = [];
    StackPushState(0);

    // loop forever
    for (;;) {
        var s = StackPeek();
        // get the state off of the top of the stack
        if (s.token || s.state == -1 || s.state >= parser.numStates)
        {
            console.log("Parse error: invalid state on top of the stack.");
            return 0;
        }
        if (cur >= lexing.length) {
            console.log("Parse error: unexpected end of input.");
            return 0;
        }
        // find the action table entry for the state and input
        var action = ActionTable(parser, s.state, lexing[cur].token);
        // perform the parse action
        if (action.type == ACTION_SHIFT)
        {
            // push a then s' on top of the stack;
            StackPushToken(lexing[cur]);
            StackPushState(action.action);
            // advance ip to the next input symbol
            cur++;
        }
        else if (action.type == ACTION_REDUCE)
        {
            var node, r, rhs;
            if (action.action < 0 || action.action >= grammar.numRules)
            {
                console.log("Parse error: invalid production for reduce action.");
                PrintErrorInput(lexing[cur], grammar);
                return 0;
            }
            r = grammar.rules[action.action];

            // pop 2*|B| symbols off of the stack
            node = {};
            node.token = r.lhs;
            node.production = action.action;
            node.string = "";
            node.len = 0;
            node.line = 0;
            node.children = [];
            node.numChildren = r.rhsLength;
            for (rhs = 0; rhs < r.rhsLength; rhs++)
                node.children.push(0);

            for (rhs = 0; rhs < r.rhsLength; rhs++)
            {
                var state = StackPop();
                var symbol = StackPop();
                if (symbol.token === undefined)
                {
                    console.log("Parse error: expected token.");
                    PrintErrorInput(lexing[cur], grammar);
                    return 0;
                }

                var child = r.rhsLength - rhs - 1;
                if (symbol.type == TOKEN_L_TOKEN) {
                    var token = symbol.token;
                    node.children[child] = {};
                    node.children[child].token = token.token;
                    node.children[child].production = 0;
                    node.children[child].string = token.string;
                    node.children[child].line = token.line;
                    node.children[child].children = [];
                    node.children[child].numChildren = 0;
                }
                else if (symbol.type == TOKEN_SYNTAX_TREE) {
                    node.children[child] = symbol.token;
                }
                else {
                    console.log("Parse error: expected token object.");
                    PrintErrorInput(lexing[cur], grammar);
                }
            }
            if (r.rhsLength) node.line = node.children[0].line;

            // let s' be the state now on top of the stack;
            s = StackPeek();
            if (s.token || s.state == -1 || s.state >= parser.numStates)
            {
                console.log("Parse error: expected state on top of the stack.");
                PrintErrorInput(lexing[cur], grammar);
                return 0;
            }

            // push A then goto[s', A] on top of the stack;
            if (r.lhs == gSymbolGoal) {
                ast = node;
            }
            StackPushTree(node);
            StackPushState(GotoTable(parser, s.state, r.lhs));
        }
        else if (action.type == ACTION_ACCEPT)
        {
            // accept
            break;
        }
        else
        {
            if (lexing[cur].token == gSymbolEOF) {
                successful = 0;
                console.log("Unexpected end of input.");
            } else {
                console.log("Parse error: illegal action type.");
                PrintErrorInput(lexing[cur], grammar);
            }
            return 0;
        }
    }
   
    // free the stack
    while (gParseStack.length)
        StackPop();
    
    // no errors
    return ast;
}

