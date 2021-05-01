#ifndef DYNMEM_utility_utility_h
#define DYNMEM_utility_utility_h

#ifdef DYNMEM_INTERNAL_USE_utility_utility_h

#include "common/defines.h"
#include "common/standard_includes.h"
#include "common/types.h"

// source_size <= destination_size
void DYNMEM_UTILITY_EXPORT DynMemUtilitySetMemoryBlock(uint8_t *destination, uint8_t *source, intmax_t size);

// source_size <= destination_size
void DYNMEM_UTILITY_EXPORT DynMemUtilitySetMemory(void *destination, intmax_t destination_size,
                                                  void *source, intmax_t source_size);

#endif  // DYNMEM_INTERNAL_USE_utility_utility_h

#endif  // DYNMEM_utility_utility_h
