/* parser.c */

#include "lr_parser.h"


// table indices
ACTION ActionTable(LR_TABLE table, int state, int token)
{
    ACTION action;
    action.type = ACTION_ERROR;

    if (token & K_TOKEN)
        token = token ^ K_TOKEN;

    if (state >= 0 && state < table.numStates
        && token > 0 && token <= table.numTokens)
    {
        action = table.actionTable[state * table.numTokens + token - 1];
    }

    return action;
}

int GotoTable(LR_TABLE table, int state, int symbol)
{
    int nextState = -1;

    if (symbol & K_SYMBOL)
        symbol = symbol ^ K_SYMBOL;

    if (state >= 0 && state < table.numStates
        && symbol > 0 && symbol <= table.numSymbols)
    {
        nextState = table.gotoTable[state * table.numSymbols + symbol - 1];
    }

    return nextState;
}

/* static data */

PARSE_STACK* gParseStack = NULL;
PARSE_STACK* gParseTop = NULL;

/* stack operations */

void StackPushState(int state)
{
    if (gParseTop) {
        gParseTop->next = (PARSE_STACK*)malloc(sizeof(PARSE_STACK));
        gParseTop->next->prev = gParseTop;
        gParseTop = gParseTop->next;
    } else {
        gParseStack = gParseTop = (PARSE_STACK*)malloc(sizeof(PARSE_STACK));
        gParseTop->prev = NULL;
    }
    gParseTop->next = NULL;
    gParseTop->token = NULL;
    gParseTop->type = 0;
    gParseTop->state = state;
}

void StackPushToken(L_TOKEN* token)
{
    if (gParseTop) {
        gParseTop->next = (PARSE_STACK*)malloc(sizeof(PARSE_STACK));
        gParseTop->next->prev = gParseTop;
        gParseTop = gParseTop->next;
    } else {
        gParseStack = gParseTop = (PARSE_STACK*)malloc(sizeof(PARSE_STACK));
        gParseTop->prev = NULL;
    }
    gParseTop->next = NULL;
    gParseTop->token = token;
    gParseTop->type = TOKEN_L_TOKEN;
    gParseTop->state = -1;
}

void StackPushTree(SYNTAX_TREE* tree)
{
    if (gParseTop) {
        gParseTop->next = (PARSE_STACK*)malloc(sizeof(PARSE_STACK));
        gParseTop->next->prev = gParseTop;
        gParseTop = gParseTop->next;
    } else {
        gParseStack = gParseTop = (PARSE_STACK*)malloc(sizeof(PARSE_STACK));
        gParseTop->prev = NULL;
    }
    gParseTop->next = NULL;
    gParseTop->token = tree;
    gParseTop->type = TOKEN_SYNTAX_TREE;
    gParseTop->state = -1;
}

PARSE_STACK StackPeek()
{
    PARSE_STACK r;
    r.token = NULL;
    r.type = 0;
    r.state = -1;
    
    if (gParseTop) {
        r = *gParseTop;
        r.next = NULL;
        r.prev = NULL;
    }
    
    return r;
}

PARSE_STACK StackPop()
{
    PARSE_STACK r;
    r.token = NULL;
    r.type = 0;
    r.state = -1;
    
    if (gParseTop) {
        r = *gParseTop;
        r.next = NULL;
        r.prev = NULL;
        if (gParseTop->prev) {
            gParseTop = gParseTop->prev;
            free(gParseTop->next);
            gParseTop->next = NULL;
        } else {
            free(gParseTop);
            gParseTop = NULL;
            gParseStack = NULL;
        }
    }
    
    return r;
}

void PrintErrorInput(L_TOKEN* input, GRAMMAR_TABLE g)
{
    int i;
    if (input)
    {
        printf("Syntax error on line %i: ", (input->line+1));
        if (input->string)
        {
            for (i = 0; i < input->length; i++)
            {
                printf("%c", input->string[i]);
            }
        }
        else
        {
            printf("%s", GetElement(input->token, g));
        }
        printf("\n");
    }
}

