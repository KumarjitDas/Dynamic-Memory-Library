#ifndef DYNMEM_INTERNAL_USE_utility_defines_h
#   define DYNMEM_INTERNAL_USE_utility_defines_h
#endif
#ifndef DYNMEM_INTERNAL_USE_utility_utility_h
#   define DYNMEM_INTERNAL_USE_utility_utility_h
#endif

#include "utility/defines.h"
#include "utility/utility.h"
#include "dynmem/dynmem.h"

#include <stdlib.h>


_Bool DynMemAppend(dynmem_t *dynmem_address, void *value_address) {
    if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
        return DYNMEM_FAILED;

    dynmem_address->ei += dynmem_address->es;

    if (dynmem_address->ei == dynmem_address->cs) {
        dynmem_address->cs += dynmem_address->eis;

        dynmem_address->m = realloc(dynmem_address->m, dynmem_address->cs);
        if (!dynmem_address->m) {
            DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);
            return DYNMEM_FAILED;
        }

        dynmem_address->eis *= 2;
    }

    if (!value_address) return DYNMEM_SUCCEED;

    uint8_t *destination = dynmem_address->m + dynmem_address->ei;

    switch (dynmem_address->es) {
    case sizeof(uint8_t):
        *(uint8_t*)destination = *(uint8_t*)value_address;
        break;
    case sizeof(uint16_t):
        *(uint16_t*)destination = *(uint16_t*)value_address;
        break;
    case sizeof(uint32_t):
        *(uint32_t*)destination = *(uint32_t*)value_address;
        break;

    #ifdef UINT64_MAX
    case sizeof(uint64_t):
        *(uint64_t*)destination = *(uint64_t*)value_address;
        break;
    #endif

    default:
        DynMemUtilitySetMemoryBlock(destination, value_address, dynmem_address->es);
    }

    return DYNMEM_SUCCEED;
}

