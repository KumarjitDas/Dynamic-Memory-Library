#include "dynmem/dynmem.h"

#include <stdlib.h>

_Bool DynMemAllocate(dynmem_t *dynmem, intmax_t element_size, intmax_t element_count) {
    if (!dynmem || element_size <= 0 || element_count <= 0)
        return FALSE;

    dynmem->element_size = element_size;
    dynmem->initial_size = element_size * element_count;
    dynmem->size         = dynmem->initial_size;
    dynmem->length       = element_count;
    dynmem->index        = 0;

    dynmem->memory = malloc(dynmem->initial_size);
    if (!dynmem->memory) {
        dynmem->element_size = 0;
        dynmem->initial_size = 0;
        dynmem->size         = 0;
        dynmem->length       = 0;
        dynmem->index        = 0;

        return FALSE;
    }

    return TRUE;
}

void DynMemDeallocate(dynmem_t *dynmem) {
    dynmem->element_size = 0;
    dynmem->initial_size = 0;
    dynmem->size         = 0;
    dynmem->length       = 0;
    dynmem->index        = 0;

    if (dynmem->memory)
        free(dynmem->memory);

    dynmem->memory = NULL;
}

_Bool DYNMEM_EXPORT DynMemSet(dynmem_t *dynmem, intmax_t index, void *value) {

    return TRUE;
}

_Bool DYNMEM_EXPORT DynMemGet(dynmem_t *dynmem, intmax_t index, void *value) {

    return TRUE;
}

_Bool DynMemAppend(dynmem_t *dynmem, void *value) {
    if (!dynmem || !dynmem->memory || !dynmem->initial_size || !dynmem->element_size || 
        !value  || !dynmem->size   || !dynmem->length
       )
        return FALSE;

    if (dynmem->index < dynmem->size)
        for (; dynmem->index < dynmem->element_size && dynmem->index < dynmem->size; dynmem->index++)
            dynmem->memory[dynmem->index] = ((uint8_t*)value)[dynmem->index];
    else {

    }

    return TRUE;
}
