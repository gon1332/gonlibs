#include "MEM/memwrap.h"
#include "DBG/reporterr.h"

#include <stdlib.h>
#include <assert.h>


void *memwrap_malloc(int64_t nbytes, const char *file, int line)
{
    assert(nbytes > 0);

    void *ptr = malloc(nbytes);
    if (!ptr)
        ERRNO_REPORT_EXIT("malloc", file, line);

    return ptr;
}


void *memwrap_calloc(int64_t count, int64_t nbytes, const char *file, int line)
{
    assert(count > 0);
    assert(nbytes > 0);

    void *ptr = calloc(count, nbytes);
    if (!ptr)
        ERRNO_REPORT_EXIT("calloc", file, line);

    return ptr;
}


void *memwrap_resize(void *ptr, int64_t nbytes, const char *file, int line)
{
    assert(ptr);
    assert(nbytes > 0);

    ptr = realloc(ptr, nbytes);
    if (!ptr)
        ERRNO_REPORT_EXIT("realloc", file, line);

    return ptr;
}


void memwrap_free(void *ptr, const char *file, int line)
{
    (void)file;
    (void)line;

    if (ptr)
        free(ptr);
}
