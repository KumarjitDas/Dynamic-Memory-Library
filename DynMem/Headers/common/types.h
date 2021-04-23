#ifndef DYNMEM_common_types_h
#define DYNMEM_common_types_h

#include "standard_includes.h"

struct DynMemDynMem {
    intmax_t  element_size;
    intmax_t  initial_size;
    intmax_t  size;
    intmax_t  length;
    intmax_t  index;
    uint8_t  *memory;
};

typedef struct DynMemDynMem dynmem_t;

#endif  // DYNMEM_common_types_h
