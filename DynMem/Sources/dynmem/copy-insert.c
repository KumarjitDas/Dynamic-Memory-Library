#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#define DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#endif

#include "dynmem/utility/defines.h"
#include "dynmem/utility/utility.h"
#include "dynmem/dynmem.h"

#include <stdlib.h>

_Bool DynMemCopy(dynmem_t *destination_address, dynmem_t *source_address) {
   if (destination_address == NULL || !DYNMEM_UTILITY_VALIDATE_ADDRESS(source_address))
      return DYNMEM_FAILED;

   destination_address->cs = source_address->cs;
   destination_address->m = malloc(destination_address->cs);

   if (destination_address->m == NULL) {
      DYNMEM_UTILITY_RESET_ADDRESS(destination_address);
      return DYNMEM_FAILED;
   }

   intmax_t size = DYNMEM_UTILITY_GET_SIZE_ADDRESS(source_address);

   if (size > 0)
      DynMemUtilitySetMemoryBlock(destination_address->m + source_address->bi,
                                  source_address->m + source_address->bi, size);

   destination_address->es = source_address->es;
   destination_address->is = source_address->is;
   destination_address->bi = source_address->bi;
   destination_address->ei = source_address->ei;

   return DYNMEM_SUCCEED;
}

_Bool DynMemCopyInitial(dynmem_t *destination_address, dynmem_t *source_address) {
   if (destination_address == NULL || !DYNMEM_UTILITY_VALIDATE_ADDRESS(source_address))
      return DYNMEM_FAILED;

   destination_address->cs = source_address->is * 2;
   destination_address->m = malloc(destination_address->cs);

   if (destination_address->m == NULL) {
      DYNMEM_UTILITY_RESET_ADDRESS(destination_address);
      return DYNMEM_FAILED;
   }

   destination_address->es = source_address->es;
   destination_address->is = source_address->is;
   destination_address->bi = source_address->is;
   destination_address->ei = source_address->is - source_address->es;

   return DYNMEM_SUCCEED;
}
