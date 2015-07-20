#ifndef _DUCK_ARITHMETIC_H
#define _DUCK_ARITHMETIC_H

/*
  Basic Math and Logic for the Duck Programming Language
  Addition, Subtraction, Multiplication, Division
  Modulus, and, or, not, or, xor, etc
*/

#include "types.h"

int EvaluatesTrue(VALUE value);

VALUE TrueValue();
VALUE FalseValue();

VALUE Concat(VALUE a, VALUE b);

VALUE Add(VALUE a, VALUE b);
VALUE Subtract(VALUE a, VALUE b);
VALUE Multiply(VALUE a, VALUE b);
VALUE Divide(VALUE a, VALUE b);
VALUE Modulus(VALUE a, VALUE b);

VALUE CompareEquality(VALUE a, VALUE b);
VALUE CompareInequality(VALUE a, VALUE b);

/*VALUE LogicAND(VALUE a, VALUE b);
VALUE LogicOR(VALUE a, VALUE b);
VALUE LogicNOR(VALUE a, VALUE b);*/
VALUE LogicXOR(VALUE a, VALUE b);

VALUE CompareLessThan(VALUE a, VALUE b);
VALUE CompareGreaterThan(VALUE a, VALUE b);
VALUE CompareLessThanOrEqual(VALUE a, VALUE b);
VALUE CompareGreaterThanOrEqual(VALUE a, VALUE b);

#endif // _DUCK_ARITHMETIC_H

