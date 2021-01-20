#include "util.h"
#include "mem/_fast.h"



// void * AllocMemFast (size_t size)
// {

// }



// void * ReallocMemFast (void *ptr, size_t sz_new)
// {

// }



// void FreeMemFast (void *ptr)
// {

// }



size_t MemSizeFast (void *ptr)
{
   return ((mem_head_t*)((_MEM_T)(ptr) - sizeof(mem_head_t)))->sz_mem;
}



// void ClrMemFast (void *ptr, size_t size)
// {

// }



// void SetMemFast (void *ptr, size_t idx_s, size_t idx_e,
//                  void *ptr_dat, size_t sz_dat
//                 )
// {

// }



// void * CpyMemFast (void *ptr, size_t idx_s, size_t idx_e)
// {

// }



// void * ApnMemFast (void *ptr_dst, size_t sz_dst,
//                    void *ptr_src, size_t sz_src
//                   )
// {

// }



size_t MemInfoSizeFast (void *ptr)
{
   return ((mem_head_t*)((_MEM_T)(ptr) - sizeof(mem_head_t)))->sz_inf;
}



void * GetMemInfoFast (void *ptr)
{
   return ((mem_head_t*)((_MEM_T)(ptr) - sizeof(mem_head_t)))->ptr_inf;
}