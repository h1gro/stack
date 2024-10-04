#include "prototype.h"

#include <TXLib.h>
#include <stdlib.h>

int main()
{
    struct stack_t stk = {INIT(stk)};

    StackCtor(&stk);

    StackPush(&stk, 1);
    StackPush(&stk, 2);
    StackPush(&stk, 3);
    StackPush(&stk, 4);
    StackPush(&stk, 5);
    StackPop(&stk);

    StackDump(&stk, __func__, __FILE__, __LINE__);

    StackDtor(&stk);

    return 0;
}
