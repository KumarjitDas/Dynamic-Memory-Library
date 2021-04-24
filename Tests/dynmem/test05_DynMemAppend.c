#include "dynmem/dynmem.h"
#include <stdio.h>

int main() {
    dynmem_t dynmem;
    intmax_t length = 10;

    if (!DynMemAllocate(&dynmem, sizeof(int), length, NULL))
        return 1;

    int value = 1;
    int result = 1;

    for (intmax_t i = 0; i < length * 5; i++) {
        value += i;
        if (!DynMemAppend(&dynmem, &value)) return 1;
    }
    result &= dynmem.element_size == sizeof(int);
    result &= dynmem.initial_size == sizeof(int) * length;
    result &= dynmem.size         == sizeof(int) * length * 5;
    result &= dynmem.length       == length * 5;
    result &= dynmem.index        == sizeof(int) * length * 5;
    result &= dynmem.memory       != NULL;

    if (!DynMemDeallocate(&dynmem))
        return 1;

    return !result;
}
