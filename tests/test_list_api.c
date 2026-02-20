#include "test.h"
#include "list.h"

/* Helper: assert size and SUCCESS */
static void expect_size(List_t *list, size_t expected) {
    ListError_t err = LIST_SUCCESS;
    size_t s = list_size(list, &err);
    ASSERT_EQ_INT(err, LIST_SUCCESS);
    ASSERT_EQ_SIZE(s, expected);
}

/* Helper: assert head/tail values and SUCCESS */
static void expect_front(List_t *list, int expected) {
    ListError_t err = LIST_SUCCESS;
    int v = peek_front(list, &err);
    ASSERT_EQ_INT(err, LIST_SUCCESS);
    ASSERT_EQ_INT(v, expected);
}

static void expect_back(List_t *list, int expected) {
    ListError_t err = LIST_SUCCESS;
    int v = peek_back(list, &err);
    ASSERT_EQ_INT(err, LIST_SUCCESS);
    ASSERT_EQ_INT(v, expected);
}

static void expect_pop_front(List_t *list, int expected) {
    ListError_t err = LIST_SUCCESS;
    int v = pop_front(list, &err);
    ASSERT_EQ_INT(err, LIST_SUCCESS);
    ASSERT_EQ_INT(v, expected);
}

static void expect_pop_back(List_t *list, int expected) {
    ListError_t err = LIST_SUCCESS;
    int v = pop_back(list, &err);
    ASSERT_EQ_INT(err, LIST_SUCCESS);
    ASSERT_EQ_INT(v, expected);
}

/* 1) create_list + print smoke + destroy behavior */
void test_list_create_print_destroy(void) {
    printf("Test Case: test_list_create_print_destroy\n");
    int arr[5] = {4, 2, 3, 6, 8};
    List_t *list = create_list(arr, sizeof(arr)/sizeof(arr[0]));
    ASSERT_NOT_NULL(list);

    expect_size(list, 5);
    expect_front(list, 4);
    expect_back(list, 8);

    /* Smoke test: should not crash */
    print(list, HEAD_TO_TAIL);
    print(list, TAIL_TO_HEAD);

    destroy_list(&list);
    ASSERT_NULL(list);

    /* Optional: calling print(NULL, ...) should be safe if you support it.
       If you DON'T support NULL, comment these out. */
    print(list, HEAD_TO_TAIL);
    print(list, TAIL_TO_HEAD);
}

/* 2) push_back flow (your list2 block) */
void test_list_push_back_peek_pop_back(void) {
    printf("Test Case: test_list_push_back_peek_pop_back\n");
    ListError_t result = LIST_SUCCESS;

    List_t *list = init_list();
    ASSERT_NOT_NULL(list);

    ASSERT_EQ_INT(push_back(list, 1), LIST_SUCCESS);
    expect_front(list, 1);
    expect_back(list, 1);
    expect_size(list, 1);

    ASSERT_EQ_INT(push_back(list, 2), LIST_SUCCESS);
    expect_front(list, 1);
    expect_back(list, 2);
    expect_size(list, 2);

    /* Smoke prints */
    print(list, HEAD_TO_TAIL);
    print(list, TAIL_TO_HEAD);

    /* pop_back twice: should yield 2 then 1 */
    expect_pop_back(list, 2);
    expect_size(list, 1);

    print(list, HEAD_TO_TAIL);
    print(list, TAIL_TO_HEAD);

    expect_pop_back(list, 1);
    expect_size(list, 0);

    print(list, HEAD_TO_TAIL);
    print(list, TAIL_TO_HEAD);

    /* extra pop_back on empty should error */
    int v = pop_back(list, &result);
    (void)v;
    ASSERT_EQ_INT(result, LIST_ERROR_EMPTY);

    destroy_list(&list);
    ASSERT_NULL(list);
}

/* 3) push_front + clear + reuse + pop_front flow (your list3 block) */
void test_list_push_front_clear_reuse_pop_front(void) {
    printf("Test Case: test_list_push_front_clear_reuse_pop_front\n");
    ListError_t result = LIST_SUCCESS;

    List_t *list = init_list();
    ASSERT_NOT_NULL(list);

    ASSERT_EQ_INT(push_front(list, 1), LIST_SUCCESS);
    expect_front(list, 1);
    expect_back(list, 1);
    expect_size(list, 1);

    ASSERT_EQ_INT(push_front(list, 2), LIST_SUCCESS);
    expect_front(list, 2);
    expect_back(list, 1);
    expect_size(list, 2);

    print(list, HEAD_TO_TAIL);
    print(list, TAIL_TO_HEAD);

    /* clear should empty but keep list usable */
    clear_list(list);
    expect_size(list, 0);

    /* after clear, peeks should error empty */
    int v = peek_front(list, &result);
    (void)v;
    ASSERT_EQ_INT(result, LIST_ERROR_EMPTY);

    v = peek_back(list, &result);
    (void)v;
    ASSERT_EQ_INT(result, LIST_ERROR_EMPTY);

    /* reuse after clear */
    ASSERT_EQ_INT(push_front(list, 500), LIST_SUCCESS);
    expect_front(list, 500);
    expect_back(list, 500);
    expect_size(list, 1);

    ASSERT_EQ_INT(push_front(list, 999), LIST_SUCCESS);
    expect_front(list, 999);
    expect_back(list, 500);
    expect_size(list, 2);

    print(list, HEAD_TO_TAIL);
    print(list, TAIL_TO_HEAD);

    /* pop_front twice: should yield 999 then 500 */
    expect_pop_front(list, 999);
    expect_size(list, 1);

    print(list, HEAD_TO_TAIL);
    print(list, TAIL_TO_HEAD);

    expect_pop_front(list, 500);
    expect_size(list, 0);

    print(list, HEAD_TO_TAIL);
    print(list, TAIL_TO_HEAD);

    /* extra pop_front on empty should error */
    v = pop_front(list, &result);
    (void)v;
    ASSERT_EQ_INT(result, LIST_ERROR_EMPTY);

    destroy_list(&list);
    ASSERT_NULL(list);
}
