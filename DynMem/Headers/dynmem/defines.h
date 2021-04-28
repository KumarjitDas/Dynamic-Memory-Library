#ifndef DYNMEM_dynmem_defines_h
#define DYNMEM_dynmem_defines_h

#define DYNMEM_GET_ELEMENT_SIZE(dynmem)      (dynmem.element_size)
#define DYNMEM_GET_LENGTH(dynmem)            (dynmem.end_index - dynmem.start_index + 1)
#define DYNMEM_GET_ACTUAL_LENGTH(dynmem)     (dynmem.length)

#define DYNMEM_GET_SIZE(dynmem)              (dynmem.element_size * DYNMEM_GET_LENGTH(dynmem))
#define DYNMEM_GET_ACTUAL_SIZE(dynmem)       (dynmem.element_size * dynmem.length)

#define DYNMEM_GET_MEMORY(Type, dynmem)      ((Type*)dynmem.memory)
#define DYNMEM_VALUE_AT(Type, dynmem, index) DYNMEM_GET_MEMORY(Type, dynmem)[index]

#define DynMemPush      DynMemAppend
#define DynMemPop       DynMemDeduct
#define DynMemPushBack  DynMemPush
#define DynMemPopBack   DynMemPop
#define DynMemPushFront DynMemPrepend
#define DynMemPopFront  DynMemDeductFront

#endif  // DYNMEM_dynmem_defines_h
