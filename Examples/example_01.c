#include <stdio.h>
#include <stdlib.h>

#include "dynmem/dynmem.h"

int main(int argc, char **argv) {
   if (argc < 4) {
      printf("Usage: %s begin:int end:int value:int\n", argv[0]);
      return 1;
   }

   dynmem_t dynmem;
   intmax_t begin = strtoll(argv[1], NULL, 10);
   intmax_t end = strtoll(argv[2], NULL, 10);
   int value = strtod(argv[3], NULL);

   if (DynMemAllocate(&dynmem, sizeof(int), 5, NULL)) {
      printf("Error allocation.\n");
      return 2;
   }

   for (int i = 0; i < 5; i++) {
      if (DynMemPrepend(&dynmem, NULL)) {
         printf("Error prepending.\n");
         return 3;
      }
   }

   for (int i = 0; i < 5; i++) {
      if (DynMemAppend(&dynmem, NULL)) {
         printf("Error appending.\n");
         return 4;
      }
   }

   printf("\n ---- Before setting ----\n");

   for (intmax_t i = dynmem.bi, j = dynmem.ei; i <= j; i += dynmem.es)
      printf(" %d,", *(int *)(dynmem.m + i));

   if (DynMemSet(&dynmem, begin, end, &value)) {
      printf("\n\nError setting.\n");
   } else {
      printf("\n\n ---- After setting ----\n");

      for (intmax_t i = dynmem.bi, j = dynmem.ei; i <= j; i += dynmem.es)
         printf(" %d,", *(int *)(dynmem.m + i));
   }

   if (DynMemDeallocate(&dynmem)) {
      printf("Error deallocation.\n");
      return 6;
   }

   return 0;
}

// int main()
// {
//    dynmem_t mem;
//    int value;
//
//    if (DynMemAllocate(&mem, sizeof(int), 4, NULL)) {
//       printf("Error allocation.\n");
//       return 1;
//    }
//
// //    printf("\nAppending...\n\n");
// //
// //    for (int i = 0; i < 20; i++) {
// //       int value = i + 1;
// //       if (DynMemAppend(&mem, &value)) {
// //          printf("Error appending.\n");
// //          return 1;
// //       }
// //
// //       for (intmax_t j = mem.bi; j <= mem.ei; j += mem.es)
// //          printf("%lld:%d, ", j, *(int *)(mem.m + j));
// //
// //       printf("\n---- %lld - %lld ----\n", mem.csh, mem.cs);
// //    }
// //
// //    printf("\nDeducting...\n\n");
// //
// //    for (int i = 0; i < 20, !DynMemDeduct(&mem, &value); i++) {
// //       printf("-- %d deducted --\n", value);
// //
// //       for (intmax_t j = mem.bi; j <= mem.ei; j += mem.es)
// //          printf("%lld:%d, ", j, *(int *)(mem.m + j));
// //
// //       printf("\n---- %lld - %lld ----\n", mem.csh, mem.cs);
// //    }
// //
// //    printf("\nAppending...\n\n");
// //
// //    for (int i = 0; i < 20; i++) {
// //       int value = i + 1;
// //       if (DynMemAppend(&mem, &value)) {
// //          printf("Error appending.\n");
// //          return 1;
// //       }
// //
// //       for (intmax_t j = mem.bi; j <= mem.ei; j += mem.es)
// //          printf("%lld:%d, ", j, *(int *)(mem.m + j));
// //
// //       printf("\n---- %lld - %lld ----\n", mem.csh, mem.cs);
// //    }
// //
// //    printf("\nPrepending...\n\n");
// //
// //    for (int i = 0; i < 10; i++) {
// //       int value = i + 1;
// //       if (DynMemPrepend(&mem, &value)) {
// //          printf("Error appending.\n");
// //          return 1;
// //       }
// //
// //       for (intmax_t j = mem.bi; j <= mem.ei; j += mem.es)
// //          printf("%lld:%d, ", j, *(int *)(mem.m + j));
// //
// //       printf("\n---- %lld - %lld ----\n", mem.csh, mem.cs);
// //    }
// //
// //    printf("\nDeducting...\n\n");
// //
// //    for (int i = 0; i < 40, !DynMemDeduct(&mem, &value); i++) {
// //       printf("-- %d deducted --\n", value);
// //
// //       for (intmax_t j = mem.bi; j <= mem.ei; j += mem.es)
// //          printf("%lld:%d, ", j, *(int *)(mem.m + j));
// //
// //       printf("\n---- %lld - %lld ----\n", mem.csh, mem.cs);
// //    }
//
// /*****************************************************************************/
//
//    printf("\nPrepending...\n\n");
//
//    for (int i = 0; i < 20; i++) {
//       int value = i + 1;
//       if (DynMemPrepend(&mem, &value)) {
//          printf("Error appending.\n");
//          return 1;
//       }
//
//       for (intmax_t j = mem.bi; j <= mem.ei; j += mem.es)
//          printf("%lld:%d, ", j, *(int *)(mem.m + j));
//
//       printf("\n---- %lld - %lld ----\n", mem.csh, mem.cs);
//    }
//
//    printf("\nDeducting...\n\n");
//
//    for (int i = 0; i < 20, !DynMemDeductFront(&mem, &value); i++) {
//       printf("-- %d deducted --\n", value);
//
//       for (intmax_t j = mem.bi; j <= mem.ei; j += mem.es)
//          printf("%lld:%d, ", j, *(int *)(mem.m + j));
//
//       printf("\n---- %lld - %lld ----\n", mem.csh, mem.cs);
//    }
//
//    printf("\nPrepending...\n\n");
//
//    for (int i = 0; i < 20; i++) {
//       int value = i + 1;
//       if (DynMemPrepend(&mem, &value)) {
//          printf("Error appending.\n");
//          return 1;
//       }
//
//       for (intmax_t j = mem.bi; j <= mem.ei; j += mem.es)
//          printf("%lld:%d, ", j, *(int *)(mem.m + j));
//
//       printf("\n---- %lld - %lld ----\n", mem.csh, mem.cs);
//    }
//
//    printf("\nAppending...\n\n");
//
//    for (int i = 0; i < 10; i++) {
//       int value = i + 1;
//       if (DynMemAppend(&mem, &value)) {
//          printf("Error appending.\n");
//          return 1;
//       }
//
//       for (intmax_t j = mem.bi; j <= mem.ei; j += mem.es)
//          printf("%lld:%d, ", j, *(int *)(mem.m + j));
//
//       printf("\n---- %lld - %lld ----\n", mem.csh, mem.cs);
//    }
//
//    printf("\nDeducting...\n\n");
//
//    for (int i = 0; i < 40, !DynMemDeductFront(&mem, &value); i++) {
//       printf("-- %d deducted --\n", value);
//
//       for (intmax_t j = mem.bi; j <= mem.ei; j += mem.es)
//          printf("%lld:%d, ", j, *(int *)(mem.m + j));
//
//       printf("\n---- %lld - %lld ----\n", mem.csh, mem.cs);
//    }
//
//    if (DynMemDeallocate(&mem)) {
//       printf("Error deallocation");
//       return 1;
//    }
//
//    return 0;
// }
