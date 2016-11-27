#include "tests.h"

int main(void)
{
    CHECK_SANITY(test__MEM_memwrap(),   "MEM_memwrap");
    CHECK_SANITY(test__ADT_stack(),     "ADT_stack");
    CHECK_SANITY(test__ADT_dequeue(),   "ADT_dequeue");
    CHECK_SANITY(test__ADT_hashtable(), "ADT_hashtable");

    return EXIT_SUCCESS;
}
