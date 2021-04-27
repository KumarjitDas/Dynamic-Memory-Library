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
        return DYNMEM_FAILED;

    dynmem_address->element_size = element_size;
    dynmem_address->length       = element_count * 2;
    dynmem_address->start_index  = element_count;
    dynmem_address->end_index    = element_count - 1;

    uint8_t **memory_address_ = memory_address;

    if (memory_address_ && *memory_address_) {
        dynmem_address->memory = *memory_address_;
        *memory_address_ = NULL;
    }
    else
        dynmem_address->memory = malloc(element_size * dynmem_address->length);

    if (!dynmem_address->memory) {
        DYNMEM_UTILITY_RESET(dynmem_address);
        return DYNMEM_FAILED;
    }

    return DYNMEM_SUCCEED;
}

_Bool DynMemDeallocate(dynmem_t *dynmem_address) {
    if (!dynmem_address)
        return DYNMEM_FAILED;

    if (dynmem_address->memory)
        free(dynmem_address->memory);

    DYNMEM_UTILITY_RESET(dynmem_address);

    return DYNMEM_SUCCEED;
}

_Bool DynMemAppend(dynmem_t *dynmem_address, void *value_address) {
    if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || !value_address)
        return DYNMEM_FAILED;

    dynmem_address->end_index++;

    if (dynmem_address->end_index == dynmem_address->length) {
        dynmem_address->length += dynmem_address->length / 2;
        dynmem_address->memory = realloc(dynmem_address->memory, 
                                         dynmem_address->length * dynmem_address->element_size
                                        );
        if (!dynmem_address->memory) {
            DYNMEM_UTILITY_RESET(dynmem_address);
            return DYNMEM_FAILED;
        }
    }

    void *destination = dynmem_address->memory + dynmem_address->end_index * dynmem_address->element_size;

    switch (dynmem_address->element_size) {
        case sizeof(uint8_t):
            *(uint8_t*)destination = *(uint8_t*)value_address;
            break;
        case sizeof(uint16_t):
            *(uint16_t*)destination = *(uint16_t*)value_address;
            break;
        case sizeof(uint32_t):
            *(uint32_t*)destination = *(uint32_t*)value_address;
            break;

        #ifdef INT64_MAX
        case sizeof(uint64_t):
            *(uint64_t*)destination = *(uint64_t*)value_address;
            break;
        #endif  // INT64_MAX

        default:
            DynMemUtilitySetMemory(destination, dynmem_address->element_size,
                                   value_address, dynmem_address->element_size
                                  );
    }

    return DYNMEM_SUCCEED;
}

_Bool DynMemDeduct(dynmem_t *dynmem_address, void *value_address) {
    if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
        return DYNMEM_FAILED;

    if (value_address) {
        void *destination = dynmem_address->memory + dynmem_address->end_index * dynmem_address->element_size;

        switch (dynmem_address->element_size) {
            case sizeof(uint8_t):
                *(uint8_t*)value_address = *(uint8_t*)destination;
                break;
            case sizeof(uint16_t):
                *(uint16_t*)value_address = *(uint16_t*)destination;
                break;
            case sizeof(uint32_t):
                *(uint32_t*)value_address = *(uint32_t*)destination;
                break;

            #ifdef INT64_MAX
            case sizeof(uint64_t):
                *(uint64_t*)value_address = *(uint64_t*)destination;
                break;
            #endif  // INT64_MAX

            default:
                DynMemUtilitySetMemory(value_address, dynmem_address->element_size,
                                       destination, dynmem_address->element_size
                                      );
        }
    }

    if (dynmem_address->end_index == dynmem_address->start_index) {
        dynmem_address->length = dynmem_address->start_index +
                                 (dynmem_address->length - dynmem_address->start_index) / 2;
        dynmem_address->memory = realloc(dynmem_address->memory,
                                         dynmem_address->length * dynmem_address->element_size
                                        );
        if (!dynmem_address->memory) {
            DYNMEM_UTILITY_RESET(dynmem_address);
            return DYNMEM_FAILED;
        }
    }

    if (dynmem_address->end_index >= dynmem_address->start_index)
        dynmem_address->end_index--;

    return DYNMEM_SUCCEED;
}

_Bool DynMemSet(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
    if (index < 0) index += dynmem_address->end_index + 1;
    else           index += dynmem_address->start_index;

    if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || !value_address ||
        index < dynmem_address->start_index || index > dynmem_address->end_index
       )
        return DYNMEM_FAILED;

    switch (dynmem_address->element_size) {
        case sizeof(uint8_t):
            dynmem_address->memory[index] = *(uint8_t*)value_address;
            break;
        case sizeof(uint16_t):
            ((uint16_t*)dynmem_address->memory)[index] = *(uint16_t*)value_address;
            break;
        case sizeof(uint32_t):
            ((uint32_t*)dynmem_address->memory)[index] = *(uint32_t*)value_address;
            break;

        #ifdef INT64_MAX
        case sizeof(uint64_t):
            ((uint64_t*)dynmem_address->memory)[index] = *(uint64_t*)value_address;
            break;
        #endif  // INT64_MAX

        default:
            DynMemUtilitySetMemory(dynmem_address->memory + dynmem_address->element_size * index,
                                   dynmem_address->element_size, value_address, dynmem_address->element_size
                                  );
    }
    return DYNMEM_SUCCEED;
}

_Bool DynMemGet(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
    if (index < 0) index += dynmem_address->end_index + 1;
    else           index += dynmem_address->start_index;

    if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || !value_address ||
        index < dynmem_address->start_index || index > dynmem_address->end_index
       )
        return DYNMEM_FAILED;

    switch (dynmem_address->element_size) {
        case sizeof(uint8_t):
            *(uint8_t*)value_address = dynmem_address->memory[index];
            break;
        case sizeof(uint16_t):
            *(uint16_t*)value_address = ((uint16_t*)dynmem_address->memory)[index];
            break;
        case sizeof(uint32_t):
            *(uint32_t*)value_address = ((uint32_t*)dynmem_address->memory)[index];
            break;

        #ifdef INT64_MAX
        case sizeof(uint64_t):
            *(uint64_t*)value_address = ((uint64_t*)dynmem_address->memory)[index];
            break;
        #endif  // INT64_MAX

        default:
            DynMemUtilitySetMemory(value_address, dynmem_address->element_size,
                                   dynmem_address->memory + dynmem_address->element_size * index,
                                   dynmem_address->element_size
                                  );
    }
    return DYNMEM_SUCCEED;
}
