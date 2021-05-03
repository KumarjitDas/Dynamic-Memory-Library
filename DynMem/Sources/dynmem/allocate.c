#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#define DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_ALLOCATE_H
#define DYNMEM_INTERNAL_USE_UTILITY_ALLOCATE_H
#endif

#include <stdlib.h>

#include "dynmem/dynmem.h"
#include "dynmem/utility/defines.h"
#include "dynmem/utility/utility.h"
#include "dynmem/utility/allocate.h"

_Bool DynMemAllocate(dynmem_t *dynmem_address, intmax_t element_size, intmax_t element_count, void *memory_address) {
   if (dynmem_address == NULL || element_size <= 0 || element_count <= 0)
      return DYNMEM_FAILED;

   dynmem_address->is = element_size * element_count;
   uint8_t **memory_address_ = memory_address;

   if (memory_address_ != NULL && *memory_address_ != NULL) {
      dynmem_address->m = *memory_address_;
      dynmem_address->is /= 2;
      dynmem_address->cs = dynmem_address->is * 2;

      *memory_address_ = NULL;
   } else {
      if (dynmem_address->is < sizeof(intmax_t))
         dynmem_address->is = ((sizeof(intmax_t) + element_size) / element_size) * element_size;

      dynmem_address->cs = dynmem_address->is * 2;
      dynmem_address->m = malloc(dynmem_address->cs);

      if (dynmem_address->m == NULL) {
         DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);
         return DYNMEM_FAILED;
      }
   }

   dynmem_address->es = element_size;
   dynmem_address->bi = dynmem_address->is;
   dynmem_address->ei = dynmem_address->is - element_size;

   return DYNMEM_SUCCEED;
}

_Bool DynMemDeallocate(dynmem_t *dynmem_address) {
   if (dynmem_address == NULL)
      return DYNMEM_FAILED;

   if (dynmem_address->m != NULL)
      free(dynmem_address->m);

   DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);

   return DYNMEM_SUCCEED;
}

_Bool DynMemReduce_s(dynmem_t *dynmem_address, void *memory_address, intmax_t *size_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   return (memory_address == NULL)
              ? DynMemUtilityReduce(dynmem_address)
              : DynMemUtilityReduceToMemory(dynmem_address, memory_address, size_address);
}

_Bool DynMemReduce(dynmem_t *dynmem_address, void *array_address, intmax_t *length_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   intmax_t element_size = dynmem_address->es;
   _Bool return_value = DynMemReduce_s(dynmem_address, array_address, length_address);

   if (length_address != NULL) *length_address = *length_address / element_size;

   return return_value;
}
