#ifndef HASHF
#define HASHF

#include <assert.h>
#include "StackFunc.h"

hash_t djb2(const void* data, size_t size);
hash_t gon1(Stack *Stk);

#endif