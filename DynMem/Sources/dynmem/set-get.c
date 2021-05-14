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

_Bool DynMemGetEndIndex_s(dynmem_t *dynmem_address, intmax_t *index_address_s) {
   if (index_address_s == NULL)
      return DYNMEM_FAILED;
   else
      *index_address_s = -1;

   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   if (dynmem_address->bi <= dynmem_address->ei)
      *index_address_s = dynmem_address->ei - dynmem_address->bi;

   return DYNMEM_SUCCEED;
}

_Bool DynMemGetEndIndex(dynmem_t *dynmem_address, intmax_t *index_address) {
   if (index_address == NULL)
      return DYNMEM_FAILED;
   else
      *index_address = -1;

   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   if (dynmem_address->bi <= dynmem_address->ei)
      *index_address = (dynmem_address->ei - dynmem_address->bi) / dynmem_address->es;

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

_Bool DynMemGetBegin(dynmem_t *dynmem_address, void *pointer_address) {
   if (pointer_address == NULL)
      return DYNMEM_FAILED;
   else
      *(void **)pointer_address = NULL;

   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   if (dynmem_address->ei >= dynmem_address->bi) {
      *(void **)pointer_address = dynmem_address->m + dynmem_address->bi;
      return DYNMEM_SUCCEED;
   }

   return DYNMEM_FAILED;
}

_Bool DynMemGetEnd(dynmem_t *dynmem_address, void *pointer_address) {
   if (pointer_address == NULL)
      return DYNMEM_FAILED;
   else
      *(void **)pointer_address = NULL;

   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   if (dynmem_address->ei >= dynmem_address->bi) {
      *(void **)pointer_address = dynmem_address->m + dynmem_address->ei;
      return DYNMEM_SUCCEED;
   }

   return DYNMEM_FAILED;
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

   dynmem_address->bi = ((dynmem_address->cs / dynmem_address->es) / 2) * dynmem_address->es;
   dynmem_address->ei = dynmem_address->bi - dynmem_address->es;

   return DYNMEM_SUCCEED;
}

_Bool DynMemResetMemory(dynmem_t *dynmem_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address))
      return DYNMEM_FAILED;

   intmax_t current_size = dynmem_address->is * 2;

   if (dynmem_address->cs != current_size) {
      dynmem_address->m = realloc(dynmem_address->m, current_size);

      if (dynmem_address->m == NULL) {
         DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address);
         return DYNMEM_FAILED;
      }
   }

   dynmem_address->bi = dynmem_address->is;
   dynmem_address->ei = dynmem_address->is - dynmem_address->es;
   dynmem_address->cs = current_size;

   return DYNMEM_SUCCEED;
}

_Bool DynMemSet_s(dynmem_t *dynmem_address, intmax_t index_s, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   index_s += (index_s < 0 ? dynmem_address->ei + dynmem_address->es
                           : dynmem_address->bi);
   if (index_s < dynmem_address->bi || index_s > dynmem_address->ei)
      return DYNMEM_FAILED;

   void *destination = dynmem_address->m + index_s;
   DYNMEM_UTILITY_ASSIGN(dynmem_address->es, destination, value_address);

   return DYNMEM_SUCCEED;
}

_Bool DynMemSet(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   index *= dynmem_address->es;
   index += (index < 0 ? dynmem_address->ei + dynmem_address->es
                       : dynmem_address->bi);
   if (index < dynmem_address->bi || index > dynmem_address->ei)
      return DYNMEM_FAILED;

   void *destination = dynmem_address->m + index;
   DYNMEM_UTILITY_ASSIGN(dynmem_address->es, destination, value_address);

   return DYNMEM_SUCCEED;
}

_Bool DynMemGet_s(dynmem_t *dynmem_address, intmax_t index_s, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   index_s += (index_s < 0 ? dynmem_address->ei + dynmem_address->es
                           : dynmem_address->bi);
   if (index_s < dynmem_address->bi || index_s > dynmem_address->ei)
      return DYNMEM_FAILED;

   void *destination = dynmem_address->m + index_s;
   DYNMEM_UTILITY_ASSIGN(dynmem_address->es, value_address, destination);

   return DYNMEM_SUCCEED;
}

