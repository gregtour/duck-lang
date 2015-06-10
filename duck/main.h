#ifndef __DUCK_MAIN_H
#define __DUCK_MAIN_H

const char* demo =
"/* Duck REPL ** Enter statements to be evaluated. */\n"
"duck.println(\"Duck Language REPL - type quit() to exit\")\n"
"running = true\n"
"while running do\n"
"    program = \"\"\n"
"    typing = true\n"
"    expr = 0\n"
"    duck.println(\"Type expression or statements:\")\n"
"    while typing do\n"
"        line = duck.prompt(\" > \")\n"
"        program = program + line + duck.newline\n"
"        parsable = duck.parses(program)\n"
"        if parsable == 1 then\n"
"            typing = false\n"
"        else if parsable == -1 then\n"
"            duck.println(\"Syntax error.\")\n"
"            duck.print(duck.newline)\n"
"            program = \"\"\n"
"        end\n"
"    loop\n"
"    ; duck.print(duck.newline)\n"
"    expr = eval(program)\n"
"    if expr or Type(expr) != 'NIL' then\n"
"        duck.print(\">> \")\n"
"        duck.println(expr)\n"
"    end\n"
"    duck.print(duck.newline)\n"
"loop\n";

#endif // __DUCK_MAIN_H

