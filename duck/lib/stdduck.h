/* Duck Programming Language Standard Library */
#ifndef _STDDUCK_H
#define _STDDUCK_H

#include "interpreter.h"

void BindStandardLibrary();
int DuckPrint(int argument_count);
int DuckPrompt(int argument_count);
/* int Length(int argument_count); */
void PrintObject(CONTEXT*);

#endif // _STDDUCK_H

