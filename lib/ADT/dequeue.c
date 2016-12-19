#include "ADT/dequeue.h"
#include "MEM/memwrap.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>

#define SECRET_ID 0x0064657175657565

#define T dequeue_t

struct T {
    int count;

    struct elem {
        void *x;
        struct elem *next;
        struct elem *prev;
    } *front, *rear;

    pthread_mutex_t lock;

    uint64_t id;
};


T dequeue_new(void)
{
    T dequeue;

    NEW(dequeue);

    dequeue->count = 0;
    dequeue->front = NULL;
    dequeue->rear  = NULL;
    dequeue->id    = SECRET_ID;
    pthread_mutex_init(&dequeue->lock, NULL);

    return dequeue;
}


bool dequeue_isempty(T dequeue)
{
    assert(dequeue);
    assert(dequeue->id == SECRET_ID);

    return !dequeue->count;
}


uintmax_t dequeue_size(T dequeue)
{
    assert(dequeue);

    return dequeue->count;
}


void dequeue_push_back(T dequeue, void *elem)
{
    assert(dequeue);
    assert(dequeue->id == SECRET_ID);

    struct elem *t;
    NEW(t);

    t->x = elem;
    t->next = NULL;
    t->prev = NULL;

    pthread_mutex_lock(&dequeue->lock);
    if (dequeue_isempty(dequeue)) {
        dequeue->front = t;
        dequeue->rear  = t;
    } else {
        t->next             = dequeue->rear;
        dequeue->rear->prev = t;
        dequeue->rear       = t;
    }

    dequeue->count++;
    pthread_mutex_unlock(&dequeue->lock);
}


void dequeue_push_front(T dequeue, void *elem)
{
    assert(dequeue);
    assert(dequeue->id == SECRET_ID);

    struct elem *t;
    NEW(t);

    t->x = elem;
    t->next = NULL;
    t->prev = NULL;

    pthread_mutex_lock(&dequeue->lock);
    if (dequeue_isempty(dequeue)) {
        dequeue->front = t;
        dequeue->rear  = t;
    } else {
        t->prev              = dequeue->front;
        dequeue->front->next = t;
        dequeue->front       = t;
    }

    dequeue->count++;
    pthread_mutex_unlock(&dequeue->lock);
}


void *dequeue_pop_back(T dequeue)
{
    assert(dequeue);
    assert(dequeue->id == SECRET_ID);
    assert(dequeue->count > 0);

    pthread_mutex_lock(&dequeue->lock);
    struct elem *t = dequeue->rear;
    void *x = t->x;

    if (dequeue->count == 1) {
        dequeue->front = NULL;
        dequeue->rear  = NULL;
        dequeue->count = 0;
    } else if (dequeue->count > 1) {
        t->next->prev = NULL;
        dequeue->rear = t->next;
        dequeue->count--;
    }
    pthread_mutex_unlock(&dequeue->lock);

    FREE(t);

    return x;
}


void *dequeue_pop_front(T dequeue)
{
    assert(dequeue);
    assert(dequeue->id == SECRET_ID);
    assert(dequeue->count > 0);

    pthread_mutex_lock(&dequeue->lock);
    struct elem *t = dequeue->front;
    void *x = t->x;

    if (dequeue->count == 1) {
        dequeue->front = NULL;
        dequeue->rear  = NULL;
        dequeue->count = 0;
    } else if (dequeue->count > 1) {
        t->prev->next  = NULL;
        dequeue->front = t->prev;
        dequeue->count--;
    }
    pthread_mutex_unlock(&dequeue->lock);

    FREE(t);

    return x;
}


// Searches based on pointer equality
// It is a project specific function
void *dequeue_remove(T dequeue, void *elem)
{
    assert(dequeue);
    assert(dequeue->id == SECRET_ID);
    assert(dequeue->count > 0);

    pthread_mutex_lock(&dequeue->lock);
    struct elem *curr;
    for (curr = dequeue->rear; curr; curr = curr->next) {
        if (curr->x == elem) {
            break;
        }
    }

    void *x = NULL;
    if (curr) {
        x = curr->x;
        if (dequeue->count == 1) {
            dequeue->front = NULL;
            dequeue->rear  = NULL;
            dequeue->count = 0;
        } else if (dequeue->count > 1) {
            if (curr == dequeue->front) {
                curr->prev->next = NULL;
                dequeue->front = curr->prev;
            } else if (curr == dequeue->rear) {
                curr->next->prev = NULL;
                dequeue->rear = curr->next;
            } else {
                curr->next->prev = curr->prev;
                curr->prev->next = curr->next;
            }

            dequeue->count--;
        }
    }

    pthread_mutex_unlock(&dequeue->lock);

    FREE(curr);

    return x;
}


void dequeue_clear(T dequeue, void (*elem_free)(void *))
{
    assert(dequeue);
    assert(dequeue->id == SECRET_ID);

    while (!dequeue_isempty(dequeue)) {
        elem_free(dequeue_pop_front(dequeue));
    }

    dequeue->count = 0;
    dequeue->front = NULL;
    dequeue->rear  = NULL;
}

void dequeue_free(T *dequeue, void (*elem_free)(void *))
{
    assert(dequeue && *dequeue);
    assert((*dequeue)->id == SECRET_ID);

    dequeue_clear(*dequeue, elem_free);
    FREE(*dequeue);
}
