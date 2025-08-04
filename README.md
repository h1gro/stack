# STACK

## About task

Stack - data structure, it is lockated in every PC. Stack works like FILO (first in - last out), new element lockated at the top of the stack.

This project is an emulator of stack, that based on array, user can add number to stack or delete last added element.

![Stack Visualisation](https://github.com/h1gro/stack/blob/main/image/AQAKYYPaN9shRTH2Q3jRWOfX5GFd-QSaSaP6Nre3uuPhT9e-89toJ9598WrFQNUteQ820ruUaO7-1FOGvylcpe7Pl9I.png)


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

Expluatation of the stack included debug mode for more easy finding errors and bugs.

```C
//on/off debug mode
#define DEBUG 153.153
```

Debug mode demonstrates where Verifier have finded error. It show file, line and function where is error.

## Levels of Protection

The project has 3 levels of protection from huck, attack on data, on memory.

```C
// Levels of protection:
// ZERO_LP   no protection
// FIRST_LP  canaries in buffer and in struct
// SECOND_LP canaries + hash in buffer and in struct
```

### 0 Level of protection (ZLP)

This level doesn't have any built-in technology of protection. It has only hardware protection.

### 1 Level of protection (FLP)

FLP has "canaries" - protection on the borders of the stack (exactly buffer with data) and the main structure (it has full information about stack and working with the stack goes directly through the elements of the structure). If one of canaries is damaged during regular check, it will mean that the buffer of structure is corrupted.

### 2 Level of protection (SLP)

Besides the canaries SLP has hash function, that calculate current hash-sum of elements in buffer and elements in structure and compare them with old hash-sums. If one of hash-sums is not matched during regular check, it will mean that the buffer of structure is corrupted.
