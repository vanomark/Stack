#include "StackFunc.h"
#include "Hash.h"

hash_t djb2(const double* data, size_t size)
{
    hash_t hash = 5381;
    for (size_t i = 0; i < size; i++) {
        hash += data[i];
        hash = hash * 31 ^ (int) data[i];
    }

    return hash;
}