#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include <stdint.h>

#define T hashtable_t
typedef struct T *T;

extern T         hashtable_new    (void);
extern bool      hashtable_isempty(T hashtable);
extern uint64_t  hashtable_size   (T hashtable);
extern void      hashtable_insert (T hashtable, int key, void *elem);
extern void     *hashtable_remove (T hashtable, int key);
extern void     *hashtable_find   (T hashtable, int key);
extern void      hashtable_clear  (T hashtable, void (*elem_free)(void *));
extern void      hashtable_free   (T *hashtable, void (*elem_free)(void *));

#undef T

#endif // HASHTABLE_H
