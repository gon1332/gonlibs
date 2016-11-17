#ifndef MEMWRAP_H
#define MEMWRAP_H

#include <stdlib.h>

#define ALLOC(nbytes) \
    ( \
        memwrap_malloc((nbytes)) \
    )

#define NEW(ptr) \
    ( \
        (ptr) = ALLOC(sizeof *(ptr)) \
    )

#define FREE(ptr) \
    ( \
        (void)memwrap_free((ptr)), \
        (ptr) = NULL \
    )

extern void *memwrap_malloc(size_t nbytes);
extern void  memwrap_free  (void *ptr);

#endif // MEMWRAP_H
