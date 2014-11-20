/* Duck Programming Language Standard Library */
#ifndef _STDDUCK_H
#define _STDDUCK_H

#include "interpreter.h"

void PrintValue(VALUE);
void PrintFunction(FUNCTION*);
void PrintDictionary(struct HASH_TABLE*);
void PrintObject(CONTEXT*);

void BindStandardLibrary();

int DuckPrint(int argument_count);
int DuckPrompt(int argument_count);
int DuckType(int argument_count);
int DuckInt(int argument_count);
int DuckLength(int argument_count);

#endif // _STDDUCK_H

