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


static struct my_node *new_node()
{
    static uint8_t id = 0;

    char *s = ALLOC(10);
    if (!s) { perror("malloc"); exit(EXIT_FAILURE); }

    snprintf(s, 10, "hello_%u", id);

    struct my_node *n;
    NEW(n);
    if (!n) { perror("malloc"); exit(EXIT_FAILURE); }

    n->id   = id++;
    n->name = s;

    return n;
}


int test__ADT_stack(void)
{
    stack_t s = stack_new();
    assert(s != NULL);

    assert(stack_empty(s) == true);
    assert(stack_size(s) == 0);

    stack_push(s, new_node());
    assert(stack_empty(s) == false);
    assert(stack_size(s) == 1);

    struct my_node *n;
    n = stack_pop(s);
    assert(n != NULL && n->id == 0 && !strcmp(n->name, "hello_0"));
    my_free(n);

    for (uint8_t i = 1; i <= 10; i++) {
        stack_push(s, new_node());
    }

    for (uint8_t i = 10; i >= 1; i--) {
        n = stack_pop(s);
        assert(n != NULL && n->id == i);
        my_free(n);
    }

    stack_free(&s, my_free);
    assert(s == NULL);

    return EXIT_SUCCESS;
}
