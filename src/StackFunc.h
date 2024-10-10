#ifndef STACK_FUNC
#define STACK_FUNC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ON_DEBUG



enum STACK_ERROR {
    OK          = 0,
    ERROR       = 1,
    PtrErr      = 2,
    SizeErr     = 4,
    CanErr      = 8,
    DataErr     = 16,
    FileErr     = 32,
    HashErr     = 64,
};

typedef int StackElem_t;
typedef size_t hash_t;
typedef size_t canary_t;


struct Stack {
    #ifdef ON_DEBUG
    canary_t     Lcan;
    #endif

    StackElem_t* data;
    void*        buffer;
    size_t       size;
    size_t       capacity;

    #ifdef ON_DEBUG
    hash_t       HashStk;
    hash_t       HashBuf;
    canary_t     Rcan;
    #endif
};

int  StackCtor      (Stack *Stk, size_t size);
int  StackPush      (Stack *Stk, StackElem_t elem);
int  StackPushFile  (Stack *Stk, const char *FileName);
int  StackPop       (Stack *Stk, StackElem_t *elem);
int  StackDtor      (Stack *Stk);
int  PoisonFill     (Stack *Stk);
int  StackRec       (Stack *Stk, double factor);

const size_t MIN_SIZE = 8;
const size_t MAX_SIZE = 4000000;

const canary_t CANLA = 0xCAFEBABE;
const canary_t CANRA = 0xFEE1DEAD;
const canary_t CANLS = 0xBAADF00D;
const canary_t CANRS = 0x3CA7FACE;

#endif