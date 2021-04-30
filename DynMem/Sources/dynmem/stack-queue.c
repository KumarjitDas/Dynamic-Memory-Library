#ifndef DYNMEM_INTERNAL_USE_utility_defines_h
#define DYNMEM_INTERNAL_USE_utility_defines_h
#endif
#ifndef DYNMEM_INTERNAL_USE_utility_utility_h
#define DYNMEM_INTERNAL_USE_utility_utility_h
#endif

#include <stdio.h>
#include <stdlib.h>

#include "dynmem/dynmem.h"
#include "utility/defines.h"
#include "utility/utility.h"

_Bool DynMemAppend(dynmem_t *dynmem_address, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   dynmem_address->ei += dynmem_address->es;

   if (dynmem_address->ei == dynmem_address->cs) {
      dynmem_address->cs *= 2;
      dynmem_address->m = realloc(dynmem_address->m, dynmem_address->cs);

      if (dynmem_address->m == NULL) {
         DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);
         return DYNMEM_FAILED;
      }

      dynmem_address->csh *= 2;
   }

   if (value_address == NULL) return DYNMEM_SUCCEED;

   uint8_t *destination = dynmem_address->m + dynmem_address->ei;
   DYNMEM_UTILITY_ASSIGN(dynmem_address->es, destination, value_address);

   return DYNMEM_SUCCEED;
}

_Bool DynMemPrepend(dynmem_t *dynmem_address, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   dynmem_address->bi -= dynmem_address->es;

   if (dynmem_address->bi < 0) {
      intmax_t size = dynmem_address->cs * 2;
      dynmem_address->m = realloc(dynmem_address->m, size);

      if (dynmem_address->m == NULL) {
         DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);
         return DYNMEM_FAILED;
      }

      DynMemUtilitySetMemoryBlock(dynmem_address->m + dynmem_address->cs, dynmem_address->m,
                                  dynmem_address->ei + dynmem_address->es);
      dynmem_address->csh *= 2;
      dynmem_address->bi += dynmem_address->cs;
      dynmem_address->ei += dynmem_address->cs;
      dynmem_address->cs = size;
   }

   if (value_address == NULL) return DYNMEM_SUCCEED;

   uint8_t *destination = dynmem_address->m + dynmem_address->bi;
   DYNMEM_UTILITY_ASSIGN(dynmem_address->es, destination, value_address);

   return DYNMEM_SUCCEED;
}

_Bool DynMemDeduct(dynmem_t *dynmem_address, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   if (value_address != NULL) {
      uint8_t *destination = dynmem_address->m + dynmem_address->bi;
      DYNMEM_UTILITY_ASSIGN(dynmem_address->es, value_address, destination);
   }

   if (dynmem_address->ei >= dynmem_address->bi)
      dynmem_address->ei -= dynmem_address->es;
   else
      return DYNMEM_SUCCEED;

   if (dynmem_address->csh <= dynmem_address->is)
      return DYNMEM_SUCCEED;

   intmax_t size = 0;

   if (dynmem_address->ei < dynmem_address->bi && dynmem_address->csh > dynmem_address->is) {
      size = dynmem_address->is * 2;
      dynmem_address->cs = size;
      dynmem_address->csh = dynmem_address->is;
      dynmem_address->bi = dynmem_address->is;
      dynmem_address->ei = dynmem_address->is - dynmem_address->es;
   } else if (dynmem_address->ei < dynmem_address->csh) {
      size = dynmem_address->csh;
      dynmem_address->cs = dynmem_address->csh;
      dynmem_address->csh /= 2;
   }

   if (size > 0) {
      dynmem_address->m = realloc(dynmem_address->m, size);

      if (dynmem_address->m == NULL) {
         DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);
         return DYNMEM_FAILED;
      }
   }

   return DYNMEM_SUCCEED;
}