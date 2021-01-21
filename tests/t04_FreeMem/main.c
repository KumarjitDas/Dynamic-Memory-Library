#include "mem/mem.h"
#include "mem/_mem.h"


typedef struct
{
   int a, b;
   long long c;
}
info1_t;


int main(int argc, char **argv)
{
   if (argc < 2)
   {
      return 0;
   }

   int       ret    = 0;
   char     *mem    = NULL;
   size_t    sz_mem = 5;
   info1_t   inf1   = {.a = 987, .b = 654321, .c = 987654321};
   uint32_t  sz_inf = sizeof(inf1);

   switch (strtol(argv[1], NULL, 10))
   {
      case 1:  // ---------- test 1 ----------
      {
         return !(FreeMem(NULL) == MEM_RET_SUCCESS);
      }

      case 2:  // ---------- test 2 ----------
      {
         return !(FreeMem(&mem) == MEM_RET_SUCCESS);
      }

      case 3:  // ---------- test 3 ----------
      {
         mem = malloc(sz_mem);
         if (!mem)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         ret = FreeMem(&mem);

         return !(mem == NULL &&
                  ret == MEM_RET_SUCCESS
                 );
      }

      case 4:  // ---------- test 4 ----------
      {
         // Assuming AllocMem is tested
         if (AllocMem(&mem, sz_mem, NULL, 0, NULL, 0) ==
             MEM_ERR_ALLOC
         ) {
            return 0;   // Because we can do nothing about malloc crashing
         }

         ret = FreeMem(&mem);

         return !(mem == NULL &&
                  ret == MEM_RET_SUCCESS
                 );
      }

      case 5:  // ---------- test 5 ----------
      {
         // Assuming AllocMem is tested
         if (AllocMem(&mem, sz_mem, NULL, 0, &inf1, sz_inf) ==
             MEM_ERR_ALLOC
         ) {
            return 0;   // Because we can do nothing about malloc crashing
         }

         ret = FreeMem(&mem);

         return !(mem == NULL &&
                  ret == MEM_RET_SUCCESS
                 );
      }
   }  // switch (strtol(argv[1], NULL, 10))

   return 0;
}