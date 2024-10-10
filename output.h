#ifndef OUTPUT
#define OUTPUT

#define DUMP_FILE "dump.txt"

void StackErrorOutput(struct stack_t *stk, FILE * output);
void StackDump(struct stack_t *stk, const char* func, const char* file, int line, int dump_call);

#endif

