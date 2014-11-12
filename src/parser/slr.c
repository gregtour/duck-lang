/* lr_table.c */
/*
    builds LR(0) canonical collection of item sets
    for building an LR(0) parse table
*/

#include "lr_parser.h"
#ifdef _SLR

// static data
int* FIRST_SETS = NULL;
int* FOLLOW_SETS = NULL;
int* NULLABLE_NONTERMINALS = NULL;

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

// FIRST table indices
int SetFirstTable(int symbol, int token, int value, GRAMMAR_TABLE* G)
{
    if (symbol & K_SYMBOL) symbol ^= K_SYMBOL;
    if (token & K_TOKEN) token ^= K_TOKEN;
    if (token & K_SYMBOL) return 0;
    
    if (token > 0 && symbol > 0
        && token <= G->numTokens
        && symbol <= G->numSymbols
        && token != (gSymbolEpsilon ^ K_TOKEN))
    {
        symbol--;
        token--;
        int index = symbol*G->numTokens + token;
        if (FIRST_SETS[index] != value)
        {
            FIRST_SETS[index] = value;
            return 1;
        }
    }
    return 0;
}

int GetFirstTable(int symbol, int token, GRAMMAR_TABLE* G)
{
    if (symbol & K_TOKEN) return (symbol == token) ? 1 : 0;
    if (symbol & K_SYMBOL) symbol ^= K_SYMBOL;
    if (token & K_TOKEN) token ^= K_TOKEN;
    if (token & K_SYMBOL) return -1;

    if (token > 0 && symbol > 0
        && token <= G->numTokens
        && symbol <= G->numSymbols)
    {
        symbol--;
        token--;
        return FIRST_SETS[symbol*G->numTokens + token];
    }
    return -1;
}

// FOLLOW table indices
int SetFollowTable(int symbol, int token, int value, GRAMMAR_TABLE* G)
{
    if (symbol & K_SYMBOL) symbol ^= K_SYMBOL;
    if (token & K_TOKEN) token ^= K_TOKEN;
    if (token & K_SYMBOL) return 0;

    if (token > 0 && symbol > 0
        && token <= G->numTokens
        && symbol <= G->numSymbols
        && token != (gSymbolEpsilon ^ K_TOKEN))
    {
        symbol--;
        token--;
        int index = symbol*G->numTokens + token;
        if (FOLLOW_SETS[index] != value)
        {
            FOLLOW_SETS[index] = value;
            return 1;
        }
    }
    return 0;
}

int GetFollowTable(int symbol, int token, GRAMMAR_TABLE* G)
{
    if (symbol & K_SYMBOL) symbol ^= K_SYMBOL;
    if (token & K_TOKEN) token ^= K_TOKEN;
    if (token & K_SYMBOL) return -1;

    if (token > 0 && symbol > 0
        && token <= G->numTokens
        && symbol <= G->numSymbols)
    {
        symbol--;
        token--;
        return FOLLOW_SETS[symbol*G->numTokens + token];
    }
    return -1;
}

int IsNullable(int symbol)
{
    if (symbol & K_TOKEN)
        return 0;
        
    if (symbol & K_SYMBOL)
    {
        symbol = (symbol ^ K_SYMBOL) - 1;
    }
    return NULLABLE_NONTERMINALS[symbol];
}