_Bool DynMemGet(dynmem_t *dynmem_address, intmax_t index, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   index *= dynmem_address->es;
   index += (index < 0 ? dynmem_address->ei + dynmem_address->es
                       : dynmem_address->bi);
   if (index < dynmem_address->bi || index > dynmem_address->ei)
      return DYNMEM_FAILED;

   void *destination = dynmem_address->m + index;
   DYNMEM_UTILITY_ASSIGN(dynmem_address->es, value_address, destination);

   return DYNMEM_SUCCEED;
}

_Bool DynMemSetValues_s(dynmem_t *dynmem_address, intmax_t begin_s, intmax_t end_s, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   begin_s += (begin_s < 0 ? dynmem_address->ei + dynmem_address->es
                           : dynmem_address->bi);
   if (begin_s < dynmem_address->bi || begin_s > dynmem_address->ei)
      return DYNMEM_FAILED;

   end_s += (end_s < 0 ? dynmem_address->ei + dynmem_address->es
                       : dynmem_address->bi);
   if (end_s < dynmem_address->bi || end_s > dynmem_address->ei || end_s < begin_s)
      return DYNMEM_FAILED;

   DynMemUtilitySetMemory(dynmem_address->m + begin_s, end_s - begin_s + dynmem_address->es,
                          value_address, dynmem_address->es);
   return DYNMEM_SUCCEED;
}

_Bool DynMemSetValues(dynmem_t *dynmem_address, intmax_t begin, intmax_t end, void *value_address) {
   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || value_address == NULL)
      return DYNMEM_FAILED;

   begin *= dynmem_address->es;
   begin += (begin < 0 ? dynmem_address->ei + dynmem_address->es
                       : dynmem_address->bi);
   if (begin < dynmem_address->bi || begin > dynmem_address->ei)
      return DYNMEM_FAILED;

   end *= dynmem_address->es;
   end += (end < 0 ? dynmem_address->ei + dynmem_address->es
                   : dynmem_address->bi);
   if (end < dynmem_address->bi || end > dynmem_address->ei || end < begin)
      return DYNMEM_FAILED;

   DynMemUtilitySetMemory(dynmem_address->m + begin, end - begin + dynmem_address->es,
                          value_address, dynmem_address->es);
   return DYNMEM_SUCCEED;
}

_Bool DynMemGetValues_s(dynmem_t *dynmem_address, intmax_t begin_s, intmax_t end_s,
                        void *memory, intmax_t size, intmax_t *got_size) {
   if (got_size != NULL) *got_size = 0;

   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || memory == NULL)
      return DYNMEM_FAILED;

   begin_s += (begin_s < 0 ? dynmem_address->ei + dynmem_address->es
                           : dynmem_address->bi);
   if (begin_s < dynmem_address->bi || begin_s > dynmem_address->ei)
      return DYNMEM_FAILED;

   end_s += (end_s < 0 ? dynmem_address->ei + dynmem_address->es
                       : dynmem_address->bi);
   if (end_s < dynmem_address->bi || end_s > dynmem_address->ei || end_s < begin_s)
      return DYNMEM_FAILED;

   intmax_t temporary_size = end_s - begin_s + dynmem_address->es;

   if (size <= 0 || size > temporary_size)
      size = temporary_size;

   DynMemUtilitySetMemoryBlock(memory, dynmem_address->m + begin_s, size);

   if (got_size != NULL) *got_size = size;

   return DYNMEM_SUCCEED;
}

_Bool DynMemGetValues(dynmem_t *dynmem_address, intmax_t begin, intmax_t end,
                      void *array, intmax_t length, intmax_t *got_length) {
   if (got_length != NULL) *got_length = 0;

   if (!DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address) || array == NULL)
      return DYNMEM_FAILED;

   begin *= dynmem_address->es;
   begin += (begin < 0 ? dynmem_address->ei + dynmem_address->es
                       : dynmem_address->bi);
   if (begin < dynmem_address->bi || begin > dynmem_address->ei)
      return DYNMEM_FAILED;

   end *= dynmem_address->es;
   end += (end < 0 ? dynmem_address->ei + dynmem_address->es
                   : dynmem_address->bi);
   if (end < dynmem_address->bi || end > dynmem_address->ei || end < begin)
      return DYNMEM_FAILED;

   length *= dynmem_address->es;
   intmax_t temporary_size = end - begin + dynmem_address->es;

   if (length <= 0 || length > temporary_size)
      length = temporary_size;

   DynMemUtilitySetMemoryBlock(array, dynmem_address->m + begin, length);

   if (got_length != NULL) *got_length = length / dynmem_address->es;

   return DYNMEM_SUCCEED;
}
