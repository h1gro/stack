#include <stdio.h>
#include <stdlib.h>

#include "../include/global.h"
#include "../include/stackfuncs.h"
#include "../include/output.h"

int main()
{
    struct stack_t stk = {INIT(CANARY, stk)};

    StackCtor(&stk);

    StackPush(&stk, 10);
    StackPush(&stk, 20);
    double a = StackPop(&stk);
    printf("%lg\n", a);

    int dump_call = INFO_PRINT;
    StackDump(&stk, __func__, __FILE__, __LINE__, dump_call);

    StackDtor(&stk);

    return 0;
}
