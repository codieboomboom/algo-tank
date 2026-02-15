#include "test.h"

int g_failures = 0;

void test_list_create_print_destroy(void);
void test_list_push_back_peek_pop_back(void);
void test_list_push_front_clear_reuse_pop_front(void);

int main(void) {
    test_list_create_print_destroy();
    test_list_push_back_peek_pop_back();
    test_list_push_front_clear_reuse_pop_front();

    if (g_failures) {
        fprintf(stderr, "%d test(s) failed\n", g_failures);
        return 1;
    }
    printf("All tests passed\n");
    return 0;
}
