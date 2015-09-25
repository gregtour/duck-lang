/* interpreter.h */
#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "lr_parser.h"
#include "duck.h"
#include "types.h"

/* memory allocation */
void* ALLOCATE(size_t amount);
/* void  FREE(void* data_ptr); */
void CreateEnvironment();
void  FreeEnvironment();

/* library routines */
VALUE LinkNamespace(const char* identifier);
VALUE CreateFunction(int (*function)(int, void*));
void  AddParameter(VALUE functor,
                   const char* argument_name);
void  LinkFunction(VALUE ref_namespace,
                   const char* identifier,
                   VALUE function);
void  LinkConstPrimitive(VALUE ref_namespace,
                         const char* identifier,
                         long long int value);
void  LinkConstFloatp(VALUE ref_namespace,
                      const char* identifier,
                      long double value);
void  LinkConstString(VALUE ref_namespace,
                      const char* identifier,
                      const char* string);

/* execution context */
extern CLOSURE* gGlobalContext;
extern CLOSURE* gCurrentContext;
extern VALUE    gLastExpression;
extern PAIR*    gParameterListing;
//extern CLOSURE* gDictionaryInit;
extern struct HASH_TABLE* gDictionaryInit;
extern long int  gArrayIndex;
extern PAIR*     gArgumentEvaluation;
extern CALLSTACK gStackTrace;


typedef struct 
CONTEXT_STACK {
    CLOSURE*    context;
    struct CONTEXT_STACK* prev;
    struct CONTEXT_STACK* next;
} CONTEXT_STACK;

extern CONTEXT_STACK*   gExecutionStack;
void PushExecutionStack(CLOSURE* context);
int  PopExecutionStack();

extern const char* gLValueIdentifier;
extern CLOSURE*    gLValueContext;
extern VALUE       gLValueStringReference;
extern VALUE       gLValueIndex;
extern struct HASH_TABLE* gLValueDictionary;

extern int array_indexing;

extern int returning;
extern int breaking;
extern int continuing;
extern int halting;

extern int stack_depth;
extern int greatest_stack_depth;

extern int line_error;
extern SYNTAX_TREE* failed_production;

extern int gc_collect_count;
extern int gc_inst_count;

extern long int test_inst_count;;

//extern int return_value_exists;

/* functions */
void PrintContext(CLOSURE* context);
VALUE GetRecord(const char* identifier, CLOSURE* context);
void  StoreRecord(const char* identifier, VALUE value, CLOSURE* context);

/* type-casting */
//long double TypeFloat(VALUE value);
//long int TypeInt(VALUE value);

/* interpreter */
int Interpret(SYNTAX_TREE*);
/* remove redundant abstract syntax tree branches */
void ReduceProgramAST(SYNTAX_TREE**);

/* stack trace */
void ClearCallStack(CALLSTACK*);
void PushCallStack(CALLSTACK*, FUNCTION*);
//void PushCallStack(CALLSTACK*, const char*);
void PrintStackTrace();

/* error */
extern const char* ErrorMessage(int error);

/* extended precision floating-point support */

#define _SUPPORTS_80BIT_FLOATING_POINT       (sizeof(long double) > sizeof(double))

/* Unit tests */
#define  TEST_INST_LIMIT            1048576

#endif // _INTERPRETER_H

