#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#define DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_STACK_QUEUE_H
#define DYNMEM_INTERNAL_USE_UTILITY_STACK_QUEUE_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H
#define DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H
#endif

#include "dynmem/utility/defines.h"
#include "dynmem/utility/utility.h"
#include "dynmem/utility/stack-queue.h"
#include "dynmem/utility/set-get.h"

#include <stdlib.h>

_Bool DynMemUtilityAppend(dynmem_t *dynmem_address, void *memory, intmax_t size) {
   intmax_t temporary_size = dynmem_address->ei + size;

   if (temporary_size >= dynmem_address->cs) {
      while (dynmem_address->cs < temporary_size)
         dynmem_address->cs *= 2;

      dynmem_address->m = realloc(dynmem_address->m, dynmem_address->cs);

      if (dynmem_address->m == NULL) {
         DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);
         return DYNMEM_FAILED;
      }
   }

   if (memory == NULL) return DYNMEM_SUCCEED;

   uint8_t *destination = dynmem_address->m + dynmem_address->ei + dynmem_address->es;
   DYNMEM_UTILITY_ASSIGN(size, destination, memory);

   return DYNMEM_SUCCEED;
}
