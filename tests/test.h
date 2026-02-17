#ifndef TEST_H
#define TEST_H

#include <stdio.h>

extern int g_failures;

/* =========================================================
   Colored output (ANSI escape codes)
   ========================================================= */

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RESET   "\x1b[0m"

/* =========================================================
   Core assertion macros
   ========================================================= */

#define ASSERT_TRUE(expr)                                    \
    do {                                                     \
        if (!(expr)) {                                       \
            fprintf(stderr,                                  \
                COLOR_RED "FAIL %s:%d: %s\n" COLOR_RESET,    \
                __FILE__, __LINE__, #expr);                  \
            g_failures++;                                    \
        }                                                    \
    } while (0)

#define ASSERT_FALSE(expr) ASSERT_TRUE(!(expr))

#define ASSERT_EQ_INT(a, b)                                  \
    do {                                                     \
        int _a = (a);                                        \
        int _b = (b);                                        \
        if (_a != _b) {                                      \
            fprintf(stderr,                                  \
                COLOR_RED "FAIL %s:%d: %s=%d, %s=%d\n"       \
                COLOR_RESET,                                 \
                __FILE__, __LINE__, #a, _a, #b, _b);         \
            g_failures++;                                    \
        }                                                    \
    } while (0)

#define ASSERT_NE_INT(a, b)                                  \
    do {                                                     \
        int _a = (a);                                        \
        int _b = (b);                                        \
        if (_a == _b) {                                      \
            fprintf(stderr,                                  \
                COLOR_RED "FAIL %s:%d: %s == %s (%d)\n"      \
                COLOR_RESET,                                 \
                __FILE__, __LINE__, #a, #b, _a);             \
            g_failures++;                                    \
        }                                                    \
    } while (0)

#define ASSERT_EQ_SIZE(a, b)                                 \
    do {                                                     \
        size_t _a = (a);                                     \
        size_t _b = (b);                                     \
        if (_a != _b) {                                      \
            fprintf(stderr,                                  \
                COLOR_RED "FAIL %s:%d: %s=%zu, %s=%zu\n"     \
                COLOR_RESET,                                 \
                __FILE__, __LINE__, #a, _a, #b, _b);         \
            g_failures++;                                    \
        }                                                    \
    } while (0)

#define ASSERT_NULL(ptr) ASSERT_TRUE((ptr) == NULL)
#define ASSERT_NOT_NULL(ptr) ASSERT_TRUE((ptr) != NULL)
#endif
