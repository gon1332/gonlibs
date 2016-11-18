#ifndef REPORTERR_H
#define REPORTERR_H

#include <stdio.h>
#include <string.h>
#include <errno.h>

#define ERRNO_REPORT_EXIT(reason, file, line) \
    do { \
        fprintf(stderr, "Error %s", reason); \
        if (file && line > 0) \
            fprintf(stderr, " at %s:%d", (file), (line)); \
        fprintf(stderr, ": %s\n", strerror(errno)); \
        fflush(stderr); \
        exit(EXIT_FAILURE); \
    } while (0);


#endif // REPORTERR_H
