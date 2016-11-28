#include "tests.h"
#include "ADT/hashtable.h"
#include "MEM/memwrap.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
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

int test__ADT_hashtable(void)
{
    hashtable_t m = hashtable_new();

    assert(hashtable_isempty(m) == true);
    assert(hashtable_size(m) == 0);

    struct my_node *n;
    for (unsigned i = 1; i <= 10; i++) {
        n = new_node();
        hashtable_insert(m, n->id, n);

        assert(hashtable_isempty(m) == false);
        assert(hashtable_size(m) == i);
    }

    for (unsigned i = 1; i <= 10; i++) {
        n = hashtable_find(m, i-1);
        assert(n != NULL);
        assert(hashtable_isempty(m) == false);
        assert(hashtable_size(m) == 10);
    }

    n = hashtable_remove(m, 0);
    assert(n != NULL);
    assert(hashtable_isempty(m) == false);
    assert(hashtable_size(m) == 9);

    n = hashtable_remove(m, 0);
    assert(n == NULL);
    assert(hashtable_isempty(m) == false);
    assert(hashtable_size(m) == 9);

    for (unsigned i = 2; i <= 10; i++) {
        n = hashtable_find(m, i-1);
        assert(n != NULL);
        assert(hashtable_isempty(m) == false);
        assert(hashtable_size(m) == 9);
    }

    n = hashtable_remove(m, 9);
    assert(n != NULL);
    assert(hashtable_isempty(m) == false);
    assert(hashtable_size(m) == 8);

    hashtable_clear(m, NULL);
    assert(hashtable_isempty(m) == true);
    assert(hashtable_size(m) == 0);

    hashtable_free(&m, my_free);

    return EXIT_SUCCESS;
}
