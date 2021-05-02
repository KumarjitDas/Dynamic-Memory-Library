#ifndef DYNMEM_dynmem_defines_h
#define DYNMEM_dynmem_defines_h

#define DYNMEM_GET_ELEMENT_SIZE(dynmem) (dynmem.es)
#define DYNMEM_GET_SIZE(dynmem) (dynmem.ei - dynmem.si + dynmem.es)
#define DYNMEM_GET_LENGTH(dynmem) (DYNMEM_GET_SIZE(dynmem) / dynmem.es)

#define DYNMEM_GET_MEMORY(Type, dynmem) ((Type *)(dynmem.m + dynmem.si))
#define DYNMEM_VALUE_AT(Type, dynmem, index) (DYNMEM_GET_MEMORY(Type, dynmem)[index])

#define DYNMEM_GET_BEGIN(dynmem) (dynmem.si)
#define DYNMEM_GET_END(dynmem) (dynmem.ei + dynmem.es)
#define DYNMEM_GET_POINTER(dynmem) (dynmem.m)

#define DynMemFree DynMemDeallocate
#define DynMemPush DynMemAppend
#define DynMemPop DynMemDeduct
#define DynMemPushBack DynMemPush
#define DynMemPopBack DynMemPop
#define DynMemPushFront DynMemPrepend
#define DynMemPopFront DynMemDeductFront

#endif  // DYNMEM_dynmem_defines_h
