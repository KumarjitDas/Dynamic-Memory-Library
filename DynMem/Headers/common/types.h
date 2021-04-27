#ifndef DYNMEM_common_types_h
#define DYNMEM_common_types_h

#include "defines.h"
#include "standard_includes.h"

struct DynMemDynMem {
    intmax_t  element_size;
    intmax_t  length;
    intmax_t  current_length;
    intmax_t  start_index;
    intmax_t  end_index;
    uint8_t  *memory;
};

typedef struct DynMemDynMem dynmem_t;

#endif  // DYNMEM_common_types_h
