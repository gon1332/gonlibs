#include "ADT/hashtable.h"
#include "MEM/memwrap.h"

#include <assert.h>

#include <stdio.h>

#define SECRET_ID 0x0064657175657565

#define T hashtable_t

#define MERSENNE_PRIME(x)   ((2<<(x)) - 1)      // Mersenne prime
#define MAP_SIZE            ((uint64_t)(MERSENNE_PRIME(7)))
#define HASH(x)             ((x) % MAP_SIZE)


struct T {
    uint64_t count;

    struct elem {
        int   key;
        void *x;

        struct elem *next;
        struct elem *prev;
    } *table;

    uint64_t id;
};


T hashtable_new(void)
{
    T hashtable;

    NEW(hashtable);

    hashtable->count = 0;
    hashtable->table = CALLOC(MAP_SIZE, sizeof(struct elem));
    hashtable->id    = SECRET_ID;

    return hashtable;
}


bool hashtable_isempty(T hashtable)
{
    assert(hashtable);
    assert(hashtable->id == SECRET_ID);

    return !hashtable->count;
}


uint64_t hashtable_size(T hashtable)
{
    assert(hashtable);
    assert(hashtable->id == SECRET_ID);

    return hashtable->count;
}


void hashtable_insert(T hashtable, int key, void *elem)
{
    assert(hashtable);
    assert(hashtable->id == SECRET_ID);

    struct elem *t;
    NEW(t);

    t->key  = key;
    t->x    = elem;
    t->next = NULL;
    t->prev = NULL;

    struct elem *bucket = &hashtable->table[HASH(key)];

    t->next = bucket->next;
    t->prev = NULL;
    if (bucket->next) {
        bucket->next->prev = t;
    }
    bucket->next = t;

    hashtable->count++;
}


void *hashtable_remove(T hashtable, int key)
{
    assert(hashtable);
    assert(hashtable->id == SECRET_ID);

    struct elem *bucket = &hashtable->table[HASH(key)];

    struct elem *curr;
    for (curr = bucket->next; curr; curr = curr->next) {
        if (curr->key != key)
            continue;

        void *removed = curr->x;

        if (curr->next) curr->next->prev = curr->prev;
        if (curr->prev) curr->prev->next = curr->next;
        else bucket->next = curr->next;
        FREE(curr);

        hashtable->count--;
        return removed;
    }

    return NULL;
}


void *hashtable_find(T hashtable, int key)
{
    assert(hashtable);
    assert(hashtable->id == SECRET_ID);

    struct elem bucket = hashtable->table[HASH(key)];

    for (struct elem *curr = bucket.next; curr; curr = curr->next) {
        if (curr->key == key)
            return curr->x;
    }
    return NULL;
}


void hashtable_clear(T hashtable, void (*elem_free)(void *))
{
    assert(hashtable);
    assert(hashtable->id == SECRET_ID);

    for (uint64_t b = 0; b < MAP_SIZE; b++) {
        struct elem *bucket = &hashtable->table[b];
        struct elem *next;
        for (struct elem *curr = bucket->next; curr; ) {
            next = curr->next;
            if (elem_free) elem_free(curr->x);
            FREE(curr);
            hashtable->count--;
            curr = next;
        }
    }
}


void hashtable_free(T *hashtable, void (*elem_free)(void *))
{
    assert(hashtable && *hashtable);
    assert((*hashtable)->id == SECRET_ID);

    hashtable_clear(*hashtable, elem_free);

    FREE((*hashtable)->table);
    FREE(*hashtable);
}
