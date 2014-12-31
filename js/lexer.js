/*var gSymbolEOF = "EOF";
var gSymbolEndLine = "END LINE";
var gSymbolInteger = "INT";
var gSymbolFloat = "FLOAT";
var gSymbolString = "STRING";
var gSymbolIdentifier = "IDENTIFIER";
*/

function EOFSYMBOL(line) 
{
    return {"token": gSymbolEOF, "string": "", "length": 1, "line": line};
}

function NEWLINE(line) 
{
    return {"token": gSymbolEndLine, "string": "", "length": 1, "line": line};   
}

function INTEGER(text, line)
{
    return {"token": gSymbolInteger, "string": text, "length": text.length, "line": line};
}

function FLOAT(text, line)
{
    return {"token": gSymbolFloat, "string": text, "length": text.length, "line": line};
}

function STRING(text, line)
{
    return {"token": gSymbolString, "string": text.substr(1, text.length-2), "length": text.length, "line": line};
}

function TOKEN(text, line, grammar)
{
    var token = grammar.FindToken(text);
    if (token) {
        return {"token": token, "string": text, "length": text.length, "line": line};
    } else {
        program.output("Syntax error on line " + line + ": token '" + text + "'.");
        return 0;
    }
}

function IDENTIFIER(text, line, grammar)
{
    var token = grammar.FindToken(text);
    if (token) {
        return {"token": token, "string": text, "length": text.length, "line": line};
    } else {
        return {"token": gSymbolIdentifier, "string": text, "length": text.length, "line": line};
    }
}

function isAlpha(c) {
    var code = c.charCodeAt(0);
    return (('a'.charCodeAt(0) <= code && code <= 'z'.charCodeAt(0)) ||
            ('A'.charCodeAt(0) <= code && code <= 'Z'.charCodeAt(0)));
}

function isNumeric(c) {
    var code = c.charCodeAt(0);
    return ('0'.charCodeAt(0) <= code && code <= '9'.charCodeAt(0));
}

function isSpace(c) {
    return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
}

function isGlyph(c) {
    return (!isAlpha(c) && !isNumeric(c) && !isSpace(c));
}

function LexSource(text, grammar)
{
    var size = text.length;
    var line_number = [];
    var line = 0;
    var i;

    // count lines
    for (i = 0; i <= size; i++) {
        line_number.push(line);
        if (text.charAt(i) == '\n') {
            line++;
        }
    }

    // strip clean
    var format = "";
    var j = 0;
    for (i = 0; i < size; i++) {
        if (text.charAt(i) == '/' &&
            text.charAt(i+1) == '/') {
            while (i < size && text.charAt(i) != '\n')
                i++;
            i--;
        }
        else if (text.charAt(i) == '/' &&
                 text.charAt(i+1) == '*') {
            i++; i++;
            while (i < size - 1 &&
                    (text.charAt(i) != '*' ||
                     text.charAt(i+1) != '/'))
            {
                i++;
            }
            i++;
        }
        else if (text.charAt(i) == '#' ||
                 text.charAt(i) == ';') {
            while (i < size && text.charAt(i) != '\n')
                i++;
            i--;
        }
        else if (isSpace(text.charAt(i))) {
            var lb = false;
            line_number[j] = line_number[i];
            while (i < size && isSpace(text.charAt(i)))
            {
                if (text.charAt(i) == '\n') {
                    lb = true;
                    line_number[j] = line_number[i];
                }
                i++;
            }
            if (lb)
                format += '\n';
            else
                format += ' ';
            i--;
            j++;
        }
        else if (text.charAt(i) == '"' ||
                 text.charAt(i) == '\'') {
            var quote = text.charAt(i);
            format += text.charAt(i++);
            j++;
            while (i < size - 1 && text.charAt(i) != quote) {
                line_number[j] = line_number[i];
                format += text.charAt(i++);
                j++;
            }
            line_number[j] = line_number[i];
            format += text.charAt(i);
            j++;
        }
        else {
            line_number[j] = line_number[i];
            format += text.charAt(i);
            j++;
        }
    }

    //program.output(format);

    var sizen = size;
    size = j;

//    var start = [];
//    var end = [];
    var tokens = [];
                    
    // lex
    var a, b;
    for (i = 0; i < size; i++) {
        line = line_number[i];
        // check next character
        if (isAlpha(format.charAt(i))) {
            a = i;
            // alpha
            while (i < size &&
                    (isAlpha(format.charAt(i)) ||
                     isNumeric(format.charAt(i)) ||
                     format.charAt(i) == '_'))
            {
                i++;
            }
            b = i;
            tokens.push(IDENTIFIER(format.substr(a, b-a), line, grammar));
            i--;
        }
        else if (isNumeric(format.charAt(i))) {
            // numeric
            a = i;
            while (i < size && isNumeric(format.charAt(i)))
            {
                i++;
            }
            if (format.charAt(i) == '.') {
                i++;
                while (i < size && isNumeric(format.charAt(i)))
                {
                    i++;
                }
                b = i;
                tokens.push(FLOAT(format.substr(a, b-a), line, grammar));
                i--;
            }
            else {
                b = i;
                tokens.push(INTEGER(format.substr(a, b-a), line, grammar));
                i--;
            }
        }
        else if (format.charAt(i) == '"' || format.charAt(i) == '\'') {
            // string literal
            var delimiter = format.charAt(i);
            a = i++;
            while (i < size && format.charAt(i) != delimiter)
            {
                i++;
            }
            b = i++;
            tokens.push(STRING(format.substr(a, b-a+1), line, grammar));
            i--;
        }
        else if (isGlyph(format.charAt(i))) {
            // token symbol or glyph
            a = i; b = 0;
            while (i < size && isGlyph(format.charAt(i))) {
                i++;
                if (grammar.FindToken(format.substr(a, i-a), grammar))
                    b = i;
            }
            b = b ? b : i;
            tokens.push(TOKEN(format.substr(a, b-a), line, grammar));
            i = b - 1;
        }
        else if (format.charAt(i) == '\n') {
            // new line
            tokens.push(NEWLINE(line));
        }
        else if (format.charAt(i) == ' ') {
            // whitespace
        }
        else {
            // error
            program.output("Syntax error on line " + line + ".");
            return 0;
        }
    }

    // add trailing line feed
    tokens.push(NEWLINE(line));
    tokens.push(EOFSYMBOL(line));
    
    // output tokenized source
    // program.output(JSON.stringify(tokens));
    
    return tokens;
}


