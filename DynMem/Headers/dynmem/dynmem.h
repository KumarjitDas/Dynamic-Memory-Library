#ifndef DYNMEM_DYNMEM_H
#define DYNMEM_DYNMEM_H

#include "common/defines.h"
#include "common/standard_includes.h"
#include "common/types.h"
#include "defines.h"
#include "dynmem_export.h"

_Bool DYNMEM_EXPORT DynMemAllocate(dynmem_t *dynmem_address,
                                   intmax_t element_size,
                                   intmax_t element_count,
                                   void *memory_address);

_Bool DYNMEM_EXPORT DynMemDeallocate(dynmem_t *dynmem_address);

_Bool DYNMEM_EXPORT DynMemReduce_s(dynmem_t *dynmem_address, void *memory_address, intmax_t *size_address);

_Bool DYNMEM_EXPORT DynMemReduce(dynmem_t *dynmem_address, void *array_address, intmax_t *length_address);

_Bool DYNMEM_EXPORT DynMemAppend(dynmem_t *dynmem_address, void *value_address);

_Bool DYNMEM_EXPORT DynMemPrepend(dynmem_t *dynmem_address, void *value_address);

_Bool DYNMEM_EXPORT DynMemDeduct(dynmem_t *dynmem_address, void *value_address);

_Bool DYNMEM_EXPORT DynMemDeductFront(dynmem_t *dynmem_address, void *value_address);

_Bool DYNMEM_EXPORT DynMemSetElementSize(dynmem_t *dynmem_address, intmax_t size);

_Bool DYNMEM_EXPORT DynMemGetElementSize(dynmem_t *dynmem_address, intmax_t *size_address);

_Bool DYNMEM_EXPORT DynMemGetSize(dynmem_t *dynmem_address, intmax_t *size_address);

_Bool DYNMEM_EXPORT DynMemGetLength(dynmem_t *dynmem_address, intmax_t *length_address);

_Bool DYNMEM_EXPORT DynMemGetPointer(dynmem_t *dynmem_address, void *pointer_address);

_Bool DYNMEM_EXPORT DynMemGetHeapSize(dynmem_t *dynmem_address, intmax_t *size_address);

_Bool DYNMEM_EXPORT DynMemGetHeapPointer(dynmem_t *dynmem_address, void *pointer_address);

_Bool DYNMEM_EXPORT DynMemReset(dynmem_t *dynmem_address);

_Bool DYNMEM_EXPORT DynMemSet(dynmem_t *dynmem_address, intmax_t index, void *value_address);

_Bool DYNMEM_EXPORT DynMemGet(dynmem_t *dynmem_address, intmax_t index, void *value_address);

_Bool DYNMEM_EXPORT DynMemSetValues(dynmem_t *dynmem_address, intmax_t begin, intmax_t end, void *value_address);

#endif  // DYNMEM_DYNMEM_H
