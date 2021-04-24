#include "dynmem/dynmem.h"

int main() {
    dynmem_t dynmem;
    intmax_t length = 16;

    if (!DynMemAllocate(&dynmem, sizeof(int), length, NULL))
        return 1;

    int value;
    int result = 1;

    // Test 1

    value = 69;
    result &= DynMemSet(&dynmem, 0, &value);
    result &= DYNMEM_GET_MEMORY(int, dynmem)[0] == value;

    // Test 2

    value = 420;
    result &= DynMemSet(&dynmem, length - 1, &value);
    result &= DYNMEM_GET_MEMORY(int, dynmem)[length - 1] == value;

    // Test 3

    value = 42069;
    result &= DynMemSet(&dynmem, length / 2, &value);
    result &= DYNMEM_GET_MEMORY(int, dynmem)[length / 2] == value;

    // Test 4

    value = 42069;
    result &= !DynMemSet(&dynmem, length + 2, &value);

    if (!DynMemDeallocate(&dynmem))
        return 1;

    return !result;
}
