#include "mem/mem.h"


#include <stdio.h>


int main()
{
   printf("\nExample 8\n\n");

   int *arr = NULL;
   int len = 10;
   int ret = AllocMem(&arr, len * sizeof(int),
                      NULL, 0, NULL, 0
                     );

   printf("AllocMem ret value: %d\n\n", ret);
   if (ret)
   {
      printf("Unable to allocate memory.\n\n");

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

   for (int i = 0; i < len; i++)
   {
      arr[i] = i;
   }

   printf("Array content:\n\n> ");
   for (int i = 0; i < len; i++)
   {
      printf("%d, ", arr[i]);
   }

   printf("\n\n");

   int *arrcpy = NULL;
   ret = CpyMem(&arrcpy, arr,
                MEM_IDX_S,
                MEM_IDX_E
               );

   printf("CpyMem ret value: %d", ret);
   if (ret)
   {
      printf("Unable to copy memory.\n\n");

      ret = FreeMem(&arr);

      printf("FreeMem ret value: %d", ret);
      if (ret)
      {
         printf("Unable to free memory.");
      }

      printf("\n\n");

      return MEM_RET_FAILURE;
   }

   printf("\n\n");

   sz_arr = MemSize(arrcpy);
   printf("Memory size of arrcpy: %llu byte%s\n\n",
          sz_arr,
          sz_arr > 1 ?
          "s" :
          ""
         );
   len = (int)(sz_arr / sizeof(int));

   printf("Copied array content:\n\n> ");
   for (int i = 0; i < len; i++)
   {
      printf("%d, ", arrcpy[i]);
   }

   printf("\n\n");

   ret = FreeMem(&arr);

   printf("FreeMem ret value of arr: %d", ret);
   if (ret)
   {
      printf("Unable to free memory of arr.");
   }

   printf("\n\n");

   ret = FreeMem(&arrcpy);

   printf("FreeMem ret value of arrcpy: %d", ret);
   if (ret)
   {
      printf("Unable to free memory of arrcpy.");
   }

   printf("\n\n");

   return MEM_RET_SUCCESS;
}