#ifndef _MEM__UTIL__H_
#define _MEM__UTIL__H_


#include "mem/mem.h"
#include "config/memConfig.h"


#define _MEM_HEADER_SIZE    (sizeof(size_t) + 2)
#define _MEM_HEADER1_ID     0XF0
#define _MEM_HEADER2_ID     0X0F
#define _MEM_HEADER2CONT_ID 0X1F

#define _MEM_RET_HAS_HEADER2CONT 2

#define _BYTE_T unsigned char
#define _MEM_T  _BYTE_T *
#define _ADDR_T _MEM_T*

#define _GET_MEM_SIZE(M) (*(size_t*)((_MEM_T)(M) - (1 + sizeof(size_t))))


void _setMemExtraInfo(_MEM_T ptr, _MEM_T ptr_inf, size_t sz_inf);


void _setMemSizeHeader(_MEM_T ptr, size_t size, int has_cont);


void _setMemElems(_MEM_T ptr, size_t size, _MEM_T ptr_elem, size_t sz_elem);


int _hasMemHeader(_MEM_T ptr);


#endif  // _MEM__UTIL__H_