#ifndef DYNMEM_INTERNAL_USE_utility_defines_h
#define DYNMEM_INTERNAL_USE_utility_defines_h
#endif
#ifndef DYNMEM_INTERNAL_USE_utility_utility_h
#define DYNMEM_INTERNAL_USE_utility_utility_h
#endif

#include <stdlib.h>

#include "dynmem/dynmem.h"
#include "utility/defines.h"
#include "utility/utility.h"

_Bool DynMemReset(dynmem_t *dynmem_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   intmax_t current_size = dynmem_address->is * 2;

   if (dynmem_address->bi > dynmem_address->ei && dynmem_address->cs == current_size)
      DynMemUtilityResetMemory(dynmem_address->m, dynmem_address->cs);

   dynmem_address->cs = current_size;
   dynmem_address->bi = dynmem_address->is;
   dynmem_address->ei = dynmem_address->is - dynmem_address->es;

   if (dynmem_address->m != NULL && dynmem_address->cs != current_size) {
      dynmem_address->m = realloc(dynmem_address->m, dynmem_address->cs);

      if (dynmem_address->m == NULL) {
         DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);
         return DYNMEM_FAILED;
      }
   }

   DynMemUtilityResetMemory(dynmem_address->m, dynmem_address->cs);

   return DYNMEM_SUCCEED;
}
