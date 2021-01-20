#ifndef _MEMLIB___FAST__H_
#define _MEMLIB___FAST__H_


#include "defs.h"


#ifdef __cplusplus
extern "C" {
#endif


void MEMLIB_API * AllocMemFast (size_t size);


void MEMLIB_API * ReallocMemFast (void *ptr, size_t sz_new);


void MEMLIB_API FreeMemFast (void *ptr);


size_t MEMLIB_API MemSizeFast (void *ptr);


void MEMLIB_API ClrMemFast (void *ptr, size_t size);


void MEMLIB_API SetMemFast (void *ptr, size_t idx_s, size_t idx_e,
                            void *ptr_dat, size_t sz_dat
                           );


void MEMLIB_API * CpyMemFast (void *ptr, size_t idx_s, size_t idx_e);


void MEMLIB_API * ApnMemFast (void *ptr_dst, size_t sz_dst,
                              void *ptr_src, size_t sz_src
                             );


size_t MEMLIB_API MemInfoSizeFast (void *ptr);


void MEMLIB_API * GetMemInfoFast (void *ptr);



#ifdef __cplusplus
}
#endif


#endif   // _MEMLIB___FAST__H_