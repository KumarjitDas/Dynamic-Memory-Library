#include "mem/mem.h"


#include <stdio.h>


int main()
{
   printf("\nExample 6\n\n");

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

   ret = ClrMem(arr, MEM_AUTO_DTCT);

   printf("ClrMem ret value: %d", ret);
   if (ret)
   {
      printf("Unable to clear memory.");
   }

   printf("\n\n");

   printf("After clearing, array content:\n\n> ");
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