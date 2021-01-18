#include "mem/mem.h"


#include <stdio.h>


int main()
{
   printf("\nExample 1\n\n");

   int maj, min, pat;
   MemLibVersion(&maj, &min, &pat);

   printf("Library version: %d.%d.%d\n\n", maj, min, pat);

   return MEM_RET_SUCCESS;
}