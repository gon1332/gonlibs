#include "ADT/forwardlist.h"
#include "MEM/memwrap.h"

#include <stdarg.h>
#include <stddef.h>
#include <assert.h>

#define SECRET_ID 0x666f72776172646c
                  
#define T forwardlist_t

struct T {
    int size;

    struct elem {
        void *first;

        struct elem *rest;
    } *front, *rear;

    uint64_t id;
};


T forwardlist_new(void *elem, ...)
{
    T list;

    NEW(list);
    list->size = 0;
    list->front = NULL;
    list->rear  = NULL;
    list->id    = SECRET_ID;

    va_list ap;
    struct elem  *head = NULL;
    struct elem **p = &head;

    va_start(ap, elem);
    for ( ; elem; elem = va_arg(ap, void *)) {
        NEW(*p);
        (*p)->first = elem;
        list->rear = *p;
        p = &(*p)->rest;
        list->size++;
    }
    *p = NULL;
    va_end(ap);

    list->front = head;

    return list;
}


void forwardlist_free(T *list)
{
    assert(list && *list);
    assert((*list)->id == SECRET_ID);

    forwardlist_clear(*list);
    FREE(*list);
}


bool forwardlist_empty(T list)
{
    assert(list);
    assert(list->id == SECRET_ID);

    return !list->size;
}


uintmax_t forwardlist_size(T list)
{
    assert(list);
    assert(list->id == SECRET_ID);

    return list->size;
}


void forwardlist_push_front(T list, void *elem)
{
    assert(list);
    assert(list->id == SECRET_ID);

    // Create and initialize the new element
    struct elem *new_node;
    NEW(new_node);

    new_node->first = elem;
    new_node->rest  = list->front;

    // Insert the new element at the front of the list
    list->front = new_node;

    if (forwardlist_empty(list))
        list->rear = new_node;

    list->size++;
}


void *forwardlist_pop_front(T list)
{
    assert(list);
    assert(list->id == SECRET_ID);
    assert(list->size);

    // The list is empty
    if (forwardlist_empty(list))
        return NULL;

    // Find element to pop
    struct elem *head = list->front;
    void *elem = head->first;

    // Remove the first element from the list
    list->front = list->front->rest;
    list->size--;
    FREE(head);

    if (forwardlist_empty(list))
        list->rear = NULL;

    return elem;
}


void forwardlist_append(T list, T tail)
{
    assert(list);
    assert(list->id == SECRET_ID);

    list->rear->rest = tail->front;
    list->rear = tail->rear;
    list->size += tail->size;

    FREE(tail);
}


void forwardlist_clear(T list)
{
    assert(list);
    assert(list->id == SECRET_ID);

    struct elem *next;
    for (struct elem *head = list->front; head; head = next) {
        next = head->rest;
        list->size--;
        FREE(head);
    }

    list->front = NULL;
    list->rear  = NULL;
}


void forwardlist_map(T list, void apply(void **x, void *cl), void *cl)
{
    assert(list);
    assert(list->id == SECRET_ID);
    assert(apply);

    for (struct elem *node = list->front; node; node = node->rest)
        apply(&node->first, cl);
}


void forwardlist_reverse(T list)
{
    assert(list);
    assert(list->id == SECRET_ID);

    struct elem *head = NULL,
                *next;

    // Reverse the list
    for (struct elem *node = list->front ; node; node = next) {
        next = node->rest;
        node->rest = head;
        head = node;
    }

    // Update list pointers
    list->rear  = list->front;
    list->front = head;
}


// T forward_list_copy(T list)
// {
//     T  head,
//       *p = &head;

//     for ( ; list; list = list->rest) {
//         NEW(*p);
//         (*p)->first = list->first;
//         p = &(*p)->rest;
//     }

//     *p = NULL;
//     return head;
// }


void **forwardlist_to_array(T list, void *end)
{
    assert(list);
    assert(list->id == SECRET_ID);

    uintmax_t n = forwardlist_size(list);

    void **array = ALLOC((n + 1) * sizeof(*array));

    uintmax_t i;
    struct elem *node = list->front;
    for (i = 0; i < n; i++) {
        array[i] = node->first;
        node = node->rest;
    }
    array[i] = end;
    return array;
}

