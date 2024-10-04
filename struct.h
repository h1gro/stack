#ifndef IFDEF_CONST
#define IFDEF_CONST

#include <stdlib.h>

typedef double stackelem_t;

struct stack_t
{
    stackelem_t *data;
    int size;
    int capacity;
    int error_code;
};

#endif
