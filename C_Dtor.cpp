#include "prototype.h"

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
    stk->data = (stackelem_t*) calloc(stk->capacity + NUM_CANARIES_BUF, sizeof(double)) + 1;

    FillingDataPoison(stk);

    stk->data[-1] = CANARY;
    stk->data[stk->capacity] = CANARY;

    printf("here %d %s\n", __LINE__, __func__);

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

    free(stk->data);
}

void FillingDataPoison(struct stack_t *stk)
{
    for (int i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = POISON;
    }
    //printf("end of poison\n");
}
