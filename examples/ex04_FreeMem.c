#include "mem/mem.h"


#include <stdio.h>


int main()
{
   printf("\nExample 4\n\n");

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

   ret = FreeMem(&arr);

   printf("FreeMem ret value: %d", ret);
   if (ret)
   {
      printf("Unable to free memory.\n\n");

      return MEM_RET_FAILURE;
   }

   printf("\n\n");

   printf("Array is%s NULL.\n\n",
          arr ?
          " not" :
          ""
         );

   return MEM_RET_SUCCESS;
}