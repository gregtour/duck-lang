/*
Author: Robert Cope

These are thin wrappers over the C math libraries.
*/

#include <math.h>
#include "dmath.h"
#include "interpreter.h"

int MathSin(int arg_count){
  int error = 0;
  float angle = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("angle", gCurrentContext);


  if(argument.type == VAL_FLOATING_POINT){
    angle = argument.floatp;
  }
  else if(argument.type == VAL_PRIMITIVE){
    angle = argument.primitive*1.0;
  }

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


  if(argument.type == VAL_FLOATING_POINT){
    angle = argument.floatp;
  }
  else if(argument.type == VAL_PRIMITIVE){
    angle = argument.primitive*1.0;
  }

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


  if(argument.type == VAL_FLOATING_POINT){
    angle = argument.floatp;
  }
  else if(argument.type == VAL_PRIMITIVE){
    angle = argument.primitive*1.0;
  }

  val = tan(angle);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathAsin(int arg_count){
  int error = 0;
  float input = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("input", gCurrentContext);


  if(argument.type == VAL_FLOATING_POINT){
    input = argument.floatp;
  }
  else if(argument.type == VAL_PRIMITIVE){
    input = argument.primitive*1.0;
  }

  val = asin(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathAcos(int arg_count){
  int error = 0;
  float input = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("input", gCurrentContext);


  if(argument.type == VAL_FLOATING_POINT){
    input = argument.floatp;
  }
  else if(argument.type == VAL_PRIMITIVE){
    input = argument.primitive*1.0;
  }

  val = acos(input);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

int MathAtan(int arg_count){
  int error = 0;
  float input = 0.0;
  float val = 0.0;
  VALUE argument = GetRecord("input", gCurrentContext);


  if(argument.type == VAL_FLOATING_POINT){
    input = argument.floatp;
  }
  else if(argument.type == VAL_PRIMITIVE){
    input = argument.primitive*1.0;
  }

  val = atan(input);

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

  if(base_arg.type == VAL_FLOATING_POINT){
    base = base_arg.floatp;
  }
  else if(base_arg.type == VAL_PRIMITIVE){
    base = base_arg.primitive*1.0;
  }

  if(exp_arg.type == VAL_FLOATING_POINT){
    exponent = exp_arg.floatp;
  }
  else if(exp_arg.type == VAL_PRIMITIVE){
    exponent = exp_arg.primitive*1.0;
  }

  val = pow(base, exponent);

  gLastExpression.type = VAL_FLOATING_POINT;
  gLastExpression.floatp = val;

  return error;
}

void BindMathLibrary()
{
    VALUE mathLib = LinkNamespace("math");

    //Trig and inverse trig functions.
    VALUE dcos = CreateFunction(MathCos);
    AddParameter(dcos, "angle");
    LinkFunction(mathLib, "cos", dcos);

    VALUE dsin = CreateFunction(MathSin);
    AddParameter(dsin, "angle");
    LinkFunction(mathLib, "sin", dsin);

    VALUE dtan = CreateFunction(MathTan);
    AddParameter(dtan, "angle");
    LinkFunction(mathLib, "tan", dtan);

    VALUE dasin = CreateFunction(MathAsin);
    AddParameter(dasin, "input");
    LinkFunction(mathLib, "asin", dasin);

    VALUE dacos = CreateFunction(MathAcos);
    AddParameter(dacos, "input");
    LinkFunction(mathLib, "acos", dacos);

    VALUE datan = CreateFunction(MathAtan);
    AddParameter(datan, "input");
    LinkFunction(mathLib, "atan", datan);


    LinkConstFloatp(mathLib, "pi", 3.14159);

    LinkConstPrimitive(mathLib, "test", 3);

    //Exponentials and logs


    //Power function
    VALUE dpow = CreateFunction(MathPow);
    AddParameter(dpow, "base");
    AddParameter(dpow, "exponent");
    LinkFunction(mathLib, "pow", dpow);

}
