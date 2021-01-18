#include "util.h"



_MEM_T _SetMemExtraInfo(_MEM_T ptr, _MEM_T ptr_inf, size_t sz_inf)
{
   for (size_t i = sz_inf; i--; ptr++, ptr_inf++)
   {
      *ptr = *ptr_inf;
   }

   *(size_t*)ptr = sz_inf;

   return ptr + sizeof(size_t);
}



_MEM_T _SetMemSizeHeader(_MEM_T ptr, size_t size, int has_cont)
{
   *ptr = has_cont ?
          (_BYTE_T)_MEM_HEADER2CONT_ID :
          (_BYTE_T)_MEM_HEADER2_ID;

   ptr++;
   *(size_t*)ptr = size;

   ptr += sizeof(size_t);
   *ptr = (_BYTE_T)_MEM_HEADER1_ID;

   return ptr + 1;
}



_MEM_T _SetMemElems(_MEM_T ptr, size_t size, _MEM_T ptr_elem, size_t sz_elem)
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



int _HasMemHeader(_MEM_T ptr)
{
   ptr--;
   if (*ptr == (_BYTE_T)_MEM_HEADER1_ID)
   {
      ptr -= (sizeof(size_t) + 1);

      if (*ptr == (_BYTE_T)_MEM_HEADER2_ID)
      {
         return MEM_RET_TRUE;
      }
      else if (*ptr == (_BYTE_T)_MEM_HEADER2CONT_ID)
      {
         return _MEM_RET_HAS_HEADER2CONT;
      }
   }

   return MEM_RET_FAILURE;
}