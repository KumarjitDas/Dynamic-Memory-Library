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
   printf("\nExample 11\n\n");

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

   info_t *ptr_inf = NULL;
   ret = GetMemInfo(&ptr_inf, arr);
   printf("GetMemInfo ret value: %d\n\n", ret);
   if (ret || !ptr_inf)
   {
      printf("Unable to get the info.\n\n");
   }
   else
   {
      printInfo(ptr_inf);
   }

   ret = FreeMem(&arr);
   printf("FreeMem ret value: %d", ret);
   if (ret)
   {
      printf("Unable to free memory.");
   }

   printf("\n\n");

   return MEM_RET_SUCCESS;
}