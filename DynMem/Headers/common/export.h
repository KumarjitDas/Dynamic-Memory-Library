
#ifndef DYNMEM_EXPORT_H
#define DYNMEM_EXPORT_H

#ifdef DYNMEM_STATIC_DEFINE
#  define DYNMEM_EXPORT
#  define DYNMEM_NO_EXPORT
#else
#  ifndef DYNMEM_EXPORT
#    ifdef DynMem_EXPORTS
        /* We are building this library */
#      define DYNMEM_EXPORT 
#    else
        /* We are using this library */
#      define DYNMEM_EXPORT 
#    endif
#  endif

#  ifndef DYNMEM_NO_EXPORT
#    define DYNMEM_NO_EXPORT 
#  endif
#endif

#ifndef DYNMEM_DEPRECATED
#  define DYNMEM_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef DYNMEM_DEPRECATED_EXPORT
#  define DYNMEM_DEPRECATED_EXPORT DYNMEM_EXPORT DYNMEM_DEPRECATED
#endif

#ifndef DYNMEM_DEPRECATED_NO_EXPORT
#  define DYNMEM_DEPRECATED_NO_EXPORT DYNMEM_NO_EXPORT DYNMEM_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef DYNMEM_NO_DEPRECATED
#    define DYNMEM_NO_DEPRECATED
#  endif
#endif

#endif /* DYNMEM_EXPORT_H */
