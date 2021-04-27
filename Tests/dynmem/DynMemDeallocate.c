#include "dynmem/dynmem.h"

int main() {
    dynmem_t dynmem;
    intmax_t length = 16;

    // Test 1

    if (DynMemAllocate(&dynmem, sizeof(int), length, NULL) == DYNMEM_FAILED)
        return 1;

    if (DynMemDeallocate(&dynmem) == DYNMEM_FAILED)
        return 1;

    int result = 1;
    result &= dynmem.element_size   == 0;
    result &= dynmem.length         == 0;
    result &= dynmem.start_index    == 0;
    result &= dynmem.end_index      == 0;
    result &= dynmem.memory         == NULL;

    return !result;
}
