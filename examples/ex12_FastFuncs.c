#include "mem/mem.h"


#include <stdio.h>


typedef struct
{
   int a, b;
   long long c;
}
info_t;


void printInfo(info_t *ptr_inf)
{
   printf("Info:\n\na: %d,\nb: %d,\nc: %lld\n\n",
          ptr_inf->a,
          ptr_inf->b,
          ptr_inf->c
         );
}


int main()
{
   printf("\nExample 12\n\n");

   info_t inf =
   {
      .a = 123456789,
      .b = -69042069,
      .c = 9876543210
   };
   printInfo(&inf);

   int *arr = NULL;
   int len = 5;
   int ret = AllocMem(&arr, len * sizeof(int),
                      NULL, 0,
                      &inf, sizeof(info_t)
                     );
   printf("AllocMem ret value: %d\n\n", ret);
   if (ret)
   {
      printf("Unable to allocate memory.\n\n");

      return MEM_RET_FAILURE;
   }

   size_t size = MemSize(arr);
   printf("Memory size: %llu byte%s\n\n",
          size,
          size > 1 ?
          "s" :
          ""
         );

   size = MemInfoSizeFast(arr);
   printf("Memory info size: %llu byte%s\n\n",
          size,
          size > 1 ?
          "s" :
          ""
         );

   info_t *ptr_inf = NULL;
   (void) GetMemInfoFast(&ptr_inf, arr);
   printInfo(ptr_inf);

   ret = FreeMem(&arr);
   printf("FreeMem ret value: %d", ret);
   if (ret)
   {
      printf("Unable to free memory.");
   }

   printf("\n\n");

   return MEM_RET_SUCCESS;
}