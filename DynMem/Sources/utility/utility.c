#ifndef DYNMEM_INTERNAL_USE_utility_defines_h
#   define DYNMEM_INTERNAL_USE_utility_defines_h
#endif
#include "utility/defines.h"

#ifndef DYNMEM_INTERNAL_USE_utility_utility_h
#   define DYNMEM_INTERNAL_USE_utility_utility_h
#endif
#include "utility/utility.h"

void DynMemUtilitySetMemory(void *destination, intmax_t destination_size, void *source, intmax_t source_size) {
    uint8_t *destination_ = destination;
    uint8_t *source_      = source;

    for (intmax_t i = 0; i < destination_size;)
        for (intmax_t j = 0; j < source_size && i < destination_size; j++, i++)
            destination_[i] = source_[j];
}
