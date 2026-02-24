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

void test_q_enqueue_and_dequeue(void) {
    printf("Test Case: test_q_enqueue_and_dequeue\n");
    Queue_t* q = init_queue();
    QueueError_t q_err = QUEUE_SUCCESS;
    int v;
    int expected;

    q_err = q_enqueue(q, 1);
    ASSERT_EQ_INT(q_err, QUEUE_SUCCESS);
    expect_size(q, 1);
    expect_q_front(q, 1);

    expected = 1;

    v = q_dequeue(q, &q_err);
    ASSERT_EQ_INT(q_err, QUEUE_SUCCESS);
    ASSERT_EQ_INT(v, expected);
    expect_size(q, 0);

    destroy_queue(&q);
}

void test_multiple_enqueue_and_dequeue(void) {
    printf("Test Case: test_multiple_enqueue_and_dequeue\n");
    Queue_t* q = init_queue();
    QueueError_t q_err = QUEUE_SUCCESS;

    int v;
    int expected;

    q_err = q_enqueue(q, 1);
    ASSERT_EQ_INT(q_err, QUEUE_SUCCESS);
    expect_size(q, 1);
    expect_q_front(q, 1);

    q_err = q_enqueue(q, 2);
    ASSERT_EQ_INT(q_err, QUEUE_SUCCESS);
    expect_size(q, 2);
    expect_q_front(q, 1);

    expected = 1;

    v = q_dequeue(q, &q_err);
    ASSERT_EQ_INT(q_err, QUEUE_SUCCESS);
    ASSERT_EQ_INT(v, expected);
    expect_size(q, 1);

    expected = 2;

    v = q_dequeue(q, &q_err);
    ASSERT_EQ_INT(q_err, QUEUE_SUCCESS);
    ASSERT_EQ_INT(v, expected);
    expect_size(q, 0);

    destroy_queue(&q);
}

void test_enqueue_not_exist_queue(void) {
    printf("Test Case: test_enqueue_not_exist_queue\n");
    Queue_t* q = NULL;
    QueueError_t q_err = q_enqueue(q, 1);
    expect_q_error(q_err, QUEUE_NOT_EXIST);
}

void test_dequeue_not_exist_queue(void) {
    printf("Test Case: test_dequeue_not_exist_queue\n");
    Queue_t* q = NULL;
    QueueError_t q_err = QUEUE_SUCCESS;
    q_dequeue(q, &q_err);
    expect_q_error(q_err, QUEUE_NOT_EXIST);
}

void test_dequeue_empty_queue(void) {
    printf("Test Case: test_dequeue_empty_queue\n");
    Queue_t* q = init_queue();
    QueueError_t q_err = QUEUE_SUCCESS;
    q_front(q, &q_err);
    expect_q_error(q_err, QUEUE_EMPTY);
    destroy_queue(&q);
}

void test_front_not_exist_queue(void) {
    printf("Test Case: test_front_not_exist_queue\n");
    Queue_t* q = NULL;
    QueueError_t q_err = QUEUE_SUCCESS;
    q_front(q, &q_err);
    expect_q_error(q_err, QUEUE_NOT_EXIST);
}

void test_front_empty_queue(void) {
    printf("Test Case: test_front_empty_queue\n");
    Queue_t* q = init_queue();
    QueueError_t q_err = QUEUE_SUCCESS;
    q_front(q, &q_err);
    expect_q_error(q_err, QUEUE_EMPTY);
    destroy_queue(&q);
}

void test_queue_size_not_exist_queue(void) {
    printf("Test Case: test_queue_size_not_exist_queue\n");
    Queue_t* q = NULL;
    QueueError_t q_err = QUEUE_SUCCESS;
    q_size(q, &q_err);
    expect_q_error(q_err, QUEUE_NOT_EXIST);
}

void queue_tests(void) {
    test_q_init_and_destroy();
}
