#include "dynmem/dynmem.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
   dynmem_t dynmem;
   int value;

   if (DynMemAllocate(&dynmem, sizeof(int), 4, NULL)) {
      printf("Unable to allocate memory dynamically.\n");
      return 1;
   }

//    printf("\nAppending...\n\n");
//
//    for (int i = 0; i < 65; i++) {
//       value = i + 1;
//       if (DynMemAppend(&dynmem, &value)) {
//          printf("Error appending.\n");
//          return 1;
//       }
//
//       for (intmax_t j = dynmem.bi; j <= dynmem.ei; j += dynmem.es)
//          printf("%lld: %d, ", j, *(int *)(dynmem.m + j));
//
//       printf("\n---- bi: %lld - ei: %lld, cs: %lld ----\n", dynmem.bi, dynmem.ei, dynmem.cs);
//    }
//
//    printf("\nDeducting...\n\n");
//
//    for (int i = 0; i < 65, !DynMemDeduct(&dynmem, &value); i++) {
//       printf("-- %d deducted --\n", value);
//
//       for (intmax_t j = dynmem.bi; j <= dynmem.ei; j += dynmem.es)
//          printf("%lld: %d, ", j, *(int *)(dynmem.m + j));
//
//       printf("\n---- bi: %lld - ei: %lld, cs: %lld ----\n", dynmem.bi, dynmem.ei, dynmem.cs);
//    }
//
//    if (DynMemReduce(&dynmem, NULL, NULL)) {
//       printf("Unable to reduce memory.\n");
//       return 1;
//    }
//
//    printf("\nAfter reducing:~ bi: %lld, ei: %lld, cs: %lld ----\n", dynmem.bi, dynmem.ei, dynmem.cs);
//
//    printf("\nAppending again...\n\n");
//
//    for (int i = 0; i < 10; i++) {
//       value = i + 1;
//       if (DynMemAppend(&dynmem, &value)) {
//          printf("Error appending.\n");
//          return 1;
//       }
//
//       for (intmax_t j = dynmem.bi; j <= dynmem.ei; j += dynmem.es)
//          printf("%lld: %d, ", j, *(int *)(dynmem.m + j));
//
//       printf("\n---- bi: %lld - ei: %lld, cs: %lld ----\n", dynmem.bi, dynmem.ei, dynmem.cs);
//    }

   printf("\nPrepending...\n\n");

   for (int i = 0; i < 65; i++) {
      value = i + 1;
      if (DynMemPrepend(&dynmem, &value)) {
         printf("Error appending.\n");
         return 1;
      }

      for (intmax_t j = dynmem.bi; j <= dynmem.ei; j += dynmem.es)
         printf("%lld: %d, ", j, *(int *)(dynmem.m + j));

      printf("\n---- bi: %lld - ei: %lld, cs: %lld ----\n", dynmem.bi, dynmem.ei, dynmem.cs);
   }

//    printf("\nDeducting front...\n\n");
//
//    for (int i = 0; i < 25 && !DynMemDeductFront(&dynmem, &value); i++) {
//       printf("-- %d deducted --\n", value);
//
//       for (intmax_t j = dynmem.bi; j <= dynmem.ei; j += dynmem.es)
//          printf("%lld: %d, ", j, *(int *)(dynmem.m + j));
//
//       printf("\n---- bi: %lld - ei: %lld, cs: %lld ----\n", dynmem.bi, dynmem.ei, dynmem.cs);
//    }

   int *array = NULL;
   intmax_t size, length;

   if (DynMemReduce(&dynmem, &array, &size)) {
      printf("Unable to reduce memory.\n");
      return 1;
   }

   length = size / sizeof(int);

   printf("\nAfter reducing:~ bi: %lld, ei: %lld, cs: %lld ----\n", dynmem.bi, dynmem.ei, dynmem.cs);
   printf("\nArray content:");

   for (intmax_t i = 0; i < length; i++)
      printf(" [%lld]: %d,", i, array[i]);

//    printf("\nAppending again...\n\n");
//
//    for (int i = 0; i < 10; i++) {
//       value = i + 1;
//       if (DynMemAppend(&dynmem, &value)) {
//          printf("Error appending.\n");
//          return 1;
//       }
//
//       for (intmax_t j = dynmem.bi; j <= dynmem.ei; j += dynmem.es)
//          printf("%lld: %d, ", j, *(int *)(dynmem.m + j));
//
//       printf("\n---- bi: %lld - ei: %lld, cs: %lld ----\n", dynmem.bi, dynmem.ei, dynmem.cs);
//    }

   if (array != NULL) free(array);

   if (DynMemDeallocate(&dynmem)) {
      printf("Unable to deallocate memory dynamically.\n");
      return 1;
   }

    return 0;
}
