#include "StackFunc.h"
#include "Hash.h"

hash_t hash(const StackElem_t* data, size_t size)
{
    hash_t hash = 0;
    for (size_t i = 0; i < size; i++)
        hash += data[i];

    return hash;
}