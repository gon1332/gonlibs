#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <string.h>
#include <errno.h>

#define LOG_LEVEL   1
#define LVL_HIGH    3
#define LVL_MEDIUM  2
#define LVL_LOW     1
#define LVL_NO      0
#define LOG(lvl, msg, ...) \
    do { \
        switch (LEVEL) { \
            case LVL_NO: break; \
            case LVL_LOW:    (void)((lvl >= LVL_LOW)    && fprintf(stderr, msg, ##__VA_ARGS__)); break; \
            case LVL_MEDIUM: (void)((lvl >= LVL_MEDIUM) && fprintf(stderr, msg, ##__VA_ARGS__)); break; \
            case LVL_HIGH:   (void)((lvl >= LVL_HIGH)   && fprintf(stderr, msg, ##__VA_ARGS__)); break; \
        } \
    } while (0)


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