// Find the nullable nonterminal symbols
void FindNullableNonterminals(GRAMMAR_TABLE* G)
{
    NULLABLE_NONTERMINALS = malloc(G->numSymbols * sizeof(int));
    RULE rule;
    int  changing;
    int  i, p, r;
    
    // clear the set
    for (i = 0; i < G->numSymbols; i++)
    {
        NULLABLE_NONTERMINALS[i] = 0;
    }
    
    do {
        changing = 0;
        // go through all productions
        for (p = 1; p < G->numRules; p++)
        {
            RULE rule = G->rules[p];
            int lhs = (rule.lhs ^ K_SYMBOL) - 1;
            if (!NULLABLE_NONTERMINALS[lhs])
            {
                if (rule.rhs[0] == gSymbolEpsilon)
                {
                    // add productions that go to epsilon
                    NULLABLE_NONTERMINALS[lhs] = 1;
                    changing = 1;
                } else {
                    int allNullable = 1;
                    
                    // add productions that are made of nullable nonterminals
                    for (r = 0; r < rule.rhsLength; r++)
                    {
                        if (rule.rhs[r] & K_TOKEN ||
                           (rule.rhs[r] & K_SYMBOL &&
                           !NULLABLE_NONTERMINALS[(rule.rhs[r] ^ K_SYMBOL)-1]))
                        {
                            allNullable = 0;
                            break;
                        }
                    }
                        
                    if (allNullable)
                    {
                        NULLABLE_NONTERMINALS[lhs] = 1;
                        changing = 1;
                    }
                }
			}
        }
    } while (changing);
}

// construct FIRST sets
void BuildFirstSets(GRAMMAR_TABLE* G)
{
    int finished;
    int symbol, i, p, r;
    RULE rule;

    FIRST_SETS = malloc(sizeof(int) * G->numTokens * G->numSymbols);
    
    // clear first map
    for (i = 0; i < G->numTokens * G->numSymbols; i++)
        FIRST_SETS[i] = 0;

    // map nullable nonterminals to epsilon
    for (symbol = 0; symbol < G->numSymbols; symbol++)
    {
        if (IsNullable(symbol))
        {
            SetFirstTable(symbol, gSymbolEpsilon, 1, G);
        }
    }
    
    // join first sets from production rules while they continue to change
    int changing;
    do {
        changing = 0;
        for (p = 0; p < G->numRules; p++)
        {
            RULE rule = G->rules[p];
            int left = rule.lhs;
            for (r = 0; r < rule.rhsLength; r++)
            {
                // terminal
                if (rule.rhs[r] & K_TOKEN)
                {
                    if (SetFirstTable(left, rule.rhs[r], 1, G))
                        changing = 1;
                    break;
                }

                // add symbols from table
                for (i = 1; i <= G->numSymbols; i++)
                {
                    if (GetFirstTable(rule.rhs[r], i | K_SYMBOL, G) == 1 &&
                        SetFirstTable(left, i | K_SYMBOL, 1, G))
                    {
                        changing = 1;
                    }
                }
                
                // add tokens from table
                for (i = 1; i <= G->numTokens; i++)
                {
                    if (GetFirstTable(rule.rhs[r], i | K_TOKEN, G) == 1 &&
                        SetFirstTable(left, i | K_TOKEN, 1, G))
                    {
                        changing = 1;
                    }
                }
                
                // continue only if it's nullable
                if (!IsNullable(rule.rhs[r]))
                    break;
            }
        }
    } while (changing);
}

