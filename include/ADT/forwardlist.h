#ifndef FORWARDLIST_H
#define FORWARDLIST_H

#include <stdbool.h>
#include <stdint.h>

#define T forwardlist_t
typedef struct T *T;

extern T    forwardlist_new (void *elem, ...);
extern void forwardlist_free(T *list);

// Capacity
extern bool      forwardlist_empty(T list);
extern uintmax_t forwardlist_size (T list);

// Modifiers
extern void  forwardlist_push_front  (T list, void *elem);
extern void *forwardlist_pop_front   (T list);
extern void  forwardlist_append      (T list, T tail);
// extern void  forwardlist_insert_after(T list, const uintmax_t pos, void *elem);
// extern void  forwardlist_erase_after (T list, const void *pos);
extern void  forwardlist_map         (T list,
        void apply(void **x, void *cl), void *cl);
extern void  forwardlist_clear       (T list);

// Operations
extern void   forwardlist_reverse (T list);
// extern T      forwardlist_copy    (T list);
extern void **forwardlist_to_array(T list, void *end);

#undef T
#endif // FORWARDLIST_H
