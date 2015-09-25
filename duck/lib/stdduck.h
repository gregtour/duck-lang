/* Duck Programming Language Standard Library */
#ifndef _STDDUCK_H
#define _STDDUCK_H

#include "interpreter.h"

extern unsigned int start_t;

char* ToString(VALUE value);

void PrintValue(VALUE);
void PrintFunction(FUNCTION*);
void PrintObject(CLOSURE*);
void PrintDictionary(struct HASH_TABLE*);

void BindStandardLibrary();
void BindStringLibrary();

int DuckEval(int argument_count, void* data);
int DuckParses(int argument_count, void* data);
int DuckPrint(int argument_count, void* data);
int DuckPrompt(int argument_count, void* data);
int DuckType(int argument_count, void* data);
int DuckInt(int argument_count, void* data);
int DuckFloat(int argument_count, void* data);
int DuckLength(int argument_count, void* data);
int DuckQuit(int argument_count, void* data);

int DuckTime(int argument_count, void* data);

#endif // _STDDUCK_H

