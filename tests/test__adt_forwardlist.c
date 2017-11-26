#include "tests.h"
#include "ADT/forwardlist.h"
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

static void apply_free(void **ptr, void *cl)
{
    puts("hey");
    struct my_node *n = *ptr;
    FREE(n->name);
}

static void apply_print(void **ptr, void *cl)
{
    FILE *fptr = cl;
    fprintf(fptr, "%s\n", (char *)*ptr);
}

static struct my_node *new_node(void)
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


int test__ADT_forwardlist(void)
{
    forwardlist_t list = forwardlist_new(NULL);
    assert(list != NULL);

    assert(forwardlist_empty(list) == true);

    forwardlist_push_front(list, new_node()); // id=0

    assert(forwardlist_empty(list) == false);

    struct my_node *n;
    n = forwardlist_pop_front(list); // id=0
    assert(n->id == 0 && !strcmp(n->name, "hello_0"));
    my_free(n);

    assert(forwardlist_empty(list) == true);

    forwardlist_push_front(list, new_node()); // id=1
    forwardlist_push_front(list, new_node()); // id=2

    assert(forwardlist_empty(list) == false);
    assert(forwardlist_size(list) == 2);

    // forwardlist_map(list, apply_print, stderr);

    n = forwardlist_pop_front(list); // id=2
    assert(n->id == 2 && !strcmp(n->name, "hello_2"));
    my_free(n);

    forwardlist_clear(list);
    assert(forwardlist_empty(list) == true);
    assert(forwardlist_size(list) == 0);

    // dequeue_push_front(d, new_node()); // id=3

    // n = dequeue_pop_back(d); // id=2
    // assert(n->id == 2 && !strcmp(n->name, "hello_2"));
    // my_free(n);

    // n = dequeue_pop_back(d); // id=3
    // assert(n->id == 3 && !strcmp(n->name, "hello_3"));
    // my_free(n);

    forwardlist_map(list, apply_free, NULL);
    forwardlist_free(&list);
    assert(list == NULL);

    
    list = forwardlist_new("One", "Two", "Three", NULL);

    forwardlist_push_front(list, "Zero");
    assert(forwardlist_empty(list) == false);
    assert(forwardlist_size(list) == 4);

    forwardlist_reverse(list);
    // forwardlist_map(list, apply_print, stderr);
    assert(forwardlist_empty(list) == false);
    assert(forwardlist_size(list) == 4);

    forwardlist_free(&list);
    assert(list == NULL);

    // Test append
    forwardlist_t p1, p2;
    p1 = forwardlist_new("One", "Two", "Three", NULL);
    p2 = forwardlist_new("Four", "Five", NULL);
    forwardlist_append(p1, p2);
    // forwardlist_map(p1, apply_print, stderr);

    // Test to_array
    char **array = (char **)forwardlist_to_array(p1, NULL);
    // for (int i = 0; array[i]; i++) {
    //     printf("%s\n", array[i]);
    // }

    return EXIT_SUCCESS;
}

