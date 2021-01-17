#include "util.h"



void _setMemExtraInfo(_MEM_T ptr, _MEM_T ptr_inf, size_t sz_inf)
{
  for(size_t i = sz_inf; i--; ptr++, ptr_inf++) *ptr = *ptr_inf;

  *(size_t*)ptr = sz_inf;
}



void _setMemSizeHeader(_MEM_T ptr, size_t size, int has_cont)
{
  *ptr = has_cont ?
    (_BYTE_T)_MEM_HEADER2CONT_ID :
    (_BYTE_T)_MEM_HEADER2_ID;

  ptr++;
  *(size_t*)ptr = size;

  ptr += sizeof(size_t);
  *ptr = (_BYTE_T)_MEM_HEADER1_ID;
}



void _setMemElems(_MEM_T ptr, size_t size, _MEM_T ptr_elem, size_t sz_elem)
{
  for(size_t i = 0, j = 0; i < size; i++, j++)
  {
    if(j == sz_elem) j = 0;
    ptr[i] = ptr_elem[j];
  }
}



int _hasMemHeader(_MEM_T ptr)
{
  ptr--;
  if(*ptr == (_BYTE_T)_MEM_HEADER1_ID)
  {
    ptr -= (sizeof(size_t) + 1);
    if(*ptr == (_BYTE_T)_MEM_HEADER2_ID)     return MEM_RET_TRUE;
    if(*ptr == (_BYTE_T)_MEM_HEADER2CONT_ID) return _MEM_RET_HAS_HEADER2CONT;
  }

  return MEM_RET_FALSE;
}