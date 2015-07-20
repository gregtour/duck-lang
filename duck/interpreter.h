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
VALUE CreateFunction(int (*function)(int));
void  AddParameter(VALUE functor,
                   const char* argument_name);
void  LinkFunction(VALUE ref_namespace,
                   const char* identifier,
                   VALUE function);
void  LinkConstPrimitive(VALUE ref_namespace,
                         const char* identifier,
                         int value);
void  LinkConstFloatp(VALUE ref_namespace,
                      const char* identifier,
                      long double value);
void  LinkConstString(VALUE ref_namespace,
                      const char* identifier,
                      const char* string);

/* execution context */
extern CONTEXT* gGlobalContext;
extern CONTEXT* gCurrentContext;
extern VALUE    gLastExpression;
extern PAIR*    gParameterListing;
//extern CONTEXT* gDictionaryInit;
extern struct HASH_TABLE* gDictionaryInit;
extern int      gArrayIndex;
extern PAIR*    gArgumentEvaluation;
extern CALLSTACK gStackTrace;


typedef struct 
CONTEXT_STACK {
    CONTEXT*    context;
    struct CONTEXT_STACK* prev;
    struct CONTEXT_STACK* next;
} CONTEXT_STACK;

extern CONTEXT_STACK*   gExecutionStack;
void PushExecutionStack(CONTEXT* context);
int  PopExecutionStack();

extern const char* gLValueIdentifier;
extern CONTEXT*    gLValueContext;
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

//extern int return_value_exists;

/* functions */
void PrintContext(CONTEXT* context);
VALUE GetRecord(const char* identifier, CONTEXT* context);
void  StoreRecord(const char* identifier, VALUE value, CONTEXT* context);

/* type-casting */
long double TypeFloat(VALUE value);
int TypeInt(VALUE value);

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

/* extended precision floating-point suppport */

#define _SUPPORTS_80BIT_FLOATING_POINT       (sizeof(long double) > sizeof(double))

#endif // _INTERPRETER_H

