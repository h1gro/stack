#ifndef IFDEF_CONST
#define IFDEF_CONST

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STACK_CHECK(stk) (StackCheck(stk, __FILE__, __LINE__, __func__));

//on/off debug mode
#define DEBUG 153.153

// 0 level - checks;
// 1 level - asserts + checks;
#define LEVEL_OF_PROTECTION 1

#ifdef DEBUG
    #define ON_DEBUG(code)code
#else
    #define ON_DEBUG(code)
#endif

#ifdef DEBUG
    #define INIT(canary ,name) canary ,__FILE__, __LINE__, __func__, #name  //TODO CTOR()
#else
    #define INIT(name)
#endif

typedef double stackelem_t;

const stackelem_t POISON  = -153.153;
const stackelem_t CANARY  = 531.531;
const stackelem_t EPSILON = 1E-9;

enum errors
{
    NO_ERRORS           = 0,
    PUSH_ERROR          = 1,
    POP_ERROR           = 2,
    CTOR_ERROR          = 3,
    STK_ERROR           = 4,
    CAPACITY_ERROR      = 5,
    SIZE_ERROR          = 6,
    CANARY1_BUF_ERROR   = 7,
    CANARY2_BUF_ERROR   = 8,
    CANARY1_STR_ERROR   = 9,
    CANARY2_STR_ERROR   = 10,
    ERROR               = 11
};

enum stack
{
    CAPACITY     = 10,
    CAPAC_RESIZE = 2,
    CAPAC_SHIFT  = 4
};

enum call_funcs
{
    PUSH     = 777,
    POP      = 666,
    MAIN     = 555,
    NOT_MAIN = 444,
};

enum canaries
{
    NUM_CANARIES_BUF      = 2,
    NUM_CANARIES_STR      = 2,
    NUM_CANARIES_IN_RIGHT = 1,
    NUM_CANARIES_IN_LEFT  = 1
};

struct stack_t
{
#ifdef DEBUG
    stackelem_t canary1;
    const char* file;
    const int   line;
    const char* func;
    const char* name;
#endif
    stackelem_t *data;
    int size;
    int capacity;
    int error_code;
#ifdef DEBUG
    stackelem_t canary2;
#endif
};

int CheckForErrors(struct stack_t *stk);
int StackCheck(struct stack_t *stk, const char* file, int line, const char* func);


void StackCtor(struct stack_t *stk);
void StackDtor(struct stack_t *stk);
void FillingDataPoison(struct stack_t *stk);
void StackErrorOutput(struct stack_t *stk);
void StackPush(struct stack_t *stk, stackelem_t elem);
void ResizeIf(struct stack_t *stk, bool is_pop_or_push);
void StackDump(struct stack_t *stk, const char* func, const char* file, int line, int dump_call);



stackelem_t StackPop(struct stack_t *stk);

#endif
