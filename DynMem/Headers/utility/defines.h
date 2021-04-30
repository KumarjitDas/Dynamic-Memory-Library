#ifndef DYNMEM_utility_defines_h
#define DYNMEM_utility_defines_h

#ifdef DYNMEM_INTERNAL_USE_utility_defines_h

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

#define DYNMEM_UTILITY_VALIDATE(dynmem) (dynmem.es && dynmem.is && dynmem.cs && dynmem.csh && dynmem.m)

#define DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) \
   (dynmem_address->es && dynmem_address->is && dynmem_address->cs && dynmem_address->csh && dynmem_address->m)

#define DYNMEM_UTILITY_RESET(dynmem) \
   {                                 \
      dynmem.es = 0;                 \
      dynmem.is = 0;                 \
      dynmem.cs = 0;                 \
      dynmem.csh = 0;                \
      dynmem.bi = 0;                 \
      dynmem.ei = 0;                 \
      dynmem.m = NULL;               \
   }

#define DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address) \
   {                                                 \
      dynmem_address->es = 0;                        \
      dynmem_address->is = 0;                        \
      dynmem_address->cs = 0;                        \
      dynmem_address->csh = 0;                       \
      dynmem_address->bi = 0;                        \
      dynmem_address->ei = 0;                        \
      dynmem_address->m = NULL;                      \
   }

#ifdef UINT64_MAX
#define DYNMEM_UTILITY_ASSIGN(size, left_value, right_value)            \
   {                                                                    \
      switch (size) {                                                   \
         case sizeof(uint8_t):                                          \
            *(uint8_t *)left_value = *(uint8_t *)right_value;           \
            break;                                                      \
         case sizeof(uint16_t):                                         \
            *(uint16_t *)left_value = *(uint16_t *)right_value;         \
            break;                                                      \
         case sizeof(uint32_t):                                         \
            *(uint32_t *)left_value = *(uint32_t *)right_value;         \
            break;                                                      \
         case sizeof(uint64_t):                                         \
            *(uint64_t *)left_value = *(uint64_t *)right_value;         \
            break;                                                      \
         default:                                                       \
            DynMemUtilitySetMemoryBlock(left_value, right_value, size); \
      }                                                                 \
   }
#else
#define DYNMEM_UTILITY_ASSIGN(size, left_value, right_value)                        \
   {                                                                                \
      switch (size) {                                                               \
         case sizeof(uint8_t):                                                      \
            *(uint8_t *)left_value = *(uint8_t *)right_value;                       \
            break;                                                                  \
         case sizeof(uint16_t):                                                     \
            *(uint16_t *)left_value = *(uint16_t *)right_value;                     \
            break;                                                                  \
         case sizeof(uint32_t):                                                     \
            *(uint32_t *)left_value = *(uint32_t *)right_value;                     \
            break;                                                                  \
            \ default : DynMemUtilitySetMemoryBlock(left_value, right_value, size); \
      }                                                                             \
   }
#endif  // UINT64_MAX

#endif  // DYNMEM_INTERNAL_USE_utility_defines_h

#endif  // DYNMEM_utility_defines_h
