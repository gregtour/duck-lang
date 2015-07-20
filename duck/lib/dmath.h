/* Duck Programming Language Math Library */
#ifndef _DMATH_H
#define _DMATH_H

#include "interpreter.h"


void BindMathLibrary();
//Trig functions.
int MathSin(int arg_count);
int MathCos(int arg_count);
int MathTan(int arg_count);
int MathAsin(int arg_count);
int MathAcos(int arg_count);
int MathAtan(int arg_count);
int MathAtan2(int arg_count);
//Exponents and logs.
int MathExp(int arg_count);
int MathLog(int arg_count);
int MathLog10(int arg_count);
//Power functions.
int MathPow(int arg_count);
int MathSqrt(int arg_count);
//Misc functions
int MathCeil(int arg_count);
int MathFloor(int arg_count);
int MathAbs(int arg_count);

#endif // _STDDUCK_H
