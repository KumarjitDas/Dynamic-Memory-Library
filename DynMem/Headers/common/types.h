#ifndef DYNMEM_common_types_h
#define DYNMEM_common_types_h

#include "defines.h"
#include "standard_includes.h"

struct DynMemHeader {
   intmax_t
       es,   // Element size
       is,   // Initial size
       cs,   // Current size
       bis,  // Beginning index in size
       eis,  // Ending index in size
       bi,   // Beginning index in size
       ei;   // Ending index in size
   uint8_t *m;
};

typedef struct DynMemHeader dynmem_t;

#endif  // DYNMEM_common_types_h
