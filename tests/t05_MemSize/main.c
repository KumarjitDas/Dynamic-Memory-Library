#include "mem/mem.h"


int main(int argc, char **argv)
{
   if (argc < 2)
   {
      return 0;
   }

   char   *mem    = NULL;
   size_t  sz_mem = 5;

   switch (strtol(argv[1], NULL, 10))
   {
      case 1:  // ---------- test 1 ----------
      {
         return !(MemSize(NULL) == 0);
      }

      case 2:  // ---------- test 2 ----------
      {
         mem = malloc(sz_mem);
         if (!mem)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         sz_mem = MemSize(mem);

         // Assuming FreeMem is tested
         (void) FreeMem(&mem);

         return !(sz_mem == 0);
      }

      case 3:  // ---------- test 4 ----------
      {
         // Assuming AllocMem is tested
         if (AllocMem(&mem, sz_mem, NULL, 0, NULL, 0) ==
             MEM_ERR_ALLOC
         ) {
            return 0;   // Because we can do nothing about malloc crashing
         }

         size_t tmp_sz_mem = MemSize(mem);

         // Assuming FreeMem is tested
         (void) FreeMem(&mem);

         return !(tmp_sz_mem == sz_mem);
      }
   }  // switch (strtol(argv[1], NULL, 10))

   return 0;
}