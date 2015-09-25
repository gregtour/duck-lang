# Duck Programming Language      ![Build Status](https://travis-ci.org/gregtour/duck-lang.svg?branch=master)
A simple scripting language based on the idea of duck-typing (or dynamic typing). 

>&ldquo;When I see a bird that walks like a duck and swims like a duck and quacks like a duck, I call that bird a duck.&rdquo;
> &mdash; James Whitcomb Riley

## Language Features

The duck programming language supports first-class functions, integer and floating-point arithmetic, string manipulation, dynamically-sized arrays, dictionary types, and basic object oriented programming. The syntax is strongly reminiscent of BASIC, Lua, or Python. While indentation is not strictly specified, the language requires specific whitespace in required newlines at the end of certain statements. Duck is currently only implemented in the form of a slow, interpreted frontend, making it useful as a portable scripting language. This frontend has been developed entirely in C.

The syntax of loops is somewhat different than in BASIC or other languages. For example, a while loop has the following syntax:
```
while (condition) do
	// loop body
	// ...
loop
```
while a for loop in Duck looks like this
```
for i = 1 to 10 do
    // iterated instructions
    // ...
    // ...
loop
```
Notice the use of the syntax \`do' and \`loop.' &nbsp;There are a number of other example programs in the _examples_ directory of the source repository.

The programming language's grammar is represented below in Backas-Naur form. The duck language has its own parser-generator, generating SLR(1) parse tables, so it is relatively easy to change the syntax of the language. Other optional ways to configure the language include disabling case-sensitivity or changing the format of comments, which are currently implemented as `/* C-style block comments */`, `// full line comments`, `; semicolon until end of line comments`, and `# any macro use`.

It is easy to port libraries to Duck. Function hooks are implemented as pointers, of the form `int (function_pointer)(int)` where the argument count is passed as the only parameter. Arguments are bound as string identifiers, and are accessed dynamically in the bound-function's body.

Example:
```c
void BindStandardLibrary()
{
    VALUE duckStdLib = LinkNamespace("duck");

    VALUE print = CreateFunction(DuckPrint);
    AddParameter(print, "output");
    
    LinkFunction(duckStdLib, "print", print);
    LinkFunction(duckStdLib, "println", print);

    VALUE prompt = CreateFunction(DuckPrompt);
    LinkFunction(duckStdLib, "prompt", prompt);
}
```

As an example of what a typical program might look like written in Duck, the following is an example of computing prime numbers.

```
function display_primes(limit)
	count = 0
	numbers = []
	for i = 2 to limit do
		numbers[i] = 1
	loop
	for i = 2 to limit do
		if numbers[i] == 1 then
			count = count + 1
			for j = 2 to limit/i do
				numbers[i*j] = 0
			loop
			duck.print(i)
		end
	loop
end
```

