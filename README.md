# gonlibs
Libraries of generic stuff written in C for my projects and yours. ;)

## Contents
  * ADT
    * stack
    * dequeue
  * MEM
    * memwrapper

### ADT
#### stack
A generic LIFO queue. A stack.

```c
stack_t  stack_new    (void);
bool     stack_isempty(stack_t stack);
void     stack_push   (stack_t stack, void *elem);
void    *stack_pop    (stack_t stack);
void     stack_free   (stack_t *stack, void (*elem_free)(void *));
```

#### dequeue
A generic double-ended queue.

```c
dequeue_t  dequeue_new       (void);
bool       dequeue_isempty   (dequeue_t dequeue);
void       dequeue_push_back (dequeue_t dequeue, void *elem);
void       dequeue_push_front(dequeue_t dequeue, void *elem);
void      *dequeue_pop_back  (dequeue_t dequeue);
void      *dequeue_pop_front (dequeue_t dequeue);
void       dequeue_clear     (dequeue_t dequeue, void (*elem_free)(void *));
void       dequeue_free      (dequeue_t *dequeue, void (*elem_free)(void *));
```

### MEM
#### memwrapper
A simple wrapper for standard memory calls. Not all of them yet and nothing special. *Brevity is the soul of wit.*

```c
#define ALLOC(nbytes) (memwrap_malloc((nbytes)))
#define NEW  (ptr)    ((ptr) = ALLOC(sizeof *(ptr)))
#define FREE (ptr)    ((void)memwrap_free((ptr)), (ptr) = NULL)

void *memwrap_malloc(size_t nbytes);
void  memwrap_free  (void *ptr);
```
