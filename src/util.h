#ifndef _MEM__UTIL__H_
#define _MEM__UTIL__H_



#include "mem/mem.h"
#include "config/memConfig.h"

#include <stdint.h>



// MEM ID:         M E M
#define _MEM_ID 0x04D454D0

#define _BYTE_T unsigned char
#define _MEM_T  _BYTE_T *
#define _ADDR_T _MEM_T*



typedef struct
{
   void     *ptr_inf;
   uint32_t  sz_inf;
   size_t    sz_mem;
   uint32_t  id_mem;
}
mem_head_t;



_MEM_T _SetMemElems(_MEM_T ptr, size_t size, _MEM_T ptr_elem, size_t sz_elem);



#endif  // _MEM__UTIL__H_