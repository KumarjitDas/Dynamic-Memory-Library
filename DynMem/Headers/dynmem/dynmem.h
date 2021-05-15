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

_Bool DYNMEM_EXPORT DynMemAppendValues(dynmem_t *dynmem_address, void *value_address, intmax_t count);

_Bool DYNMEM_EXPORT DynMemPrependValues(dynmem_t *dynmem_address, void *value_address, intmax_t count);

_Bool DYNMEM_EXPORT DynMemAppendArray(dynmem_t *dynmem_address, void *array, intmax_t length);

_Bool DYNMEM_EXPORT DynMemPrependArray(dynmem_t *dynmem_address, void *array, intmax_t length);

_Bool DYNMEM_EXPORT DynMemSetElementSize(dynmem_t *dynmem_address, intmax_t size);

_Bool DYNMEM_EXPORT DynMemGetElementSize(dynmem_t *dynmem_address, intmax_t *size_address);

_Bool DYNMEM_EXPORT DynMemGetSize(dynmem_t *dynmem_address, intmax_t *size_address);

_Bool DYNMEM_EXPORT DynMemGetLength(dynmem_t *dynmem_address, intmax_t *length_address);

_Bool DYNMEM_EXPORT DynMemGetEndIndex_s(dynmem_t *dynmem_address, intmax_t *index_address_s);

_Bool DYNMEM_EXPORT DynMemGetEndIndex(dynmem_t *dynmem_address, intmax_t *index_address);

_Bool DYNMEM_EXPORT DynMemSetForAppending(dynmem_t *dynmem_address);

_Bool DYNMEM_EXPORT DynMemSetForPrepending(dynmem_t *dynmem_address);

_Bool DYNMEM_EXPORT DynMemGetBegin(dynmem_t *dynmem_address, void *pointer_address);

_Bool DYNMEM_EXPORT DynMemGetEnd(dynmem_t *dynmem_address, void *pointer_address);

_Bool DYNMEM_EXPORT DynMemGetHeapSize(dynmem_t *dynmem_address, intmax_t *size_address);

_Bool DYNMEM_EXPORT DynMemGetHeapPointer(dynmem_t *dynmem_address, void *pointer_address);

_Bool DYNMEM_EXPORT DynMemReset(dynmem_t *dynmem_address);

_Bool DYNMEM_EXPORT DynMemResetMemory(dynmem_t *dynmem_address);

_Bool DYNMEM_EXPORT DynMemSet_s(dynmem_t *dynmem_address, intmax_t index_s, void *value_address);

_Bool DYNMEM_EXPORT DynMemSet(dynmem_t *dynmem_address, intmax_t index, void *value_address);

_Bool DYNMEM_EXPORT DynMemGet_s(dynmem_t *dynmem_address, intmax_t index_s, void *value_address);

_Bool DYNMEM_EXPORT DynMemGet(dynmem_t *dynmem_address, intmax_t index, void *value_address);

_Bool DYNMEM_EXPORT DynMemSetValues_s(dynmem_t *dynmem_address, intmax_t begin_s, intmax_t end_s, void *value_address);

_Bool DYNMEM_EXPORT DynMemSetValues(dynmem_t *dynmem_address, intmax_t begin, intmax_t end, void *value_address);

_Bool DYNMEM_EXPORT DynMemGetValues_s(dynmem_t *dynmem_address, intmax_t begin_s, intmax_t end_s,
                                      void *memory, intmax_t size, intmax_t *got_size);

_Bool DYNMEM_EXPORT DynMemGetValues(dynmem_t *dynmem_address, intmax_t begin, intmax_t end,
                                    void *array, intmax_t length, intmax_t *got_length);

_Bool DYNMEM_EXPORT DynMemCopy(dynmem_t *destination_address, dynmem_t *source_address);

_Bool DYNMEM_EXPORT DynMemCopyExceptValues(dynmem_t *destination_address, dynmem_t *source_address);

_Bool DYNMEM_EXPORT DynMemCopyInitial(dynmem_t *destination_address, dynmem_t *source_address);

#endif  // DYNMEM_DYNMEM_H
