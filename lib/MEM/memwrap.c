#include "MEM/memwrap.h"

#include <stdlib.h>
#include <assert.h>


void *memwrap_malloc(size_t nbytes)
{
    assert(nbytes > 0);

    void *ptr = malloc(nbytes);
    if (!ptr)
        return NULL;

    return ptr;
}


void memwrap_free(void *ptr)
{
    if (ptr)
        free(ptr);
}
