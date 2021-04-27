#include "dynmem/dynmem.h"

int main() {
    dynmem_t dynmem;
    intmax_t length = 16;

    if (DynMemAllocate(&dynmem, sizeof(int), length, NULL))
        return 1;

    int value = 0;
    for (intmax_t i = 0; i < length; i++)
        if (DynMemAppend(&dynmem, &value))
            return 1;

    int result = 1;


    // Test 1

    value = 69;
    result &= DynMemSet(&dynmem, 0, &value) == DYNMEM_SUCCEED;
    result &= DYNMEM_VALUE_AT(int, dynmem, 0) == value;


    // Test 2

    value = 420;
    result &= DynMemSet(&dynmem, length - 1, &value) == DYNMEM_SUCCEED;
    result &= DYNMEM_VALUE_AT(int, dynmem, length - 1) == value;


    // Test 3

    value = 42069;
    result &= DynMemSet(&dynmem, length / 2, &value) == DYNMEM_SUCCEED;
    result &= DYNMEM_VALUE_AT(int, dynmem, length / 2) == value;


    // Test 4

    value = 123456;
    result &= DynMemSet(&dynmem, length + 2, &value) == DYNMEM_FAILED;


    // Test 5

    value = 69;
    result &= DynMemSet(&dynmem, -1, &value) == DYNMEM_SUCCEED;
    result &= DYNMEM_VALUE_AT(int, dynmem, length - 1) == value;


    // Test 6

    value = 420;
    result &= DynMemSet(&dynmem, -3, &value) == DYNMEM_SUCCEED;
    result &= DYNMEM_VALUE_AT(int, dynmem, length - 3) == value;


    // Test 7

    value = 42069;
    result &= DynMemSet(&dynmem, -100, &value) == DYNMEM_FAILED;


    if (DynMemDeallocate(&dynmem))
        return 1;

    return !result;
}
