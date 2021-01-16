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

#define MEM_ERR_PTR_NULL      0x8001
#define MEM_ERR_PTR_ADDR_NULL 0x8002
#define MEM_ERR_ALLOC         0x8003
#define MEM_ERR_INVALID_SIZE  0x8004

#define MEM_IS_ERR(X)     ((0xF000 & X)==0X8000)
#define MEM_IS_NOT_ERR(X) ((0xF000 & X)==0X0000)


#ifdef __cplusplus
extern "C" {
#endif


void MEM_EXPORT memLibVersion(int *addr_maj, int *addr_min, int *addr_pat);


int MEM_EXPORT allocMem(
  void *addr_ptr, size_t size,
  void *ptr_dat,  size_t sz_dat,
  void *ptr_inf,  size_t sz_inf
);


int MEM_EXPORT freeMem(void *addr_ptr);


size_t MEM_EXPORT memSize(void *mem);


int MEM_EXPORT setMem(void *mem, size_t size, void *ptr_elem, size_t sz_elem);


int MEM_EXPORT getMemExtraInfo(void *addr_ex_inf, void *mem);


size_t MEM_EXPORT memExtraInfoSize(void *mem);


int MEM_EXPORT reallocMem(
  void *addr_new_ptr, size_t sz_new_ptr, void *addr_ptr,
  void *ptr_new_dat,  size_t sz_new_dat,
  void *ptr_new_inf,  size_t sz_new_inf
);


int MEM_EXPORT cpyMem(void *adst, void *amem);


#ifdef __cplusplus
}
#endif


#endif  // _MEM__H_