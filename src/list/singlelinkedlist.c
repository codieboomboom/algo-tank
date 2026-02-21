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

List_t *init_list(void) {
    List_t *list = calloc(1, sizeof(List_t));
    if (!list) return NULL;
    return list;
}

List_t *create_list(const int* elements, size_t nmemb) {
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

int list_peek_front(const List_t* list, ListError_t* err_status) {
    *err_status = LIST_SUCCESS;

    if (!list) {
        *err_status = LIST_ERROR_NOT_EXIST;
        return -1;
    }

    if (!(list->head)) {
        *err_status = LIST_ERROR_EMPTY; // cannot peek
        return -1;
    }

    return list->head->value;
}
int list_peek_back(const List_t* list, ListError_t* err_status) {
    *err_status = LIST_SUCCESS;

    if (!list) {
        *err_status = LIST_ERROR_NOT_EXIST;
        return -1;
    }

    if (!(list->head)) {
        *err_status = LIST_ERROR_EMPTY;
        return -1;
    }

    ListNode_t* curr = list->head;
    while(curr->next) {
        curr = curr->next;
    }

    return curr->value;
}

size_t list_size(const List_t* list, ListError_t* err_status) {
    *err_status = LIST_SUCCESS;
    if (!list) {
        *err_status = LIST_ERROR_NOT_EXIST;
        return 0;
    }
    return list->size;
}

ListError_t push_back(List_t* list, int value) {
    if (!list) return LIST_ERROR_NOT_EXIST;

    ListNode_t* curr_node = list->head;
    ListNode_t* prev_node = NULL;

    while(curr_node) {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    ListNode_t* node = calloc(1, sizeof(ListNode_t));
    if (!node) return LIST_ERROR_ALLOC_FAILED;
    node->value = value;

    if (prev_node) {
        prev_node->next = node;
    } else {
        list->head = node;
    }

    list->size++;

    return LIST_SUCCESS;
}

ListError_t push_front(List_t* list, int value) {
    if (!list) return LIST_ERROR_NOT_EXIST;

    ListNode_t* node = calloc(1, sizeof(ListNode_t));
    if (!node) {
        return LIST_ERROR_ALLOC_FAILED;
    }
    node->value = value;
    node->next = list->head;
    list->head = node;

    list->size++;

    return LIST_SUCCESS;
}

int list_pop_front(List_t* list, ListError_t* err_status) {
    *err_status = LIST_SUCCESS;

    if (!list) {
        *err_status = LIST_ERROR_NOT_EXIST;
        return -1;
    }

    if (!(list->head)) {
        *err_status = LIST_ERROR_EMPTY;
        return -1;
    }

    ListNode_t* next_node = list->head->next;
    int value = list->head->value;
    free(list->head);
    if (!next_node) {
        list->head = NULL;
    } else {
        list->head = next_node;
    }

    list->size--;

    return value;
}

int list_pop_back(List_t* list, ListError_t* err_status) {
    *err_status = LIST_SUCCESS;

    if (!list) {
        *err_status = LIST_ERROR_NOT_EXIST;
        return -1;
    }

    if (!(list->head)) {
        *err_status = LIST_ERROR_EMPTY;
        return -1;
    }

    int value;
    ListNode_t* curr = list->head;
    ListNode_t* prev = NULL;
    while(curr->next) {
        prev = curr;
        curr = curr->next;
    }

    value = curr->value;
    free(curr); // deallocate the last node
    // handle the previous node link to this node
    if (!prev) {
        // popping the only node in the list
        list->head = NULL;
    } else {
        prev->next = NULL;
    }

    list->size--;

    return value;
}

void print_list(const List_t* list, Order_t order) {
    if (order == TAIL_TO_HEAD) {
        printf("Tail To Head Order not supported!\n");
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
