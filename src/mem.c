#include "util.h"



void MemLibVersion (int *ptr_maj, int *ptr_min, int *ptr_pat)
{
   if (ptr_maj)
   {
      *ptr_maj = mem_VERSION_MAJOR;
   }

   if (ptr_min)
   {
      *ptr_min = mem_VERSION_MINOR;
   }

   if (ptr_pat)
   {
      *ptr_pat = mem_VERSION_PATCH;
   }
}



int AllocMem (void *addr_ptr, size_t size,
              void *ptr_dat,  size_t sz_dat,
              void *ptr_inf,  size_t sz_inf
             )
{
   if (!addr_ptr)
   {
      return MEM_ERR_ADDR_PTR_NULL;
   }

   *(_ADDR_T)addr_ptr = NULL;

   if (!size)
   {
      return MEM_ERR_INVALID_SIZE;
   }

   size_t sz_total = size + _MEM_HEADER_SIZE;

   if (sz_inf)
   {
      sz_total += sz_inf + sizeof(size_t);
   }

   _MEM_T ptr = malloc(sz_total);
   if (!ptr)
   {
      return MEM_ERR_ALLOC;
   }

   if (sz_inf)
   {
      if (ptr_inf)
      {
         ptr = _SetMemExtraInfo(ptr, ptr_inf, sz_inf);
      }
      else
      {
         ptr += sz_inf + sizeof(size_t);
      }
   }

   ptr = _SetMemSizeHeader(ptr, size, sz_inf > 0);

   *(_ADDR_T)addr_ptr = ptr;

   if (ptr_dat && sz_dat)
   {
      (void)_SetMemElems(ptr, size, ptr_dat, sz_dat);
   }

   return MEM_RET_SUCCESS;
}



int ResizeMem (void *addr_ptr, size_t sz_old, size_t sz_new,
               void *ptr_dat,  size_t sz_dat
              )
{
   if (!addr_ptr)
   {
      return MEM_ERR_ADDR_PTR_NULL;
   }

   _MEM_T ptr = *(_ADDR_T)addr_ptr;
   if (!ptr)
   {
      return MEM_ERR_PTR_NULL;
   }

   *(_ADDR_T)addr_ptr = NULL;

   size_t sz_inf = 0;
   size_t sz_tot = sz_new;

   int mem_head = _HasMemHeader(ptr);
   if (mem_head)
   {
      sz_tot += _MEM_HEADER_SIZE;

      ptr -= (sizeof(size_t) + 1);
      sz_old = *(size_t*)ptr;

      ptr--;

      if (mem_head == (_BYTE_T)_MEM_HEADER2CONT_ID)
      {
         ptr -= sizeof(size_t);
         sz_inf = *(size_t*)ptr;
         ptr -= sz_inf;

         sz_inf += sizeof(size_t);
         sz_tot += sz_inf;
      }
   }

   if (!sz_new)
   {
      free(ptr);

      return MEM_RET_SUCCESS;
   }

   if (sz_new == sz_old)
   {
      *(_ADDR_T)addr_ptr = ptr;

      return MEM_RET_SUCCESS;
   }

   ptr = realloc(ptr, sz_tot);
   if (!ptr)
   {
      return MEM_ERR_ALLOC;
   }

   if (mem_head)
   {
      ptr           += sz_inf + 1;
      *(size_t*)ptr  = sz_new;
      ptr           += sizeof(size_t) + 1;
   }

   *(_ADDR_T)addr_ptr = ptr;

   sz_tot = sz_new > sz_old ?
            sz_new - sz_old :
            0;
   if (sz_tot && ptr_dat && sz_dat)
   {
      (void)_SetMemElems(ptr + sz_old,
                         sz_tot,
                         ptr_dat,
                         sz_dat
                        );
   }

   return MEM_RET_SUCCESS;
}



int FreeMem (void *addr_ptr)
{
   return ResizeMem(addr_ptr, 0, 0, NULL, 0);
}



size_t MemSize (void *ptr)
{
   return ptr && _HasMemHeader(ptr) ?
          _GET_MEM_SIZE(ptr) :
          0;
}



int ClrMem (void *ptr, size_t size)
{
   if (!ptr)
   {
      return MEM_ERR_PTR_NULL;
   }

   if (!size)
   {
      size = MemSize(ptr);
   }

   if (!size)
   {
      return MEM_ERR_INVALID_SIZE;
   }

   _MEM_T tmp_ptr = ptr;

   while (size--)
   {
      tmp_ptr[size] = 0;
   }

   return MEM_RET_SUCCESS;
}



