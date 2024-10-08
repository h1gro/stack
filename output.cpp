#include "prototype.h"

void StackDump(struct stack_t *stk, const char* func, const char* file, int line, int dump_call)
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

        if(dump_call != MAIN)
        {
            StackErrorOutput(stk);
        }
    #endif

    printf("size %d\n"
           "capacity %d\n Data:\n",
           stk->size, stk->capacity);

    for (int i = -1; i < stk->capacity + NUM_CANARIES_IN_RIGHT; i++)
    {
        printf("data [%d] = %lg\n", i, (stk->data)[i]);
    }

    //printf("End of Dump\n");
}

void StackErrorOutput(struct stack_t *stk)
{
    switch(stk->error_code)
    {
    case PUSH_ERROR:        printf("Error in stackpush()\n");
                            break;
    case CTOR_ERROR:        printf("Error in ctor\n");
                            break;
    case STK_ERROR:         printf("Error in struct\n");
                            break;
    case CAPACITY_ERROR:    printf("Error in capacity\n");
                            break;
    case SIZE_ERROR:        printf("Error in size\n");
                            break;
    case CANARY1_BUF_ERROR: printf("Error first canary in buffer\n");
                            break;
    case CANARY2_BUF_ERROR: printf("Error second canary in buffer\n");
                            break;
    case CANARY1_STR_ERROR: printf("Error first canary in struct\n");
                            break;
    case CANARY2_STR_ERROR: printf("Error second canary in strucr\n");
                            break;
    default:                printf("Unknown error\n");
    }
}
