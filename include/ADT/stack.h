#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdint.h>

#define T stack_t
typedef struct T *T;

extern T          stack_new    (void);
extern bool       stack_isempty(T stack);
extern uintmax_t  stack_size   (T stack);
extern void       stack_push   (T stack, void *elem);
extern void      *stack_pop    (T stack);
extern void       stack_free   (T *stack, void (*elem_free)(void *));

#undef T
#endif // STACK_H