/* check if a source is parsable */
int ParseSucceeds(L_TOKEN* input, 
                  LR_TABLE parser, 
                  GRAMMAR_TABLE grammar)
{
    // set ip and init stack
    L_TOKEN* ip = input;
    StackPushState(0);
    
    // the program's syntax tree
    SYNTAX_TREE* ast = NULL;

    int successful = 0;

    // loop forever
    for (;;)
    {
        // get the state off the top of the stack
        PARSE_STACK s = StackPeek();
        if (s.token || s.state == -1
                || s.state >= parser.numStates)
        {
            // error
            successful = -1;
            break;
        }

        if (ip == NULL) {
            successful = 0;
            break;
        }
        
        // find the action table entry for the state and input
        ACTION action = ActionTable(parser, s.state, ip->token);

        // perform the parse action
        if (action.type == ACTION_SHIFT)
        {
            // push a then s' on top of the stack;
            StackPushToken(ip);
            StackPushState(action.value);
            // advance ip to the next input symbol
            ip = ip->next;
        }
        else if (action.type == ACTION_REDUCE)
        {
            RULE r;
            int rhs;
            
            // output the production A -> B
            if (action.value < 0 || action.value >= grammar.numRules) 
            {
                // error, free
                successful = -1;
                break;
            }
            r = grammar.rules[action.value];

            // pop 2*|B| symbols off the stack;
            for (rhs = 0; rhs < r.rhsLength; rhs++)
            {
                StackPop();
                StackPop();
            }
                
            // let s' be the state now on top of the stack;
            s = StackPeek();
            if (s.token || s.state == -1 || s.state >= parser.numStates)
            {
                successful = -1;
                break;
            }
            
            // push A then goto[s', A] on top of the stack;
            StackPushTree(NULL);
            StackPushState(GotoTable(parser, s.state, r.lhs));
        }
        else if (action.type == ACTION_ACCEPT)
        {
            // accept
            successful = 1;
            break;
        }
        else
        {
            // error
            if (ip->token == gSymbolEOF)
                successful = 0;
            else
                successful = -1;
            break;
        }
    }
    
    // free the stack
    while (gParseStack)
        StackPop();

    // no errors
    return successful;
}

/* parse a lexed source file */
/*
set ip to point to the first symbol of w$;
repeat forever begin
    let s be the state on top of the stack and
        a the symbol pointed to by ip;
    if action[s, a] = shift s' then begin
        push a then s' on top of the stack;
        advance ip to the next input symbol
    end
    else if action[s, a] = reduce A -> B then begin
        pop 2*|B| symbols off the stack;
        let s' be the state now on top of the stack;
        push A then goto[s', A] on top of the stack;
        output the production A -> B
    end
    else if action[s, a] = accept then
        return
    else error()
end
*/
SYNTAX_TREE* ParseSource(L_TOKEN*      input,
                         LR_TABLE      parser,
                         GRAMMAR_TABLE grammar)
{
    // set ip and init stack
    L_TOKEN* ip = input;
    StackPushState(0);
    // printf("Parsing source...\n");
    
    // the program's syntax tree
    SYNTAX_TREE* ast = NULL;

    // loop forever
    for (;;)
    {
        // get the state off the top of the stack
        PARSE_STACK s = StackPeek();
        if (s.token || s.state == -1
                || s.state >= parser.numStates
                || ip == NULL)
        {
            if (ip)
                printf("Parse error: invalid state on top of the stack.\n");
            else
                printf("Parse error: unexpected end of input.\n");
            return 0;
        }
        
        // find the action table entry for the state and input
        ACTION action = ActionTable(parser, s.state, ip->token);

        // perform the parse action
        if (action.type == ACTION_SHIFT)
        {
            // push a then s' on top of the stack;
            StackPushToken(ip);
            StackPushState(action.value);
            // advance ip to the next input symbol
            ip = ip->next;
        }
        else if (action.type == ACTION_REDUCE)
        {
            SYNTAX_TREE* node;
            RULE r;
            int rhs;
            
            // output the production A -> B
            if (action.value < 0 || action.value >= grammar.numRules) {
                printf("Parse error: invalid production for reduce action.\n");
                PrintErrorInput(ip, grammar);
                return 0;
            }
            r = grammar.rules[action.value];
            //printf("%s\n", GetElement(r.lhs, grammar));

            // pop 2*|B| symbols off the stack;
            node = (SYNTAX_TREE*)malloc(sizeof(SYNTAX_TREE));
            node->token = r.lhs;
            node->production = action.value;
            node->string = NULL;
            node->length = 0;
            node->line = 0;
            node->children = (SYNTAX_TREE**)malloc(r.rhsLength * sizeof(SYNTAX_TREE*));
            node->numChildren = r.rhsLength;
            for (rhs = 0; rhs < r.rhsLength; rhs++)
            {
                /*PARSE_STACK state = */ StackPop();
                PARSE_STACK symbol = StackPop();
                if (symbol.token == NULL)
                {
                    printf("Parse error: expected token.\n");
                    PrintErrorInput(ip, grammar);
                    return 0;
                }
                
                int child = r.rhsLength - rhs - 1;
                if (symbol.type == TOKEN_L_TOKEN)
                {
                    L_TOKEN* token = (L_TOKEN*)symbol.token;
                    node->children[child] = (SYNTAX_TREE*)malloc(sizeof(SYNTAX_TREE));
                    node->children[child]->token = token->token;
                    node->children[child]->production = 0;
                    node->children[child]->string = token->string;
                    node->children[child]->length = token->length;
                    node->children[child]->line = token->line;
                    node->children[child]->children = NULL;
                    node->children[child]->numChildren = 0;
                }
                else if (symbol.type == TOKEN_SYNTAX_TREE)
                {
                    node->children[child] = (SYNTAX_TREE*)symbol.token;
                }
                else
                {
                    printf("Parse error: expected token object.\n");
                    PrintErrorInput(ip, grammar);
                }
            }
            if (r.rhsLength) node->line = node->children[0]->line;
                
            // let s' be the state now on top of the stack;
            s = StackPeek();
            if (s.token || s.state == -1 || s.state >= parser.numStates)
            {
                printf("Parse error: expected state on top of stack.\n");
                PrintErrorInput(ip, grammar);
                return 0;
            }
            
            // push A then goto[s', A] on top of the stack;
            if (r.lhs == gSymbolGoal)
            {
                ast = node;
            }
            StackPushTree(node);
            StackPushState(GotoTable(parser, s.state, r.lhs));
        }
        else if (action.type == ACTION_ACCEPT)
        {
            // accept
            // printf("Parse accepted!\n");
            break;
        }
        else
        {
            // error
            printf("Parse error: illegal action type.\n");
            PrintErrorInput(ip, grammar);
            return 0;
        }
    }
    
    // free the stack
    while (gParseStack)
        StackPop();

    // no errors
    return ast;
}

