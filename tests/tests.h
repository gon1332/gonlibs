#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include <stdlib.h>

#define CHECK_SANITY(x, y) \
    switch (x) { \
        case EXIT_SUCCESS: puts("[PASS]..." y); break; \
        case EXIT_FAILURE: puts("[FAIL]..." y); break; \
    } \

extern int test__MEM_memwrap    (void);
extern int test__ADT_stack      (void);
extern int test__ADT_dequeue    (void);
extern int test__ADT_hashtable  (void);
extern int test__ADT_forwardlist(void);

#endif // TESTS_H
