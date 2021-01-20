#include "util.h"
#include "mem/mem.h"



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

   if (sz_inf)
   {
      void *tmp_ptr_inf = malloc(sz_inf);
      if (!tmp_ptr_inf)
      {
         return MEM_ERR_ALLOC;
      }

      if (ptr_inf)
      {
         (void) _SetMemElems(tmp_ptr_inf, sz_inf,
                             ptr_inf,     sz_inf
                            );
      }

      ptr_inf = tmp_ptr_inf;
   }

   _MEM_T ptr = malloc(sizeof(mem_head_t) + size);
   if (!ptr)
   {
      if (ptr_inf)
      {
         free(ptr_inf);
      }

      return MEM_ERR_ALLOC;
   }

   mem_head_t *mem_head = (mem_head_t*)ptr;

   mem_head->ptr_inf = ptr_inf;
   mem_head->sz_inf  = (uint32_t)sz_inf;
   mem_head->sz_mem  = size;
   mem_head->id_mem  = _MEM_ID;

   ptr += sizeof(mem_head_t);
   *(_ADDR_T)addr_ptr = ptr;

   if (ptr_dat && sz_dat)
   {
      (void) _SetMemElems(ptr, size, ptr_dat, sz_dat);
   }

   return MEM_RET_SUCCESS;
}



int ReallocMem (void *addr_ptr, size_t sz_old, size_t sz_new,
                void *ptr_dat,  size_t sz_dat,
                int ch_inf,
                void *ptr_inf,  size_t sz_inf
               )
{
   if (!addr_ptr)
   {
      return MEM_ERR_ADDR_PTR_NULL;
   }

   _MEM_T ptr = *(_ADDR_T)addr_ptr;
   if (!ptr)
   {
      return AllocMem(addr_ptr, sz_new,
                      ptr_dat,  sz_dat,
                      ptr_inf,  sz_inf
                     );
   }

   *(_ADDR_T)addr_ptr = NULL;

   mem_head_t *mem_head = (mem_head_t*)(ptr - sizeof(mem_head_t));
   int is_memlib = mem_head->id_mem == _MEM_ID;
   if (is_memlib)
   {
      ptr = (_MEM_T)mem_head;
   }

   if (!sz_new)
   {
      if (is_memlib)
      {
         sz_new = mem_head->sz_mem;

         if (mem_head->sz_inf && mem_head->ptr_inf)
         {
            free(mem_head->ptr_inf);
         }
      }

      if (!ch_inf)
      {
         free(ptr);

         return MEM_RET_SUCCESS;
      }
   }

   size_t sz_tot = sz_new;

   if (is_memlib)
   {
      if (sz_old != mem_head->sz_mem)
      {
         sz_old = mem_head->sz_mem;
      }

      if (ch_inf)
      {
         if (!sz_inf)
         {
            mem_head->sz_inf = 0;
            ptr_inf = NULL;

            if (mem_head->ptr_inf)
            {
               free(mem_head->ptr_inf);
            }

            mem_head->ptr_inf = NULL;
         }
         else if (sz_inf != mem_head->sz_inf)
         {
            mem_head->sz_inf  = (uint32_t)sz_inf;
            mem_head->ptr_inf = realloc(mem_head->ptr_inf, sz_inf);
            if (!(mem_head->ptr_inf))
            {
               free(ptr);

               return MEM_ERR_ALLOC;
            }
         }

         if (ptr_inf && mem_head->ptr_inf)
         {
            (void) _SetMemElems(mem_head->ptr_inf, sz_inf,
                                ptr_inf,           sz_inf
                               );
         }

      }  // if (ch_inf)

      ptr_inf = mem_head->ptr_inf;
      mem_head->sz_mem = sz_tot;
      sz_tot += sizeof(mem_head_t);

   }  // if (is_memlib)

   else
   {
      ptr_inf = NULL;
   }

   if (sz_old == sz_new)
   {
      if (is_memlib)
      {
         ptr += sizeof(mem_head_t);
      }

      *(_ADDR_T)addr_ptr = ptr;

      return MEM_RET_SUCCESS;
   }

   ptr = realloc(ptr, sz_tot);
   if (!ptr)
   {
      if (ptr_inf)
      {
         free(ptr_inf);
      }

      return MEM_ERR_ALLOC;
   }

   ptr += sizeof(mem_head_t);
   *(_ADDR_T)addr_ptr = ptr;

   if (ptr_dat && sz_dat && sz_new > sz_old)
   {
      (void) _SetMemElems(ptr + sz_old,
                          sz_new - sz_old,
                          ptr_dat,
                          sz_dat
                         );
   }

   return MEM_RET_SUCCESS;
}



