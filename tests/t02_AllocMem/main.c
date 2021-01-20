#include "mem/mem.h"
#include "mem/_mem.h"


typedef struct
{
   int a, b;
   long long c;
}
info_t;


int CmpInfo(info_t * i1, info_t * i2)
{
   return i1->a == i2->a &&
          i1->b == i2->b &&
          i1->c == i2->c;
}


// To compare the contents of two different memory location
int CmpPtr(char * p1, char * p2, size_t s)
{
   while (s--)
   {
      if (p1[s] != p2[s])
      {
         return 0;
      }
   }

   return 1;
}


int main(int argc, char **argv)
{
   if (argc < 2)
   {
      return 0;
   }

   int      ret     = 0;
   char   * mem     = NULL;
   size_t   sz_mem  = 5;
   info_t   inf     = {.a = 987, .b = 654321, .c = 987654321};
   size_t   sz_inf  = sizeof(inf);
   char     dat     = 'A';
   size_t   sz_dat  = sizeof(dat);

   switch (strtol(argv[1], NULL, 10))
   {
      case 1:  // test 1
      {
         return !(AllocMem(NULL, 0, NULL, 0, NULL, 0) ==
                  MEM_ERR_ADDR_PTR_NULL
                 );
      }

      case 2:  // test 2
      {
         return !(AllocMem(&mem, 0, NULL, 0, NULL, 0) ==
                  MEM_ERR_INVALID_SIZE
                 );
      }

      case 3:  // test 3
      {
         ret = AllocMem(&mem, sz_mem, NULL, 0, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)0x04D454D0 &&
               head->sz_mem  == sz_mem               &&
               head->sz_inf  == 0                    &&
               head->ptr_inf == NULL                 &&
               ret == MEM_RET_SUCCESS;

         free(head);

         return !ret;
      }

      case 4:  // test 4
      {
         ret = AllocMem(&mem, sz_mem, &dat, 0, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)0x04D454D0 &&
               head->sz_mem  == sz_mem               &&
               head->sz_inf  == 0                    &&
               head->ptr_inf == NULL                 &&
               !CmpPtr(mem, &dat, sz_dat)            &&
               ret == MEM_RET_SUCCESS;

         free(head);

         return !ret;
      }

      case 5:  // test 5
      {
         ret = AllocMem(&mem, sz_mem, NULL, sz_dat, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)0x04D454D0 &&
               head->sz_mem  == sz_mem               &&
               head->sz_inf  == 0                    &&
               head->ptr_inf == NULL                 &&
               !CmpPtr(mem, &dat, sz_dat)            &&
               ret == MEM_RET_SUCCESS;

         free(head);

         return !ret;
      }

      case 6:  // test 6
      {
         ret = AllocMem(&mem, sz_mem, &dat, sz_dat, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)0x04D454D0 &&
               head->sz_mem  == sz_mem               &&
               head->sz_inf  == 0                    &&
               head->ptr_inf == NULL                 &&
               CmpPtr(mem, &dat, sz_dat)             &&
               ret == MEM_RET_SUCCESS;

         free(head);

         return !ret;
      }

      case 7:  // test 7
      {
         ret = AllocMem(&mem, sz_mem, &dat, sz_dat, &inf, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)0x04D454D0 &&
               head->sz_mem  == sz_mem               &&
               head->sz_inf  == 0                    &&
               head->ptr_inf == NULL                 &&
               CmpPtr(mem, &dat, sz_dat)             &&
               ret == MEM_RET_SUCCESS;

         free(head);

         return !ret;
      }

      case 8:  // test 8
      {
         ret = AllocMem(&mem, sz_mem, &dat, sz_dat, NULL, sz_inf);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)0x04D454D0 &&
               head->sz_mem  == sz_mem               &&
               head->sz_inf  == sz_inf               &&
               head->ptr_inf != NULL                 &&
               CmpPtr(mem, &dat, sz_dat)             &&
               ret == MEM_RET_SUCCESS;

         free(head->ptr_inf);
         free(head);

         return !ret;
      }

      case 9:  // test 9
      {
         ret = AllocMem(&mem, sz_mem, &dat, sz_dat, &inf, sz_inf);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)0x04D454D0 &&
               head->sz_mem  == sz_mem               &&
               head->sz_inf  == sz_inf               &&
               head->ptr_inf != NULL                 &&
               CmpPtr(mem, &dat, sz_dat)             &&
               CmpInfo(head->ptr_inf, &inf)          &&
               ret == MEM_RET_SUCCESS;

         free(head->ptr_inf);
         free(head);

         return !ret;
      }

   }  // switch (strtol(argv[1], NULL, 10))

   return 0;
}