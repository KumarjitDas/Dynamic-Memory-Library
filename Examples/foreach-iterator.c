#include <stdio.h>
#include <stdlib.h>

#include "dynmem/dynmem.h"

int main() {
   dynmem_t dynmem;
   int value;

   if (DynMemAllocate(&dynmem, sizeof(int), 4, NULL)) {
      printf("Unable to allocate memory dynamically.\n");
      return 1;
   }

   printf("\nAppending...\n");

   for (int i = 0; i < 20; i++) {
      value = i + 1;

      if (DynMemAppend(&dynmem, &value)) {
         printf("Error appending.\n");
         return 1;
      }

      printf(" %d,", value);
   }

   printf("\nPrepending...\n");

   for (int i = 0; i < 20; i++) {
      value = -i - 1;

      if (DynMemPrepend(&dynmem, &value)) {
         printf("Error appending.\n");
         return 1;
      }

      printf(" %d,", value);
   }

   printf("\nIterating...\n\nContent:");

   DYNMEM_FOREACH_ITERATOR(dynmem, iterator)
   printf(" %d,", DYNMEM_ITERATOR_VALUE(int, iterator));

   if (DynMemDeallocate(&dynmem)) {
      printf("Unable to deallocate memory dynamically.\n");
      return 1;
   }

   return 0;
}
