/* Duck Programming Language Math Library */
#ifndef _DMATH_H
#define _DMATH_H

#include "interpreter.h"


void BindMathLibrary();
//Trig functions.
int MathSin(int arg_count, void* data);
int MathCos(int arg_count, void* data);
int MathTan(int arg_count, void* data);
int MathAsin(int arg_count, void* data);
int MathAcos(int arg_count, void* data);
int MathAtan(int arg_count, void* data);
int MathAtan2(int arg_count, void* data);
//Exponents and logs.
int MathExp(int arg_count, void* data);
int MathLog(int arg_count, void* data);
int MathLog10(int arg_count, void* data);
//Power functions.
int MathPow(int arg_count, void* data);
int MathSqrt(int arg_count, void* data);
//Misc functions
int MathCeil(int arg_count, void* data);
int MathFloor(int arg_count, void* data);
int MathAbs(int arg_count, void* data);

#endif // _STDDUCK_H
