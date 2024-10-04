#include "prototype.h"

void StackCtor(struct stack_t *stk)
{
    assert(stk);

    stk->error_code = NO_ERRORS;
    stk->size = 0;
    stk->capacity = CAPACITY;
    stk->data = (stackelem_t*)calloc(stk->capacity, sizeof(int));

    printf("here %d %s\n", __LINE__, __func__);

    assert(stk->data);
    assert(stk->capacity);

    #define ID_SIZE

    STACK_CHECK(stk);

    printf("here %d %s\n", __LINE__, __func__);
    #undef ID_SIZE
}

void StackDtor(struct stack_t *stk)
{
    assert(stk);
    assert(stk->data);

    for (int i = 0; i < stk->size; i++)
    {
        stk->data[i] = POISON;
    }

    stk->capacity = 0;
    stk->size = 0;

    free(stk->data);
}
