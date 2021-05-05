#ifndef DYNMEM_UTILITY_SET_GET_H
#define DYNMEM_UTILITY_SET_GET_H

#ifdef DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H

#include "dynmem/common/defines.h"
#include "dynmem/common/standard_includes.h"
#include "dynmem/common/types.h"

_Bool DYNMEM_UTILITY_EXPORT DynMemUtilitySet(dynmem_t *dynmem_address, intmax_t index, void *value_address);

_Bool DYNMEM_UTILITY_EXPORT DynMemUtilityGet(dynmem_t *dynmem_address, intmax_t index, void *value_address);

#endif  // DYNMEM_INTERNAL_USE_UTILITY_SET_GET_H

#endif  // DYNMEM_UTILITY_SET_GET_H