// construct FOLLOW sets
void BuildFollowSets(GRAMMAR_TABLE* G)
{
    RULE rule;
    int  finished;
    int  i, j, p, r;

    FOLLOW_SETS = malloc(sizeof(int) * G->numTokens * G->numSymbols);

    // clear follow map
    for (i = 0; i < G->numTokens * G->numSymbols; i++)
        FOLLOW_SETS[i] = 0;

    // add goal
    SetFollowTable(gSymbolGoal, gSymbolEOF, 1, G);

    // go through productions and construct follow sets for the rhs
    int changing;
    do {
        changing = 0;
        for (p = 0; p < G->numRules; p++)
        {
            rule = G->rules[p];
            int left = rule.lhs;
            // compute follow for all of the rhs terms
            for (r = 0; r < rule.rhsLength; r++)
            {
                int symbol = rule.rhs[r];
                if (symbol & K_SYMBOL)
                {
                    for (j = r+1; j < rule.rhsLength; j++)
                    {
                        // add following tokens to the follow set
                        if (rule.rhs[j] & K_TOKEN) {
                            if (SetFollowTable(symbol, rule.rhs[j], 1, G))
                                changing = 1;
                            break;
                        }
                        
                        // for following symbols, add the first set
                        for (i = 1; i <= G->numTokens; i++)
                        {
                            if (GetFirstTable(rule.rhs[j], i | K_TOKEN, G) == 1
                                && SetFollowTable(symbol, i | K_TOKEN, 1, G))
                            {
                                changing = 1;
                            }
                        }
                        
                        // continue while nullable
                        if (!IsNullable(rule.rhs[j]))
                            break;
                    }
                    
                    // add all from the follow set of the lhs
                    if (j == rule.rhsLength)
                    {
                        for (i = 1; i <= G->numTokens; i++)
                        {
                            if (GetFollowTable(left, i | K_TOKEN, G) == 1
                                && SetFollowTable(symbol, i | K_TOKEN, 1, G))
                            {
                                changing = 1;
                            }
                        }
                    }
                }
            }
        }
    } while (changing);
}

void RemoveEpsilons(GRAMMAR_TABLE* G)
{
    int r;
    for (r = 0; r < G->numRules; r++)
    {
        if (G->rules[r].rhsLength &&
            G->rules[r].rhs[0] == gSymbolEpsilon)
        {
            G->rules[r].rhsLength = 0;
        }
    }
}

// LR_ITEM functions
int CompareItems(LR_ITEM one, LR_ITEM two)
{
    if (one.production < two.production ||
        (one.production == two.production && one.dot < two.dot))
    {
        return -1;
    }
    else if (one.production == two.production &&
             one.dot == two.dot)
    {
        return 0;
    }
    return 1;
}

void SWAP_ITEMS(LR_ITEM* one, LR_ITEM* two)
{
    LR_ITEM three = *one;
    *one = *two;
    *two = three;
}

// sort LR_ITEM_SET list for easy comparison
LR_ITEM_SET* Sort(LR_ITEM_SET* I)
{
    LR_ITEM_SET* itr;
    LR_ITEM* heap;
    int i, size;
    
    if (I == NULL) return I;
    
    // count elements [O(N)]
    size = 0;
    for (itr = I; itr; itr = itr->next)
    {
        size++;
    }
    
    // allocate heap [O(1)]
    heap = malloc(sizeof(LR_ITEM) * size);
    
    // add items to the heap [O(N log N)]
    for (itr = I, i = 0; itr; itr = itr->next, i++)
    {
        heap[i] = itr->item;
        int a = i; int b = (i-1)/2;
        while (a > 0 && CompareItems(heap[a], heap[b]) < 0)
        {
            SWAP_ITEMS(&heap[a], &heap[b]);
            a = b;
            b = (b-1)/2;
        }
    }
    
    // pop items off the heap [O(N log N)]
    for (itr = I; itr; itr = itr->next)
    {
        itr->item = heap[0];
        size--;
        heap[0] = heap[size];
        
        int j = 0;
        int a = 1; int b = 2;
        while (j < size &&
               ((a < size && CompareItems(heap[j], heap[a]) > 0)
             || (b < size && CompareItems(heap[j], heap[b]) > 0)))
        {
            if (b < size && CompareItems(heap[a], heap[b]) > 0)
            {
                SWAP_ITEMS(&heap[b], &heap[j]);
                j = b;
            }
            else
            {
                SWAP_ITEMS(&heap[a], &heap[j]);
                j = a;
            }
            a = 2*j + 1;
            b = 2*j + 2;
        }
    }
    
    // free memory [O(1)]
    free(heap);
    return I;
}

// Check two item set lists for equality
int CompareItemSets(LR_ITEM_SET* one, LR_ITEM_SET* two)
{
    while (one && two)
    {
        if (CompareItems(one->item, two->item) != 0)
            return 1;
        one = one->next;
        two = two->next;
    }
    
    if (one || two)
        return 1;
    return 0;
}

