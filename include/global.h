#ifndef IFDEF_CONST
#define IFDEF_CONST

#define STACK_CHECK(stk) (StackCheck(stk, __FILE__, __LINE__, __func__));

//on/off debug mode
#define DEBUG 153.153

//----------------------------------------------------
// Levels of protection:
// ZERO_LP   no protection
// FIRST_LP  canaries in buffer and in struct
// SECOND_LP canaries + hash in buffer and in struct

//Uncomment only one mode! Don't mixe!
//================
//#define ZERO_LP
//#define FIRST_LP
#define SECOND_LP
//================

#ifndef ZERO_LP
    #ifdef  SECOND_LP
        #define FIRST_LP
    #endif
#endif
//----------------------------------------------------

#ifdef FIRST_LP
    #ifdef DEBUG
        #define INIT(canary, name) canary, __LINE__, __FILE__, __func__, #name
    #else
        #define INIT(canary)
    #endif
#else
    #ifdef DEBUG
        #define INIT(name) __LINE__, __FILE__, __func__, #name
    #else
        #define INIT()
    #endif
#endif

typedef double stackelem_t;

static const char* DUMP_FILE = "dump.txt";

const stackelem_t POISON  = -153.153;
const stackelem_t CANARY  = 531.531;
const stackelem_t EPSILON = 1e-4;

enum errors
{
    NO_ERRORS         = 0,
    PUSH_ERROR        = 1,
    POP_ERROR         = 2,
    CTOR_ERROR        = 3,
    STK_ERROR         = 4,
    CAPACITY_ERROR    = 5,
    SIZE_ERROR        = 6,
    CANARY1_BUF_ERROR = 7,
    CANARY2_BUF_ERROR = 8,
    CANARY1_STR_ERROR = 9,
    CANARY2_STR_ERROR = 10,
    ERROR             = 11,
    HASH_BUFFER_ERROR = 12,
    HASH_STRUCT_ERROR = 13,
    FILE_ERROR        = 14,
    MY_PUSH_ERROR     = 20,
};

enum stack
{
    SIZE_OF_ELEM = 1,
    CAPAC_RESIZE = 2,
    CAPACITY     = 3,
    CAPAC_SHIFT  = 4,
};

enum call_funcs
{
    ERROR_PRINT = 444,
    INFO_PRINT  = 555,
    POP         = 666,
    PUSH        = 777,
};

enum canaries
{
    NUM_CANARIES_IN_LEFT  = 1,
    NUM_CANARIES_IN_RIGHT = 1,
    NUM_CANARIES_BUF      = 2,
    NUM_CANARIES_STR      = 2,
};

struct stack_t
{
    #ifdef FIRST_LP
    stackelem_t canary1;
    #endif

    #ifdef DEBUG
        const int   line;
        const char* file;
        const char* func;
        const char* name;
    #endif

    #ifdef SECOND_LP
    uint_least32_t hash_buffer;
    uint_least32_t hash_struct;
    #endif

    stackelem_t* data;
    FILE* output;
    int size;
    int capacity;
    int error_code;

    #ifdef FIRST_LP
        stackelem_t canary2;
    #endif
};

#endif
