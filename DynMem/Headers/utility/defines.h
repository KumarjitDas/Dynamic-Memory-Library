#ifndef DYNMEM_utility_defines_h
#define DYNMEM_utility_defines_h

#ifdef DYNMEM_INTERNAL_USE_utility_defines_h

#include "dynmem_export.h"

#ifndef DYNMEM_UTILITY_EXPORT
#   ifdef DYNMEM_UTILITY_TEST
#      define DYNMEM_UTILITY_EXPORT DYNMEM_EXPORT
#   else
#      define DYNMEM_UTILITY_EXPORT
#   endif
#endif  // DYNMEM_UTILITY_EXPORT

#ifndef TRUE
#   define TRUE  (_Bool)(1)
#endif
#ifndef FALSE
#   define FALSE (_Bool)(0)
#endif

#define DYNMEM_UTILITY_VALIDATE(dynmem) (dynmem.element_size && dynmem.length && dynmem.memory)

#define DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) \
    (dynmem_address && dynmem_address->element_size &&  \
     dynmem_address->length && dynmem_address->memory)

#define DYNMEM_UTILITY_RESET(dynmem_address) \
    { dynmem_address->element_size   = 0;    \
      dynmem_address->length         = 0;    \
      dynmem_address->start_index    = 0;    \
      dynmem_address->end_index      = 0;    \
      dynmem_address->memory         = NULL; }

#ifdef INT64_MAX
#   define DYNMEM_UTILITY_ASSIGN(destination, destination_size, source, source_size)        \
        switch (source_size) {                                                              \
            case sizeof(uint8_t):                                                           \
                *(uint8_t*)destination = *(uint8_t*)source;                                 \
                return;                                                                     \
            case sizeof(uint16_t):                                                          \
                *(uint16_t*)destination = *(uint16_t*)source;                               \
                return;                                                                     \
            case sizeof(uint32_t):                                                          \
                *(uint32_t*)destination = *(uint32_t*)source;                               \
                return;                                                                     \
            case sizeof(uint64_t):                                                          \
                *(uint64_t*)destination = *(uint64_t*)source;                               \
                return;                                                                     \
            default:                                                                        \
                DynMemUtilitySetMemory(destination, destination_size, source, source_size); \
        }
#else
#   define DYNMEM_UTILITY_ASSIGN(destination, destination_size, source, source_size)        \
        switch (source_size) {                                                              \
            case sizeof(uint8_t):                                                           \
                *(uint8_t*)destination = *(uint8_t*)source;                                 \
                return;                                                                     \
            case sizeof(uint16_t):                                                          \
                *(uint16_t*)destination = *(uint16_t*)source;                               \
                return;                                                                     \
            case sizeof(uint32_t):                                                          \
                *(uint32_t*)destination = *(uint32_t*)source;                               \
                return;                                                                     \
            default:                                                                        \
                DynMemUtilitySetMemory(destination, destination_size, source, source_size); \
        }
#endif  // INT64_MAX

#endif  // DYNMEM_INTERNAL_USE_utility_defines_h

#endif  // DYNMEM_utility_defines_h
