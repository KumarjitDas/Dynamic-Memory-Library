#ifndef DYNMEM_dynmem_dynmem_h
#define DYNMEM_dynmem_dynmem_h

#include "dynmem_export.h"
#include "common/defines.h"
#include "common/standard_includes.h"
#include "common/types.h"
#include "defines.h"

_Bool DYNMEM_EXPORT DynMemAllocate(dynmem_t *dynmem_address,
                                   intmax_t  element_size,
                                   intmax_t  element_count,
                                   void     *memory_address
                                  );

_Bool DYNMEM_EXPORT DynMemDeallocate(dynmem_t *dynmem_address);

_Bool DYNMEM_EXPORT DynMemSet(dynmem_t *dynmem_address, intmax_t index, void *value_address);

_Bool DYNMEM_EXPORT DynMemGet(dynmem_t *dynmem_address, intmax_t index, void *value_address);

_Bool DYNMEM_EXPORT DynMemAppend(dynmem_t *dynmem_address, void *value_address);

#endif  // DYNMEM_dynmem_dynmem_h
