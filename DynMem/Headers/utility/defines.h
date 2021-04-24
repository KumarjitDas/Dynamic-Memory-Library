#ifndef DYNMEM_utility_defines_h
#define DYNMEM_utility_defines_h

#ifdef DYNMEM_INTERNAL_USE_utility_defines_h

#ifndef TRUE
#   define TRUE  (_Bool)(1)
#endif
#ifndef FALSE
#   define FALSE (_Bool)(0)
#endif

#define DYNMEM_UTILITY_VALIDATE(dynmem) \
    (dynmem.element_size && dynmem.initial_size && dynmem.size && dynmem.length && dynmem.memory)

#define DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address)                                \
    (dynmem_address && dynmem_address->element_size && dynmem_address->initial_size && \
     dynmem_address->size && dynmem_address->length && dynmem_address->memory          \
    )

#define DYNMEM_UTILITY_RESET(dynmem_address) \
{                                            \
    dynmem_address->element_size = 0;        \
    dynmem_address->initial_size = 0;        \
    dynmem_address->size         = 0;        \
    dynmem_address->length       = 0;        \
    dynmem_address->index        = 0;        \
    dynmem_address->memory       = NULL;     \
}

#endif  // DYNMEM_INTERNAL_USE_utility_defines_h

#endif  // DYNMEM_utility_defines_h
