#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "ColorPrintFile.h"

#define CHECK_ if(!err) err =

enum STACK_ERROR {
    OK          = 0,
    ERROR       = 1,
    PushErr     = 2,
    PopErr      = 4,
    CtorErr     = 8,
    PushFileErr = 16,
    DumpErr     = 32,
    DtorErr     = 64,
};

struct Stack {
    double* data;
    size_t  size;
    size_t  capacity;
};

typedef double StackElem_t;

int  StackCtor      (Stack *Stk, size_t size);
int  StackPush      (Stack *Stk, StackElem_t elem);
int  StackPushFile  (Stack *Stk, const char *FileName);
int  StackPop       (Stack *Stk, StackElem_t *elem);
int  StackDump      (Stack *Stk);
int  StackDtor      (Stack *Stk);
int  StackError     (Stack *Stk);

const size_t MIN_SIZE = 10;
const size_t MAX_SIZE = 400000000;

int main() 
{
    Stack Stk = {};

    int err = OK;
    CHECK_ StackCtor(&Stk, MIN_SIZE);
    CHECK_ StackDump(&Stk);
    CHECK_ StackPushFile(&Stk, "StackPushFile.txt");
    CHECK_ StackDump(&Stk);

    StackElem_t elem = 0;
    for (size_t i = Stk.size; i > 1/4 * Stk.capacity; i--) {
        CHECK_ StackPop(&Stk, &elem);
        YELLOW_PRINT_ARG("%lg\n", elem);
    }
    CHECK_ StackDump(&Stk);
    CHECK_ StackDtor(&Stk);
    CHECK_ StackDump(&Stk);
    RED_PRINT_ARG("%d", err);

    return OK;
}

int StackCtor(Stack *Stk, size_t StackSize)
{   
    if (!Stk || StackSize > MAX_SIZE)
        return CtorErr;

    Stk->capacity = StackSize;
    Stk->data = (StackElem_t *) calloc(Stk->capacity + 1, sizeof(StackElem_t));

    return OK;
}

int StackPushFile(Stack *Stk, const char * FileName)
{   
    FILE *ReadFile;
    if ((ReadFile = fopen(FileName, "r")) == 0) {
        fclose(ReadFile);
        ReadFile = fopen("StackPushFile.txt", "r");
    }

    if (ReadFile == NULL) {
        fprintf(stderr, "Null pointer\n");
        fclose(ReadFile);

        return PushFileErr;
    }

    double elem = 0;
    while (fscanf(ReadFile, "%lg", &elem) != EOF)
        StackPush(Stk, elem);
        StackDump(Stk);

    return OK;
}

int StackPush(Stack *Stk, StackElem_t elem)
{   
    if (Stk->size >= Stk->capacity) { 
        Stk->capacity *= 2;
        Stk->data = (StackElem_t *) realloc(Stk->data, Stk->capacity * sizeof(StackElem_t));
    }

    if (Stk->size < Stk->capacity) {
        Stk->data[Stk->size] = elem;
        Stk->size += 1;
    }

    StackDump(Stk);

    return OK;
}

int StackPop(Stack *Stk, StackElem_t *elem)
{   
    if (!Stk || !elem)
        return PopErr;

    if (Stk->size <= 0.25 * Stk->capacity && Stk->capacity > MIN_SIZE) {
        Stk->capacity /= 2;
        Stk->data = (StackElem_t *) realloc(Stk->data, Stk->capacity * sizeof(StackElem_t));
    }

    StackDump(Stk);

    Stk->size -= 1;
    *elem = Stk->data[Stk->size];
    Stk->data[Stk->size] = 0;

    StackDump(Stk);

    return OK;
}

int StackDump(Stack *Stk)
{   
    if (Stk && Stk->data) {
        CYAN_PRINT_ARG("\nStackSize = %u, StackCapacity = %u\n", Stk->size, Stk->capacity);
    
        for (size_t i = 0; i < Stk->capacity; i++) {
            GREEN_PRINT_ARG("StackData[%u] = %lg\n", i, (Stk->data)[i]);
        }

        return OK;        

    } else {
        return DumpErr; 
    }
}

int StackDtor(Stack *Stk)
{   
    if (!Stk)
        return DtorErr;

    free(Stk->data); Stk->data = NULL;
    Stk->size = 0;
    Stk->capacity = 0;

    return OK;
}

int StackError(Stack *Stk) 
{
    if (!Stk)
        return ERROR;

    if (!Stk->data)
        return ERROR;

    if (Stk->size > Stk->)
}