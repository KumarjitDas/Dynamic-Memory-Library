#ifndef DYNMEM_dynmem_defines_h
#define DYNMEM_dynmem_defines_h

#define DYNMEM_GET_ELEMENT_SIZE(dynmem)  (dynmem.element_size)
#define DYNMEM_GET_SIZE(dynmem)          (dynmem.size)
#define DYNMEM_GET_ACTUAL_LENGTH(dynmem) (dynmem.length)
#define DYNMEM_GET_LENGTH(dynmem)        (dynmem.index / dynmem.element_size)
#define DYNMEM_GET_MEMORY(Type, dynmem)  ((Type*)dynmem.memory)

#define DYNMEM_SET_VALUE(Type, dynmem, index, value)     (((Type*)dynmem.memory)[index]) = value
#define DYNMEM_GET_VALUE(Type, variable, dynmem, index)  variable = (((Type*)dynmem.memory)[index])

#endif  // DYNMEM_dynmem_defines_h
