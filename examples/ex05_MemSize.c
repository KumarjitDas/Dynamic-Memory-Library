#include "mem/mem.h"


#include <stdio.h>


int main()
{
   printf("\nExample 5\n\n");

   int *arr = NULL;
   int len = 50;
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
   printf("Memory size: %llu byte%s\n\n",
          sz_arr,
          sz_arr > 1 ?
          "s" :
          ""
         );

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