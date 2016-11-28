#include "ADT/stack.h"
#include "MEM/memwrap.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define SECRET_ID 0x000000737461636b

#define T stack_t

struct T {
    int count;

    struct elem {
        void *x;
        struct elem *link;
    } *head;

    uint64_t id;
};


T stack_new(void)
{
    T stack;

    NEW(stack);

    stack->count = 0;
    stack->head  = NULL;
    stack->id    = SECRET_ID;

    return stack;
}


bool stack_isempty(T stack)
{
    assert(stack);
    assert(stack->id == SECRET_ID);

    return !stack->count;
}


uintmax_t stack_size(T stack)
{
    assert(stack);
    assert(stack->id == SECRET_ID);

    return stack->count;
}


void stack_push(T stack, void *elem)
{
    assert(stack);
    assert(stack->id == SECRET_ID);

    struct elem *t;
    NEW(t);

    t->x = elem;
    t->link = stack->head;
    stack->head = t;
    stack->count++;
}


void *stack_pop(T stack)
{
    assert(stack);
    assert(stack->id == SECRET_ID);
    assert(stack->count);

    struct elem *t = stack->head;
    stack->head = t->link;
    stack->count--;
    void *x = t->x;
    FREE(t);

    return x;
}


void stack_free(T *stack, void (*elem_free)(void *))
{
    assert(stack && *stack);
    assert((*stack)->id == SECRET_ID);

    struct elem *u;
    for (struct elem *t = (*stack)->head; t; t = u) {
        u = t->link;
        if (elem_free) elem_free(t->x);
        FREE(t);
    }

    FREE(*stack);
}
