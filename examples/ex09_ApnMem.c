#include "mem/mem.h"


#include <stdio.h>


int main()
{
   printf("\nExample 9\n\n");

   int *arr = NULL;
   int len = 7;
   int val = -69;
   int ret = AllocMem(&arr, len * sizeof(int),
                      &val, sizeof(int),
                      NULL, 0
                     );

   printf("AllocMem ret value of arr: %d\n\n", ret);
   if (ret)
   {
      printf("Unable to allocate memory for arr.\n\n");

      return MEM_RET_FAILURE;
   }

   size_t sz_arr = MemSize(arr);
   printf("Memory size of arr: %llu byte%s\n\n",
          sz_arr,
          sz_arr > 1 ?
          "s" :
          ""
         );
   len = (int)(sz_arr / sizeof(int));

   printf("Array content:\n\n> ");
   for (int i = 0; i < len; i++)
   {
      printf("%d, ", arr[i]);
   }

   printf("\n\n");

   len = 3;
   val = 420;
   int *arr2 = NULL;
   ret = AllocMem(&arr2, len * sizeof(int),
                  &val, sizeof(int),
                  NULL, 0
                 );

   printf("AllocMem ret value of arr2: %d", ret);
   if (ret)
   {
      printf("Unable to allocate memory for arr2.\n\n");

      ret = FreeMem(&arr);

      printf("FreeMem ret value: %d", ret);
      if (ret)
      {
         printf("Unable to free memory of arr.");
      }

      printf("\n\n");

      return MEM_RET_FAILURE;
   }

   printf("\n\n");

   sz_arr = MemSize(arr2);
   printf("Memory size of arr2: %llu byte%s\n\n",
          sz_arr,
          sz_arr > 1 ?
          "s" :
          ""
         );
   len = (int)(sz_arr / sizeof(int));

   printf("Array 2 content:\n\n> ");
   for (int i = 0; i < len; i++)
   {
      printf("%d, ", arr2[i]);
   }

   printf("\n\n");

   ret = ApnMem(&arr, MEM_MAX_SIZE,
                arr2, MEM_MAX_SIZE
               );
   printf("ApnMem ret value: %d", ret);
   if (ret)
   {
      printf("Unable to append memory.\n\n");

      ret = FreeMem(&arr2);

      printf("FreeMem ret value of arr2: %d", ret);
      if (ret)
      {
         printf("Unable to free memory of arr2.");
      }

      printf("\n\n");

      return MEM_RET_FAILURE;
   }

   printf("\n\n");

   sz_arr = MemSize(arr);
   printf("After appending, memory size of arr: %llu byte%s\n\n",
          sz_arr,
          sz_arr > 1 ?
          "s" :
          ""
         );
   len = (int)(sz_arr / sizeof(int));

   printf("After appending, array content:\n\n> ");
   for (int i = 0; i < len; i++)
   {
      printf("%d, ", arr[i]);
   }

   printf("\n\n");

   ret = FreeMem(&arr);

   printf("FreeMem ret value of arr: %d", ret);
   if (ret)
   {
      printf("Unable to free memory of arr.");
   }

   printf("\n\n");

   ret = FreeMem(&arr2);

   printf("FreeMem ret value of arr2: %d", ret);
   if (ret)
   {
      printf("Unable to free memory of arr2.");
   }

   printf("\n\n");

   return MEM_RET_SUCCESS;
}