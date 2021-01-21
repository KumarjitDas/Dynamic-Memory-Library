#include "mem/mem.h"
#include "mem/_mem.h"


#define MEM_HEAD 0x04D454D0


typedef struct
{
   int a, b;
   long long c;
}
info1_t;

typedef struct
{
   long long a, b, c;
}
info2_t;


int CmpInfo1(info1_t * i1, info1_t * i2)
{
   return i1->a == i2->a &&
          i1->b == i2->b &&
          i1->c == i2->c;
}


int CmpInfo2(info2_t * i1, info2_t * i2)
{
   return i1->a == i2->a &&
          i1->b == i2->b &&
          i1->c == i2->c;
}


int main(int argc, char **argv)
{
   if (argc < 2)
   {
      return 0;
   }

   int       ret    = 0;
   char     *mem    = NULL;
   size_t    sz_mem = 5;
   size_t    sz_new = 7;
   info1_t   inf1   = {.a = 987, .b = 654321, .c = 987654321};
   uint32_t  sz_inf = sizeof(inf1);
   char      dat    = 'A';
   size_t    sz_dat = sizeof(dat);

   switch (strtol(argv[1], NULL, 10))
   {
      case 1:  // ---------- test 1 ----------
      {
         return !(ReallocMem(NULL, 0, 0, NULL, 0, MEM_FALSE, NULL, 0) ==
                  MEM_ERR_ADDR_PTR_NULL
                 );
      }

      case 2:  // ---------- test 2 ----------
      {
         return !(ReallocMem(&mem, 0, 0, NULL, 0, MEM_FALSE, NULL, 0) ==
                  MEM_ERR_INVALID_SIZE
                 );
      }

      case 3:  // ---------- test 3 ----------
      {
         return !(ReallocMem(&mem, 123, 0, NULL, 0, MEM_FALSE, NULL, 0) ==
                  MEM_ERR_INVALID_SIZE
                 );
      }

      case 4:  // ---------- test 4 ----------
      {
         ret = ReallocMem(&mem, 0, sz_mem, NULL, 0, MEM_FALSE, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)MEM_HEAD &&
               head->sz_mem  == sz_mem             &&
               head->sz_inf  == 0                  &&
               head->ptr_inf == NULL               &&
               ret == MEM_RET_SUCCESS;

         free(head);

         return !ret;
      }

      case 5:  // ---------- test 5 ----------
      {
         ret = ReallocMem(&mem, 0, sz_mem, &dat, 0, MEM_FALSE, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)MEM_HEAD &&
               head->sz_mem  == sz_mem             &&
               head->sz_inf  == 0                  &&
               head->ptr_inf == NULL               &&
               ret == MEM_RET_SUCCESS;

         free(head);

         return !ret;
      }

      case 6:  // ---------- test 6 ----------
      {
         ret = ReallocMem(&mem, 0, sz_mem, NULL, sz_dat, MEM_FALSE, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)MEM_HEAD &&
               head->sz_mem  == sz_mem             &&
               head->sz_inf  == 0                  &&
               head->ptr_inf == NULL               &&
               ret == MEM_RET_SUCCESS;

         free(head);

         return !ret;
      }

      case 7:  // ---------- test 7 ----------
      {
         ret = ReallocMem(&mem, 0, sz_mem, &dat, sz_dat, MEM_FALSE, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)MEM_HEAD &&
               head->sz_mem  == sz_mem             &&
               head->sz_inf  == 0                  &&
               head->ptr_inf == NULL               &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == dat;
         }

         free(head);

         return !ret;
      }

      case 8:  // ---------- test 8 ----------
      {
         ret = ReallocMem(&mem, 0, sz_mem, &dat, sz_dat, MEM_FALSE, &inf1, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)MEM_HEAD &&
               head->sz_mem  == sz_mem             &&
               head->sz_inf  == 0                  &&
               head->ptr_inf == NULL               &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == dat;
         }

         free(head);

         return !ret;
      }

      case 9:  // ---------- test 9 ----------
      {
         ret = ReallocMem(&mem, 0, sz_mem,
                          &dat, sz_dat,
                          MEM_FALSE,
                          &inf1, sz_inf
                         );
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)MEM_HEAD &&
               head->sz_mem  == sz_mem             &&
               head->sz_inf  == sz_inf             &&
               head->ptr_inf != NULL               &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == dat;
         }

         free(head->ptr_inf);
         free(head);

         return !ret;
      }

      case 10:  // ---------- test 10 ----------
      {
         ret = ReallocMem(&mem, 0, sz_mem,
                          &dat, sz_dat,
                          MEM_FALSE,
                          &inf1, sz_inf
                         );
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = head->id_mem  == (uint32_t)MEM_HEAD &&
               head->sz_mem  == sz_mem             &&
               head->sz_inf  == sz_inf             &&
               head->ptr_inf != NULL               &&
               CmpInfo1(head->ptr_inf, &inf1)      &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == dat;
         }

         free(head->ptr_inf);
         free(head);

         return !ret;
      }

      case 11:  // ---------- test 11 ----------
      {
         mem = malloc(sz_mem);
         if (!mem)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         ret = ReallocMem(&mem, 0, 0, NULL, 0, MEM_FALSE, NULL, 0);

         return !(mem == NULL &&
                  ret == MEM_RET_SUCCESS
                 );
      }

      case 12:  // ---------- test 12 ----------
      {
         mem = malloc(sz_mem);
         if (!mem)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         ret = ReallocMem(&mem, sz_mem, sz_mem, NULL, 0, MEM_FALSE, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         ret = mem != NULL &&
               ret == MEM_RET_SUCCESS;

         if (mem)
         {
            free(mem);
         }

         return !ret;
      }

      case 13:  // ---------- test 13 ----------
      {
         mem = malloc(sz_mem);
         if (!mem)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         ret = ReallocMem(&mem, sz_mem, sz_new, NULL, 0, MEM_FALSE, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }
         ret = mem != NULL &&
               ret == MEM_RET_SUCCESS;

         if (mem)
         {
            free(mem);
         }

         return !ret;
      }

      case 14:  // ---------- test 14 ----------
      {
         mem = malloc(sz_mem);
         if (!mem)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         char val = 'E';
         for (size_t i = 0; i < sz_mem; i++)
         {
            mem[i] = val;
         }

         ret = ReallocMem(&mem, sz_mem, sz_new, NULL, 0, MEM_FALSE, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }
         ret = mem != NULL &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == val;
         }

         if (mem)
         {
            free(mem);
         }

         return !ret;
      }

      case 15:  // ---------- test 15 ----------
      {
         mem = malloc(sz_mem);
         if (!mem)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         char val = 'E';
         for (size_t i = 0; i < sz_mem; i++)
         {
            mem[i] = val;
         }

         ret = ReallocMem(&mem, sz_mem, sz_new,
                          &dat, 0,
                          MEM_FALSE,
                          NULL, 0
                         );
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }
         ret = mem != NULL &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == val;
         }

         if (mem)
         {
            free(mem);
         }

         return !ret;
      }

      case 16:  // ---------- test 16 ----------
      {
         mem = malloc(sz_mem);
         if (!mem)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         char val = 'E';
         for (size_t i = 0; i < sz_mem; i++)
         {
            mem[i] = val;
         }

         ret = ReallocMem(&mem, sz_mem, sz_new,
                          &dat, sz_dat,
                          MEM_FALSE,
                          NULL, 0
                         );
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }
         ret = mem != NULL &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == val;
         }

         for (size_t i = sz_mem; i < sz_new; i++)
         {
            ret = ret &&
                  mem[i] == dat;
         }

         if (mem)
         {
            free(mem);
         }

         return !ret;
      }

      case 17:  // ---------- test 17 ----------
      {
         mem = malloc(sz_mem);
         if (!mem)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         char val = 'E';
         for (size_t i = 0; i < sz_mem; i++)
         {
            mem[i] = val;
         }

         sz_new = sz_mem - 2;
         ret = ReallocMem(&mem, sz_mem, sz_new,
                          &dat, sz_dat,
                          MEM_FALSE,
                          NULL, 0
                         );
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }
         ret = mem != NULL &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_new; i++)
         {
            ret = ret &&
                  mem[i] == val;
         }

         if (mem)
         {
            free(mem);
         }

         return !ret;
      }

      case 18:  // ---------- test 18 ----------
      {
         // Assuming AllocMem is tested
         if (AllocMem(&mem, sz_mem, &dat, sz_dat, &inf1, sz_inf) ==
             MEM_ERR_ALLOC
         ) {
            return 0;   // Because we can do nothing about malloc crashing
         }

         return !(ReallocMem(&mem, 0, 0, NULL, 0, MEM_FALSE, NULL, 0) ==
                  MEM_RET_SUCCESS
                 );
      }

      case 19:  // ---------- test 19 ----------
      {
         // Assuming AllocMem is tested
         if (AllocMem(&mem, sz_mem, &dat, sz_dat, &inf1, sz_inf) ==
             MEM_ERR_ALLOC
         ) {
            return 0;   // Because we can do nothing about malloc crashing
         }

         ret = ReallocMem(&mem, 0, 0, NULL, 0, MEM_FALSE, NULL, 0);

         return !(mem == NULL &&
                  ret == MEM_RET_SUCCESS
                 );
      }

      case 20:  // ---------- test 20 ----------
      {
         // Assuming AllocMem is tested
         if (AllocMem(&mem, sz_mem, &dat, sz_dat, &inf1, sz_inf) ==
             MEM_ERR_ALLOC
         ) {
            return 0;   // Because we can do nothing about malloc crashing
         }

         ret = ReallocMem(&mem, 0, sz_mem, NULL, 0, MEM_FALSE, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = mem != NULL                    &&
               head->id_mem  == MEM_HEAD      &&
               head->sz_mem  == sz_mem        &&
               head->sz_inf  == sz_inf        &&
               head->ptr_inf != NULL          &&
               CmpInfo1(&inf1, head->ptr_inf) &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == dat;
         }

         free(head->ptr_inf);
         free(head);

         return !ret;
      }

      case 21:  // ---------- test 21 ----------
      {
         // Assuming AllocMem is tested
         if (AllocMem(&mem, sz_mem, &dat, sz_dat, &inf1, sz_inf) ==
             MEM_ERR_ALLOC
         ) {
            return 0;   // Because we can do nothing about malloc crashing
         }

         ret = ReallocMem(&mem, 0, sz_new, NULL, 0, MEM_FALSE, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = mem != NULL                    &&
               head->id_mem  == MEM_HEAD      &&
               head->sz_mem  == sz_new        &&
               head->sz_inf  == sz_inf        &&
               head->ptr_inf != NULL          &&
               CmpInfo1(&inf1, head->ptr_inf) &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == dat;
         }

         free(head->ptr_inf);
         free(head);

         return !ret;
      }

      case 22:  // ---------- test 22 ----------
      {
         // Assuming AllocMem is tested
         if (AllocMem(&mem, sz_mem, &dat, sz_dat, &inf1, sz_inf) ==
             MEM_ERR_ALLOC
         ) {
            return 0;   // Because we can do nothing about malloc crashing
         }

         char val = 'E';
         ret = ReallocMem(&mem, 0, sz_new,
                          &val, sizeof(val),
                          MEM_FALSE,
                          NULL, 0
                         );
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = mem != NULL                    &&
               head->id_mem  == MEM_HEAD      &&
               head->sz_mem  == sz_new        &&
               head->sz_inf  == sz_inf        &&
               head->ptr_inf != NULL          &&
               CmpInfo1(&inf1, head->ptr_inf) &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == dat;
         }

         for (size_t i = sz_mem; i < sz_new; i++)
         {
            ret = ret &&
                  mem[i] == val;
         }

         free(head->ptr_inf);
         free(head);

         return !ret;
      }

      case 23:  // ---------- test 23 ----------
      {
         // Assuming AllocMem is tested
         if (AllocMem(&mem, sz_mem, &dat, sz_dat, &inf1, sz_inf) ==
             MEM_ERR_ALLOC
         ) {
            return 0;   // Because we can do nothing about malloc crashing
         }

         ret = ReallocMem(&mem, 0, 0, NULL, 0, MEM_TRUE, NULL, 0);
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = mem != NULL                    &&
               head->id_mem  == MEM_HEAD      &&
               head->sz_mem  == sz_mem        &&
               head->sz_inf  == 0             &&
               head->ptr_inf == NULL          &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == dat;
         }

         free(head);

         return !ret;
      }

      case 24:  // ---------- test 24 ----------
      {
         // Assuming AllocMem is tested
         if (AllocMem(&mem, sz_mem, &dat, sz_dat, &inf1, sz_inf) ==
             MEM_ERR_ALLOC
         ) {
            return 0;   // Because we can do nothing about malloc crashing
         }

         char val = 'E';
         ret = ReallocMem(&mem, 0, sz_new,
                          &val, sizeof(val),
                          MEM_TRUE,
                          NULL, 0
                         );
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = mem != NULL               &&
               head->id_mem  == MEM_HEAD &&
               head->sz_mem  == sz_new   &&
               head->sz_inf  == 0        &&
               head->ptr_inf == NULL     &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == dat;
         }

         for (size_t i = sz_mem; i < sz_new; i++)
         {
            ret = ret &&
                  mem[i] == val;
         }

         free(head);

         return !ret;
      }

      case 25:  // ---------- test 25 ----------
      {
         // Assuming AllocMem is tested
         if (AllocMem(&mem, sz_mem, &dat, sz_dat, &inf1, sz_inf) ==
             MEM_ERR_ALLOC
         ) {
            return 0;   // Because we can do nothing about malloc crashing
         }

         char val = 'E';
         info1_t inf2 = {.a = 123, .b = 456789, .c = 12345678910};
         ret = ReallocMem(&mem, 0, sz_new,
                          &val, sizeof(val),
                          MEM_TRUE,
                          &inf2, sizeof(inf2)
                         );
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = mem != NULL                    &&
               head->id_mem  == MEM_HEAD      &&
               head->sz_mem  == sz_new        &&
               head->sz_inf  == sizeof(inf2)  &&
               head->ptr_inf != NULL          &&
               CmpInfo1(&inf2, head->ptr_inf) &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == dat;
         }

         for (size_t i = sz_mem; i < sz_new; i++)
         {
            ret = ret &&
                  mem[i] == val;
         }

         free(head);

         return !ret;
      }

      case 26:  // ---------- test 26 ----------
      {
         // Assuming AllocMem is tested
         if (AllocMem(&mem, sz_mem, &dat, sz_dat, &inf1, sz_inf) ==
             MEM_ERR_ALLOC
         ) {
            return 0;   // Because we can do nothing about malloc crashing
         }

         char val = 'E';
         info2_t inf2 = {.a = 12345678910, .b = 12345678911, .c = 12345678912};
         ret = ReallocMem(&mem, 0, sz_new,
                          &val, sizeof(val),
                          MEM_TRUE,
                          &inf2, sizeof(inf2)
                         );
         if (ret == MEM_ERR_ALLOC)
         {
            return 0;   // Because we can do nothing about malloc crashing
         }

         _mem_head_t *head = (_mem_head_t*)(mem - sizeof(_mem_head_t));

         ret = mem != NULL                    &&
               head->id_mem  == MEM_HEAD      &&
               head->sz_mem  == sz_new        &&
               head->sz_inf  == sizeof(inf2)  &&
               head->ptr_inf != NULL          &&
               CmpInfo2(&inf2, head->ptr_inf) &&
               ret == MEM_RET_SUCCESS;

         for (size_t i = 0; i < sz_mem; i++)
         {
            ret = ret &&
                  mem[i] == dat;
         }

         for (size_t i = sz_mem; i < sz_new; i++)
         {
            ret = ret &&
                  mem[i] == val;
         }

         free(head);

         return !ret;
      }

   }  // switch (strtol(argv[1], NULL, 10))

   return 0;
}