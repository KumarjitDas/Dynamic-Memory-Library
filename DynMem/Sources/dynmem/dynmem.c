#ifndef DYNMEM_INTERNAL_USE_utility_defines_h
#   define DYNMEM_INTERNAL_USE_utility_defines_h
#endif
#include "utility/defines.h"

#ifndef DYNMEM_INTERNAL_USE_utility_utility_h
#   define DYNMEM_INTERNAL_USE_utility_utility_h
#endif
#include "utility/utility.h"

#include "dynmem/dynmem.h"

#include <stdlib.h>

_Bool DynMemAllocate(dynmem_t *dynmem_address, intmax_t element_size, intmax_t element_count, void *memory_address) {
    if (!dynmem_address || element_size <= 0 || element_count <= 0)
        return FALSE;

    dynmem_address->element_size = element_size;
    dynmem_address->initial_size = element_size * element_count;
    dynmem_address->size         = dynmem_address->initial_size;
    dynmem_address->length       = element_count;
    dynmem_address->index        = 0;

    uint8_t **memory_address_ = memory_address;

    if (memory_address_ && *memory_address_) {
        dynmem_address->memory = *memory_address_;
        *memory_address_ = NULL;
    }
    else
        dynmem_address->memory = malloc(dynmem_address->initial_size);

    if (!dynmem_address->memory) {
        DYNMEM_UTILITY_RESET(dynmem_address);
        return FALSE;
    }

    return TRUE;
}

_Bool DynMemDeallocate(dynmem_t *dynmem_address) {
    if (!dynmem_address)
        return FALSE;

    dynmem_address->element_size = 0;
    dynmem_address->initial_size = 0;
    dynmem_address->size         = 0;
    dynmem_address->length       = 0;
    dynmem_address->index        = 0;

    if (dynmem_address->memory)
        free(dynmem_address->memory);

    dynmem_address->memory = NULL;

    return TRUE;
}

_Bool DynMemSet(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
    if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || index >= dynmem_address->length || !value_address)
        return FALSE;

    DynMemUtilitySetMemory(dynmem_address->memory + dynmem_address->element_size * index,
                           dynmem_address->element_size, value_address, dynmem_address->element_size
                          );
    return TRUE;
}

_Bool DynMemGet(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
    if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || index >= dynmem_address->length || !value_address)
        return FALSE;

    DynMemUtilitySetMemory(value_address, dynmem_address->element_size,
                           dynmem_address->memory + dynmem_address->element_size * index, dynmem_address->element_size
                          );
    return TRUE;
}

_Bool DynMemAppend(dynmem_t *dynmem_address, void *value_address) {
    if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || !value_address)
        return FALSE;

    if (dynmem_address->index >= dynmem_address->size) {
        dynmem_address->size += dynmem_address->initial_size;

        uint8_t *temporary_memory = realloc(dynmem_address->memory, dynmem_address->size);
        if (!temporary_memory) {
            DYNMEM_UTILITY_RESET(dynmem_address);
            return FALSE;
        }

        dynmem_address->memory = temporary_memory;
        dynmem_address->length = dynmem_address->size / dynmem_address->element_size;
    }

    DynMemUtilitySetMemory(dynmem_address->memory + dynmem_address->index, dynmem_address->element_size,
                           value_address, dynmem_address->element_size
                          );
    dynmem_address->index += dynmem_address->element_size;

    return TRUE;
}