// Copy a set, useful for building new sets (reverses the list)
LR_ITEM_SET* CopyItemSet(LR_ITEM_SET* I)
{
    LR_ITEM_SET* J = NULL;
    while (I) {
        LR_ITEM_SET* copy = malloc(sizeof(LR_ITEM_SET));
        copy->item = I->item;
        copy->next = J;
        J = copy;
        I = I->next;
    }
    return J;
}

// Free an LR_ITEM_SET list
void FreeItemSet(LR_ITEM_SET* I)
{
    LR_ITEM_SET* iterator;
    while (I) {
        iterator = I->next;
        free(I);
        I = iterator;
    }
}

/*
function closure(I):
begin
    J := I;
    repeat
        for each item A -> a*Bb in J and each production
            B -> y of G such that B -> *y is not in J do
                    add B -> *y to J
    until no more items can be added to J;
    return J
end
*/
LR_ITEM_SET* Closure(LR_ITEM_SET* I, GRAMMAR_TABLE* G)
{
    // J := I;
    LR_ITEM_SET* J = CopyItemSet(I);
    
    // repeat
    int stillAdding;
    do {
        stillAdding = 0;
        
        // for each item A-> a*Bb in J
        LR_ITEM_SET* itr;
        for (itr = J; itr; itr = itr->next)
        {
            LR_ITEM item = itr->item;
            if (item.dot < G->rules[item.production].rhsLength)
            {
                int B = G->rules[item.production].rhs[item.dot];
                // and each production B -> y of G
                int i;
                for (i = 0; i < G->numRules; i++)
                {
                    if (G->rules[i].lhs == B)
                    {
                        // such that B -> *y is not in J
                        LR_ITEM add;
                        add.production = i;
                        add.dot = 0;

                        LR_ITEM_SET* find;
                        for (find = J; find; find = find->next)
                        {
                            if (CompareItems(find->item, add) == 0)
                                break;
                        }

                        if (find == NULL)
                        {
                            // add B -> *y to J
                            find = malloc(sizeof(LR_ITEM_SET));
                            find->item = add;
                            find->next = J;
                            J = find;
                            stillAdding = 1;
                        }
                    }
                }
            }
        }
    } while (stillAdding);
    // until no more items can be added to J;
    
    // return J
    return Sort(J);
}

/*
function goto(I, X):
begin
    J := {};
    for each item A -> a*Xb in I
            add A -> aX*b to J
    return closure(J)
end
*/
LR_ITEM_SET* Goto(LR_ITEM_SET* I, int X, GRAMMAR_TABLE* G)
{
    // J := {};
    LR_ITEM_SET* J = NULL;
    
    // for each item A -> a*Xb in I
    LR_ITEM_SET* itr;
    for (itr = I; itr; itr = itr->next)
    {
        LR_ITEM item = itr->item;
        int B = G->rules[item.production].rhs[item.dot];
        if (B == X)
        {
            // add A -> aX*b to J
            LR_ITEM_SET* add = malloc(sizeof(LR_ITEM_SET));
            add->item = item;
            add->item.dot++;
            add->next = J;
            J = add;
        }
    }
    
    // return closure(J)
    LR_ITEM_SET* K = Closure(J, G);
    FreeItemSet(J);
    return K;
}

int GotoState(LR_ITEM_SET* set, LR_ITEM_COLLECTION* find)
{
    int state = 0;
    for (; find; find = find->next, state++)
    {
        if (CompareItemSets(find->set, set) == 0)
        {
            return state;
        }
    }
    return -1;
}

