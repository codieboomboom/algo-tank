#include <stdlib.h>
#include "list.h"
#include "queue.h"

struct Queue {
    List_t* _list;
};

static QueueError_t convert_list_err_to_q_err(ListError_t list_err) {
    QueueError_t q_err;

    switch(list_err) {
        case LIST_SUCCESS:
            q_err = QUEUE_SUCCESS;
            break;
        case LIST_ERROR_NOT_EXIST:
            q_err = QUEUE_NOT_EXIST;
            break;
        case LIST_ERROR_EMPTY:
            q_err = QUEUE_EMPTY;
            break;
        case LIST_ERROR_ALLOC_FAILED:
            q_err = QUEUE_ALLOC_FAILED;
            break;
        default:
            q_err = QUEUE_NOT_IMPLEMENTED;
            break;
    }

    return q_err;
}

Queue_t* init_queue(void);

void destroy_queue(Queue_t** queue);

QueueError_t q_enqueue(Queue_t* queue, int value);

int q_dequeue(Queue_t* queue, QueueError_t* q_err);

int q_front(const Queue_t* queue, QueueError_t* q_err);

size_t q_size(const Queue_t* queue, QueueError_t* q_err);
