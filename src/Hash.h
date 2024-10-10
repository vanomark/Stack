#ifndef HASHF
#define HASHF

#include <assert.h>
#include "StackFunc.h"
#include "StackCheck.h"

size_t djb2(const void* data, size_t size);
hash_t gon1(Stack *Stk);

#endif