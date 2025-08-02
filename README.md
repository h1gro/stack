# STACK

## About task

Stack - data structure, it is lockated in every PC. Stack works like FILO (first in - last out), new element lockated at the top of the stack.

This project is an emulator of stack, that based on array, user can add number to stack or delete last added element.

![Stack Visualisation](https://github.com/h1gro/stack/tree/main/image)

## Comands

### PUSH

Function: ```void StackPush(struct stack_t *stk, stackelem_t elem)```

Comand adds element to stack. Element will be at the top of the stack. If next comand will be POP (about comand POP - next article), this new element would get out of the stack.

### POP

Function: ```stackelem_t StackPop(struct stack_t *stk)```

Return discarded element.

Comand deletes last added element (gets out) from the stack.


### DUMP

Function: ```void StackDump (struct stack_t *stk, const char* func, const char* file, int line, int dump_call)```

Comand write information about stack in dump file. In DEBUG mode, in file will be information about place in program where function ```StackDump()``` was called.

## Debug mode

Expluatation of realisation of the stack included debug mode.

```C
//on/off debug mode
#define DEBUG 153.153
```
