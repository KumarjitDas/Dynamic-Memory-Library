#include "dynmem/dynmem.h"
#include <stdio.h>

int main() {
    dynmem_t dynmem;
    intmax_t length = 4;

    if (DynMemAllocate(&dynmem, sizeof(int), length, NULL))
        return 1;

    int value1 = 1;
    int result = 1;

    for (intmax_t i = 0; i < 100; i++) {
        value1 = i + 1;
        if (DynMemAppend(&dynmem, &value1) == DYNMEM_FAILED)
            return 1;
    }

    int value2 = value1;
    intmax_t end_index   = dynmem.end_index;
    intmax_t start_index = dynmem.start_index;
    length = dynmem.length;

    for (intmax_t i = 0; i < 100; i++) {
        if (DynMemDeduct(&dynmem, &value1) == DYNMEM_FAILED)
            return 1;

        result &= value1 == value2;
        value2--;

        if (end_index == start_index)
            length = start_index + (length - end_index) / 2;
        result &= dynmem.length == length;

        if (end_index >= start_index) end_index--;
        result &= dynmem.end_index == end_index;
    }

    if (DynMemDeallocate(&dynmem))
        return 1;

    return !result;
}
