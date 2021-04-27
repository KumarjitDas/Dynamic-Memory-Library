#ifndef DYNMEM_dynmem_defines_h
#define DYNMEM_dynmem_defines_h

#define DYNMEM_GET_ELEMENT_SIZE(dynmem)       (dynmem.element_size)
#define DYNMEM_GET_LENGTH(dynmem)             (dynmem.current_length)
#define DYNMEM_GET_ACTUAL_LENGTH(dynmem)      (dynmem.length)

#define DYNMEM_GET_SIZE(dynmem)               (dynmem.element_size * dynmem.current_length)
#define DYNMEM_GET_ACTUAL_SIZE(dynmem)        (dynmem.element_size * dynmem.length)

#define DYNMEM_GET_START_INDEX(dynmem)        (dynmem.start_index)
#define DYNMEM_GET_END_INDEX(dynmem)          (dynmem.end_index)

#define DYNMEM_GET_MEMORY(Type, dynmem)       ((Type*)dynmem.memory)
#define DYNMEM_SET_VALUE(Type, dynmem, index) ((Type*)dynmem.memory)[index]
#define DYNMEM_GET_VALUE(Type, dynmem, index) ((Type*)dynmem.memory)[index]

#endif  // DYNMEM_dynmem_defines_h
