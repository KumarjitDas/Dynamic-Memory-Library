#ifndef DYNMEM_utility_defines_h
#define DYNMEM_utility_defines_h

#ifdef DYNMEM_INTERNAL_USE_utility_defines_h

#include "dynmem_export.h"


#ifndef DYNMEM_UTILITY_EXPORT

#   ifdef DYNMEM_UTILITY_TEST
#      define DYNMEM_UTILITY_EXPORT DYNMEM_EXPORT
#   else
#      define DYNMEM_UTILITY_EXPORT
#   endif  // DYNMEM_UTILITY_TEST

#endif  // DYNMEM_UTILITY_EXPORT

#ifndef TRUE
#   define TRUE  (_Bool)(1)
#endif
#ifndef FALSE
#   define FALSE (_Bool)(0)
#endif


#define DYNMEM_UTILITY_VALIDATE(dynmem) (dynmem.es && dynmem.is && dynmem.cs && dynmem.bis && dynmem.eis && dynmem.m)

#define DYNMEM_UTILITY_VALIDATE_ADDRESS(dynmem_address)                  \
    (dynmem_address->es  && dynmem_address->is  && dynmem_address->cs && \
     dynmem_address->bis && dynmem_address->eis && dynmem_address->m)

#define DYNMEM_UTILITY_RESET(dynmem)                                                                             \
    { dynmem.es = 0; dynmem.is = 0; dynmem.cs = 0; dynmem.bis = 0; dynmem.eis = 0; dynmem.bi = 0; dynmem.ei = 0; \
      dynmem.m  = NULL; }

#define DYNMEM_UTILITY_RESET_ADDRESS(dynmem_address)                                                       \
    { dynmem_address->es  = 0; dynmem_address->is = 0; dynmem_address->cs = 0; dynmem_address->bis = 0;    \
      dynmem_address->eis = 0; dynmem_address->bi = 0; dynmem_address->ei = 0; dynmem_address->m   = NULL; }


#endif  // DYNMEM_INTERNAL_USE_utility_defines_h

#endif  // DYNMEM_utility_defines_h
