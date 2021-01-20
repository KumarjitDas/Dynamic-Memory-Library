#include "mem/mem.h"


/*! I know this is too much! But I am using CTest for the first time.
 */


#define MAJ 999999
#define MIN 999999
#define PAT 999999


int main(int argc, char **argv)
{
   if (argc < 2)
   {
      return 0;
   }

   int maj = MAJ,
       min = MIN,
       pat = PAT;

   switch (strtol(argv[1], NULL, 10))
   {
      case 1:  // test 1
      {
         MemLibVersion(NULL, NULL, NULL);

         return !(maj == MAJ &&
                  min == MIN &&
                  pat == PAT
                 );
      }
      case 2:  // test 2
      {
         MemLibVersion(NULL, NULL, &pat);

         return !(maj == MAJ &&
                  min == MIN &&
                  pat != PAT
                 );
      }
      case 3:  // test 3
      {
         MemLibVersion(NULL, &min, NULL);

         return !(maj == MAJ &&
                  min != MIN &&
                  pat == PAT
                 );
      }
      case 4:  // test 4
      {
         MemLibVersion(NULL, &min, &pat);

         return !(maj == MAJ &&
                  min != MIN &&
                  pat != PAT
                 );
      }
      case 5:  // test 5
      {
         MemLibVersion(&maj, NULL, NULL);

         return !(maj != MAJ &&
                  min == MIN &&
                  pat == PAT
                 );
      }
      case 6:  // test 6
      {
         MemLibVersion(&maj, NULL, &pat);

         return !(maj != MAJ &&
                  min == MIN &&
                  pat != PAT
                 );
      }
      case 7:  // test 7
      {
         MemLibVersion(&maj, &min, NULL);

         return !(maj != MAJ &&
                  min != MIN &&
                  pat == PAT
                 );
      }
      case 8:  // test 8
      {
         MemLibVersion(&maj, &min, &pat);

         return !(maj != MAJ &&
                  min != MIN &&
                  pat != PAT
                 );
      }
   }

   return 0;
}