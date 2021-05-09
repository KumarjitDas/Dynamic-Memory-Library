#ifndef DYNMEM_UTILITY_STACK_QUEUE_H
#define DYNMEM_UTILITY_STACK_QUEUE_H

#ifdef DYNMEM_INTERNAL_USE_UTILITY_STACK_QUEUE_H

#include "dynmem/common/defines.h"
#include "dynmem/common/standard_includes.h"
#include "dynmem/common/types.h"

_Bool DYNMEM_UTILITY_EXPORT DynMemUtilityAppend(dynmem_t *dynmem_address, void *memory, intmax_t size);

_Bool DYNMEM_UTILITY_EXPORT DynMemUtilityPrepend(dynmem_t *dynmem_address, void *memory, intmax_t size);

#endif  // DYNMEM_INTERNAL_USE_UTILITY_STACK_QUEUE_H

#endif  // DYNMEM_UTILITY_STACK_QUEUE_H
