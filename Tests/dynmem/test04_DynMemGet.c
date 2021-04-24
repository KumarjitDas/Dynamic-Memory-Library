#include "dynmem/dynmem.h"

int main() {
    dynmem_t dynmem;
    intmax_t length = 16;

    if (!DynMemAllocate(&dynmem, sizeof(int), length, NULL))
        return 1;

    for (intmax_t i = 0; i < length; i++)
        DYNMEM_GET_MEMORY(int, dynmem)[i] = i + 101;

    int value;
    int result = 1;

    // Test 1

    result &= DynMemGet(&dynmem, 0, &value);
    result &= DYNMEM_GET_MEMORY(int, dynmem)[0] == value;

    // Test 2

    result &= DynMemGet(&dynmem, length - 1, &value);
    result &= DYNMEM_GET_MEMORY(int, dynmem)[length - 1] == value;

    // Test 3

    result &= DynMemGet(&dynmem, length / 2, &value);
    result &= DYNMEM_GET_MEMORY(int, dynmem)[length / 2] == value;

    // Test 4

    result &= !DynMemGet(&dynmem, length + 2, &value);

    if (!DynMemDeallocate(&dynmem))
        return 1;

    return !result;
}
