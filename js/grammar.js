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
