/* Duck Programming Language Random Numbers Library */
#ifndef _DRANG_H
#define _DRAND_H

#include "interpreter.h"
#include <stdint.h>

uint64_t XORShiftNext();

void BindRandLibrary();
int SeedRand(int arg_count);
int GetRand(int arg_count);
int GetBoundedRandFloat(int arg_count);
#endif // _LIBRARY_H
