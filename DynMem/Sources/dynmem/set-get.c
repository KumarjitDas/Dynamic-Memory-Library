#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#define DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#endif

#include <stdlib.h>

#include "dynmem/dynmem.h"
#include "dynmem/utility/defines.h"
#include "dynmem/utility/utility.h"

_Bool DynMemSetElementSize(dynmem_t *dynmem_address, intmax_t size) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || size <= 0)
      return DYNMEM_FAILED;

   dynmem_address->es = size;

   return DYNMEM_SUCCEED;
}

_Bool DynMemGetElementSize(dynmem_t *dynmem_address, intmax_t *size_address) {
   if (size_address == NULL)
      return DYNMEM_FAILED;
   else
      *size_address = 0;

   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   *size_address = dynmem_address->es;

   return DYNMEM_SUCCEED;
}

_Bool DynMemGetSize(dynmem_t *dynmem_address, intmax_t *size_address) {
   if (size_address == NULL)
      return DYNMEM_FAILED;
   else
      *size_address = 0;

   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   *size_address = DYNMEM_UTILITY_GET_SIZE_ADDRESS(dynmem_address);

   return DYNMEM_SUCCEED;
}

_Bool DynMemGetLength(dynmem_t *dynmem_address, intmax_t *length_address) {
   if (length_address == NULL)
      return DYNMEM_FAILED;
   else
      *length_address = 0;

   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   *length_address = DYNMEM_UTILITY_GET_LENGTH_ADDRESS(dynmem_address);

   return DYNMEM_SUCCEED;
}

_Bool DynMemGetPointer(dynmem_t *dynmem_address, void *pointer_address) {
   if (pointer_address == NULL)
      return DYNMEM_FAILED;
   else
      *(void **)pointer_address = NULL;

   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   *(void **)pointer_address = dynmem_address->m + dynmem_address->bi;

   return DYNMEM_SUCCEED;
}

_Bool DynMemGetHeapSize(dynmem_t *dynmem_address, intmax_t *size_address) {
   if (size_address == NULL)
      return DYNMEM_FAILED;
   else
      *size_address = 0;

   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   *size_address = dynmem_address->cs;

   return DYNMEM_SUCCEED;
}

_Bool DynMemGetHeapPointer(dynmem_t *dynmem_address, void *pointer_address) {
   if (pointer_address == NULL)
      return DYNMEM_FAILED;
   else
      *(void **)pointer_address = NULL;

   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   *(void **)pointer_address = dynmem_address->m;

   return DYNMEM_SUCCEED;
}

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

_Bool DynMemSet(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   index = index * dynmem_address->es + dynmem_address->bi;

   if (index < 0) index += (dynmem_address->ei + dynmem_address->es);

   if (index < dynmem_address->bi || index > dynmem_address->ei)
      return DYNMEM_FAILED;

   void *destination = dynmem_address->m + index;
   DYNMEM_UTILITY_ASSIGN(dynmem_address->es, destination, value_address);

   return DYNMEM_SUCCEED;
}

_Bool DynMemGet(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   index = index * dynmem_address->es + dynmem_address->bi;

   if (index < 0) index += (dynmem_address->ei + dynmem_address->es);

   if (index < dynmem_address->bi || index > dynmem_address->ei)
      return DYNMEM_FAILED;

   void *destination = dynmem_address->m + index;
   DYNMEM_UTILITY_ASSIGN(dynmem_address->es, value_address, destination);

   return DYNMEM_SUCCEED;
}

_Bool DynMemSetValues(dynmem_t *dynmem_address, intmax_t begin, intmax_t end, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   begin = begin * dynmem_address->es + dynmem_address->bi;
   intmax_t end_offset = dynmem_address->ei + dynmem_address->es;

   if (begin < 0) begin += end_offset;

   if (begin < dynmem_address->bi || begin > dynmem_address->ei)
      return DYNMEM_FAILED;

   end = end * dynmem_address->es + dynmem_address->bi;

   if (end < 0) end += (end_offset + dynmem_address->es);

   if (end <= begin || end < dynmem_address->bi || end > end_offset)
      return DYNMEM_FAILED;

   DynMemUtilitySetMemory(dynmem_address->m + begin, end - begin, value_address, dynmem_address->es);

   return DYNMEM_SUCCEED;
}
