#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define T stack_t
typedef struct T *T;

extern T     stack_new    (void);
extern bool  stack_isempty(T stack);
extern void  stack_push   (T stack, void *elem);
extern void *stack_pop    (T stack);
extern void  stack_free   (T *stack, void (*elem_free)(void *));

#undef T
#endif // STACK_H
