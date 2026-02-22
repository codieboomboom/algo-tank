#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue Queue_t;

typedef enum QueueError {
    QUEUE_SUCCESS,
    QUEUE_NOT_IMPLEMENTED,
    QUEUE_NOT_EXIST,
    QUEUE_EMPTY,
    QUEUE_ALLOC_FAILED,
    QUEUE_BAD_FORMAT,
} QueueError_t;

Queue_t* init_queue(void);

void destroy_queue(Queue_t** queue);

QueueError_t q_enqueue(Queue_t* queue, int value);

int q_dequeue(Queue_t* queue, QueueError_t* q_err);

int q_front(const Queue_t* queue, QueueError_t* q_err);

size_t q_size(const Queue_t* queue, QueueError_t* q_err);

#endif
