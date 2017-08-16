/* lexer */

var INCLUDE_NEWLINES = true;
var INCLUDE_WHITESPACE = false;
var INCLUDE_COMMENTS = false;

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
    return {"token": gSymbolString, "string": text.substr(1, text.length-2), "length": text.length, "line": line, "delimiter": text.charAt(0)};
}

function TOKEN(text, line)
{
    var token = FindToken(text);
    if (token) {
        return {"token": token, "string": text, "length": text.length, "line": line};
    } else {
        program.output("Syntax error on line " + line + ": token '" + text + "'.");
        return 0;
    }
}

function SPACE(text, line) {
    return {"token": gSymbolEOF, "space": true, "string": text, "line": line};
}

function COMMENT(text, line, lineCount) 
{
    return {"token": gSymbolEOF, "comment": true, "string": text, "line": line, "lineCount": lineCount};
}

function IDENTIFIER(text, line)
{
    var token = FindToken(text);
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

function LexSource(text, includeWSC)
{
    var tokens = [];
    var size = text.length;
    var a, b, c, cc, i;
    var line = 0;

    text = text + "";

    for (i = 0; i < size; i++) 
    {
        c = text.charAt(i);
        cc = (i+1) < size ? c + text.charAt(i+1) : null;

        // whitespace
        if (isSpace(c)) {
            // newline
            if (c == '\n') {
                if (INCLUDE_NEWLINES) {
                    // concatenate successive newlines
                    var prevNewline = (tokens.length > 0 && tokens[tokens.length-1].token === gSymbolEndLine);
                    if (prevNewline) {
                        tokens[tokens.length - 1].length++;
                    } else {
                        tokens.push(NEWLINE(line));                        
                    }
                }
                line++;
            } 
            // space or tab
            else if (c != '\r') {
                if (INCLUDE_WHITESPACE) {
                    // concatenate successive spaces
                    var prevSpace = (tokens.length > 0 && tokens[tokens.length-1].space);
                    if (prevSpace) {
                        tokens[tokens.length - 1]["string"] += c;
                    } else {
                        tokens.push(SPACE(c, line));
                    }
                }
            }
        }
        // single-line comment
        else if (c == '#' || c == ';' || cc == "//") {
            a = i;
            // search for trailing newline
            while (i < size) {
                if ((i+1) < size && text.charAt(i+1) == "\n")
                    break;
                i++;
            }
            b = i;
            if (INCLUDE_COMMENTS) {
                var commentText = text.substr(a, b-a);
                tokens.push(COMMENT(commentText, line, 0));
            }
        }
        // multiline comment
        else if (cc == "/*") {
            var lineCount = 0;
            a = i;
            i += 2;
            // search for trailing "*/"
            while ((i+1) < size) 
            {
                if (text.charAt(i) == "\n") {
                    lineCount++;
                    line++;
                }
                if (text.substr(i,2) == "*/") {
                    break;
                }
                i++;
            }
            i++;
            b = i;
            if (INCLUDE_COMMENTS) {
                var commentText = text.substr(a, b-a);
                tokens.push(COMMENT(commentText, line, lineCount));
            }
        }
        // alphabetical identifier or keyword
        else if (isAlpha(c)) {
            a = i;
            while (i < size &&
                    (isAlpha(text.charAt(i)) ||
                     isNumeric(text.charAt(i)) ||
                     text.charAt(i) == '_'))
            {
                i++;
            }
            b = i;
            tokens.push(IDENTIFIER(text.substr(a, b-a), line));
            i--;
        }
        // number - float or int
        else if (isNumeric(c)) {
            a = i;
            while (i < size && isNumeric(text.charAt(i)))
            {
                i++;
            }
            if (text.charAt(i) == '.') {
                i++;
                while (i < size && isNumeric(text.charAt(i)))
                {
                    i++;
                }
                b = i;
                tokens.push(FLOAT(text.substr(a, b-a), line));
                i--;
            }
            else {
                b = i;
                tokens.push(INTEGER(text.substr(a, b-a), line));
                i--;
            }
        }
        // string literal
        else if (c == '"' || c == "'") {
            var delimiter = text.charAt(i);
            a = i++;
            while (i < size && text.charAt(i) != delimiter)
            {
                if (text.charAt(i) == '\n') {
                    program.output("Syntax error on line " + line + ". New line in string.");
                    return 0;
                }
                i++;
            }
            b = i++;
            tokens.push(STRING(text.substr(a, b-a+1), line));
            i--;
        }
        // token symbol or glyph
        else if (isGlyph(c)) {
            a = i; b = 0;
            while (i < size && isGlyph(text.charAt(i))) {
                i++;
                if (FindToken(text.substr(a, i-a)))
                    b = i;
            }
            b = b ? b : i;
            tokens.push(TOKEN(text.substr(a, b-a), line));
            i = b - 1;
        }
        // error
        else {
            program.output("Syntax error on line " + line + ".");
            return 0;
        }
    }

    // add trailing line feed
    if (INCLUDE_NEWLINES) {
        tokens.push(NEWLINE(line));
    }
    tokens.push(EOFSYMBOL(line));
    
    // output tokenized source
    // program.output(JSON.stringify(tokens));
    
    return tokens;
}


