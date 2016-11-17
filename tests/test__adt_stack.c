#include "tests.h"
#include "ADT/stack.h"
#include "MEM/memwrap.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

struct my_node {
    uint32_t  id;
    char     *name;
};

static void my_free(void *x)
{
    struct my_node *n = x;
    FREE(n->name);
}

int test__ADT_stack(void)
{
    stack_t s = stack_new();
    assert(s != NULL);

    bool e = stack_isempty(s);
    assert(e == true);

    char *s1 = ALLOC(10);
    if (!s1) { perror("malloc"); exit(EXIT_FAILURE); }

    strncpy(s1, "hello_1", 7);

    struct my_node *n1;
    NEW(n1);
    if (!n1) { perror("malloc"); exit(EXIT_FAILURE); }

    n1->id   = 1;
    n1->name = s1;
    stack_push(s, n1);
    e = stack_isempty(s);
    assert(e == false);

    n1 = stack_pop(s);
    assert(n1 != NULL);
    assert(n1->id == 1);
    assert(n1->name != NULL);
    assert(!strcmp(n1->name, "hello_1"));

    stack_free(&s, my_free);

    return EXIT_SUCCESS;
}