/*
// LR(0) canonical collection of sets
procedure items(G');
begin
    C := {closure({[S' -> *S]})};
    repeat
        for each set of items I in C and each grammar symbol X
            such that goto(I, X) is not empty and not in C do
                    add goto(I, X) to C
    until no more sets of items can be added to C
end
*/
LR_ITEM_COLLECTION* CanonicalCollection(GRAMMAR_TABLE* G)
{
    // C := {closure({[S' -> *S]})};
    LR_ITEM_COLLECTION* C = malloc(sizeof(LR_ITEM_COLLECTION));
    C->set = malloc(sizeof(LR_ITEM_SET));
    C->set->item.production = 0;
    C->set->item.dot = 0;
    C->set->next = NULL;
    C->next = NULL;
    
    LR_ITEM_SET* closure = Closure(C->set, G);
    FreeItemSet(C->set);
    C->set = closure;
    
    // repeat
    int finished;
    do {
        finished = 1;
        // for each set of items I in C
        LR_ITEM_COLLECTION* itr;
        for (itr = C; itr; itr = itr->next)
        {
            LR_ITEM_SET* I = itr->set;
            // and each grammar symbol X
            int i;
            for (i = 0; i < G->numSymbols + G->numTokens; i++)
            {
                int X = (i < G->numSymbols) ? K_SYMBOL + i + 1 :
                    K_TOKEN + (i - G->numSymbols) + 1;
                    
                LR_ITEM_SET* gotoSet = Goto(I, X, G);
                
                // such that goto(I, X) is not empty
                if (gotoSet == NULL) continue;

                // and not in C
                LR_ITEM_COLLECTION* find;
                for (find = C; find; find = find->next)
                {
                    if (CompareItemSets(find->set, gotoSet) == 0)
                    {
                        FreeItemSet(gotoSet);
                        gotoSet = NULL;
                        break;
                    }
                    else if (find->next == NULL)
                    {
                        // add goto(I, X) to C
                        find->next = malloc(sizeof(LR_ITEM_COLLECTION));
                        find = find->next;
                        find->next = NULL;
                        find->set = gotoSet;
                        finished = 0;
                    }
                }
            }
        }
    } while (!finished);
    // until no more sets of items can be added to C
    
    return C;
}

// Free the canonical collection and all the item sets it contains
void FreeCollection(LR_ITEM_COLLECTION* collection)
{
    LR_ITEM_COLLECTION* iterator;
    while (collection)
    {
        iterator = collection->next;
        FreeItemSet(collection->set);
        free(collection);
        collection = iterator;
    }
}


