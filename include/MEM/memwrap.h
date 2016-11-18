#ifndef MEMWRAP_H
#define MEMWRAP_H

#include <stdlib.h>
#include <stdint.h>

#define ALLOC(nbytes) \
    ( \
        memwrap_malloc((nbytes), __FILE__, __LINE__) \
    )

#define CALLOC(count, nbytes) \
    ( \
        memwrap_calloc((count), (nbytes), __FILE__, __LINE__) \
    )

#define NEW(ptr) \
    ( \
        (ptr) = ALLOC((int64_t)sizeof *(ptr)) \
    )

#define NEWZ(ptr) \
    ( \
        (ptr) = CALLOC(1, (int64_t)sizeof *(ptr)) \
    )

#define RESIZE(ptr, nbytes) \
    ( \
        (ptr) = memwrap_resize((ptr), (nbytes), __FILE__, __LINE__) \
    )

#define FREE(ptr) \
    ( \
        (void)memwrap_free((ptr), __FILE__, __LINE__), \
        (ptr) = NULL \
    )

extern void *memwrap_malloc(int64_t nbytes, const char *file, int line);
extern void *memwrap_calloc(int64_t count, int64_t nbytes, const char *file, int line);
extern void *memwrap_resize(void *ptr, int64_t nbytes, const char *file, int line);
extern void  memwrap_free  (void *ptr, const char *file, int line);

#endif // MEMWRAP_H
