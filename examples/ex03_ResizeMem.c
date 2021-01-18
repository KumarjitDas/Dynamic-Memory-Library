#include "mem/mem.h"


#include <stdio.h>


int main()
{
   printf("\nExample 3\n\n");

   int *arr = NULL;
   int len = 7;
   int val = 420;
   int ret = AllocMem(&arr, len * sizeof(int),
                      &val, sizeof(int),
                      NULL, 0
                     );

   printf("AllocMem ret value: %d", ret);
   if (ret)
   {
      printf("Unable to allocate memory.\n\n");

      return MEM_RET_FAILURE;
   }

   printf("\n\n");

   printf("Array content:\n\n> ");
   for (int i = 0; i < len; i++)
   {
      printf("%d, ", arr[i]);
   }

   printf("\n\n");

   len = 5;
   val = -69;
   ret = ResizeMem(&arr, 0, len * sizeof(int),
                   &val, sizeof(int)
                  );

   printf("ResizeMem ret value: %d", ret);
   if (ret)
   {
      printf("Unable to allocate memory.\n\n");

      return MEM_RET_FAILURE;
   }

   printf("\n\n");

   printf("Resized array content:\n\n> ");
   for (int i = 0; i < len; i++)
   {
      printf("%d, ", arr[i]);
   }

   printf("\n\n");

   return MEM_RET_SUCCESS;
}