#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H
#define DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H
#endif

#include "dynmem/utility/defines.h"
#include "dynmem/utility/set-get.h"

_Bool DynMemUtilitySet(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
   index += dynmem_address->bi;

   if (index < 0) index += (dynmem_address->ei + dynmem_address->es);

   if (index < dynmem_address->bi || index > dynmem_address->ei)
      return DYNMEM_FAILED;

   void *destination = dynmem_address->m + index;
   DYNMEM_UTILITY_ASSIGN(dynmem_address->es, destination, value_address);

   return DYNMEM_SUCCEED;
}

_Bool DynMemUtilityGet(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
   index += dynmem_address->bi;

   if (index < 0) index += (dynmem_address->ei + dynmem_address->es);

   if (index < dynmem_address->bi || index > dynmem_address->ei)
      return DYNMEM_FAILED;

   void *destination = dynmem_address->m + index;
   DYNMEM_UTILITY_ASSIGN(dynmem_address->es, value_address, destination);

   return DYNMEM_SUCCEED;
}

_Bool DynMemUtilitySetValues(dynmem_t *dynmem_address, intmax_t begin, intmax_t end, void *value_address) {
   begin += dynmem_address->bi;
   intmax_t end_offset = dynmem_address->ei + dynmem_address->es;

   if (begin < 0) begin += end_offset;

   if (begin < dynmem_address->bi || begin > dynmem_address->ei)
      return DYNMEM_FAILED;

   end += dynmem_address->bi;

   if (end < 0) end += (end_offset + dynmem_address->es);

   if (end <= begin || end < dynmem_address->bi || end > end_offset)
      return DYNMEM_FAILED;

   DynMemUtilitySetMemory(dynmem_address->m + begin, end - begin, value_address, dynmem_address->es);

   return DYNMEM_SUCCEED;
}