/*
Input:  An augmented grammar G'.

Output: The SLR parsing table functions *action* and *goto* for G'.

Method.

1. Construct C = {I0, I1, ..., In}, the collection of sets of LR(0) items for
   G'.
2. State i is costructed from Ii. The parsing actions for state i are deter-
   mined as follows:
    a) If [A -> z*aB] is in Ii and goto(Ii, a) = Ij, then set action[i, a] to
       "shift j." Here a must be a terminal.
    b) If [A -> z*] is in Ii, then set action[i, a] to "reduce A->z" for all a
       in FOLLOW(A); here A may not be S'.
    c) If [S' -> S*] is in Ii, then set action[i, $] to "accept."
    
If any conflicting actions are generated y the above rules, we say the grammar
is not SLR(1). The algorithm fails to produce a parser in this case.

3. The goto transitions for state i are constructed for all nonterminals A
   using the rule: If goto(Ii, A) = Ij, then goto[i, A] = j.
   
4. All entries not defined by rules (2) and (3) are made "error."

5. The initial state of the parser is the one constructed from the set of items
   containing [S' -> *S].
*/
LR_TABLE ConstructTable(LR_ITEM_COLLECTION* C, GRAMMAR_TABLE* G)
{
    LR_ITEM_COLLECTION* itr;
    LR_TABLE table;
    int numStates = 0;
    int state;

    // count the number of states
    for (itr = C; itr; itr = itr->next)
        numStates++;
        
    printf("Building LR table with %i states.\n", numStates);

    // allocate the action and goto tables
    table.numTokens = G->numTokens;
    table.numSymbols = G->numSymbols;
    table.numStates = numStates;
    table.actionTable = malloc(table.numStates * table.numTokens
        * sizeof(ACTION));
    table.gotoTable = malloc(table.numStates * table.numSymbols
        * sizeof(int));
    
    // clear the tables
    memset(table.actionTable, 0, table.numStates * table.numTokens
        * sizeof(ACTION));
    memset(table.gotoTable, 0, table.numStates * table.numSymbols
        * sizeof(int));
    
    // for each state
    for (itr = C, state = 0; itr; itr = itr->next, state++)
    {
        // and for each terminal
        int x;
        for (x = 1; x <= G->numSymbols; x++)
        {
            // generate the GOTO table
            LR_ITEM_SET* gotoSet = Goto(itr->set, x | K_SYMBOL, G);
            int gotoState = GotoState(gotoSet, C);
            table.gotoTable[state * table.numSymbols + x - 1] = gotoState;
        }
    }
    
    int reduceReduceConflicts = 0;
    int shiftReduceConflicts = 0;

    // for each item collection in a parser state
    for (itr = C, state = 0; itr; itr = itr->next, state++)
    {
        ACTION action;
        
        // and each production item
        LR_ITEM_SET* items;
        for (items = itr->set; items; items = items->next)
        {
            LR_ITEM item = items->item;
            RULE production = G->rules[item.production];
            int dot = item.dot;
            
            // SHIFT if it's of the form [A -> z*aB]
            // where a is a terminal, and the new state is GOTO[state, a]
            if (dot < production.rhsLength
                && production.rhs[dot] & K_TOKEN)
            {
                LR_ITEM_SET* gotoSet;
                int          index;
                
                gotoSet = Goto(itr->set, production.rhs[dot], G);
                action.type = ACTION_SHIFT;
                action.value = GotoState(gotoSet, C);
                
                index = state * table.numTokens
                    + (production.rhs[dot] ^ K_TOKEN) - 1;
                    
                if (table.actionTable[index].type != ACTION_ERROR &&
                    (table.actionTable[index].type != action.type ||
                     table.actionTable[index].value != action.value))
                {
                    if (table.actionTable[index].type == ACTION_REDUCE)
                    {
                        // prefer shift over reduce actions
                        shiftReduceConflicts++;
                        /*

                        */
                        printf("Conflict with reduce %i on input %s",
                            table.actionTable[index].value,
                            GetElement(production.rhs[dot], *G));
                        printf(", using shift\n");
                        PrintItem(item, G);
                        table.actionTable[index] = action;
                    } else {
                        printf("Shift shift conflict?\n");
                    }
                } else {
                    table.actionTable[index] = action;
                }
            }
            
            // REDUCE if it's of the form [A -> z*]
            // where A != S' and the rule is reduced for all a in FOLLOW(A)
            if (dot == production.rhsLength
                && production.lhs != gSymbolRoot)
            {
                int i;
                
                action.type = ACTION_REDUCE;
                action.value = item.production;
                
                for (i = 1; i <= G->numTokens; i++)
                {
                    if (GetFollowTable(production.lhs, i | K_TOKEN, G) == 1)
                    {
                        int index = state * table.numTokens + i - 1;
                        if (table.actionTable[index].type != ACTION_ERROR &&
                            (table.actionTable[index].type != action.type ||
                             table.actionTable[index].value != action.value))
                        {
                            // conflict
                            if (table.actionTable[index].type == ACTION_REDUCE)
                            {
                                reduceReduceConflicts++;
                                // prefer reductions of earlier productions
                                /*

                                */
                                printf("Conflict with reduce %i on input %s, ",
                                    table.actionTable[index].value,
                                    GetElement(i | K_TOKEN, *G));
                                if (action.value
                                        < table.actionTable[index].value)
                                {
                                    table.actionTable[index] = action;
                                    printf("using reduce %i.\n",
                                        table.actionTable[index].value);
                                }
                                else
                                {
                                    printf("not using reduce %i.\n",
                                        action.value);
                                }
                            }
                            else if (table.actionTable[index].type
                                                        == ACTION_SHIFT)
                            {
                                shiftReduceConflicts++;
                                /*

                                */
                                printf("Conflict with reduce %i on input %s",
                                    action.value,
                                    GetElement(i | K_TOKEN, *G));
                                printf(", using shift %i.\n",
                                    table.actionTable[index].value);
                            }
                            else
                            {
                                printf("Reduce/????? conflict?\n");
                            }
                        }
                        else
                        {
                            // no conflict
                            table.actionTable[index] = action;
                        }
                    }
                }
            }
            
            // ACCEPT if it's the item [S' -> S*]
            // for the input $
            if (items->item.production == 0 && dot == 1)
            {
                action.type = ACTION_ACCEPT;
                action.value = 0;
                
                int index = state * table.numTokens
                    + (gSymbolEOF ^ K_TOKEN) - 1;
                if (table.actionTable[index].type != ACTION_ERROR &&
                    (table.actionTable[index].type != action.type ||
                     table.actionTable[index].value != action.value))
                {
                    printf("Action table conflict for accept.\n");
                }
                table.actionTable[index] = action;
            }
        }
    }
    
    if (shiftReduceConflicts)
        printf("%i shift/reduce conflicts.\n", shiftReduceConflicts);
    if (reduceReduceConflicts)
        printf("%i reduce/reduce conflicts.\n", reduceReduceConflicts);
    
    return table;
}

