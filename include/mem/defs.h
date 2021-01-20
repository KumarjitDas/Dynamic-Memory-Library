#ifndef _MEMLIB__DEFS__H_
#define _MEMLIB__DEFS__H_


#include "mem_export.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define MEM_TRUE  1
#define MEM_FALSE 0

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

#define MEMLIB_API MEM_EXPORT


#endif   // _MEMLIB__DEFS__H_