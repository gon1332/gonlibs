#include "tests.h"
#include "DBG/logger.h"

int main(void)
{
    LOG("start of testing\n");
    CHECK_SANITY(test__MEM_memwrap(),   "MEM_memwrap");
    CHECK_SANITY(test__ADT_stack(),     "ADT_stack");
    CHECK_SANITY(test__ADT_dequeue(),   "ADT_dequeue");
    CHECK_SANITY(test__ADT_hashtable(), "ADT_hashtable");
    LOG("end of testing\n");

    return EXIT_SUCCESS;
}
