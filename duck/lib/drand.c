/*
  Duck Language Random Number Library
  Author: Robert Cope

  TODO:
    * More functions?
    * Clean up code, make sure implementation of XORSHIFT works well.

*/
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <limits.h>
#include <math.h>

#include "drand.h"
#include "interpreter.h"


/*  XORShift128+ Written in 2014 by Sebastiano Vigna (vigna@acm.org)

To the extent possible under law, the author has dedicated all copyright
and related and neighboring rights to this software to the public domain
worldwide. This software is distributed without any warranty.

See <http://creativecommons.org/publicdomain/zero/1.0/>. */

uint64_t xorshift_seed[ 2 ] = {0x021f9c6a70ca0c24ULL, 0xbae766b26645aa22ULL};

uint64_t XORShiftNext() {
    uint64_t s1 = xorshift_seed[ 0 ];
    const uint64_t s0 = xorshift_seed[ 1 ];
    xorshift_seed[ 0 ] = s0;
    s1 ^= s1 << 23; // a
    return ( xorshift_seed[ 1 ] = ( s1 ^ s0 ^ ( s1 >> 17 ) ^ ( s0 >> 26 ) ) ) + s0; // b, c
}


const uint64_t XORSHIFT_MAX = 0xffffffffffffffffULL;


/*Rand.seed((OPTIONAL) seed_num)*/
/*If no seed given, will seed using current UNIX second.*/
/*Returns the seed used.*/
int SeedRand(int arg_count, void* data){
  VALUE argument = GetRecord("seed_number", gCurrentContext);

  //TODO: Seeding the XORSHIFT128+ with the built in generator is somewhat questionable.
  int seed = 0;
  if(argument.type != VAL_NIL) {
    seed = TypeInt(argument);
  } else {
    seed = (int)time(NULL);
  }

  srand(seed);
  //Seed the XORSHIFT128+ PRNG with whatever junky random number generator was built in.
  xorshift_seed[0] = ((long long)rand() << 32) | rand();
  xorshift_seed[1] = ((long long)rand() << 32) | rand();

  gLastExpression.type = VAL_PRIMITIVE;
  gLastExpression.data.primitive = seed;

  return 0;
}


/*Rand.rand((OPTIONAL) first_bound, (OPTIONAL) second_bound)*/
/*Returns a random primitive*/
int GetBoundedRand(int arg_count, void* data){
    VALUE fb_arg = GetRecord("first_bound", gCurrentContext);
    VALUE sb_arg = GetRecord("second_bound", gCurrentContext);

    int num = 0;
    long lower_bound = 0;
    long upper_bound = 0;
    if(fb_arg.type != VAL_NIL)
        lower_bound = TypeInt(fb_arg);
    else
        lower_bound = INT_MIN;
    if(sb_arg.type != VAL_NIL)
        upper_bound = TypeInt(sb_arg);
    else
        upper_bound = INT_MAX;

    //Swap if user has misordered bounds..
    if(upper_bound < lower_bound){
      int tmp = lower_bound;
      lower_bound = upper_bound;
      upper_bound = tmp;
    }

    //TODO: Fix this hack.
    num = (int)((XORShiftNext() & UINT_MAX) % (upper_bound - lower_bound + 1)) + lower_bound;
    gLastExpression.type = VAL_PRIMITIVE;
    gLastExpression.data.primitive = num;

    return 0;
}


/*Rand.randfloat(first_bound, second_bound)*/
/*Returns a random float.*/
int GetBoundedRandFloat(int arg_count, void* data){
    VALUE fb_arg = GetRecord("first_bound", gCurrentContext);
    VALUE sb_arg = GetRecord("second_bound", gCurrentContext);

    long double num = 0;
    long double lower_bound = TypeFloat(fb_arg);
    long double upper_bound = TypeFloat(sb_arg);

    //Swap if user has misordered bounds.
    if(upper_bound < lower_bound){
      long double tmp = lower_bound;
      lower_bound = upper_bound;
      upper_bound = tmp;
    }


    num =   (XORShiftNext() * (upper_bound - lower_bound))/(XORSHIFT_MAX) + lower_bound;

    gLastExpression.type = VAL_FLOATING_POINT;
    gLastExpression.data.floatp = num;

    return 0;
}


void BindRandLibrary()
{
  VALUE rand_lib = LinkNamespace("rand");

  //Trig and inverse trig functions.
  VALUE rand_seedrand = CreateFunction(SeedRand);
  AddParameter(rand_seedrand, "seed_number");
  LinkFunction(rand_lib, "seed", rand_seedrand);

  VALUE rand_getrand = CreateFunction(GetBoundedRand);
  AddParameter(rand_getrand, "first_bound");
  AddParameter(rand_getrand, "second_bound");
  LinkFunction(rand_lib, "randint", rand_getrand);

  VALUE rand_getrandfloat = CreateFunction(GetBoundedRandFloat);
  AddParameter(rand_getrandfloat, "first_bound");
  AddParameter(rand_getrandfloat, "second_bound");
  LinkFunction(rand_lib, "randfloat", rand_getrandfloat);
}
