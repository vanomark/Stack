#include "Hash.h"

hash_t gon1(Stack* Stk)
{
    assert(Stk);

    hash_t hash = 228;

    hash += (hash_t) Stk->Lcan + (hash_t) Stk->buffer + (hash_t) Stk->data;
    hash += (hash_t) Stk->capacity + (hash_t) Stk->size;

    hash = hash - ( /* в стеке хэш считать не бросим, */ 1488 ) * Stk->size;  

    return hash;
}

hash_t djb2(const void* data, size_t size)
{   
    assert(data);

    hash_t hash = 5381;
    for (size_t i = 0; i < size; i++) {
        hash += *(StackElem_t *) (data + i*sizeof(StackElem_t));
        hash = hash * 31 ^ (int) *(StackElem_t *) (data + i*sizeof(StackElem_t));
    }

    return hash;
}

