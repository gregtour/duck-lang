/* interpreter.h */
#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "lr_parser.h"
#include "duck.h"

/* constants */
#define VAL_NIL             0
#define VAL_PRIMITIVE       1
#define VAL_STRING          2
#define VAL_REFERENCE       3
#define VAL_FUNCTION        4
#define VAL_FLOATING_POINT  5

/* types */

struct CONTEXT;
struct PAIR;

typedef struct FUNCTION
{
    struct PAIR* parameters;
    SYNTAX_TREE* body;
    unsigned int    built_in;
    int (*functor)(int);
	struct CONTEXT* closure;
} FUNCTION;

typedef struct VALUE
{
    int         type;
    int         primitive;
    float       floatp;
    const char* string;
    struct CONTEXT* reference;
    FUNCTION*   function;
} VALUE;

typedef struct PAIR
{
    const char* identifier;
    VALUE       value;
    struct PAIR* next;
} PAIR;

typedef struct CONTEXT
{
    PAIR*       list;
    struct CONTEXT* parent;
} CONTEXT;

/* memory allocation */
void* ALLOCATE(size_t amount);
/* void  FREE(void* data_ptr); */
void CreateEnvironment();
void  FreeEnvironment();

/* library routines */
VALUE LinkNamespace(const char* identifier);
VALUE CreateFunction(int (*function)(int));
void  AddParameter(VALUE functor, 
                   const char* argument_name);
void  LinkFunction(VALUE namespace, 
                   const char* identifier, 
                   VALUE function);

/* execution context */
extern CONTEXT* gGlobalContext;
extern CONTEXT* gCurrentContext;
extern VALUE    gLastExpression;
extern PAIR*    gParameterListing;
extern CONTEXT* gDictionaryInit;
extern int      gArrayIndex;
extern PAIR*    gArgumentEvaluation;

extern const char* gLValueIdentifier;
extern CONTEXT* gLValueContext;

extern int returning;
extern int breaking;
extern int continuing;

/* functions */
void PrintContext(CONTEXT* context);
VALUE GetRecord(const char* identifier, CONTEXT* context);
void  StoreRecord(const char* identifier, VALUE value, CONTEXT* context);

/* type-casting */
float CoerceFloat(VALUE val);

#endif // _INTERPRETER_H

