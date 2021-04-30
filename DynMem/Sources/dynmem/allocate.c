#ifndef DYNMEM_INTERNAL_USE_utility_defines_h
#define DYNMEM_INTERNAL_USE_utility_defines_h
#endif
#ifndef DYNMEM_INTERNAL_USE_utility_utility_h
#define DYNMEM_INTERNAL_USE_utility_utility_h
#endif

#include <stdlib.h>

#include "dynmem/dynmem.h"
#include "utility/defines.h"

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
   dynmem_address->csh = dynmem_address->is;
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
