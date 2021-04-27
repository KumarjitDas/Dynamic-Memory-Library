#ifndef DYNMEM_INTERNAL_USE_utility_defines_h
#   define DYNMEM_INTERNAL_USE_utility_defines_h
#endif
#include "utility/defines.h"

#ifndef DYNMEM_INTERNAL_USE_utility_utility_h
#   define DYNMEM_INTERNAL_USE_utility_utility_h
#endif
#include "utility/utility.h"

void DynMemUtilitySetMemoryBlocks(uint8_t *destination, uint8_t *source, intmax_t size) {
    #ifdef INT64_MAX
    intmax_t factor = sizeof(uint64_t);
    #else
    intmax_t factor = sizeof(uint32_t);
    #endif  // INT64_MAX

    while (factor <= size) {
        #ifdef INT64_MAX
        *(uint64_t*)destination = *(uint64_t*)source;
        #else
        *(uint32_t*)destination = *(uint32_t*)source;
        #endif  // INT64_MAX

        destination += factor;
        source += factor;
        size -= factor;
    }

    if (!size) return;

    #ifdef INT64_MAX
    *(uint32_t*)destination = *(uint32_t*)source;
    destination += sizeof(uint32_t);
    source += sizeof(uint32_t);
    size -= sizeof(uint32_t);
    #endif  // INT64_MAX

    if (!size) return;

    *(uint16_t*)destination = *(uint16_t*)source;
    destination += sizeof(uint16_t);
    source += sizeof(uint16_t);
    size -= sizeof(uint16_t);

    if (!size) return;

    *(uint8_t*)destination = *(uint8_t*)source;
    destination += sizeof(uint8_t);
    source += sizeof(uint8_t);
    size -= sizeof(uint8_t);
}

void DynMemUtilitySetMemory(void *destination, intmax_t destination_size, void *source, intmax_t source_size) {
    intmax_t length = destination_size / source_size;
    while (length--) {
        DynMemUtilitySetMemoryBlocks(destination, source, source_size);
        destination = (uint8_t*)destination + source_size;
    }
    DynMemUtilitySetMemoryBlocks(destination, source, destination_size % source_size);
}
