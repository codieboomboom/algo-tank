#include "test.h"
#include "stack.h"

/* Helper: assert size and SUCCESS */
static void expect_size(Stack_t *stack, size_t expected) {
    StackError_t err = STACK_SUCCESS;
    size_t s = stack_size(stack, &err);
    ASSERT_EQ_INT(err, STACK_SUCCESS);
    ASSERT_EQ_SIZE(s, expected);
}

/* Helper: assert top values and SUCCESS */
static void expect_top(Stack_t *stack, int expected) {
    StackError_t err = STACK_SUCCESS;
    int v = stack_peek(stack, &err);
    ASSERT_EQ_INT(err, STACK_SUCCESS);
    ASSERT_EQ_INT(v, expected);
}

static void expect_stack_error(StackError_t err, StackError_t expected) {
    ASSERT_EQ_INT(err, expected);
}

void test_stack_init_and_destroy(void) {
    printf("Test Case: test_stack_init_and_destroy\n");
    Stack_t *stack = init_stack();
    ASSERT_NOT_NULL(stack);

    expect_size(stack, 0);
    destroy_stack(&stack);
    ASSERT_NULL(stack);

    return;
}

void test_stack_single_push_single_pop(void) {
    printf("Test Case: test_stack_single_push_single_pop\n");
    Stack_t *stack = init_stack();
    StackError_t err = STACK_SUCCESS;

    err = stack_push(stack, 1);
    ASSERT_EQ_INT(err, STACK_SUCCESS);
    expect_size(stack, 1);
    expect_top(stack, 1);

    int v = stack_pop(stack, &err);
    int expected = 1;
    ASSERT_EQ_INT(err, STACK_SUCCESS);
    ASSERT_EQ_INT(v, expected);
    expect_size(stack, 0);
    destroy_stack(&stack);
}

void test_stack_multiple_push_multiple_pop(void) {
    printf("Test Case: test_stack_multiple_push_multiple_pop\n");
    Stack_t *stack = init_stack();
    StackError_t err = STACK_SUCCESS;

    err = stack_push(stack, 1);
    ASSERT_EQ_INT(err, STACK_SUCCESS);
    expect_size(stack, 1);
    expect_top(stack, 1);

    err = stack_push(stack, 2);
    ASSERT_EQ_INT(err, STACK_SUCCESS);
    expect_size(stack, 2);
    expect_top(stack, 2);

    int v = stack_pop(stack, &err);
    int expected = 2;
    ASSERT_EQ_INT(err, STACK_SUCCESS);
    ASSERT_EQ_INT(v, expected);
    expect_size(stack, 1);

    v = stack_pop(stack, &err);
    expected = 1;
    ASSERT_EQ_INT(err, STACK_SUCCESS);
    ASSERT_EQ_INT(v, expected);
    expect_size(stack, 0);

    destroy_stack(&stack);
    return;
}

void test_stack_peek_empty_stack(void) {
    printf("Test Case: test_stack_peek_empty_stack\n");
    Stack_t *stack = init_stack();
    StackError_t err = STACK_SUCCESS;
    stack_peek(stack, &err);
    expect_stack_error(err, STACK_EMPTY);
    destroy_stack(&stack);
    return;
}

void test_stack_pop_empty_stack(void) {
    printf("Test Case: test_stack_pop_empty_stack\n");
    Stack_t *stack = init_stack();
    StackError_t err = STACK_SUCCESS;
    stack_pop(stack, &err);
    expect_stack_error(err, STACK_EMPTY);
    destroy_stack(&stack);
    return;
}

void test_stack_peek_not_exist_stack(void) {
    printf("Test Case: test_stack_peek_not_exist_stack\n");
    Stack_t *stack = NULL;
    StackError_t err = STACK_SUCCESS;
    stack_peek(stack, &err);
    expect_stack_error(err, STACK_NOT_EXIST);
}

void test_stack_pop_not_exist_stack(void) {
    printf("Test Case: test_stack_pop_not_exist_stack\n");
    Stack_t *stack = NULL;
    StackError_t err = STACK_SUCCESS;
    stack_pop(stack, &err);
    expect_stack_error(err, STACK_NOT_EXIST);
}

void test_stack_push_not_exist_stack(void) {
    printf("Test Case: test_stack_push_not_exist_stack\n");
    Stack_t *stack = NULL;
    StackError_t err = stack_push(stack, 1);
    expect_stack_error(err, STACK_NOT_EXIST);
}

void test_stack_get_size_null_stackptr(void) {
    printf("Test Case: test_stack_get_size_null_stackptr\n");
    Stack_t *stack = NULL;
    StackError_t err = STACK_SUCCESS;
    stack_size(stack, &err);
    expect_stack_error(err, STACK_NOT_EXIST); 
}