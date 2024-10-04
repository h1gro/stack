#ifndef IFDEF_CONST
#define IFDEF_CONST

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STACK_CHECK(stk) (StackCheck(stk, __FILE__, __LINE__, __func__));
#define CHECKER() stk->error_code =

//on/off debug mode
#define DEBUG 153.153

// the poison element
#define POISON -153.153

// 0 level - checks;
// 1 level - asserts + checks;
#define LEVEL_OF_PROTECTION 1

#ifdef DEBUG
    #define ON_DEBUG(code)code
#else
    #define ON_DEBUG(code)
#endif

#ifdef DEBUG
    #define INIT(name) __FILE__, __LINE__, __func__, #name  //TODO CTOR()
#else
    #define INIT(name)
#endif

typedef double stackelem_t;

enum errors
{
    NO_ERRORS      = 0,
    PUSH_ERROR     = 1,
    POP_ERROR      = 2,
    CTOR_ERROR     = 3,
    STK_ERROR      = 4,
    CAPACITY_ERROR = 5,
    SIZE_ERROR     = 6,
    ERROR          = 7
};

enum stack
{
    CAPACITY     = 10,
    CAPAC_RESIZE = 2,
    CAPAC_SHIFT  = 4
};

struct stack_t
{
#ifdef DEBUG
    const char* file;
    const int   line;
    const char* func;
    const char* name;
#endif
    stackelem_t *data;
    int size;
    int capacity;
    int error_code;
};

int CheckForErrors(struct stack_t *stk);
int StackCheck(struct stack_t *stk, const char* file, int line, const char* func);
void StackPush(struct stack_t *stk, stackelem_t elem);
void StackCtor(struct stack_t *stk);
void StackDump(struct stack_t *stk, const char* func, const char* file, int line);
void StackDtor(struct stack_t *stk);
void StackErrorOutput(struct stack_t *stk);
void StackResize(struct stack_t *stk);
stackelem_t StackPop(struct stack_t *stk);

#endif
