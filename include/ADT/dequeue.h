#ifndef DEQUEUE_H
#define DEQUEUE_H

#include <stdbool.h>

#define T dequeue_t
typedef struct T *T;

extern T     dequeue_new       (void);
extern bool  dequeue_isempty   (T dequeue);
extern void  dequeue_push_back (T dequeue, void *elem);
extern void  dequeue_push_front(T dequeue, void *elem);
extern void *dequeue_pop_back  (T dequeue);
extern void *dequeue_pop_front (T dequeue);
extern void  dequeue_clear     (T dequeue, void (*elem_free)(void *));
extern void  dequeue_free      (T *dequeue, void (*elem_free)(void *));

#undef T
#endif // DEQUEUE_H
