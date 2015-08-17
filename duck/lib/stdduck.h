/* Duck Programming Language Standard Library */
#ifndef _STDDUCK_H
#define _STDDUCK_H

#include "interpreter.h"

extern unsigned int start_t;

char* ToString(VALUE value);

void PrintValue(VALUE);
void PrintFunction(FUNCTION*);
void PrintObject(CONTEXT*);
void PrintDictionary(struct HASH_TABLE*);

void BindStandardLibrary();
void BindStringLibrary();

int DuckEval(int argument_count);
int DuckParses(int argument_count);
int DuckPrint(int argument_count);
int DuckPrompt(int argument_count);
int DuckType(int argument_count);
int DuckInt(int argument_count);
int DuckFloat(int argument_count);
int DuckLength(int argument_count);
int DuckQuit(int argument_count);

int DuckTime(int argument_count);

#endif // _STDDUCK_H

