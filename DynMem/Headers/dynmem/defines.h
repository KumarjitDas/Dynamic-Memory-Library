#ifndef DYNMEM_dynmem_defines_h
#define DYNMEM_dynmem_defines_h

#define DYNMEM_GET_ELEMENT_SIZE(dynmem) (dynmem.element_size)
#define DYNMEM_GET_SIZE(dynmem)         (dynmem.size)
#define DYNMEM_GET_LENGTH(dynmem)       (dynmem.length)
#define DYNMEM_GET_MEMORY(Type, dynmem) ((Type*)dynmem.memory)

#endif  // DYNMEM_dynmem_defines_h
