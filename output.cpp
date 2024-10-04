#include "prototype.h"

void StackDump(struct stack_t *stk, const char* func, const char* file, int line)
{
    assert(stk);
    assert(stk->data);
    assert(stk->file);
    assert(stk->func);
    assert(stk->name);

    #ifdef DEBUG
        printf("called from %s:%d %s\n"
               "name %s born at %s:%d(%s)\n",
                func, line, file, stk->name,
                func, line, file);

        StackErrorOutput(stk);
    #endif

    printf("size %d\n"
           "capacity %d\n Data:\n",
           stk->size, stk->capacity);

    for (int i = 0; i < stk->size; i++)
    {
        printf("%lg\n", (stk->data)[i]);
    }
}

void StackErrorOutput(struct stack_t *stk)
{
    switch(stk->error_code)
    {
    case PUSH_ERROR:     printf("Error in stackpush()\n");
                         break;
    case CTOR_ERROR:     printf("Error in ctor\n");
                         break;
    case STK_ERROR:      printf("Error in struct\n");
                         break;
    case CAPACITY_ERROR: printf("Error in capacity\n");
                         break;
    case SIZE_ERROR:     printf("Error in size\n");
                         break;
    default:             printf("Unknown error\n");
    }
}
