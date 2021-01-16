#include "util.h"


void memLibVersion(int *addr_maj, int *addr_min, int *addr_pat)
{
  if(addr_maj) *addr_maj = mem_VERSION_MAJOR;
  if(addr_min) *addr_min = mem_VERSION_MINOR;
  if(addr_pat) *addr_pat = mem_VERSION_MINOR;
}


int allocMem(
  void *addr_ptr, size_t size,
  void *ptr_dat,  size_t sz_dat,
  void *ptr_inf,  size_t sz_inf
) {
  if(!addr_ptr) return MEM_ERR_PTR_ADDR_NULL;

  *(_ADDR_T)addr_ptr = NULL;

  if(!size) return MEM_ERR_INVALID_SIZE;

  size_t sz_total = size + _MEM_HEADER_SIZE;
  if(sz_inf) sz_total += sz_inf + sizeof(size_t);

  _MEM_T ptr = malloc(sz_total);
  if(!ptr) return MEM_ERR_ALLOC;

  if(sz_inf)
  {
    if(ptr_inf) _setMemExtraInfo(ptr, ptr_inf, sz_inf);

    ptr += sz_inf + sizeof(size_t);
  }

  _setMemSizeHeader(ptr, size, sz_inf > 0);

  ptr += _MEM_HEADER_SIZE;
  *(_ADDR_T)addr_ptr = ptr;

  if(ptr_dat && sz_dat) _setMemElems(ptr, size, ptr_dat, sz_dat);

  return MEM_RET_SUCCESS;
}


int freeMem(void *addr_ptr)
{
  if(!addr_ptr) return MEM_ERR_PTR_ADDR_NULL;

  _MEM_T ptr = *(_ADDR_T)addr_ptr;
  if(!ptr) return MEM_ERR_PTR_NULL;

  *(_ADDR_T)addr_ptr = NULL;

  if(_hasMemHeader(ptr))
  {
    ptr -= _MEM_HEADER_SIZE;
    if(*ptr == (_BYTE_T)_MEM_HEADER2CONT_ID)
    {
      ptr -= sizeof(size_t);
      ptr -= *(size_t*)ptr;
    }
  }

  free(ptr);

  return MEM_RET_SUCCESS;
}