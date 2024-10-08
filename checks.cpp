#include "prototype.h"

#include <stdio.h>
int CheckForErrors(struct stack_t *stk)
{
    #ifdef LEVEL_OF_PROTECTION
        assert(stk);
        assert(stk->data);
        assert(stk->capacity);
        assert(stk->size >= 0);
        assert((stk->data[-1] - CANARY) < EPSILON ||
               (CANARY - stk->data[-1]) < EPSILON);
        assert((stk->data[stk->capacity] - CANARY) < EPSILON ||
               (CANARY - stk->data[stk->capacity]) < EPSILON);

        #ifdef DEBUG
            assert((stk->canary1 - CANARY) < EPSILON ||
                   (CANARY - stk->canary1) < EPSILON);
            assert((stk->canary2 - CANARY) < EPSILON ||
                   (CANARY - stk->canary2) < EPSILON);
        #endif

    #endif

    #ifdef DEBUG
        if ((stk->canary1 - CANARY) >= EPSILON || (CANARY - stk->canary1) >= EPSILON)
        {
            printf("here %d %s\n", __LINE__, __func__);
            stk->error_code = CANARY1_STR_ERROR;
            return stk->error_code;
        }

        if ((stk->canary2 - CANARY) >= EPSILON || (CANARY - stk->canary2) >= EPSILON)
        {
            printf("here %d %s\n", __LINE__, __func__);
            stk->error_code = CANARY2_STR_ERROR;
            return stk->error_code;
        }
    #endif

    if (stk == NULL) // TODO define
    {
        printf("here %d %s\n", __LINE__, __func__);
        stk->error_code = STK_ERROR;
        return stk->error_code;
    }

    if (stk->data == NULL)
    {
        printf("here %d %s\n", __LINE__, __func__);
        stk->error_code = CTOR_ERROR;
        return stk->error_code;
    }

    if (stk->capacity == 0)
    {
        printf("here %d %s\n", __LINE__, __func__);
        stk->error_code = CAPACITY_ERROR;
        return stk->error_code;
    }

    if (stk->size < 0)
    {
        printf("here %d %s\n", __LINE__, __func__);
        stk->error_code = SIZE_ERROR;
        return stk->error_code;
    }

    if (stk->size > stk->capacity)
    {
        printf("here %d %s\n", __LINE__, __func__);
        stk->error_code = PUSH_ERROR;
        return stk->error_code;
    }

    if ((stk->data[-1] - CANARY) >= EPSILON || (CANARY - stk->data[-1]) >= EPSILON)
    {
        printf("here %d %s\n", __LINE__, __func__);
        stk->error_code = CANARY1_BUF_ERROR;
        return stk->error_code;
    }

    if ((stk->data[stk->capacity] - CANARY) >= EPSILON || (CANARY - stk->data[stk->capacity]) >= EPSILON)
    {
        printf("here %d %s\n", __LINE__, __func__);
        stk->error_code = CANARY2_BUF_ERROR;
        return stk->error_code;
    }
    return NO_ERRORS;
}

int StackCheck(struct stack_t *stk, const char* file, int line, const char* func)
{
    if (CheckForErrors(stk) == NO_ERRORS)
    {
        printf("here %d %s\n", __LINE__, __func__);
        return 0;
    }

    printf("here %d %s\n", __LINE__, __func__);

    int dump_call = NOT_MAIN;
    StackDump(stk, func, file, line, dump_call);

    return 1;
}
