#include "dynmem/dynmem.h"
#include <stdio.h>

int main() {
    dynmem_t dynmem;
    intmax_t length = 1;

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
        value = -value;
        if (DynMemPrepend(&dynmem, &value) == DYNMEM_FAILED)
            return 1;

        for (intmax_t i = dynmem.start_index; i <= dynmem.end_index; i++)
            printf("%d, ", DYNMEM_VALUE_AT(int, dynmem, i));

        if (dynmem.length > length) {
            length = dynmem.length;
            printf("\n---- length: %lld, si: %lld, ei: %lld ----\n",
                   dynmem.length, dynmem.start_index, dynmem.end_index
                  );
        }
        else
            printf("\n-------------------------\n");
    }

    if (DynMemDeallocate(&dynmem))
        return 1;

    return !result;
}
