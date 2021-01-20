#include "util.h"



_MEM_T _SetMemElems (_MEM_T ptr, size_t size, _MEM_T ptr_elem, size_t sz_elem)
{
   for (size_t i = 0; size--; i++, ptr++)
   {
      if (i == sz_elem)
      {
         i = 0;
      }

      *ptr = ptr_elem[i];
   }

   return ptr;
}