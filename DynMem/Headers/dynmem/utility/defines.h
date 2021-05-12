#ifndef DYNMEM_UTILITY_DEFINES_H
#define DYNMEM_UTILITY_DEFINES_H

#ifdef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H

#include "dynmem_export.h"

#ifndef DYNMEM_UTILITY_EXPORT

#ifdef DYNMEM_UTILITY_TEST
#define DYNMEM_UTILITY_EXPORT DYNMEM_EXPORT
#else
#define DYNMEM_UTILITY_EXPORT
#endif  // DYNMEM_UTILITY_TEST

#endif  // DYNMEM_UTILITY_EXPORT

#ifndef TRUE
#define TRUE (_Bool)(1)
#endif
#ifndef FALSE
#define FALSE (_Bool)(0)
#endif

#ifndef DYNMEM_SUCCEED
#   define DYNMEM_SUCCEED FALSE
#endif
#ifndef DYNMEM_FAILED
#   define DYNMEM_FAILED  TRUE
#endif

#define DYNMEM_UTILITY_GET_SIZE_ADDRESS(dynmem_address) (dynmem_address->ei - dynmem_address->bi + dynmem_address->es)

#define DYNMEM_UTILITY_GET_LENGTH_ADDRESS(dynmem_address) \
   (DYNMEM_UTILITY_GET_SIZE_ADDRESS(dynmem_address) / dynmem_address->es)

#define DYNMEM_UTILITY_BEGIN_END_DIFFERENCE_ADDRESS(dynmem_address) \
   (dynmem_address->ei - dynmem_address->bi + dynmem_address->es)

#define DYNMEM_UTILITY_VALIDATE(dynmem) \
   (dynmem.es > 0 && dynmem.is > 0 && dynmem.cs > 0 && dynmem.m != NULL)

#define DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address)                           \
   (dynmem_address != NULL && dynmem_address->es > 0 && dynmem_address->is > 0 && \
    dynmem_address->cs > 0 && dynmem_address->m != NULL)

#define DYNMEM_UTILITY_RESET(dynmem) \
   {                                 \
      dynmem.es = 0;                 \
      dynmem.is = 0;                 \
      dynmem.cs = 0;                 \
      dynmem.bi = 0;                 \
      dynmem.ei = 0;                 \
      dynmem.m = NULL;               \
   }

#define DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address) \
   {                                                 \
      dynmem_address->es = 0;                        \
      dynmem_address->is = 0;                        \
      dynmem_address->cs = 0;                        \
      dynmem_address->bi = 0;                        \
      dynmem_address->ei = 0;                        \
      dynmem_address->m = NULL;                      \
   }

#ifdef UINT64_MAX
#define DYNMEM_UTILITY_ASSIGN(size, left_value, right_value)                \
   {                                                                        \
      switch (size) {                                                       \
         case sizeof(uint8_t):                                              \
            *(uint8_t *)(left_value) = *(uint8_t *)(right_value);           \
            break;                                                          \
         case sizeof(uint16_t):                                             \
            *(uint16_t *)(left_value) = *(uint16_t *)(right_value);         \
            break;                                                          \
         case sizeof(uint32_t):                                             \
            *(uint32_t *)(left_value) = *(uint32_t *)(right_value);         \
            break;                                                          \
         case sizeof(uint64_t):                                             \
            *(uint64_t *)(left_value) = *(uint64_t *)(right_value);         \
            break;                                                          \
         default:                                                           \
            DynMemUtilitySetMemoryBlock((left_value), (right_value), size); \
      }                                                                     \
   }
#else  // UINT64_MAX
#define DYNMEM_UTILITY_ASSIGN(size, left_value, right_value)                            \
   {                                                                                    \
      switch (size) {                                                                   \
         case sizeof(uint8_t):                                                          \
            *(uint8_t *)(left_value) = *(uint8_t *)(right_value);                       \
            break;                                                                      \
         case sizeof(uint16_t):                                                         \
            *(uint16_t *)(left_value) = *(uint16_t *)(right_value);                     \
            break;                                                                      \
         case sizeof(uint32_t):                                                         \
            *(uint32_t *)(left_value) = *(uint32_t *)(right_value);                     \
            break;                                                                      \
         default : DynMemUtilitySetMemoryBlock((left_value), (right_value), size); \
      }                                                                                 \
   }
#endif  // UINT64_MAX

#endif  // DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H

#endif  // DYNMEM_UTILITY_DEFINES_H
