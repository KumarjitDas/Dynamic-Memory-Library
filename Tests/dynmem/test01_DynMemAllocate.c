#include "dynmem/dynmem.h"
#include <stdlib.h>

int main() {
    dynmem_t dynmem;
    intmax_t length = 16;

    // Test 1

    if (!DynMemAllocate(&dynmem, sizeof(int), length, NULL))
        return 1;

    int result = 1;
    result &= dynmem.element_size == sizeof(int);
    result &= dynmem.initial_size == sizeof(int) * length;
    result &= dynmem.size         == dynmem.initial_size;
    result &= dynmem.length       == length;
    result &= dynmem.index        == 0;
    result &= dynmem.memory       != NULL;

    if (dynmem.memory) free(dynmem.memory);

    if (!result) return 1;


    // Test 2

    int *array = malloc(sizeof(int) * length);
    if (!array) return 1;

    if (!DynMemAllocate(&dynmem, sizeof(int), length, &array))
        return 1;

    result &= array               == NULL;
    result &= dynmem.element_size == sizeof(int);
    result &= dynmem.initial_size == sizeof(int) * length;
    result &= dynmem.size         == dynmem.initial_size;
    result &= dynmem.length       == length;
    result &= dynmem.index        == 0;
    result &= dynmem.memory       != NULL;

    if (dynmem.memory) free(dynmem.memory);

    return !result;
}
