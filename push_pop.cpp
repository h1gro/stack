#include "prototype.h"

void StackPush(struct stack_t *stk, stackelem_t elem)
{
    assert(stk);
    assert(stk->data);

    bool pop_or_push = PUSH;
    ResizeIf(stk, pop_or_push);

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
    stackelem_t discared_elem = stk->data[stk->size];
    stk->data[stk->size] = POISON;

    bool pop_or_push = POP;
    ResizeIf(stk, pop_or_push);

    printf("here %d %s\n", __LINE__, __func__);
    stk->size--;

    printf("here %d %s\n", __LINE__, __func__);

    STACK_CHECK(stk);

    return discared_elem;
}

void ResizeIf(struct stack_t *stk, bool pop_or_push)
{
    if (pop_or_push == PUSH && stk->size == stk->capacity)
    {
        stk->data[stk->capacity] = POISON;
        stk->capacity = stk->capacity * CAPAC_RESIZE;
        stk->data = (stackelem_t*) realloc(stk->data - NUM_CANARIES_IN_LEFT, stk->capacity + NUM_CANARIES_BUF) + NUM_CANARIES_IN_LEFT;
        stk->data[stk->capacity] = CANARY;
        // printf("here %d %s\n", __LINE__, __func__);
    }

    if (pop_or_push == POP && stk->size * CAPAC_RESIZE + CAPAC_SHIFT < stk->capacity)
    {
        stk->capacity = stk->capacity / CAPAC_RESIZE;
        stk->data = (stackelem_t*) realloc(stk->data - NUM_CANARIES_IN_LEFT, stk->capacity + NUM_CANARIES_BUF) + NUM_CANARIES_IN_LEFT;
        stk->data[stk->capacity] = CANARY;
        // printf("here %d %s\n", __LINE__, __func__);
    }
}

