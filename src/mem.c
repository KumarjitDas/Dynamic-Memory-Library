#include "util.h"



void memLibVersion(int *addr_maj, int *addr_min, int *addr_pat)
{
  if (addr_maj) *addr_maj = mem_VERSION_MAJOR;
  if (addr_min) *addr_min = mem_VERSION_MINOR;
  if (addr_pat) *addr_pat = mem_VERSION_MINOR;
}



int allocMem(
  void *addr_ptr, size_t size,
  void *ptr_dat,  size_t sz_dat,
  void *ptr_inf,  size_t sz_inf
) {
  if (!addr_ptr) return MEM_ERR_ADDR_PTR_NULL;

  *(_ADDR_T)addr_ptr = NULL;

  if (!size) return MEM_ERR_INVALID_SIZE;

  size_t sz_total = size + _MEM_HEADER_SIZE;
  if (sz_inf) sz_total += sz_inf + sizeof(size_t);

  _MEM_T ptr = malloc(sz_total);
  if (!ptr) return MEM_ERR_ALLOC;

  if (sz_inf)
  {
    if (ptr_inf) _setMemExtraInfo(ptr, ptr_inf, sz_inf);

    ptr += sz_inf + sizeof(size_t);
  }

  _setMemSizeHeader(ptr, size, sz_inf > 0);

  ptr += _MEM_HEADER_SIZE;
  *(_ADDR_T)addr_ptr = ptr;

  if (ptr_dat && sz_dat) _setMemElems(ptr, size, ptr_dat, sz_dat);

  return MEM_RET_SUCCESS;
}



int freeMem(void *addr_ptr)
{
  if (!addr_ptr) return MEM_ERR_ADDR_PTR_NULL;

  _MEM_T ptr = *(_ADDR_T)addr_ptr;
  if (!ptr) return MEM_ERR_PTR_NULL;

  *(_ADDR_T)addr_ptr = NULL;

  if (_hasMemHeader(ptr))
  {
    ptr -= _MEM_HEADER_SIZE;
    if (*ptr == (_BYTE_T)_MEM_HEADER2CONT_ID)
    {
      ptr -= sizeof(size_t);
      ptr -= *(size_t*)ptr;
    }
  }

  free(ptr);

  return MEM_RET_SUCCESS;
}



size_t memSize(void *ptr)
{
  if (!ptr || !_hasMemHeader(ptr)) return 0;

  return _GET_MEM_SIZE(ptr);
}



int setMem(
  void *ptr, size_t idx_s, size_t idx_e,
  void *ptr_elem, size_t sz_elem
) {
  if (!ptr || !ptr_elem) return MEM_ERR_PTR_NULL;

  if (!sz_elem) return MEM_ERR_INVALID_SIZE;

  if (!idx_e && _hasMemHeader(ptr)) idx_e = _GET_MEM_SIZE(ptr);

  if (idx_s >= idx_e) return MEM_ERR_INVALID_IDX;

  _setMemElems((_MEM_T)ptr + idx_s, idx_e - idx_s, ptr_elem, sz_elem);

  return MEM_RET_SUCCESS;
}



int getMemExtraInfo(void *addr_ptr_ex_inf, void *ptr)
{
  if (!addr_ptr_ex_inf || !ptr) return MEM_ERR_PTR_NULL;

  *(_ADDR_T)addr_ptr_ex_inf = NULL;

  int ret = _hasMemHeader(ptr);
  if (!ret)                            return MEM_ERR_NOT_MEMLIB;
  if (ret != _MEM_RET_HAS_HEADER2CONT) return MEM_ERR_NOT_EXIST;

  _MEM_T tmp_ptr = ptr;
  tmp_ptr -= (_MEM_HEADER_SIZE + sizeof(size_t));
  tmp_ptr -= *(size_t*)tmp_ptr;

  *(_ADDR_T)addr_ptr_ex_inf = tmp_ptr;

  return MEM_RET_SUCCESS;
}



size_t memExtraInfoSize(void *ptr)
{
  if (!ptr) return 0;

  int ret = _hasMemHeader(ptr);
  if (!ret || ret != _MEM_RET_HAS_HEADER2CONT) return 0;

  return *(size_t*)((_MEM_T)ptr - _MEM_HEADER_SIZE - sizeof(size_t));
}



int cpyMem(void *addr_ptr_dst, void *ptr_src, size_t idx_s, size_t idx_e)
{
  if (!addr_ptr_dst) return MEM_ERR_ADDR_PTR_NULL;

  *(_ADDR_T)addr_ptr_dst = NULL;

  if (!ptr_src) return MEM_ERR_PTR_NULL;

  int has_mem_head = _hasMemHeader(ptr_src);
  if (!idx_e && has_mem_head) idx_e = _GET_MEM_SIZE(ptr_src);

  if (idx_s >= idx_e) return MEM_ERR_INVALID_IDX;

  _MEM_T tmp_ptr_dst;
  idx_e -= idx_s;

  if (has_mem_head)
  {
    _MEM_T ex_inf = NULL;
    (void)getMemExtraInfo(&ex_inf, ptr_src);

    (void)allocMem(
      &tmp_ptr_dst, idx_e, ex_inf, memExtraInfoSize(ptr_src), NULL, 0
    );
  }
  else tmp_ptr_dst = malloc(idx_e);

  if (!tmp_ptr_dst) return MEM_ERR_ALLOC;

  *(_ADDR_T)addr_ptr_dst = tmp_ptr_dst;

  _MEM_T tmp_ptr_src = (_MEM_T)ptr_src + idx_s;
  while (idx_e--) tmp_ptr_dst[idx_e] = tmp_ptr_src[idx_e];

  return MEM_RET_SUCCESS;
}