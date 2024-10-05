#include "StackCheck.h"
#include "StackFunc.h"

STACK_ERROR StackError(Stack *Stk) 
{
    if (!Stk)
        return PtrErr;

    if (!Stk->buffer)
        return BufferErr;

    if (!Stk->data)
        return DataErr;

    if (Stk->size > Stk->capacity || Stk->size > MAX_SIZE || Stk->capacity > MAX_SIZE)
        return SizeErr;
    
    if (Stk->Lcan != CANLS || Stk->Rcan != CANRS)
        return CanErr;

    canary_t  LeftArrCan = *(canary_t *) Stk->buffer;
    canary_t RightArrCan = *(canary_t *) (Stk->buffer + sizeof(canary_t) + Stk->capacity*sizeof(StackElem_t));
    if (LeftArrCan != CANLA || RightArrCan != CANRA)
        return CanErr;

    return OK;
}

STACK_ERROR StackDump(Stack *Stk)
{   

    if (!StackError) {

        FILE *LOG = fopen("LogFile.txt", "a");

        fprintf(LOG,"\nLCanS = 0x%x, RCanS = 0x%x"
                    "\nLCanA = 0x%x, RCanA = 0x%x"
                    "\nStackSize = %u, StackCapacity = %u\n", 
                        Stk->Lcan, Stk->Rcan, 
                        *(canary_t *) Stk->buffer,  
                        *(canary_t *)(Stk->buffer + Stk->capacity*sizeof(StackElem_t) + sizeof(canary_t)),
                        Stk->size, Stk->capacity);
 
        for (size_t i = 0; i < Stk->capacity; i++) {
            fprintf(LOG,"StackData[%u] = %lg\n", i, (Stk->data)[i]);
        }
        fclose(LOG);

        return OK;        
    } 

    return ERROR; 
}