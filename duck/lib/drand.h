/* Duck Programming Language Random Numbers Library */
#ifndef _DRAND_H
#define _DRAND_H

#include "interpreter.h"
#include <stdint.h>

uint64_t XORShiftNext();

void BindRandLibrary();
int SeedRand(int arg_count, void* data);
int GetRand(int arg_count, void* data);
int GetBoundedRandFloat(int arg_count, void* data);
#endif // _LIBRARY_H