void PrintItem(LR_ITEM item, GRAMMAR_TABLE* G)
{
    int i;

    printf("\t");
    if (G->rules[item.production].lhs == 0)
        printf("START");
    else
        printf("%s", GetElement(G->rules[item.production].lhs, *G));
    printf(" -> ");
    for (i = 0; i < G->rules[item.production].rhsLength; i++)
    {
        if (i == item.dot)
            printf("* ");
        //printf("%i ", G->rules[item.production].rhs[i]);
        printf("%s ", GetElement(G->rules[item.production].rhs[i], *G));
    }
    if (i == item.dot)
        printf("*");
    printf("\n");
}

// display the contents of an item set
void PrintItemSet(LR_ITEM_SET* I, GRAMMAR_TABLE* G)
{
    while (I) 
    {
        PrintItem(I->item, G);
        I = I->next;
    }
}

// display the contents of a canonical collection
void PrintCollection(LR_ITEM_COLLECTION* C, GRAMMAR_TABLE* G)
{
    int i = 0;
    printf("Canonical Collection\n");
    printf("--------------------\n");

    while (C)
    {
        printf("I(%i):\n", i);
        PrintItemSet(C->set, G);
        printf("\n");
        C = C->next;
        i++;
    }
    
    printf("====================\n\n");
}

void PrintParseTable(LR_TABLE      parser,
                     GRAMMAR_TABLE grammar)
{
    int i, j;

    // top row labels
    for (i = 0; i < parser.numTokens; i++)
        printf("\t%i", i);
    printf("\t|");
    for (i = 0; i < parser.numSymbols; i++)
        printf("\t%i", i);
        
    printf("\n");
    
    for (i = 1; i <= parser.numTokens; i++)
    {
        printf("\t");
        char* str = GetElement(i | K_TOKEN, grammar);
        j = 0; if (str[j] == '<') j++;
        for (; j < 3 && str[j] != 0
                && str[j] != '>'; j++)
            printf("%c", str[j]);
    }
    printf("\t|");
    for (i = 1; i <= parser.numSymbols; i++)
    {
        printf("\t");
        char* str = GetElement(i | K_SYMBOL, grammar);
        j = 0; if (str[j] == '<') j++;
        for (; j < 3 && str[j] != 0
                && str[j] != '>'; j++)
            printf("%c", str[j]);
    }
    
    // top row delineator
    printf("\n");
    for (i = 0; i < parser.numTokens + parser.numSymbols + 1; i++)
        printf("----");
    printf("\n");
    
    // table entries
    for (i = 0; i < parser.numStates; i++)
    {
        printf("%i.", i);
        for (j = 0; j < parser.numTokens; j++)
        {
            ACTION action = parser.actionTable[i*parser.numTokens + j];
            if (action.type == ACTION_REDUCE)
                printf("\tr%i", action.value);
            else if (action.type == ACTION_SHIFT)
                printf("\ts%i", action.value);
            else if (action.type == ACTION_ACCEPT)
                printf("\tacc");
            else
                printf("\t");
        }
        
        printf("\t|");
        
        for (j = 0; j < parser.numSymbols; j++)
        {
            int g = parser.gotoTable[i*parser.numSymbols + j];
            if (g > 0)
                printf("\t%i", g);
            else
                printf("\t");
        }
        
        printf("\n");
    }
    printf("\n");
}

