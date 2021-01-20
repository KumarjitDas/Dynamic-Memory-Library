#ifndef _MEMLIB___MEM__H_
#define _MEMLIB___MEM__H_


#include "defs.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef struct _mem_head_t
{
   void     *ptr_inf;
   uint32_t  sz_inf;
   size_t    sz_mem;
   uint32_t  id_mem;
}
_mem_head_t;


void MEMLIB_API * _AllocMem (size_t size);


void MEMLIB_API * _ReallocMem (void *ptr, size_t sz_new);


void MEMLIB_API _FreeMem (void *ptr);


size_t MEMLIB_API _MemSize (void *ptr);


void MEMLIB_API _ClrMem (void *ptr, size_t size);


void MEMLIB_API _SetMem (void *ptr, size_t idx_s, size_t idx_e,
                         void *ptr_dat, size_t sz_dat
                        );


void MEMLIB_API * _CpyMem (void *ptr, size_t idx_s, size_t idx_e);


void MEMLIB_API * _ApnMem (void *ptr_dst, size_t sz_dst,
                           void *ptr_src, size_t sz_src
                          );


size_t MEMLIB_API _MemInfoSize (void *ptr);


void MEMLIB_API * _GetMemInfo (void *ptr);



#ifdef __cplusplus
}
#endif


#endif   // _MEMLIB___MEM__H_