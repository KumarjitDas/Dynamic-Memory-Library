#ifndef DYNMEM_dynmem_dynmem_h
#define DYNMEM_dynmem_dynmem_h

#include "common/export.h"
#include "common/defines.h"
#include "common/standard_includes.h"
#include "common/types.h"
#include "defines.h"

_Bool DYNMEM_EXPORT DynMemAllocate(dynmem_t *dynmem, intmax_t element_size, intmax_t element_count);

void DYNMEM_EXPORT DynMemDeallocate(dynmem_t *dynmem);

_Bool DYNMEM_EXPORT DynMemSet(dynmem_t *dynmem, intmax_t index, void *value);

_Bool DYNMEM_EXPORT DynMemGet(dynmem_t *dynmem, intmax_t index, void *value);

_Bool DYNMEM_EXPORT DynMemAppend(dynmem_t *dynmem, void *value);

#endif  // DYNMEM_dynmem_dynmem_h
