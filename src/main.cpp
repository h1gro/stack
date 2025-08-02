#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "../include/global.h"
#include "../include/stackfuncs.h"
#include "../include/output.h"

int main()
{
    struct stack_t stk = {INIT(CANARY, stk)};

    StackCtor(&stk);

    StackPush(&stk, 10);

    StackDump(&stk, __func__, __FILE__, __LINE__, INFO_PRINT);

    StackDtor(&stk);

    return 0;
}
