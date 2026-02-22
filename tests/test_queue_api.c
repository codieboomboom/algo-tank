#include "test.h"
#include "queue.h"

/* Helper: assert size and SUCCESS */
static void expect_size(Queue_t *queue, size_t expected) {
    QueueError_t err = QUEUE_SUCCESS;
    size_t s = q_size(queue, &err);
    ASSERT_EQ_INT(err, QUEUE_SUCCESS);
    ASSERT_EQ_SIZE(s, expected);
}

/* Helper: assert top values and SUCCESS */
static void expect_q_front(Queue_t *queue, int expected) {
    QueueError_t err = QUEUE_SUCCESS;
    int v = q_front(queue, &err);
    ASSERT_EQ_INT(err, QUEUE_SUCCESS);
    ASSERT_EQ_INT(v, expected);
}

static void expect_q_error(QueueError_t err, QueueError_t expected) {
    ASSERT_EQ_INT(err, expected);
}

void test_q_init_and_destroy(void) {
    printf("Test Case: test_q_init_and_destroy\n");
    Queue_t* q = init_queue();
    ASSERT_NOT_NULL(q);

    expect_size(q, 0);
    destroy_queue(&q);
    ASSERT_NULL(q);
}

void queue_tests(void) {
    test_q_init_and_destroy();
}
