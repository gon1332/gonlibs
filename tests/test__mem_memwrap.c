#include "tests.h"
#include "MEM/memwrap.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>


int test__MEM_memwrap(void)
{
    int *s = ALLOC(10 * sizeof(int));
    assert(s != NULL);

    FREE(s);
    assert(s == NULL);

    return EXIT_SUCCESS;
}
