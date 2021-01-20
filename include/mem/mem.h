#ifndef _MEMLIB__MEM__H_
#define _MEMLIB__MEM__H_


#include "defs.h"


#ifdef __cplusplus
extern "C" {
#endif


void MEMLIB_API MemLibVersion (int *ptr_maj, int *ptr_min, int *ptr_pat);


int MEMLIB_API AllocMem (void *addr_ptr, size_t size,
                         void *ptr_dat,  size_t sz_dat,
                         void *ptr_inf,  size_t sz_inf
                        );


int MEMLIB_API ReallocMem (void *addr_ptr, size_t sz_old, size_t sz_new,
                           void *ptr_dat,  size_t sz_dat,
                           int ch_inf,
                           void *ptr_inf,  size_t sz_inf
                          );


int MEMLIB_API FreeMem (void *addr_ptr);


size_t MEMLIB_API MemSize (void *ptr);


int MEMLIB_API ClrMem (void *ptr, size_t size);


int MEMLIB_API SetMem (void *ptr, size_t idx_s, size_t idx_e,
                       void *ptr_dat, size_t sz_dat
                      );


int MEMLIB_API CpyMem (void *addr_ptr_dst, void *ptr_src,
                       size_t idx_s, size_t idx_e
                      );


int MEMLIB_API ApnMem (void *addr_ptr_dst, size_t sz_dst,
                       void *ptr_src, size_t sz_src
                      );


size_t MEMLIB_API MemInfoSize (void *ptr);


int MEMLIB_API GetMemInfo (void *addr_ptr_inf, void *ptr);



#ifdef __cplusplus
}
#endif


#endif   // _MEMLIB__MEM__H_