#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "stackfuncs.h"
#include "checks.h"

void StackCtor(struct stack_t *stk)
{
    assert(stk);

    #ifdef DEBUG
        stk->canary1 = CANARY;
        stk->canary2 = CANARY;
    #endif

    stk->size = 0;
    stk->error_code = NO_ERRORS;
    stk->capacity = CAPACITY;
    stk->data = (stackelem_t*) calloc(stk->capacity + NUM_CANARIES_BUF, sizeof(double)) + NUM_CANARIES_IN_LEFT;

    FillingDataPoison(stk->data - NUM_CANARIES_IN_LEFT, stk->capacity - stk->size);

    stk->data[-1] = CANARY;
    stk->data[stk->capacity] = CANARY;

    assert(stk->data);
    assert(stk->capacity);

    STACK_CHECK(stk);
}

void StackDtor(struct stack_t *stk)
{
    assert(stk);
    assert(stk->data);

    stk->capacity = 0;

    stk->size = 0;

    free(stk->data - NUM_CANARIES_IN_LEFT);
}

void FillingDataPoison(stackelem_t *data, int num_el_poison)
{
    for (int i = 0; i <= num_el_poison; i++)
    {
        data[i] = POISON;
    }
}

void StackPush(struct stack_t *stk, stackelem_t elem)
{
    assert(stk);
    assert(stk->data);

    STACK_CHECK(stk);

    bool pop_or_push = PUSH;
    ResizeIf(stk, pop_or_push);

    stk->data[stk->size] = elem;
    stk->size++;

    assert(stk->capacity);
    assert(stk->size);

    STACK_CHECK(stk);
}

stackelem_t StackPop(struct stack_t *stk)
{
    STACK_CHECK(stk);
    stackelem_t discared_elem = stk->data[stk->size];
    stk->data[stk->size] = POISON;

    bool pop_or_push = POP;
    ResizeIf(stk, pop_or_push);

    stk->size--;

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

        FillingDataPoison(stk->data + stk->size + NUM_CANARIES_IN_LEFT, stk->capacity - stk->size);

        stk->data[stk->capacity] = CANARY;
    }

    if (pop_or_push == POP && stk->size * CAPAC_RESIZE + CAPAC_SHIFT < stk->capacity)
    {
        stk->capacity = stk->capacity / CAPAC_RESIZE;
        
        stk->data = (stackelem_t*) realloc(stk->data - NUM_CANARIES_IN_LEFT, stk->capacity + NUM_CANARIES_BUF) + NUM_CANARIES_IN_LEFT;

        stk->data[stk->capacity] = CANARY;
    }
}
