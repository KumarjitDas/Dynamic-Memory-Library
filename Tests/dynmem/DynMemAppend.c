#include "dynmem/dynmem.h"
#include <stdio.h>

int main() {
    dynmem_t dynmem;
    intmax_t length = 4;

    if (DynMemAllocate(&dynmem, sizeof(int), length, NULL))
        return 1;

    int value = 1;
    int result = 1;
    intmax_t start_index = dynmem.start_index;
    intmax_t end_index = dynmem.end_index;
    length = dynmem.length;

    for (intmax_t i = 0; i < 100; i++) {
        value = i + 1;
        if (DynMemAppend(&dynmem, &value) == DYNMEM_FAILED)
            return 1;

        end_index++;
        result &= dynmem.end_index == end_index;

        if (end_index == length)
            length = start_index + (length - start_index) * 2;
        result &= dynmem.length == length;
    }

    if (DynMemDeallocate(&dynmem))
        return 1;

    return !result;
}
