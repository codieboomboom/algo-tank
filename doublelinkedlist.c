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

DoubleList_t* create_list(int* elements, size_t nmemb) {
    if (!nmemb) return NULL; //empty
    DoubleList_t* list = malloc(sizeof(DoubleList_t));
    if(!list) return NULL;
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

void cleanup(DoubleList_t** list){
    if (!list || !(*list)) return; // nothing to do here

    // Go through list from any direction, prefered from head
    ListNode_t* curr_node = (*list)->head;
    ListNode_t* next = NULL;
    while (curr_node) {
        printf("%d\n", curr_node->value);
        next = curr_node->next;
        free(curr_node);
        curr_node = next;
    }

    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->size = 0;
    *list = NULL;
    return;
}

void print_list(DoubleList_t* list, int head_to_tail) {
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
    int arr[5] = {4, 2, 3, 6, 8};
    DoubleList_t* list = create_list(arr, sizeof(arr)/sizeof(arr[0]));
    print_list(list, 1);
    print_list(list, 0);
    cleanup(&list);
    print_list(list, 1);
    print_list(list, 0);
}