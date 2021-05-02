#ifndef DYNMEM_UTILITY_UTILITY_H
#define DYNMEM_UTILITY_UTILITY_H

#ifdef DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H

#include "dynmem/common/defines.h"
#include "dynmem/common/standard_includes.h"
#include "dynmem/common/types.h"

void DYNMEM_UTILITY_EXPORT DynMemUtilitySetMemoryBlock(uint8_t *destination, uint8_t *source, intmax_t size);

void DYNMEM_UTILITY_EXPORT DynMemUtilitySetMemory(void *destination, intmax_t destination_size,
                                                  void *source, intmax_t source_size);

void DYNMEM_UTILITY_EXPORT DynMemUtilityResetMemory(uint8_t *destination, intmax_t size);

#endif  // DYNMEM_INTERNAL_USE_UTILITY_UTILITY_H

#endif  // DYNMEM_UTILITY_UTILITY_H
