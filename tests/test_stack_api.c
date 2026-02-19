#include "test.h"
#include "stack.h"

/* Helper: assert size and SUCCESS */
static void expect_size(Stack_t *stack, size_t expected) {
    StackError_t err = STACK_SUCCESS;
    size_t s = get_size(stack, &err);
    ASSERT_EQ_INT(err, STACK_SUCCESS);
    ASSERT_EQ_SIZE(s, expected);
}

/* Helper: assert top values and SUCCESS */
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

// TODO
void test_stack_single_push_single_pop(void) {
    printf("Test Case: test_stack_single_push_single_pop\n");
    Stack_t *stack = init_stack();
    destroy_stack(&stack);
    return;
}

// TODO
void test_stack_multiple_push_multiple_pop(void) {
    printf("Test Case: test_stack_multiple_push_multiple_pop\n");
    Stack_t *stack = init_stack();
    destroy_stack(&stack);
    return;
}

// TODO
void test_stack_peek_empty_stack(void) {
    printf("Test Case: test_stack_peek_empty_stack\n");
    Stack_t *stack = init_stack();
    destroy_stack(&stack);
    return;
}

// TODO
void test_stack_pop_empty_stack(void) {
    printf("Test Case: test_stack_pop_empty_stack\n");
    Stack_t *stack = init_stack();
    destroy_stack(&stack);
    return;
}

void test_stack_peek_not_exist_stack(void) {
    printf("Test Case: test_stack_peek_not_exist_stack\n");
    Stack_t *stack = NULL;
    StackError_t err;
    int v = peek(stack, &err);
    expect_stack_error(err, STACK_NOT_EXIST);
}

void test_stack_pop_not_exist_stack(void) {
    printf("Test Case: test_stack_pop_not_exist_stack\n");
    Stack_t *stack = NULL;
    StackError_t err;
    int v = pop(stack, &err);
    expect_stack_error(err, STACK_NOT_EXIST);
}

void test_stack_push_not_exist_stack(void) {
    printf("Test Case: test_stack_push_not_exist_stack\n");
    Stack_t *stack = NULL;
    StackError_t err = push(stack, 1);
    expect_stack_error(err, STACK_NOT_EXIST);
}

void test_stack_get_size_null_stackptr(void) {
    printf("Test Case: test_stack_get_size_null_stackptr\n");
    Stack_t *stack = NULL;
    StackError_t err;
    size_t stack_size = get_size(stack, &err);

    expect_stack_error(err, STACK_NOT_EXIST); 
}