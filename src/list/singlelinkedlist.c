#include <stdlib.h>
#include <stdio.h>

#include "list.h"

typedef struct ListNode {
    int value;
    struct ListNode* next;
} ListNode_t;

struct List {
    ListNode_t* head;
    size_t size;
};

List_t *init_list() {
    List_t *list = calloc(1, sizeof(List_t));
    if (!list) return NULL;
    return list;
}

List_t *create_list(int* elements, size_t nmemb) {
    List_t *list = calloc(1, sizeof(List_t));
    if (!list) return NULL;

    ListNode_t* prev = NULL;

    for (size_t idx = 0; idx < nmemb; idx++) {
        ListNode_t* node = calloc(1, sizeof(ListNode_t));
        if (!node) {
            destroy_list(&list);
        }
        node->value = elements[idx];
        if (!(list->head) && list->size == 0) {
            // First node
            list->head = node;
        } else {
            // Not the first node, so there should be prev
            prev->next = node;
        }
        prev = node;
        list->size++;
    }

    return list;
}

void clear_list(List_t* list) {
    if (!list) return; // nothing to do

    ListNode_t* curr_node = list->head;
    ListNode_t* next_node = NULL;
    while (curr_node) {
        next_node = curr_node->next;
        free(curr_node);
        curr_node = next_node;
        list->size--;
    }

    list->head = NULL;
    list->size = 0;

    return;
}

void destroy_list(List_t** list) {
    if (!list || !(*list)) return;

    ListNode_t* curr_node = (*list)->head;
    ListNode_t* next_node = NULL;
    while (curr_node) {
        next_node = curr_node->next;
        free(curr_node);
        curr_node = next_node;
        (*list)->size--;
    }

    free(*list);
    *list = NULL;

    return;
}

int peek_front(List_t* list, ErrorCode_t* err_status) {
    err_status = SUCCESS;

    if (!list) {
        err_status = ERROR_LIST_NOT_EXIST;
        return -1;
    }

    if (!(list->head)) {
        err_status = ERROR_LIST_IS_EMPTY; // cannot peek
        return -1;
    }

    return list->head->value;
}
int peek_back(List_t* list, ErrorCode_t* err_status);

size_t get_size(List_t* list, ErrorCode_t* err_status) {
    err_status = SUCCESS;
    if (!list) {
        err_status = ERROR_LIST_NOT_EXIST;
        return 0;
    }
    return list->size;
}

ErrorCode_t push_back(List_t* list, int value);
ErrorCode_t push_front(List_t* list, int value);

int pop_front(List_t* list, ErrorCode_t* err_status);
int pop_back(List_t* list, ErrorCode_t* err_status);

void print(List_t* list, Order_t order) {
    if (order == TAIL_TO_HEAD) {
        printf("Tail To Head Order not supported!");
        return;
    }

    if (!list) return;

    ListNode_t* curr = list->head;
    printf("Walking list from head to tail: ");
    while(curr) {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
    return;
}

int main() {
    return 0;
}