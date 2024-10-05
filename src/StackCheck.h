#ifndef STACK_CHECK
#define STACK_CHECK

#include "StackFunc.h"

STACK_ERROR  StackDump      (Stack *Stk, const char* file, const char* func, int line);
STACK_ERROR  StackError     (Stack *Stk);

#define STACK_DUMP(Stk) StackDump(Stk, __FILE__, __PRETTY_FUNCTION__, __LINE__)

#endif