int SetMem (void *ptr, size_t idx_s, size_t idx_e,
            void *ptr_dat, size_t sz_dat
           )
{
   if (!ptr || !ptr_dat)
   {
      return MEM_ERR_PTR_NULL;
   }

   if (!sz_dat)
   {
      return MEM_ERR_INVALID_SIZE;
   }

   if (!idx_e && _HasMemHeader(ptr))
   {
      idx_e = _GET_MEM_SIZE(ptr);
   }

   if (idx_s >= idx_e)
   {
      return MEM_ERR_INVALID_IDX;
   }

   (void)_SetMemElems((_MEM_T)ptr + idx_s,
                      idx_e - idx_s,
                      ptr_dat,
                      sz_dat
                     );

   return MEM_RET_SUCCESS;
}



int CpyMem (void *addr_ptr_dst, void *ptr_src,
            size_t idx_s, size_t idx_e
           )
{
   if (!addr_ptr_dst)
   {
      return MEM_ERR_ADDR_PTR_NULL;
   }

   *(_ADDR_T)addr_ptr_dst = NULL;

   if (!ptr_src)
   {
      return MEM_ERR_PTR_NULL;
   }

   int mem_head = _HasMemHeader(ptr_src);
   if (mem_head && !idx_e)
   {
      idx_e = _GET_MEM_SIZE(ptr_src);
   }

   if (idx_s >= idx_e)
   {
      return MEM_ERR_INVALID_IDX;
   }

   _MEM_T ptr_dst     = NULL;
   _MEM_T tmp_ptr_src = ptr_src;

   idx_e -= idx_s;

   if (mem_head)
   {
      _MEM_T ptr_inf = NULL;
      size_t sz_inf = 0;

      tmp_ptr_src -= _MEM_HEADER_SIZE;

      if (mem_head == _MEM_HEADER2CONT_ID)
      {
         tmp_ptr_src -= sizeof(size_t);
         sz_inf = *(size_t*)tmp_ptr_src;
         ptr_inf = tmp_ptr_src - sz_inf;

         tmp_ptr_src += sizeof(size_t);
      }

      tmp_ptr_src += _MEM_HEADER_SIZE;

      (void) AllocMem(&ptr_dst, idx_e,
                      NULL, 0,
                      ptr_inf, sz_inf
                     );
   }
   else
   {
      ptr_dst = malloc(idx_e);
   }

   if (!ptr_dst)
   {
      return MEM_ERR_ALLOC;
   }

   *(_ADDR_T)addr_ptr_dst = ptr_dst;

   tmp_ptr_src += idx_s;

   while (idx_e--)
   {
      ptr_dst[idx_e] = tmp_ptr_src[idx_e];
   }

   return MEM_RET_SUCCESS;
}



int ApnMem (void *addr_ptr_dst, size_t sz_dst,
            void *ptr_src, size_t sz_src
           )
{
   if (!addr_ptr_dst)
   {
      return MEM_ERR_ADDR_PTR_NULL;
   }

   _MEM_T ptr_dst = *(_ADDR_T)addr_ptr_dst;

   if (!ptr_dst || !ptr_src)
   {
      return CpyMem(addr_ptr_dst, ptr_src, 0, sz_src);
   }

   if (!sz_dst)
   {
      sz_dst = MemSize(ptr_dst);

      if (!sz_dst)
      {
         return MEM_ERR_INVALID_SIZE;
      }
   }

   if (!sz_src)
   {
      sz_src = MemSize(ptr_src);

      if (!sz_src)
      {
         return MEM_ERR_INVALID_SIZE;
      }
   }

   return ResizeMem(addr_ptr_dst,
                    0,
                    sz_dst + sz_src,
                    ptr_src,
                    sz_src
                   );
}



// size_t memExtraInfoSize(void *ptr)
// {
//    if (!ptr) return 0;

//    int ret = _HasMemHeader(ptr);
//    if (!ret || ret != _MEM_RET_HAS_HEADER2CONT) return 0;

//    return _GET_MEM_INF_SIZE(ptr);
// }


// int getMemExtraInfo(void *addr_ptr_ex_inf, void *ptr)
// {
//    if (!addr_ptr_ex_inf || !ptr) return MEM_ERR_PTR_NULL;

//    *(_ADDR_T)addr_ptr_ex_inf = NULL;

//    int ret = _HasMemHeader(ptr);
//    if (!ret)                           return MEM_ERR_NOT_MEMLIB;
//    if (ret != _MEM_RET_HAS_HEADER2CONT) return MEM_ERR_NOT_EXIST;

//    _MEM_T tmp_ptr = ptr;
//    tmp_ptr -= (_MEM_HEADER_SIZE + sizeof(size_t));
//    tmp_ptr -= *(size_t*)tmp_ptr;

//    *(_ADDR_T)addr_ptr_ex_inf = tmp_ptr;

//    return MEM_RET_SUCCESS;
// }



// // int chMemExtraInfo(void *addr_ptr, void *ptr_inf, size_t sz_inf)
// // {
// //  return MEM_RET_SUCCESS;
// // }