#include "test.h"
#include "stack.h"

/* Helper: assert size and SUCCESS */
static void expect_size(Stack_t *stack, size_t expected) {
    StackError_t err = STACK_SUCCESS;
    size_t s = get_size(stack, &err);
    ASSERT_EQ_INT(err, STACK_SUCCESS);
    ASSERT_EQ_SIZE(s, expected);
}

/* Helper: assert head/tail values and SUCCESS */
static void expect_top(Stack_t *stack, int expected) {
    StackError_t err = STACK_SUCCESS;
    int v = peek_front(stack, &err);
    ASSERT_EQ_INT(err, STACK_SUCCESS);
    ASSERT_EQ_INT(v, expected);
}

static void expect_pop(Stack_t *stack, int expected) {
    StackError_t err = STACK_SUCCESS;
    int v = pop_back(stack, &err);
    ASSERT_EQ_INT(err, STACK_SUCCESS);
    ASSERT_EQ_INT(v, expected);
}

void test_stack_init_and_destroy(void) {
    return;
}

void test_stack_single_push_single_pop(void) {
    return;
}

void test_stack_multiple_push_multiple_pop(void) {
    return;
}