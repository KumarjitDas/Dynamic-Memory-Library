#ifndef DYNMEM_common_types_h
#define DYNMEM_common_types_h

#include "defines.h"
#include "standard_includes.h"

struct DynMemHeader {
   intmax_t
       es,   // Element size
       is,   // Initial size
       cs,   // Current size
       bi,   // Beginning index
       ei;   // Ending index
   uint8_t *m;
};

typedef struct DynMemHeader dynmem_t;

#endif  // DYNMEM_common_types_h
