#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#define DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_STACK_QUEUE_H
#define DYNMEM_INTERNAL_USE_UTILITY_STACK_QUEUE_H
#endif

#include "dynmem/dynmem.h"
#include "dynmem/utility/defines.h"
#include "dynmem/utility/utility.h"
#include "dynmem/utility/stack-queue.h"

_Bool DynMemAppend(dynmem_t *dynmem_address, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL ||
       DynMemUtilityAppend(dynmem_address, value_address, dynmem_address->es) == DYNMEM_FAILED)
      return DYNMEM_FAILED;

   dynmem_address->ei += dynmem_address->es;
   return DYNMEM_SUCCEED;
}

_Bool DynMemPrepend(dynmem_t *dynmem_address, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL ||
       DynMemUtilityPrepend(dynmem_address, value_address, dynmem_address->es) == DYNMEM_FAILED)
      return DYNMEM_FAILED;

   dynmem_address->bi -= dynmem_address->es;
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

_Bool DynMemAppendValues(dynmem_t *dynmem_address, void *value_address, intmax_t count) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL || count <= 0)
      return DYNMEM_FAILED;

   count *= dynmem_address->es;

   if (DynMemUtilityAppend(dynmem_address, NULL, count) == DYNMEM_FAILED)
      return DYNMEM_FAILED;

   DynMemUtilitySetMemory(dynmem_address->m + dynmem_address->ei + dynmem_address->es, count,
                          value_address, dynmem_address->es);
   dynmem_address->ei += count;

   return DYNMEM_SUCCEED;
}

_Bool DynMemPrependValues(dynmem_t *dynmem_address, void *value_address, intmax_t count) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL || count <= 0)
      return DYNMEM_FAILED;

   count *= dynmem_address->es;

   if (DynMemUtilityPrepend(dynmem_address, NULL, count) == DYNMEM_FAILED)
      return DYNMEM_FAILED;

   dynmem_address->bi -= count;
   DynMemUtilitySetMemory(dynmem_address->m + dynmem_address->bi, count, value_address, dynmem_address->es);

   return DYNMEM_SUCCEED;
}

_Bool DynMemAppendArray(dynmem_t *dynmem_address, void *array, intmax_t length) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || array == NULL || length <= 0)
      return DYNMEM_FAILED;

   length *= dynmem_address->es;

   if (DynMemUtilityAppend(dynmem_address, array, length) == DYNMEM_FAILED)
      return DYNMEM_FAILED;

   dynmem_address->ei += length;
   return DYNMEM_SUCCEED;
}

_Bool DynMemPrependArray(dynmem_t *dynmem_address, void *array, intmax_t length) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || array == NULL || length <= 0)
      return DYNMEM_FAILED;

   length *= dynmem_address->es;

   if (DynMemUtilityPrepend(dynmem_address, array, length) == DYNMEM_FAILED)
      return DYNMEM_FAILED;

   dynmem_address->bi -= length;
   return DYNMEM_SUCCEED;
}
