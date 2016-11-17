#include "tests.h"
#include "ADT/dequeue.h"
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


int test__ADT_dequeue(void)
{
    dequeue_t d = dequeue_new();
    assert(d != NULL);

    assert(dequeue_isempty(d) == true);

    dequeue_push_back(d, new_node()); // id=0

    assert(dequeue_isempty(d) == false);

    struct my_node *n;
    n = dequeue_pop_back(d); // id=0
    assert(n->id == 0 && !strcmp(n->name, "hello_0"));
    my_free(n);

    assert(dequeue_isempty(d) == true);

    dequeue_push_back(d, new_node()); // id=1
    dequeue_push_back(d, new_node()); // id=2

    assert(dequeue_isempty(d) == false);

    n = dequeue_pop_front(d); // id=1
    assert(n->id == 1 && !strcmp(n->name, "hello_1"));
    my_free(n);

    dequeue_push_front(d, new_node()); // id=3

    n = dequeue_pop_back(d); // id=2
    assert(n->id == 2 && !strcmp(n->name, "hello_2"));
    my_free(n);

    n = dequeue_pop_back(d); // id=3
    assert(n->id == 3 && !strcmp(n->name, "hello_3"));
    my_free(n);

    dequeue_free(&d, my_free);
    assert(d == NULL);

    return EXIT_SUCCESS;
}

