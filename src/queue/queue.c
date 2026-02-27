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

Queue_t* init_queue(void) {
    List_t* list = init_list();
    if (!list) return NULL; // Failed to alloc a list

    Queue_t* q = calloc(1, sizeof(Queue_t));
    if (!q) return NULL;

    q->_list = list;
    return q;
}

void destroy_queue(Queue_t** queue) {
    if (!queue || !(*queue)) {
        return; // TODO: What if the above guard is missing, as we are deref below
    }
    destroy_list((*queue)->_list);
    free(*queue);
    *queue = NULL;
}

QueueError_t q_enqueue(Queue_t* queue, int value) {
    if (!queue) return QUEUE_NOT_EXIST;
    ListError_t _list_err = push_back(queue->_list, value);

    return convert_list_err_to_q_err(_list_err);
}

int q_dequeue(Queue_t* queue, QueueError_t* q_err);

int q_front(const Queue_t* queue, QueueError_t* q_err);

size_t q_size(const Queue_t* queue, QueueError_t* q_err) {
    *q_err = QUEUE_SUCCESS;

    if (!queue || !(queue->_list)) {
        *q_err = QUEUE_NOT_EXIST;
        return 0;
    }

    ListError_t _list_err = LIST_SUCCESS;
    size_t nmemb = list_size(queue->_list, &_list_err);
    *q_err = convert_list_err_to_q_err(_list_err);
    return nmemb;
}
