#ifndef DYNMEM_INTERNAL_USE_utility_defines_h
#   define DYNMEM_INTERNAL_USE_utility_defines_h
#endif
#include "utility/defines.h"

#ifndef DYNMEM_INTERNAL_USE_utility_utility_h
#   define DYNMEM_INTERNAL_USE_utility_utility_h
#endif
#include "utility/utility.h"

#ifdef INT64_MAX
#   define MAX_BUFFER_SIZE (sizeof(int64_t) * 2 + sizeof(int32_t) + sizeof(int16_t) + sizeof(int8_t))
#else
#   define MAX_BUFFER_SIZE (sizeof(int32_t) * 2 + sizeof(int16_t) + sizeof(int8_t))
#endif  // INT64_MAX

int main() {
    uint8_t destination[MAX_BUFFER_SIZE];
    uint8_t source[MAX_BUFFER_SIZE];
    uint8_t *src = source;

    #ifdef INT64_MAX
    *(uint64_t*)src = 12345678910111213; src += sizeof(uint64_t);
    *(uint64_t*)src = 14151617181920212; src += sizeof(uint64_t);
    *(uint32_t*)src = 123456789;         src += sizeof(uint32_t);
    #else
    *(uint32_t*)src = 123456789; src += sizeof(uint32_t);
    *(uint32_t*)src = 101112131; src += sizeof(uint32_t);
    #endif  // INT64_MAX
    *(uint16_t*)src = 12345;     src += sizeof(uint16_t);
    *src = 123;

    DynMemUtilitySetMemoryBlocks(destination, source, MAX_BUFFER_SIZE);

    int result = 1;
    uint8_t *dest = destination;
    src = source;

    #ifdef INT64_MAX
    result &= *(uint64_t*)dest == *(uint64_t*)src; dest += sizeof(uint64_t); src += sizeof(uint64_t);
    result &= *(uint64_t*)dest == *(uint64_t*)src; dest += sizeof(uint64_t); src += sizeof(uint64_t);
    result &= *(uint32_t*)dest == *(uint32_t*)src; dest += sizeof(uint32_t); src += sizeof(uint32_t);
    #else
    result &= *(uint32_t*)dest == *(uint32_t*)src; dest += sizeof(uint32_t); src += sizeof(uint32_t);
    result &= *(uint32_t*)dest == *(uint32_t*)src; dest += sizeof(uint32_t); src += sizeof(uint32_t);
    #endif  // INT64_MAX
    result &= *(uint16_t*)dest == *(uint16_t*)src; dest += sizeof(uint16_t); src += sizeof(uint16_t);
    result &= *dest             == *src;

    return !result;
}
