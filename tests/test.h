#ifndef TEST_H
#define TEST_H

#include <stdio.h>

extern int g_failures;

/* Assert that expression is true */
#define ASSERT_TRUE(expr)                                    \
    do {                                                     \
        if (!(expr)) {                                       \
            fprintf(stderr,                                  \
                    "FAIL %s:%d: %s\n",                      \
                    __FILE__, __LINE__, #expr);              \
            g_failures++;                                    \
        }                                                    \
    } while (0)

/* Assert integer equality */
#define ASSERT_EQ_INT(a, b)                                  \
    do {                                                     \
        int _a = (a);                                        \
        int _b = (b);                                        \
        if (_a != _b) {                                      \
            fprintf(stderr,                                  \
                    "FAIL %s:%d: %s=%d, %s=%d\n",            \
                    __FILE__, __LINE__,                      \
                    #a, _a, #b, _b);                         \
            g_failures++;                                    \
        }                                                    \
    } while (0)

/* Assert size_t equality */
#define ASSERT_EQ_SIZE(a, b)                                 \
    do {                                                     \
        size_t _a = (a);                                     \
        size_t _b = (b);                                     \
        if (_a != _b) {                                      \
            fprintf(stderr,                                  \
                    "FAIL %s:%d: %s=%zu, %s=%zu\n",          \
                    __FILE__, __LINE__,                      \
                    #a, _a, #b, _b);                         \
            g_failures++;                                    \
        }                                                    \
    } while (0)

#endif