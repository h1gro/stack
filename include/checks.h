#ifndef CHECKS
#define CHECKS

errors Verifier    (struct stack_t* stk);

int CheckForErrors (struct stack_t *stk);
int StackCheck     (struct stack_t *stk, const char* file, int line, const char* func);

#endif
