#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#define DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_STACK_QUEUE_H
#define DYNMEM_INTERNAL_USE_UTILITY_STACK_QUEUE_H
#endif

#include <stdio.h>
#include <stdlib.h>

#include "dynmem/dynmem.h"
#include "dynmem/utility/defines.h"
#include "dynmem/utility/utility.h"
#include "dynmem/utility/stack-queue.h"

_Bool DynMemAppend(dynmem_t *dynmem_address, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   _Bool status = DynMemUtilityAppend(dynmem_address, value_address, dynmem_address->es);
   dynmem_address->ei += dynmem_address->es;

   return status;
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
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || dynmem_address->ei < dynmem_address->bi)
      return DYNMEM_FAILED;

   if (value_address != NULL) {
      uint8_t *destination = dynmem_address->m + dynmem_address->ei;
      DYNMEM_UTILITY_ASSIGN(dynmem_address->es, value_address, destination);
   }

   dynmem_address->ei -= dynmem_address->es;

   return DYNMEM_SUCCEED;
}

_Bool DynMemDeductFront(dynmem_t *dynmem_address, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || dynmem_address->bi > dynmem_address->ei)
      return DYNMEM_FAILED;

   if (value_address != NULL) {
      uint8_t *destination = dynmem_address->m + dynmem_address->bi;
      DYNMEM_UTILITY_ASSIGN(dynmem_address->es, value_address, destination);
   }

   dynmem_address->bi += dynmem_address->es;

   return DYNMEM_SUCCEED;
}