## Context free grammar
```
<program> ::= <stmt list>
<stmt list> ::= <stmt list> <stmt>
<stmt list> ::= <epsilon>
<stmt> ::= import <identifier>
<stmt> ::= call <reference>
<stmt> ::= <endl>
<stmt> ::= <expr> <endl>
<stmt> ::= <assignment> <endl>
<stmt> ::= <function def> <endl>
<stmt> ::= <if> <endl>
<stmt> ::= <if else> <endl>
<stmt> ::= <for loop> <endl>
<stmt> ::= <while loop> <endl>
<stmt> ::= return <expr> <endl>
<stmt> ::= break <endl>
<stmt> ::= continue <endl>
<function def> ::= function <identifier> <parameters> <endl> <stmt list> end
<parameters> ::= <epsilon>
<parameters> ::= ( )
<parameters> ::= (<param decl>)
<param decl> ::= <identifier>
<param decl> ::= <param decl>, <identifier>
<if> ::= if <condition> then <endl> <stmt list> end
<if else> ::= if <condition> then <endl> <stmt list> else <endl> <stmt list> end
<for loop> ::= for <identifier> = <arithmetic> to <arithmetic> do <endl> <stmt list> loop
<while loop> ::= while <condition> do <endl> <stmt list> loop
<assignment> ::= <l-value> = <assignment>
<assignment> ::= <l-value> = <condition>
<l-value> ::= <identifier>
<l-value> ::= ( <l-value> )
<l-value> ::= <reference> . <identifier>
<l-value> ::= <reference> [ <expr> ]
<expr> ::= <condition>
<condition> ::= <condition> and <logic>
<condition> ::= <condition> or <logic>
<condition> ::= <condition> nor <logic>
<condition> ::= <condition> xor <logic>
<condition> ::= <logic>
<logic> ::= not <comparison>
<logic> ::= <comparison>
<comparison> ::= <comparison> == <arithmetic>
<comparison> ::= <comparison> != <arithmetic>
<comparison> ::= <comparison> \< <arithmetic>
<comparison> ::= <comparison> > <arithmetic>
<comparison> ::= <comparison> \<= <arithmetic>
<comparison> ::= <comparison> >= <arithmetic>
<comparison> ::= <arithmetic>
<arithmetic> ::= <arithmetic> + <term>
<arithmetic> ::= <arithmetic> - <term>
<arithmetic> ::= <arithmetic> & <term>
<arithmetic> ::= <arithmetic> | <term>
<arithmetic> ::= <term>
<term> ::= <term> * <factor>
<term> ::= <term> / <factor>
<term> ::= <factor>
<factor> ::= -<factor>
<factor> ::= !<factor>
<factor> ::= <final>
<final> ::= ( <expr> )
<final> ::= <boolean>
<final> ::= <integer>
<final> ::= <float>
<final> ::= <string>
<final> ::= <object>
<final> ::= <reference>
<reference> ::= <l-value>
<reference> ::= <reference> ( )
<reference> ::= <reference> ( <arguments> )
<arguments> ::= <arguments>, <expr>
<arguments> ::= <expr>
<object> ::= [ ]
<object> ::= [ <array init> ]
<object> ::= [ <dictionary init> ]
<array init> ::= <array init>, <expr>
<array init> ::= <expr>
<dictionary init> ::= <dictionary init>, <identifier> : <expr>
<dictionary init> ::= <identifier> : <expr>
<boolean> ::= true
<boolean> ::= false

```

## Standard Library
Duck has a standard library supporting both command-line input and output. See: stdduck.h.
There are also SDL and OpenGL bindings to support making a graphical window as well as draw calls.

Here is a list of those functions:

#### Library
##### Duck
* duck.print(output)
* duck.println(output)
* duck.prompt()

##### SDL
* SDL.MakeWindow(width, height, title, fullscreen)
* SDL.flip()
* SDL.event()
* SDL.clearScreen()
* SDL.running()
* SDL.waitkey()
* SDL.quit()

##### GL
* SDL.glLoadIdentity()
* SDL.glTranslatef(x, y, z)
* SDL.glRotatef(deg, x, y, z)
* SDL.glScalef(x, y, z)
* SDL.glBegin(primitive)
* SDL.glColor3f(r, g, b)
* SDL.glVertex3f(x, y, z)
* SDL.glNormal3f(x, y, z)
* SDL.glEnd()

## Building
Duck uses CMake 2.8. To build simply run:
```
> cmake .
> make
```

Building gduck with SDL support requires SDL and OpenGL libraries. There are no platform specific libraries.

## Credits
Greg Tourville

Hiroyuki Sano

Robert Cope


## Future Work

* Implementing a binary compiler
* Memory management and garbage collection, to prevent crashes due to running out of memory
* Optional, strongly/statically typed form of DUCK
* Multithreaded parallelism &mdash; implicit or explicit through syntax analysis or library functions
* Benchmark and profiling performance intrinsics
* Expanding the standard library

