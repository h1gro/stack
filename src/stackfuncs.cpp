#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/global.h"
#include "../include/stackfuncs.h"
#include "../include/checks.h"
#include "../include/utilits.h"
#include "../include/output.h"

void StackCtor(struct stack_t *stk)
{
    assert(stk);

    stk->output = fopen(DUMP_FILE, "w");

    CheckFile(stk->output);

    #ifdef DEBUG
        stk->canary1 = CANARY;
        stk->canary2 = CANARY;
    #endif

    stk->size       = 0;
    stk->error_code = NO_ERRORS;
    stk->capacity   = CAPACITY;
    stk->data       = (stackelem_t*) calloc(stk->capacity + NUM_CANARIES_BUF, sizeof(double)) + NUM_CANARIES_IN_LEFT;

    assert(stk->data);

    FillingDataPoison(stk->data, stk->capacity - stk->size);

    stk->data[-1]            = CANARY;
    stk->data[stk->capacity] = CANARY;

    STACK_CHECK(stk);
}

void StackDtor(struct stack_t *stk)
{
    assert(stk);
    assert(stk->data);

    stk->capacity = 0;

    stk->size = 0;

    fclose(stk->output);
    free(stk->data - NUM_CANARIES_IN_LEFT);
}

void StackPush(struct stack_t *stk, stackelem_t elem)
{
    STACK_CHECK(stk);

    int pop_or_push = PUSH;
    ResizeIf(stk, pop_or_push);

    stk->data[stk->size] = elem;
    stk->size++;

    int dump_call = PUSH;
    StackDump(stk, __func__, __FILE__, __LINE__, dump_call);

    assert(stk->capacity);
    assert(stk->size);

    STACK_CHECK(stk);
}

stackelem_t StackPop(struct stack_t *stk)
{
    STACK_CHECK(stk);
    stackelem_t discared_elem = stk->data[stk->size - 1];
    stk->data[stk->size - 1] = POISON;

    int pop_or_push = POP;
    ResizeIf(stk, pop_or_push);

    stk->size--;

    int dump_call = POP;
    StackDump(stk, __func__, __FILE__, __LINE__, dump_call);

    STACK_CHECK(stk);

    return discared_elem;
}

void ResizeIf(struct stack_t *stk, int pop_or_push)
{
    if ((pop_or_push == PUSH) && (stk->size == stk->capacity))
    {
        stk->data[stk->capacity] = POISON;
        stk->capacity = stk->capacity * CAPAC_RESIZE;
        stk->data = (stackelem_t*) realloc(stk->data - NUM_CANARIES_IN_LEFT, (size_t)(stk->capacity + NUM_CANARIES_BUF) * sizeof(stackelem_t)) + NUM_CANARIES_IN_LEFT;

        FillingDataPoison(stk->data + stk->size, stk->capacity - stk->size);

        stk->data[stk->capacity] = CANARY;
    }

    if ((pop_or_push == POP) && (stk->size * CAPAC_RESIZE + CAPAC_SHIFT < stk->capacity))
    {
        stk->capacity = stk->capacity / CAPAC_RESIZE;

        stk->data = (stackelem_t*) realloc(stk->data - NUM_CANARIES_IN_LEFT, (size_t)(stk->capacity + NUM_CANARIES_BUF) * sizeof(stackelem_t)) + NUM_CANARIES_IN_LEFT;

        stk->data[stk->capacity] = CANARY;
    }
}
