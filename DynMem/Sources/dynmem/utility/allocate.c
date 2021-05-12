#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#define DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_ALLOCATE_H
#define DYNMEM_INTERNAL_USE_UTILITY_ALLOCATE_H
#endif

#include "dynmem/utility/defines.h"
#include "dynmem/utility/utility.h"
#include "dynmem/utility/allocate.h"

#include <stdlib.h>

_Bool DynMemUtilityReduce(dynmem_t *dynmem_address) {
   intmax_t begin_end_difference = DYNMEM_UTILITY_GET_SIZE_ADDRESS(dynmem_address);
   intmax_t half_size = dynmem_address->cs / 2;
   intmax_t temporary_half_size = half_size;

   while (half_size > dynmem_address->is && half_size >= begin_end_difference)
      half_size /= 2;

   dynmem_address->cs = half_size * 2;
   intmax_t begin_index = (((dynmem_address->cs - begin_end_difference) / dynmem_address->es) / 2) *
                          dynmem_address->es;

   if (temporary_half_size == half_size && begin_index == dynmem_address->bi)
      return DYNMEM_SUCCEED;

   if (begin_index < dynmem_address->bi)
      DynMemUtilitySetMemoryBlock(dynmem_address->m + begin_index, dynmem_address->m + dynmem_address->bi,
                                  begin_end_difference);
   else
      DynMemUtilitySetMemoryBlockReverse(dynmem_address->m + begin_index, dynmem_address->m + dynmem_address->bi,
                                         begin_end_difference);

   dynmem_address->m = realloc(dynmem_address->m, dynmem_address->cs);

   if (dynmem_address->m == NULL) {
      DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);
      return DYNMEM_FAILED;
   }

   dynmem_address->bi = begin_index;
   dynmem_address->ei = begin_index + begin_end_difference - dynmem_address->es;

   return DYNMEM_SUCCEED;
}

_Bool DynMemUtilityReduceToMemory(dynmem_t *dynmem_address, void *memory_address, intmax_t *size_address) {
   uint8_t **temporary_memory_address = memory_address;
   *temporary_memory_address = NULL;

   if (size_address != NULL) *size_address = 0;

   intmax_t begin_end_difference = DYNMEM_UTILITY_GET_SIZE_ADDRESS(dynmem_address);

   if (begin_end_difference == 0) {
      free(dynmem_address->m);
      DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);

      *(void **)memory_address = NULL;

      return DYNMEM_FAILED;
   }

   if (dynmem_address->bi != 0)
      DynMemUtilitySetMemoryBlock(dynmem_address->m, dynmem_address->m + dynmem_address->bi, begin_end_difference);

   if (size_address != NULL) *size_address = begin_end_difference;

   *temporary_memory_address = realloc(dynmem_address->m, begin_end_difference);
   DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);

   return (*temporary_memory_address == NULL) ? DYNMEM_FAILED : DYNMEM_SUCCEED;
}
