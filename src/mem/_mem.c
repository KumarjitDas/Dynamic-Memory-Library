// uitl.h already includes _mem.h
#include "util.h"



// void * _AllocMem (size_t size)
// {

// }



// void * _ReallocMem (void *ptr, size_t sz_new)
// {

// }



// void _FreeMem (void *ptr)
// {

// }



size_t _MemSize (void *ptr)
{
   return ((_mem_head_t*)((_MEM_T)(ptr) - sizeof(_mem_head_t)))->sz_mem;
}



// void _ClrMem (void *ptr, size_t size)
// {

// }



// void _SetMem (void *ptr, size_t idx_s, size_t idx_e,
//                  void *ptr_dat, size_t sz_dat
//                 )
// {

// }



// void * _CpyMem (void *ptr, size_t idx_s, size_t idx_e)
// {

// }



// void * _ApnMem (void *ptr_dst, size_t sz_dst,
//                    void *ptr_src, size_t sz_src
//                   )
// {

// }



size_t _MemInfoSize (void *ptr)
{
   return ((_mem_head_t*)((_MEM_T)(ptr) - sizeof(_mem_head_t)))->sz_inf;
}



void * _GetMemInfo (void *ptr)
{
   return ((_mem_head_t*)((_MEM_T)(ptr) - sizeof(_mem_head_t)))->ptr_inf;
}