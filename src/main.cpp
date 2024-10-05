

// #include "AssertFile.h"
#include "ColorPrintFile.h"
#include "Hash.h"
#include "StackCheck.h"
#include "StackFunc.h"


#define CHECK_ if(!err) err =

int main() 
{
    Stack Stk = {};

    int err = OK;
    CHECK_ StackCtor(&Stk, MIN_SIZE);
    CHECK_ StackPushFile(&Stk, "StackPushFile.txt");

    StackElem_t elem = 0;
    for (size_t i = Stk.size; i > 0; i--) {
        CHECK_ StackPop(&Stk, &elem);
    }
    CHECK_ StackDtor(&Stk);
    // RED_PRINT_LOG("%d", err);

    return OK;
}

