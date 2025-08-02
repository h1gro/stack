#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

#include "../include/global.h"
#include "../include/output.h"

void StackDump(struct stack_t* stk, const char* func, const char* file, int line, int dump_call)
{
    assert(stk);
    assert(stk->data);
    assert(stk->file);
    assert(stk->func);
    assert(stk->name);

    fprintf(stk->output, "===============================================\n");

    #ifdef DEBUG

        fprintf(stk->output, "called from %s:%d %s\n"
                        "name %s born at %s:%d(%s)\n",
                        func, line, file, stk->name,
                        func, line, file);

        if (dump_call == ERROR_PRINT)
        {
            StackErrorOutput(stk);
        }

    #endif

    fprintf(stk->output, "size %d\n"
                         "capacity %d\n"
                         "-----------DATA-----------\n",
                         stk->size, stk->capacity);

    for (int i = -1; i < stk->capacity + NUM_CANARIES_IN_RIGHT; i++)
    {
        if (fabs(stk->data[i] - POISON) < EPSILON)
        {
            fprintf(stk->output, "data [%2d] = %lg (POISON)\n", i, stk->data[i]);
        }
        else if (fabs(stk->data[i] - CANARY) < EPSILON)
        {
            fprintf(stk->output, "data [%2d] =  %lg (CANARY)\n", i, stk->data[i]);
        }
        else
        {
            fprintf(stk->output, "data [%2d] =  %lg\n", i, stk->data[i]);
        }
    }

    fprintf(stk->output, "--------------------------\n\n");
}

void StackErrorOutput(struct stack_t *stk)
{
    switch(stk->error_code)
    {
    case PUSH_ERROR:        fprintf(stk->output, "\n<<<<<<<<<<<Error in stackpush\n\n");
                            break;

    case CTOR_ERROR:        fprintf(stk->output, "\n<<<<<<<<<<<Error in ctor\n\n");
                            break;

    case STK_ERROR:         fprintf(stderr, "\n<<<<<<<<<<<Error in struct\n\n");
                            break;

    case FILE_ERROR:        fprintf(stderr, "\n<<<<<<<<<<<Error in output file\n\n");
                            break;

    case CAPACITY_ERROR:    fprintf(stk->output, "\n<<<<<<<<<<<Error in capacity\n\n");
                            break;

    case SIZE_ERROR:        fprintf(stk->output, "\n<<<<<<<<<<<Error in size\n\n");
                            break;

    #ifdef FIRST_LP
        case CANARY1_BUF_ERROR: fprintf(stk->output, "\n<<<<<<<<<<<Error first canary in buffer\n\n");
                                break;

        case CANARY2_BUF_ERROR: fprintf(stk->output, "\n<<<<<<<<<<<Error second canary in buffer\n\n");
                                break;

        case CANARY1_STR_ERROR: fprintf(stderr, "\n<<<<<<<<<<<Error first canary in struct\n\n");
                                break;

        case CANARY2_STR_ERROR: fprintf(stderr, "\n<<<<<<<<<<<Error second canary in struct\n\n");
                                break;
    #endif

    #ifdef SECOND_LP
        case HASH_BUFFER_ERROR: fprintf(stk->output, "\n<<<<<<<<<<<Error hash in buffer\n\n");
                                break;

        case HASH_STRUCT_ERROR: fprintf(stderr, "\n<<<<<<<<<<<Error hash in struct\n\n");
                                break;
    #endif

    default:                fprintf(stk->output, "\n<<<<<<<<<<<Unknown error\n\n");
    }
}
