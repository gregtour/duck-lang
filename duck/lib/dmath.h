/* Duck Programming Language Math Library */
#ifndef _DMATH_H
#define _DMATH_H

#include "interpreter.h"

void BindMathLibrary();
int MathSin(int arg_count);
int MathCos(int arg_count);
int MathTan(int arg_count);
int MathAsin(int arg_count);
int MathAcos(int arg_count);
int MathAtan(int arg_count);
int MathPow(int arg_count);

#endif // _STDDUCK_H
