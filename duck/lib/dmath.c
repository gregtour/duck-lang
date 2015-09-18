/*
Author: Robert Cope

These are thin wrappers over the C math libraries.
TODO:
  * Add Hyperbolic Trig functions?
  * Add other non-math.h functions?
  * Fault handling?

*/

#include <math.h>
#include "dmath.h"
#include "interpreter.h"

/*Math.sin(angle)*/
int MathSin(int arg_count, void* data){
  long double angle = 0.0;
  long double val = 0.0;
  VALUE argument = GetRecord("angle", gCurrentContext);

  angle = TypeFloat(argument);
  val = sin(angle);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.cos(angle)*/
int MathCos(int arg_count, void* data){
  long double angle = 0.0;
  long double val = 0.0;
  VALUE argument = GetRecord("angle", gCurrentContext);

  angle = TypeFloat(argument);
  val = cos(angle);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.tan(angle)*/
int MathTan(int arg_count, void* data){
  long double angle = 0.0;
  long double val = 0.0;
  VALUE argument = GetRecord("angle", gCurrentContext);

  angle = TypeFloat(argument);
  val = tan(angle);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.asin(num)*/
int MathAsin(int arg_count, void* data){
  long double input = 0.0;
  long double val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);
  val = asin(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.acos(num)*/
int MathAcos(int arg_count, void* data){
  long double input = 0.0;
  long double val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);
  val = acos(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.atan(num)*/
int MathAtan(int arg_count, void* data){
  long double input = 0.0;
  long double val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);
  val = atan(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.atan2(num)*/
int MathAtan2(int arg_count, void* data){
  long double input = 0.0;
  long double input2 = 0.0;
  long double val = 0.0;
  VALUE argument1 = GetRecord("opp", gCurrentContext);
  VALUE argument2 = GetRecord("adj", gCurrentContext);

  input = TypeFloat(argument1);
  input2 = TypeFloat(argument2);
  val = atan2(input, input2);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.exp(num)*/
int MathExp(int arg_count, void* data){
  long double input = 0.0;
  long double val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);
  val = exp(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.log(num)*/
int MathLog(int arg_count, void* data){
  long double input = 0.0;
  long double val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);
  val = log(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.log10(num)*/
int MathLog10(int arg_count, void* data){
  long double input = 0.0;
  long double val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);
  val = log10(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.pow(base, exponent)*/
int MathPow(int arg_count, void* data){
  long double base = 0.0;
  long double exponent = 0.0;
  long double val = 0.0;

  VALUE base_arg = GetRecord("base", gCurrentContext);
  VALUE exp_arg = GetRecord("exponent", gCurrentContext);

  base = TypeFloat(base_arg);
  exponent = TypeFloat(exp_arg);

  val = pow(base, exponent);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.sqrt(num))*/
int MathSqrt(int arg_count, void* data){
  long double input = 0.0;
  long double val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);

  val = sqrt(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.ceil(num)*/
int MathCeil(int arg_count, void* data){
  long double input = 0.0;
  long double val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);

  val = ceil(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.floor(num)*/
int MathFloor(int arg_count, void* data){
  long double input = 0.0;
  long double val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);

  val = floor(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

/*Math.abs(num)*/
int MathAbs(int arg_count, void* data){
  long double input = 0.0;
  long double val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);

  val = fabs(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.data.floatp = val;

  return 0;
}

void BindMathLibrary()
{
    VALUE math_lib = LinkNamespace("math");

    //Trig and inverse trig functions.
    VALUE dcos = CreateFunction(MathCos);
    AddParameter(dcos, "angle");
    LinkFunction(math_lib, "cos", dcos);

    VALUE dsin = CreateFunction(MathSin);
    AddParameter(dsin, "angle");
    LinkFunction(math_lib, "sin", dsin);

    VALUE dtan = CreateFunction(MathTan);
    AddParameter(dtan, "angle");
    LinkFunction(math_lib, "tan", dtan);

    VALUE dasin = CreateFunction(MathAsin);
    AddParameter(dasin, "num");
    LinkFunction(math_lib, "asin", dasin);

    VALUE dacos = CreateFunction(MathAcos);
    AddParameter(dacos, "num");
    LinkFunction(math_lib, "acos", dacos);

    VALUE datan = CreateFunction(MathAtan);
    AddParameter(datan, "num");
    LinkFunction(math_lib, "atan", datan);

    VALUE datan2 = CreateFunction(MathAtan2);
    AddParameter(datan2, "opp");
    AddParameter(datan2, "adj");
    LinkFunction(math_lib, "atan2", datan2);

    //LinkConstFloatp(math_lib, "pi", 4* atan(1.0L));
    //LinkConstFloatp(math_lib, "pi", 3.141592653589793238);
    LinkConstFloatp(math_lib, "pi", 3.1415926535897932384626L);

    //Exponentials and logs
    VALUE dexp = CreateFunction(MathExp);
    AddParameter(dexp, "num");
    LinkFunction(math_lib, "exp", dexp);

    VALUE dlog = CreateFunction(MathLog);
    AddParameter(dlog, "num");
    LinkFunction(math_lib, "log", dlog);

    VALUE dlog10 = CreateFunction(MathLog10);
    AddParameter(dlog10, "num");
    LinkFunction(math_lib, "log10", dlog10);

    //Power functions
    VALUE dpow = CreateFunction(MathPow);
    AddParameter(dpow, "base");
    AddParameter(dpow, "exponent");
    LinkFunction(math_lib, "pow", dpow);

    VALUE dsqrt = CreateFunction(MathSqrt);
    AddParameter(dsqrt, "num");
    LinkFunction(math_lib, "sqrt", dsqrt);

    //Misc Functions
    VALUE dceil = CreateFunction(MathCeil);
    AddParameter(dceil, "num");
    LinkFunction(math_lib, "ceil", dceil);

    VALUE dfloor = CreateFunction(MathFloor);
    AddParameter(dfloor, "num");
    LinkFunction(math_lib, "floor", dfloor);

    VALUE dabs = CreateFunction(MathAbs);
    AddParameter(dabs, "num");
    LinkFunction(math_lib, "abs", dabs);
}
