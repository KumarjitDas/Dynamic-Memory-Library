#include "mem/mem.h"


#include <stdio.h>


int main()
{
   printf("\nExample 10\n\n");

   int *arr = NULL;
   int len = 5;
   int ret = AllocMem(&arr, len * sizeof(int),
                      NULL, 0,
                      NULL, 27
                     );

   printf("AllocMem ret value: %d\n\n", ret);
   if (ret)
   {
      printf("Unable to allocate memory.\n\n");

      return MEM_RET_FAILURE;
   }

   size_t size = MemInfoSize(arr);
   printf("Memory info size: %llu byte%s\n\n",
          size,
          size > 1 ?
          "s" :
          ""
         );

   ret = FreeMem(&arr);

   printf("FreeMem ret value: %d", ret);
   if (ret)
   {
      printf("Unable to free memory.");
   }

   printf("\n\n");

   return MEM_RET_SUCCESS;
}