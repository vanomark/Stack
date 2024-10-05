#include "StackFunc.h"
#include "StackCheck.h"
#include "Hash.h"

int StackCtor(Stack *Stk, size_t StackSize)
{   
    if (StackError(Stk) == 0 && StackSize < MAX_SIZE) {
        Stk->Lcan = CANLS;
        Stk->Rcan = CANRS;
        Stk->capacity = StackSize;
        Stk->buffer = calloc(Stk->capacity*sizeof(StackElem_t) + 2*sizeof(canary_t), 1);

    // #ifdef ON_DEBUG
        Stk->data = (StackElem_t *) (Stk->buffer + sizeof(canary_t));
        *(canary_t *) Stk->buffer = CANLA;
        *(canary_t *) (Stk->buffer + sizeof(canary_t) + Stk->capacity*sizeof(StackElem_t)) = CANRA;
    // #endif //ON_DEBUG
        PoisonFill(Stk);

        return OK;
    }
}

int StackPushFile(Stack *Stk, const char * FileName)
{   
    if (StackError(Stk) == 0) {
        FILE *ReadFile;
        if ((ReadFile = fopen(FileName, "r")) == 0) {
            fclose(ReadFile);
            ReadFile = fopen("StackPushFile.txt", "r");
        }

        if (ReadFile == NULL) {
            fprintf(stderr, "Null pointer\n");
            fclose(ReadFile);

            return PtrErr;
        }

        double elem = 0;
        while (fscanf(ReadFile, "%lg", &elem) != EOF)
            StackPush(Stk, elem);

        return OK;
    }

    return ERROR;
}

int StackPush(Stack *Stk, StackElem_t elem)
{   
    if (StackError(Stk) == 0) {

        if (Stk->size >= Stk->capacity) { 
            Stk->capacity *= 2;
            StackRec(Stk);
        }

        if (Stk->size < Stk->capacity) {
            Stk->data[Stk->size] = elem;
            Stk->size += 1;
        }

        StackDump(Stk);
        
        return OK;
    }

    return ERROR;
}

int StackPop(Stack *Stk, StackElem_t *elem)
{   
    if (StackError(Stk) == 0 && elem) {

        if (Stk->size <= 0.25 * Stk->capacity && Stk->capacity > MIN_SIZE) {
            Stk->capacity /= 2;
            StackRec(Stk);
        }
        
        Stk->size -= 1;
        *elem = Stk->data[Stk->size];
        Stk->data[Stk->size] = -666.666;

        StackDump(Stk);

        return OK;
    }

    return ERROR;
}

int StackDtor(Stack *Stk)
{   
    if (StackError(Stk) == 0) {
        free(Stk->buffer); Stk->buffer = NULL;
        Stk->Lcan = 0;
        Stk->Rcan = 0;
        Stk->Hash = 0;
        Stk->size = 0;
        Stk->capacity = 0;

        return OK;
    }

    return ERROR;
}

int PoisonFill(Stack *Stk) 
{
    if (StackError(Stk) == 0) {
        size_t i    = Stk->size;
        size_t last = Stk->capacity;
        
        while (i < last) {
            Stk->data[i++] = -666.666;
        }

        return OK;
    }

    return ERROR;
}

int StackRec (Stack *Stk) 
{   
    if (StackError(Stk) == 0) {

        Stk->buffer = realloc(Stk->buffer, Stk->capacity*sizeof(StackElem_t) + 2*sizeof(canary_t));
        Stk->data = (StackElem_t *) (Stk->buffer + sizeof(canary_t));

        *(canary_t *) (Stk->buffer) = CANLA;
        *(canary_t *) (Stk->buffer + sizeof(canary_t) + Stk->capacity*sizeof(StackElem_t)) = CANRA;

        PoisonFill(Stk);

        return OK;
    }
}