#include "test.h"

int g_failures = 0;

void list_tests(void);
void stack_tests(void);
void queue_tests(void);

int main(void) {
    list_tests();
    stack_tests();
    queue_tests();

    if (g_failures) {
        fprintf(stderr, "%d test(s) failed\n", g_failures);
        return 1;
    }
    printf("All tests passed\n");
    return 0;
}