int FreeMem (void *addr_ptr)
{
   return ReallocMem(addr_ptr, 0, 0, NULL, 0, 0, NULL, 0);
}



size_t MemSize (void *ptr)
{
   if (!ptr)
   {
      return 0;
   }

   mem_head_t *mem_head = (mem_head_t*)((_MEM_T)ptr - sizeof(mem_head_t));

   return mem_head->id_mem == _MEM_ID ?
          mem_head->sz_mem :
          0;
}



int ClrMem (void *ptr, size_t size)
{
   size_t sz_ptr = MemSize(ptr);
   if (sz_ptr &&
       (!size || size > sz_ptr)
      )
   {
      size = sz_ptr;
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

   size_t sz_ptr = MemSize(ptr);
   if (sz_ptr &&
       (!idx_e || idx_e > sz_ptr)
      )
   {
      idx_e = sz_ptr;
   }

   if (idx_s >= idx_e)
   {
      return MEM_ERR_INVALID_IDX;
   }

   (void) _SetMemElems((_MEM_T)ptr + idx_s,
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

   mem_head_t *mem_head = (mem_head_t*)((_MEM_T)ptr_src -
                                        sizeof(mem_head_t));
   int is_memlib = mem_head->id_mem == _MEM_ID;
   if (is_memlib &&
       (!idx_e || idx_e > mem_head->sz_mem)
      )
   {
      idx_e = mem_head->sz_mem;
   }

   if (idx_s >= idx_e)
   {
      return MEM_ERR_INVALID_IDX;
   }

   idx_e -= idx_s;

   _MEM_T tmp_ptr_src = (_MEM_T)ptr_src + idx_s;

   if (is_memlib)
   {
      return AllocMem(addr_ptr_dst,
                      idx_e,
                      tmp_ptr_src,
                      idx_e,
                      mem_head->ptr_inf,
                      mem_head->sz_inf
                     );
   }

   _MEM_T ptr_dst = malloc(idx_e);
   if (!ptr_dst)
   {
      return MEM_ERR_ALLOC;
   }

   *(_ADDR_T)addr_ptr_dst = ptr_dst;

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

   size_t tmp_size = MemSize(ptr_src);
   if (tmp_size &&
       (!sz_src || sz_src > tmp_size)
      )
   {
      sz_src = tmp_size;
   }

   if (!sz_src)
   {
      return MEM_ERR_INVALID_SIZE;
   }

   mem_head_t *mem_head = (mem_head_t*)(ptr_dst - sizeof(mem_head_t));
   if (mem_head->id_mem == _MEM_ID)
   {
      if (!sz_dst || sz_dst > mem_head->sz_mem)
      {
         sz_dst = mem_head->sz_mem;
      }

      return ReallocMem(addr_ptr_dst,
                        sz_dst,
                        sz_dst + sz_src,
                        ptr_src,
                        sz_src,
                        MEM_TRUE,
                        mem_head->ptr_inf,
                        mem_head->sz_inf
                       );
   }

   *(_ADDR_T)addr_ptr_dst = NULL;
   ptr_dst = realloc(ptr_dst, sz_dst + sz_src);
   if (!ptr_dst)
   {
      return MEM_ERR_ALLOC;
   }

   *(_ADDR_T)addr_ptr_dst = ptr_dst;

   (void) _SetMemElems(ptr_dst + sz_dst,
                       sz_src,
                       ptr_src,
                       sz_src
                      );

   return MEM_RET_SUCCESS;
}



size_t MemInfoSize(void *ptr)
{
   if (!ptr)
   {
      return 0;
   }

   mem_head_t *mem_head = (mem_head_t*)((_MEM_T)ptr - sizeof(mem_head_t));

   return mem_head->id_mem == _MEM_ID ?
          mem_head->sz_inf :
          0;
}



int GetMemInfo (void *addr_ptr_inf, void *ptr)
{
   if (!addr_ptr_inf)
   {
      return MEM_ERR_ADDR_PTR_NULL;
   }

   *(_ADDR_T)addr_ptr_inf = NULL;

   if (!ptr)
   {
      return MEM_ERR_PTR_NULL;
   }

   mem_head_t *mem_head = (mem_head_t*)((_MEM_T)ptr - sizeof(mem_head_t));
   if (mem_head->id_mem != _MEM_ID)
   {
      return MEM_ERR_NOT_MEMLIB;
   }
   if (!(mem_head->sz_inf) || !(mem_head->ptr_inf))
   {
      mem_head->ptr_inf = NULL;

      return MEM_ERR_NOT_EXIST;
   }

   *(_ADDR_T)addr_ptr_inf = mem_head->ptr_inf;

   return MEM_RET_SUCCESS;
}