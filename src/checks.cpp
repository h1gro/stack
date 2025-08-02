#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

#include "../include/global.h"
#include "../include/checks.h"
#include "../include/output.h"
#include "../include/stackfuncs.h"
#include "../include/hash.h"

int StackCheck(struct stack_t *stk, const char* file, int line, const char* func)
{
    if (CheckForErrors(stk) == NO_ERRORS)
    {
        return NO_ERRORS;
    }

    StackDump(stk, func, file, line, ERROR_PRINT);

    return ERROR;
}

int CheckForErrors(struct stack_t *stk)
{
    // assert(stk);
    // assert(stk->data);
    // assert(stk->capacity);
    // assert(stk->size >= 0);
    // assert(fabs(stk->data[-1]            - CANARY) < EPSILON);
    // assert(fabs(stk->data[stk->capacity] - CANARY) < EPSILON);
    // assert(fabs(stk->canary1 - CANARY) < EPSILON);
    // assert(fabs(stk->canary2 - CANARY) < EPSILON);

    stk->error_code = Verifier(stk);

    return stk->error_code;
}

errors Verifier(struct stack_t* stk)
{
    if (stk == NULL)
    {
        return STK_ERROR;
    }

    if (stk->data == NULL)
    {
        return CTOR_ERROR;
    }

    if (stk->output == NULL)
    {
        return FILE_ERROR;
    }

    if (stk->capacity == 0)
    {
        return CAPACITY_ERROR;
    }

    if (stk->size < 0)
    {
        return SIZE_ERROR;
    }

    if (stk->size > stk->capacity)
    {
        return PUSH_ERROR;
    }

    #ifdef FIRST_LP

        if (fabs(stk->data[-1] - CANARY) > EPSILON)
        {
            return CANARY1_BUF_ERROR;
        }

        if (fabs(stk->data[stk->capacity] - CANARY) > EPSILON)
        {
            return CANARY2_BUF_ERROR;
        }

        if (fabs(stk->canary1 - CANARY) > EPSILON)
        {
            return CANARY1_STR_ERROR;
        }

        if (fabs(stk->canary2 - CANARY) > EPSILON)
        {
            return CANARY2_STR_ERROR;
        }

    #endif

    #ifdef SECOND_LP

        if (stk->hash_buffer != HashCalcs(stk->data, stk->size))
        {
            return HASH_BUFFER_ERROR;
        }

        if (stk->hash_struct != HashCalcs(stk, sizeof(stk)))
        {
            return HASH_STRUCT_ERROR;
        }

    #endif

    return NO_ERRORS;
}

