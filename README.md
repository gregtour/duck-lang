# Duck Programming Language (Development Branch) ![Build Status](https://travis-ci.org/gregtour/duck-lang.svg?branch=development)
A simple scripting language based on the idea of duck-typing (or dynamic typing).

>&ldquo;When I see a bird that walks like a duck and swims like a duck and quacks like a duck, I call that bird a duck.&rdquo;
> &mdash; James Whitcomb Riley

## Development Notes
This is the current development branch of the Duck programming language.

See the Wiki on more information for what is planned for Duck 2.0.

Current tasks include migrating to new syntax by using new grammar and parse tables, implementing the newest language features, and creating libraries to support all of the necessary tasks a Duck developer might use.

To contribute, check out from the development branch and submit pull requests.

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
func display_primes(limit)
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
		endif
	loop
end
```


## Building
Duck uses CMake 2.8. To build simply run:
```
> cmake .
> make
```

Building gduck with SDL support requires SDL and OpenGL libraries. There are no platform specific libraries.

## Contributions From
Greg Tourville

Hiroyuki Sano

Robert Cope


## Future Work

* Performance, stability, and new features.
* Expanding the standard library.