void PrintLRParser(LR_TABLE      parser,
                   GRAMMAR_TABLE grammar)
{
    int i, j, count;
    
    printf("Nullable Nonterminals:\n");
    
    count = 0;
    for (i = 0; i < grammar.numSymbols; i++)
    {
        if (NULLABLE_NONTERMINALS[i])
        {
            if (count) printf(", ");
            printf("%s", GetElement((i+1) | K_SYMBOL, grammar));
            count++;
        }
    }
    
    printf("\n\n");
    printf("First Sets:\n");
    
    for (i = 0; i < grammar.numSymbols; i++)
    {
        printf("%s: ", GetElement((i+1) | K_SYMBOL, grammar));
        count = 0;
        for (j = 0; j < grammar.numTokens; j++)
        {
            if (GetFirstTable((i+1) | K_SYMBOL, (j+1) | K_TOKEN, &grammar) == 1)
            {
                if (count) printf(", ");
                printf("%s", GetElement((j+1) | K_TOKEN, grammar));
                count++;
            }
        }
        printf("\n");
    }
    
    printf("\n\n");
    printf("Follow Sets:\n");
    
    for (i = 0; i < grammar.numSymbols; i++)
    {
        printf("%s: ", GetElement((i+1) | K_SYMBOL, grammar));
        count = 0;
        for (j = 0; j < grammar.numTokens; j++)
        {
            if (GetFollowTable((i+1) | K_SYMBOL, (j+1)
                    | K_TOKEN, &grammar) == 1)
            {
                if (count) printf(", ");
                printf("%s", GetElement((j+1) | K_TOKEN, grammar));
                count++;
            }
        }
        printf("\n");
    }
    
    printf("\n\n\n");
    
    //PrintParseTable(parser, grammar);
}


/* build an SLR parse table */
int BuildLRParser(GRAMMAR_TABLE grammar,
                  LR_TABLE*     parser)
{
    // building the collection of item sets for an LR(0) grammar
    LR_ITEM_COLLECTION* C = CanonicalCollection(&grammar);
    //PrintCollection(C, &grammar);

    FindNullableNonterminals(&grammar);
    BuildFirstSets(&grammar);
    BuildFollowSets(&grammar);
    RemoveEpsilons(&grammar);

    *parser = ConstructTable(C, &grammar);
    FreeCollection(C);
    return 0;
}

void FreeLRParser(LR_TABLE* parseTable)
{
    if (parseTable) {
        free(parseTable->actionTable);
        free(parseTable->gotoTable);
        parseTable->actionTable = NULL;
        parseTable->gotoTable = NULL;
    }
    
    free(FIRST_SETS);
    free(FOLLOW_SETS);
    free(NULLABLE_NONTERMINALS);

    FIRST_SETS = NULL;
    FOLLOW_SETS = NULL;
    NULLABLE_NONTERMINALS = NULL;
}

#endif // _SLR
