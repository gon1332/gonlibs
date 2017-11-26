# gonlibs
Libraries of generic stuff written in C for my projects and yours. ;)

## Contents
  * ADT
    * stack
    * dequeue
    * hashtable
    * forwardlist
  * MEM
    * memwrapper

### ADT
#### stack
A generic LIFO queue. A stack.

```c
stack_t  stack_new  (void);
bool     stack_empty(stack_t stack);
void     stack_push (stack_t stack, void *elem);
void    *stack_pop  (stack_t stack);
void     stack_free (stack_t *stack, void (*elem_free)(void *));
```

#### dequeue
A generic double-ended queue.

```c
dequeue_t dequeue_new (void);
void      dequeue_free(dequeue_t *dequeue, void (*elem_free)(void *));

// Capacity
bool dequeue_isempty(dequeue_t dequeue);

// Modifiers
void  dequeue_push_back (dequeue_t dequeue, void *elem);
void  dequeue_push_front(dequeue_t dequeue, void *elem);
void *dequeue_pop_back  (dequeue_t dequeue);
void *dequeue_pop_front (dequeue_t dequeue);
void  dequeue_clear     (dequeue_t dequeue, void (*elem_free)(void *));
```

#### hashtable
A generic hashtable. Stores pairs of type <int, T>.

```c
hashtable_t hashtable_new (void);
void        hashtable_free(hashtable_t *hashtable, void (*elem_free)(void *));

// Capacity
bool      hashtable_isempty(hashtable_t hashtable);
uintmax_t hashtable_size   (hashtable_t hashtable);

// Modifiers
void  hashtable_insert(hashtable_t hashtable, int key, void *elem);
void *hashtable_remove(hashtable_t hashtable, int key);
void  hashtable_clear (hashtable_t hashtable, void (*elem_free)(void *));

// Operations
void *hashtable_find(hashtable_t hashtable, int key);
```

#### forwardlist
A generic single-linked list with simplicity built in to it.

```c
T    forwardlist_new (void *elem, ...);
void forwardlist_free(T *list);

// Capacity
bool      forwardlist_empty(T list);
uintmax_t forwardlist_size (T list);

// Modifiers
void  forwardlist_push_front(T list, void *elem);
void *forwardlist_pop_front (T list);
void  forwardlist_append    (T list, T tail);
void  forwardlist_map       (T list,
        void apply(void **x, void *cl), void *cl);
void  forwardlist_clear     (T list);

// Operations
void forwardlist_reverse(T list);
```

### MEM
#### memwrapper
A simple wrapper for standard memory calls. Not all of them yet and nothing special. *Brevity is the soul of wit.*

```c
#define ALLOC (nbytes)        (memwrap_malloc((nbytes), __FILE__, __LINE__))
#define CALLOC(count, nbytes) (memwrap_calloc((count), (nbytes), __FILE__, __LINE__))
#define NEW   (ptr)           ((ptr) = ALLOC((int64_t)sizeof *(ptr)))
#define NEWZ  (ptr)           ((ptr) = CALLOC(1, (int64_t)sizeof *(ptr)))
#define RESIZE(ptr, nbytes)   ((ptr) = memwrap_resize((ptr), (nbytes), __FILE__, __LINE__))
#define FREE  (ptr)           ((void)memwrap_free((ptr), __FILE__, __LINE__), (ptr) = NULL)

void *memwrap_malloc(int64_t nbytes, const char *file, int line);
void *memwrap_calloc(int64_t count, int64_t nbytes, const char *file, int line);
void *memwrap_resize(void *ptr, int64_t nbytes, const char *file, int line);
void  memwrap_free  (void *ptr, const char *file, int line);
```
