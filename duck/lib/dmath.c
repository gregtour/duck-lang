/*
Author: Robert Cope

These are thin wrappers over the C math libraries.
TODO:
  * Add Hyperbolic Trig functions?
  * Add other non-math.h functions?

*/

#include <math.h>
#include "dmath.h"
#include "interpreter.h"

int MathSin(int arg_count){
  int error = 0;
  float angle = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("angle", gCurrentContext);

  angle = TypeFloat(argument);
  val = sin(angle);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathCos(int arg_count){
  int error = 0;
  float angle = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("angle", gCurrentContext);

  angle = TypeFloat(argument);
  val = cos(angle);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathTan(int arg_count){
  int error = 0;
  float angle = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("angle", gCurrentContext);

  angle = TypeFloat(argument);
  val = tan(angle);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathAsin(int arg_count){
  int error = 0;
  float input = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);
  val = asin(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathAcos(int arg_count){
  int error = 0;
  float input = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);
  val = acos(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathAtan(int arg_count){
  int error = 0;
  float input = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);
  val = atan(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathExp(int arg_count){
  int error = 0;
  float input = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);
  val = exp(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathLog(int arg_count){
  int error = 0;
  float input = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);
  val = log(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathLog10(int arg_count){
  int error = 0;
  float input = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);
  val = log10(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}


int MathPow(int arg_count){
  int error = 0;
  float base = 0.0;
  float exponent = 0.0;
  float val = 0.0;

  VALUE base_arg = GetRecord("base", gCurrentContext);
  VALUE exp_arg = GetRecord("exponent", gCurrentContext);

  base = TypeFloat(base_arg);
  exponent = TypeFloat(exp_arg);

  val = pow(base, exponent);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathSqrt(int arg_count){
  int error = 0;
  float input = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);

  val = sqrt(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathCeil(int arg_count){
  int error = 0;
  float input = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);

  val = ceil(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathFloor(int arg_count){
  int error = 0;
  float input = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);

  val = floor(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}


int MathAbs(int arg_count){
  int error = 0;
  float input = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("num", gCurrentContext);

  input = TypeFloat(argument);

  val = fabs(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

void BindMathLibrary()
{
    VALUE math_lib = LinkNamespace("Math");

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


    LinkConstFloatp(math_lib, "pi", 3.14159);

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
