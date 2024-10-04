#include "prototype.h"

void StackPush(struct stack_t *stk, stackelem_t elem)
{
    assert(stk);
    assert(stk->data);

    StackResize(stk);

    stk->data[stk->size] = elem;
    stk->size++;

    printf("here %d %s\n", __LINE__, __func__);

    assert(stk->capacity);
    assert(stk->size);

    STACK_CHECK(stk);

    printf("here %d %s\n", __LINE__, __func__);
}

stackelem_t StackPop(struct stack_t *stk)
{
    StackResize(stk);

    printf("here %d %s\n", __LINE__, __func__);
    //stk->data[stk->size] = POISON;
    //printf("here %d %s\n", __LINE__, __func__);
    stk->size--;

    printf("here %d %s\n", __LINE__, __func__);

    STACK_CHECK(stk);

    return stk->data[stk->size + 1];
}

void StackResize(struct stack_t *stk)
{
    if (stk->size == stk->capacity)
    {
        stk->data = (stackelem_t*) realloc(stk->data, stk->capacity * CAPAC_RESIZE);
        stk->capacity = stk->capacity * CAPAC_RESIZE;
        printf("here %d %s\n", __LINE__, __func__);
    }

    //printf("here %d %s\n", __LINE__, __func__);

    if (stk->size * CAPAC_RESIZE + CAPAC_SHIFT < stk->capacity)
    {
        stk->data = (stackelem_t*) realloc(stk->data, stk->capacity / CAPAC_RESIZE);
        stk->capacity = stk->capacity / CAPAC_RESIZE;
        printf("here %d %s\n", __LINE__, __func__);
    }
}
