#include "dynmem/dynmem.h"

int main() {
    dynmem_t dynmem;
    intmax_t length = 16;

    // Test 1

    if (!DynMemAllocate(&dynmem, sizeof(int), length, NULL))
        return 1;

    if (!DynMemDeallocate(&dynmem))
        return 1;

    int result = 1;
    result &= dynmem.element_size == 0;
    result &= dynmem.initial_size == 0;
    result &= dynmem.size         == 0;
    result &= dynmem.length       == 0;
    result &= dynmem.index        == 0;
    result &= dynmem.memory       == NULL;

    return !result;
}
