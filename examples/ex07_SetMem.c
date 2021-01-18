#include "mem/mem.h"


#include <stdio.h>


int main()
{
   printf("\nExample 7\n\n");

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

   printf("Array content:\n\n> ");
   for (int i = 0; i < len; i++)
   {
      printf("%d, ", arr[i]);
   }

   printf("\n\n");

   int val = 420;
   ret = SetMem(arr,
                MEM_IDX_S,
                MEM_IDX_E,
                &val,
                sizeof(int)
               );

   printf("SetMem ret value: %d", ret);
   if (ret)
   {
      printf("Unable to set memory.");
   }

   printf("\n\n");

   printf("After setting, array content:\n\n> ");
   for (int i = 0; i < len; i++)
   {
      printf("%d, ", arr[i]);
   }

   printf("\n\n");

   ret = FreeMem(&arr);

   printf("FreeMem ret value: %d", ret);
   if (ret)
   {
      printf("Unable to free memory.\n\n");

      return MEM_RET_FAILURE;
   }

   printf("\n\n");

   return MEM_RET_SUCCESS;
}