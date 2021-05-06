#ifndef DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#define DYNMEM_INTERNAL_USE_UTILITY_DEFINES_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#define DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H
#endif
#ifndef DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H
#define DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H
#endif

#include <stdlib.h>

#include "dynmem/dynmem.h"
#include "dynmem/utility/defines.h"
#include "dynmem/utility/utility.h"
#include "dynmem/utility/set-get.h"

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

_Bool DynMemSetForAppending(dynmem_t *dynmem_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   intmax_t begin_end_difference = DYNMEM_UTILITY_GET_SIZE_ADDRESS(dynmem_address);

   if (begin_end_difference != 0)
      DynMemUtilitySetMemoryBlock(dynmem_address->m, dynmem_address->m + dynmem_address->bi, begin_end_difference);

   dynmem_address->bi = 0;
   dynmem_address->ei = begin_end_difference - dynmem_address->es;

   return DYNMEM_SUCCEED;
}

_Bool DynMemSetForPrepending(dynmem_t *dynmem_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   intmax_t begin_end_difference = DYNMEM_UTILITY_GET_SIZE_ADDRESS(dynmem_address);
   intmax_t offset = dynmem_address->cs - dynmem_address->ei - dynmem_address->es;

   if (begin_end_difference != 0 && offset != 0) {
      uint8_t *memory = dynmem_address->m + dynmem_address->bi;
      DynMemUtilitySetMemoryBlockReverse(memory + offset, memory, begin_end_difference);
   }

   dynmem_address->bi += offset;
   dynmem_address->ei += offset;

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

_Bool DynMemSet_s(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   return DynMemUtilitySet(dynmem_address, index, value_address);
}

_Bool DynMemSet(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   return DynMemUtilitySet(dynmem_address, index * dynmem_address->es, value_address);
}

_Bool DynMemGet_s(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   return DynMemUtilityGet(dynmem_address, index, value_address);
}

_Bool DynMemGet(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   return DynMemUtilityGet(dynmem_address, index * dynmem_address->es, value_address);
}

_Bool DynMemSetValues_s(dynmem_t *dynmem_address, intmax_t begin, intmax_t end, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   return DynMemUtilitySetValues(dynmem_address, begin, end, value_address);
}

_Bool DynMemSetValues(dynmem_t *dynmem_address, intmax_t begin, intmax_t end, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   return DynMemUtilitySetValues(dynmem_address, begin * dynmem_address->es, end * dynmem_address->es, value_address);
}

_Bool DynMemGetValues_s(dynmem_t *dynmem_address, intmax_t begin, intmax_t end,
                        void *array, intmax_t size, intmax_t *got_size) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || array == NULL)
      return DYNMEM_FAILED;

   return DynMemUtilityGetValues(dynmem_address, begin, end, array, size, got_size);
}

_Bool DynMemGetValues(dynmem_t *dynmem_address, intmax_t begin, intmax_t end,
                      void *array, intmax_t length, intmax_t *got_length) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || array == NULL)
      return DYNMEM_FAILED;

   _Bool status = DynMemUtilityGetValues(dynmem_address, begin * dynmem_address->es, end * dynmem_address->es,
                                         array, length * dynmem_address->es, got_length);
   if (got_length != NULL)
      *got_length /= dynmem_address->es;

   return status;
}
