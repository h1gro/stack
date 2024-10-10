#include <assert.h>
#include <stdio.h>

#include "global.h"
#include "output.h"

void StackDump(struct stack_t *stk, const char* func, const char* file, int line, int dump_call)
{
    assert(stk);
    assert(stk->data);
    assert(stk->file);
    assert(stk->func);
    assert(stk->name);

    FILE * output = fopen(DUMP_FILE, "w");

    #ifdef DEBUG
        fprintf(output, "called from %s:%d %s\n"
                        "name %s born at %s:%d(%s)\n",
                        func, line, file, stk->name,
                        func, line, file);

        if(dump_call == ERROR_PRINT)
        {
            StackErrorOutput(stk, output);
        }
    #endif

    fprintf(output, "size %d\n"
                    "capacity %d\n Data:\n",
                    stk->size, stk->capacity);

    for (int i = -1; i < stk->capacity + NUM_CANARIES_IN_RIGHT; i++)
    {
        if ((long long int)(stk->data[i] - POISON) == 0)
        {
            fprintf(output, "data [%d] = %lg (POISON)\n", i, (stk->data)[i]);
        }
        else if ((long long int)(stk->data[i] - CANARY) == 0)
        {
            fprintf(output, "data [%d] = %lg (CANARY)\n", i, (stk->data)[i]);
        }
        else
        {
            fprintf(output, "data [%d] = %lg\n", i, (stk->data)[i]);
        }
    }

    fclose(output);
}

void StackErrorOutput(struct stack_t *stk, FILE * output)
{
    switch(stk->error_code)
    {
    case PUSH_ERROR:        fprintf(output, "Error in stackpush()\n");
                            break;
    case CTOR_ERROR:        fprintf(output, "Error in ctor\n");
                            break;
    case STK_ERROR:         fprintf(output, "Error in struct\n");
                            break;
    case CAPACITY_ERROR:    fprintf(output, "Error in capacity\n");
                            break;
    case SIZE_ERROR:        fprintf(output, "Error in size\n");
                            break;
    case CANARY1_BUF_ERROR: fprintf(output, "Error first canary in buffer\n");
                            break;
    case CANARY2_BUF_ERROR: fprintf(output, "Error second canary in buffer\n");
                            break;
    case CANARY1_STR_ERROR: fprintf(output, "Error first canary in struct\n");
                            break;
    case CANARY2_STR_ERROR: fprintf(output, "Error second canary in strucr\n");
                            break;
    default:                fprintf(output, "Unknown error\n");
    }
}
