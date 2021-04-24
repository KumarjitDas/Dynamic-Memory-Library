#ifndef DYNMEM_utility_utility_h
#define DYNMEM_utility_utility_h

#ifdef DYNMEM_INTERNAL_USE_utility_utility_h

#include "common/export.h"
#include "common/defines.h"
#include "common/standard_includes.h"
#include "common/types.h"

void DynMemUtilitySetMemory(void *destination, intmax_t destination_size, void *source, intmax_t source_size);

#undef DYNMEM_INTERNAL_USE_utility_defines_h

#endif  // DYNMEM_INTERNAL_USE_utility_utility_h

#endif  // DYNMEM_utility_utility_h
