#include "prototype.h"

int CheckForErrors(struct stack_t *stk)
{
    #ifdef LEVEL_OF_PROTECTION
        assert(stk);
        assert(stk->data);
        assert(stk->capacity);
        #ifndef ID_SIZE
            assert(stk);
        #endif
    #endif

    if (stk == NULL) //TODO define
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

    #ifdef ID_SIZE
        if (stk->size == 0)
        {
            printf("here %d %s\n", __LINE__, __func__);
            stk->error_code = SIZE_ERROR;
            return stk->error_code;
        }
    #endif

    if (stk->size > stk->capacity)
    {
        printf("here %d %s\n", __LINE__, __func__);
        stk->error_code = PUSH_ERROR;
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

    StackDump(stk, func, file, line);

    return 1;
}
