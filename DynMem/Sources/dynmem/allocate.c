#ifndef DYNMEM_INTERNAL_USE_utility_defines_h
#   define DYNMEM_INTERNAL_USE_utility_defines_h
#endif
#ifndef DYNMEM_INTERNAL_USE_utility_utility_h
#   define DYNMEM_INTERNAL_USE_utility_utility_h
#endif

#include "utility/defines.h"
#include "dynmem/dynmem.h"

#include <stdlib.h>


_Bool DynMemAllocate(dynmem_t *dynmem_address, intmax_t element_size, intmax_t element_count, void *memory_address) {
    if (!dynmem_address || element_size <= 0 || element_count <= 0)
        return DYNMEM_FAILED;

    size_t size = element_size * element_count;

    uint8_t **memory_address_ = memory_address;
    if (memory_address_ && *memory_address_) {
        dynmem_address->m = *memory_address_;
        *memory_address_ = NULL;
        size /= 2;
    }
    else {
        if (size < sizeof(intmax_t))
            size = ((sizeof(intmax_t) + element_size) / element_size) * element_size;

        dynmem_address->m = malloc(size);
        if (!dynmem_address->m) {
            DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);
            return DYNMEM_FAILED;
        }
    }

    dynmem_address->es  = element_size;
    dynmem_address->is  = size;
    dynmem_address->cs  = size * 2;
    dynmem_address->bis = size;
    dynmem_address->eis = size;
    dynmem_address->bi  = size;
    dynmem_address->ei  = size - element_size;

    return DYNMEM_SUCCEED;
}


_Bool DynMemDeallocate(dynmem_t *dynmem_address) {
    if (!dynmem_address)
        return DYNMEM_FAILED;

    if (dynmem_address->m)
        free(dynmem_address->m);

    DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);

    return DYNMEM_SUCCEED;
}
