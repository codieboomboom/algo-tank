#include <stdlib.h>
#include <stdio.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode_t;

typedef struct DoubleList {
    ListNode_t* head;
    ListNode_t* tail;
    size_t size;
} DoubleList_t;

typedef enum ErrorCode{
    SUCCESS,
    ERROR_LIST_NOT_EXIST,
    ERROR_LIST_INCONSISTENT_PTR,
    ERROR_HEAP_ALLOC_FAILED
} ErrorCode_t;

DoubleList_t* create_list(int* elements, size_t nmemb) {
    if (!nmemb) return NULL; //empty

    // Init the list
    DoubleList_t* list = malloc(sizeof(DoubleList_t));
    if(!list) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    // Declare to be NULL first
    ListNode_t* prev = NULL;
    ListNode_t* next = NULL;
    for (size_t mem_idx = 0; mem_idx < nmemb; mem_idx++) {
        ListNode_t* node = malloc(sizeof(ListNode_t));
        if(!node) {
            // TODO: Cleanup list here
            return NULL;
        }
        // First allocated node...
        if (!(list->head)) {
            list->head = node;
        }

        node->value = elements[mem_idx];
        node->prev = prev;
        node->next = next;

        if (prev) {prev->next = node;} // make link

        list->tail = node; // we create from left to right so always tail ptr to the newly created node
        list->size += 1;
        // Save this node as previous node
        prev = node;
    }
    return list;
}

DoubleList_t* init_list() {
    // Init the list empty
    DoubleList_t* list = malloc(sizeof(DoubleList_t));
    if(!list) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

ErrorCode_t push_back(DoubleList_t* list, int value) {
    if(!list) return ERROR_LIST_NOT_EXIST;

    if (list->head && !(list->tail) || !(list->head) && list->tail) {
        return ERROR_LIST_INCONSISTENT_PTR;
    }

    ListNode_t* node = malloc(sizeof(ListNode_t));
    if (!node) return ERROR_HEAP_ALLOC_FAILED;

    node->value = value;
    node->next = NULL;
    node->prev = list->tail; // previous node should be the list current tail
    if (list->tail) {
        list->tail->next = node; // previous tail should point to this new node
    }
    list->tail = node;
    list->size++;

    return SUCCESS;
}


// We use **list over *list because we want to clear the *list to NULL after free
void cleanup(DoubleList_t** list){
    if (!list || !(*list)) return; // nothing to do here

    // Go through list from any direction, prefered from head
    ListNode_t* curr_node = (*list)->head;
    ListNode_t* next = NULL;
    while (curr_node) {
        next = curr_node->next;
        free(curr_node);
        curr_node = next;
    }

    free(*list);
    *list = NULL;
    return;
}

void print_list(DoubleList_t* list, int head_to_tail) {
    if(!list) return; // GUARD IMPORTANT, otherwise list->head might be attempted, invalid...

    ListNode_t* curr_node = NULL;
    if (head_to_tail) {
        printf("Walking list from head to tail: ");
        curr_node = list->head;
        while(curr_node) {
            printf("%d ", curr_node->value);
            curr_node = curr_node->next;
        }
    } else {
        printf("Walking list from tail to head: ");
        curr_node = list->tail;
        while(curr_node) {
            printf("%d ", curr_node->value);
            curr_node = curr_node->prev;
        }
    }
    printf("\n");
}

int main() {
    ErrorCode_t result = SUCCESS;
    int arr[5] = {4, 2, 3, 6, 8};
    DoubleList_t* list = create_list(arr, sizeof(arr)/sizeof(arr[0]));
    print_list(list, 1);
    print_list(list, 0);
    cleanup(&list);
    print_list(list, 1);
    print_list(list, 0);

    DoubleList_t* list2 = init_list();
    result = push_back(list2, 1);
    print_list(list2, 1);
    print_list(list2, 0);
    cleanup(&list2);
}