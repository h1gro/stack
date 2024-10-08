#include "prototype.h"

#include <TXLib.h>
#include <stdlib.h>

int main()
{
    struct stack_t stk = {INIT(CANARY, stk)};

    StackCtor(&stk);

    StackPush(&stk, 1);
    StackPush(&stk, 2);
    StackPush(&stk, 3);
    StackPush(&stk, 4);
    StackPush(&stk, 5);
    StackPop(&stk);

    int dump_call = MAIN;
    StackDump(&stk, __func__, __FILE__, __LINE__, dump_call);

    StackDtor(&stk);

    return 0;
}