// parse tree memory management
void FreeParseTree(SYNTAX_TREE* ast)
{
    if (ast && ast->children)
    {
        unsigned int i;

        for (i = 0; i < ast->numChildren; i++)
        {
            FreeParseTree(ast->children[i]);
        }
        
        free(ast->children);
        free(ast);
    }
    else if (ast)
    {
        free(ast);
    }
}

void PrintParseTreeNode(SYNTAX_TREE* ast, GRAMMAR_TABLE g)
{
    if (!ast) return;
    if (ast->string && ast->token != gSymbolEndLine)
    {
        int i;
        for (i = 0; i < ast->length; i++)
            printf("%c", ast->string[i]);
    }
    else
    {
        printf("%s", GetElement(ast->token, g));
    }
}

void PrintParseTreeRecurse(SYNTAX_TREE*  ast,
                           unsigned int  indent,
                           GRAMMAR_TABLE g)
{
    if (ast->children)
    {
        unsigned int i;

        for (i = 0; i < indent*2; i++)
        {
            printf(" ");
        }
            
        PrintParseTreeNode(ast, g);
        
        printf(" ::= ");
        
        for (i = 0; i < ast->numChildren; i++)
        {
            PrintParseTreeNode(ast->children[i], g);
            printf(" ");
        }
        
        printf("\n");
        
        for (i = 0; i < ast->numChildren; i++)
        {
            PrintParseTreeRecurse(ast->children[i], indent+1, g);
        }
    }
}

void PrintParseTree(SYNTAX_TREE*  ast,
                    GRAMMAR_TABLE grammar)
{
    printf("\n\nAbstract Syntax Tree\n");
    printf("====================\n\n");
    PrintParseTreeRecurse(ast, 0, grammar);
}


void PrintParseTreeFormat(SYNTAX_TREE*  ast,
                          GRAMMAR_TABLE grammar)
{
    if (ast->numChildren > 0) {
        unsigned int i;
        for (i = 0; i < ast->numChildren; i++)
            PrintParseTreeFormat(ast->children[i], grammar);
    } else {
        if (ast->string && ast->token != gSymbolEndLine)
        {
            int i;
            for (i = 0; i < ast->length; i++)
                printf("%c", ast->string[i]);
        }
        else
        {
            printf("%s", GetElement(ast->token, grammar));
        }
    }
}

