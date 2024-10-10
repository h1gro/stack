#include <stdio.h>
#include <assert.h>

#include "global.h"
#include "checks.h"
#include "output.h"

int CheckForErrors(struct stack_t *stk)
{
    #ifdef LEVEL_OF_PROTECTION
        assert(stk);
        assert(stk->data);
        assert(stk->capacity);
        assert(stk->size >= 0);
        assert((long long int)(stk->data[-1] - CANARY) == 0);
        assert((long long int)(stk->data[stk->capacity] - CANARY) == 0);

        #ifdef DEBUG
            assert((long long int)(stk->canary1 - CANARY) == 0);
            assert((long long int)(stk->canary2 - CANARY) == 0);
        #endif

    #endif

    #ifdef DEBUG
        if ((long long int)(stk->canary1 - CANARY) == 0)
        {
            stk->error_code = CANARY1_STR_ERROR;
            return stk->error_code;
        }

        if ((long long int)(stk->canary2 - CANARY) == 0)
        {
            stk->error_code = CANARY2_STR_ERROR;
            return stk->error_code;
        }
    #endif

    if (stk == NULL)
    {
        stk->error_code = STK_ERROR;
        return stk->error_code;
    }

    if (stk->data == NULL)
    {
        stk->error_code = CTOR_ERROR;
        return stk->error_code;
    }

    if (stk->capacity == 0)
    {
        stk->error_code = CAPACITY_ERROR;
        return stk->error_code;
    }

    if (stk->size < 0)
    {
        stk->error_code = SIZE_ERROR;
        return stk->error_code;
    }

    if (stk->size > stk->capacity)
    {
        stk->error_code = PUSH_ERROR;
        return stk->error_code;
    }

    if ((long long int)(stk->data[-1] - CANARY) == 0)
    {
        stk->error_code = CANARY1_BUF_ERROR;
        return stk->error_code;
    }

    if ((long long int)(stk->data[stk->capacity] - CANARY) == 0)
    {
        stk->error_code = CANARY2_BUF_ERROR;
        return stk->error_code;
    }
    return NO_ERRORS;
}

int StackCheck(struct stack_t *stk, const char* file, int line, const char* func)
{
    if (CheckForErrors(stk) == NO_ERRORS)
    {
        return 0;
    }

    int dump_call = ERROR_PRINT;
    StackDump(stk, func, file, line, dump_call);

    return 1;
}
