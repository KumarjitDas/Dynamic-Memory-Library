#ifndef _MEM__H_
#define _MEM__H_


#include "mem_export.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define MEM_RET_TRUE  1
#define MEM_RET_FALSE 0

#define MEM_RET_SUCCESS 0
#define MEM_RET_FAILURE 1

#define MEM_IDX_S 0
#define MEM_IDX_E 0

#define MEM_AUTO_DTCT   0
#define MEM_TOT_SIZE    MEM_AUTO_DTCT
#define MEM_MAX_SIZE    MEM_TOT_SIZE

#define MEM_ERR_PTR_NULL      0x8001
#define MEM_ERR_ADDR_PTR_NULL 0x8002
#define MEM_ERR_ALLOC         0x8003
#define MEM_ERR_INVALID_SIZE  0x8004
#define MEM_ERR_INVALID_IDX   0x8005
#define MEM_ERR_NOT_MEMLIB    0x8006
#define MEM_ERR_NOT_EXIST     0x8007


#ifdef __cplusplus
extern "C" {
#endif


void MEM_EXPORT MemLibVersion (int *ptr_maj, int *ptr_min, int *ptr_pat);


int MEM_EXPORT AllocMem (void *addr_ptr, size_t size,
                         void *ptr_dat,  size_t sz_dat,
                         void *ptr_inf,  size_t sz_inf
                        );


int MEM_EXPORT ResizeMem (void *addr_ptr, size_t sz_old, size_t sz_new,
                          void *ptr_dat,  size_t sz_dat
                         );


int MEM_EXPORT FreeMem (void *addr_ptr);


size_t MEM_EXPORT MemSize (void *ptr);


int MEM_EXPORT ClrMem (void *ptr, size_t size);


int MEM_EXPORT SetMem (void *ptr, size_t idx_s, size_t idx_e,
                       void *ptr_dat, size_t sz_dat
                      );


int MEM_EXPORT CpyMem (void *addr_ptr_dst, void *ptr_src,
                       size_t idx_s, size_t idx_e
                      );


int MEM_EXPORT ApnMem (void *addr_ptr_dst, size_t sz_dst,
                       void *ptr_src, size_t sz_src
                      );


// size_t MEM_EXPORT MemExtraInfoSize (void *ptr);


// int MEM_EXPORT GetMemExtraInfo (void *addr_ptr_ex_inf, void *ptr);


// int MEM_EXPORT ChMemExtraInfo (void *addr_ptr, void *ptr_inf, size_t sz_inf);


#ifdef __cplusplus
}
#endif


#endif   // _MEM__H_