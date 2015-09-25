#ifndef _DUCK_TYPES_H
#define _DUCK_TYPES_H

#include "lr_parser.h"

#ifdef WIN32
#define atoll       _atoi64
#endif

/* constants */
#define VAL_NIL             0
#define VAL_PRIMITIVE       1
#define VAL_STRING          2
#define VAL_REFERENCE       3
#define VAL_FUNCTION        4
#define VAL_FLOATING_POINT  5
#define VAL_DICTIONARY      6

/* floating-point precision */
#define  DOUBLE_EPSILON     (1.0E-12)

/* long long int */
typedef long long int int64;

/* types */

struct CLOSURE;
struct PAIR;

typedef struct FUNCTION
{
    struct PAIR* parameters;
    SYNTAX_TREE* body;
    unsigned int built_in;
    int (*functor)(int, void*);
    struct CLOSURE* closure;
    int ref_count;
    const char* fn_name;
    void* func_data;
} FUNCTION;

struct HASH_TABLE;
typedef struct VALUE
{
    int         type;
    union 
    {
        int64           primitive;
        long double     floatp;
        const char*     string;
        FUNCTION*       function;
        struct CLOSURE* reference;
        struct HASH_TABLE* 
                        dictionary;
    } data;
  int const_string;
} VALUE;

typedef struct PAIR
{
    const char*  identifier;
    VALUE        value;
    struct PAIR* next;
} PAIR;

typedef struct CLOSURE
{
    PAIR*       list;
    int         ref_count;
    struct CLOSURE* parent;
} CLOSURE;

typedef struct CALLSTACK
{
    const char* fn_name;
    FUNCTION* function;
    struct CALLSTACK* next;
} CALLSTACK;

/* casts */

long double TypeFloat(VALUE value);
int64  TypeInt(VALUE value);
int    IsDynamic(VALUE type);
VALUE  CopyString(VALUE string);

#endif // _DUCK_TYPES_H

