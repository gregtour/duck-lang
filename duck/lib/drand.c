/*
  Author: Robert Cope

  TODO:
    * Expand beyond basic C random number algorithm?

*/
#include <stdlib.h>
#include "dmath.h"
#include "interpreter.h"

/*Rand.seed(seed_num)*/
int SeedRand(int arg_count){
  VALUE argument = GetRecord("seed_number", gCurrentContext);

  unsigned int seed = TypeInt(argument);
  srand(seed);

  return 0;
}

int GetRand(int arg_count){
    int random_num = rand();

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = random_num;

    return 0;
}

int GetBoundedRand(int arg_count){
    VALUE fb_arg = GetRecord("first_bound", gCurrentContext);
    VALUE sb_arg = GetRecord("second_bound", gCurrentContext);

    int num = 0;
    int lower_bound = TypeInt(fb_arg);
    int upper_bound = TypeInt(sb_arg);

    //Swap if user has misordered bounds.
    if(upper_bound < lower_bound){
      int tmp = lower_bound;
      lower_bound = upper_bound;
      upper_bound = tmp;
    }

    num = (rand() % (upper_bound - lower_bound)) + lower_bound;

    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = num;

    return 0;


}

int GetBoundedRandFloat(int arg_count){
    VALUE fb_arg = GetRecord("first_bound", gCurrentContext);
    VALUE sb_arg = GetRecord("second_bound", gCurrentContext);

    float num = 0;
    float lower_bound = TypeFloat(fb_arg);
    float upper_bound = TypeFloat(sb_arg);

    //Swap if user has misordered bounds.
    if(upper_bound < lower_bound){
      float tmp = lower_bound;
      lower_bound = upper_bound;
      upper_bound = tmp;
    }


    num =  (rand() * (upper_bound - lower_bound))/(RAND_MAX + 1.0) + lower_bound;

    gLastExpression.type = VAL_FLOATING_POINT;
    gLastExpression.data.floatp = num;

    return 0;


}

void BindRandLibrary()
{
  VALUE rand_lib = LinkNamespace("Rand");

  //Trig and inverse trig functions.
  VALUE rand_seedrand = CreateFunction(SeedRand);
  AddParameter(rand_seedrand, "seed_number");
  LinkFunction(rand_lib, "seed", rand_seedrand);

  VALUE rand_getrand = CreateFunction(GetRand);
  LinkFunction(rand_lib, "rand", rand_getrand);

  VALUE rand_getboundedrand = CreateFunction(GetBoundedRand);
  AddParameter(rand_getboundedrand, "first_bound");
  AddParameter(rand_getboundedrand, "second_bound");
  LinkFunction(rand_lib, "boundedrand", rand_getboundedrand);
  VALUE rand_getrandfloat = CreateFunction(GetBoundedRandFloat);
  AddParameter(rand_getrandfloat, "first_bound");
  AddParameter(rand_getrandfloat, "second_bound");
  LinkFunction(rand_lib, "randfloat", rand_getrandfloat);
}
