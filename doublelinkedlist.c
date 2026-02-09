#include <stdlib.h>
#include <stdio.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode_t;

// Well technically you can use 2 ptr raw and no need this data structure at all
// but that would require passing their reference into every function
// and update would still be the same, but package them like this would be so much nicer
typedef struct DoubleList {
    ListNode_t* head;
    ListNode_t* tail;
    size_t size;
} DoubleList_t;

typedef enum ErrorCode{
    SUCCESS,
    ERROR_LIST_NOT_EXIST,
    ERROR_LIST_INCONSISTENT_PTR,
    ERROR_LIST_IS_EMPTY,
    ERROR_HEAP_ALLOC_FAILED
} ErrorCode_t;

typedef enum Order{
    HEAD_TO_TAIL,
    TAIL_TO_HEAD,
} Order_t;

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
        // Existed
        list->tail->next = node; // previous tail should point to this new node
    } else {
        // First node in a list means we also need to point the head of list to this guy
        list->head = node;
    }
    list->tail = node;
    list->size++;

    return SUCCESS;
}

ErrorCode_t push_front(DoubleList_t* list, int value) {
    if (!list) return ERROR_LIST_NOT_EXIST;

    if (list->head && !(list->tail) || !(list->head) && list->tail) {
        return ERROR_LIST_INCONSISTENT_PTR;
    }

    ListNode_t* node = malloc(sizeof(ListNode_t));
    if (!node) return ERROR_HEAP_ALLOC_FAILED;

    node->value = value;
    node->prev = NULL;
    node->next = list->head;
    // Is this node the first node inserted to an empty list
    if (list->head) {
        // NO, meaning the previous head here must refer to our new node by prev ptr too
        list->head->prev = node;
    } else {
        // YES, we need to update the tail too
        list->tail = node;
    }
    list->head = node;
    list->size++;

    return SUCCESS;
}

int pop_front(DoubleList_t* list, ErrorCode_t* status_return) {
    int popped_val;
    ListNode_t* next_head = NULL;

    *status_return = SUCCESS; // default

    if (!list) {
        *status_return = ERROR_LIST_NOT_EXIST;
        return -1;
    }
    if (!(list->head) || !(list->tail) || list->size == 0) {
        *status_return = ERROR_LIST_IS_EMPTY;
        return -1;
    }

    popped_val = list->head->value;

    next_head = list->head->next; // save what is next after the head node
    free(list->head); // free the head node - pop it
    list->head = next_head; //assign the next one to be head now


    // 2 scenario, the next one (new/curr head) is NULL (popped one was only node) OR the next one is a ListNode
    if (list->head) {
        list->head->prev = NULL; //head node should have prev ptr to NULL
    } else {
        // the list is now empty, thus setting tail to null
        list->tail = NULL;
    }

    list->size--;
    return popped_val;
}

int pop_back(DoubleList_t* list, ErrorCode_t* status_return) {
    int popped_val;
    ListNode_t* next_tail = NULL;

    *status_return = SUCCESS;
    if(!list) {
        *status_return = ERROR_LIST_NOT_EXIST;
        return -1;
    }
    if(!(list->head) || !(list->tail) || list->size == 0) {
        *status_return = ERROR_LIST_IS_EMPTY;
        return -1;
    }

    popped_val = list->tail->value;

    next_tail = list->tail->prev;
    free(list->tail);
    list->tail = next_tail;

    // Either pop not the first node or pop the first node, 2 cases
    if (list->tail) {
        list->tail->next = NULL;
    } else {
        // list->tail NULL means the list also has 0 elements now, so I need to change the list head to
        list->head = NULL;
    }

    list->size--;
    return popped_val;
}

int peek_head(DoubleList_t* list, ErrorCode_t* status_return) {
    *status_return = SUCCESS;
    if (!list) {
        *status_return = ERROR_LIST_NOT_EXIST;
        return -1; // USER MUST CHECK
    }
    if (!(list->head)) {
        *status_return = ERROR_LIST_IS_EMPTY;
        return -1;
    }
    return list->head->value;
}

int peek_tail(DoubleList_t* list, ErrorCode_t* status_return) {
    *status_return = SUCCESS;
    if (!list) {
        *status_return = ERROR_LIST_NOT_EXIST;
        return -1; // USER must check outside
    }
    if(!(list->tail)) {
        *status_return = ERROR_LIST_IS_EMPTY;
        return -1;
    }
    return list->tail->value;
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

void print_list(DoubleList_t* list, Order_t print_order) {
    if(!list) return; // GUARD IMPORTANT, otherwise list->head might be attempted, invalid...

    ListNode_t* curr_node = NULL;
    if (print_order == HEAD_TO_TAIL) {
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
    print_list(list, HEAD_TO_TAIL);
    print_list(list, TAIL_TO_HEAD);
    cleanup(&list);
    print_list(list, HEAD_TO_TAIL);
    print_list(list, TAIL_TO_HEAD);

    int head_value;
    int tail_value;
    int popped_value;
    DoubleList_t* list2 = init_list();
    result = push_back(list2, 1);
    head_value = peek_head(list2, &result);
    if(result == SUCCESS) printf("HEAD: %d \n", head_value);
    tail_value = peek_tail(list2, &result);
    if(result == SUCCESS) printf("TAIL: %d \n", tail_value);
    result = push_back(list2, 2);
    print_list(list2, HEAD_TO_TAIL);
    print_list(list2, TAIL_TO_HEAD);
    head_value = peek_head(list2, &result);
    if(result == SUCCESS) printf("HEAD: %d \n", head_value);
    tail_value = peek_tail(list2, &result);
    if(result == SUCCESS) printf("TAIL: %d \n", tail_value);

    popped_value = pop_back(list2, &result);
    if(result == SUCCESS) printf("POPPED: %d \n", popped_value);
    print_list(list2, HEAD_TO_TAIL);
    print_list(list2, TAIL_TO_HEAD);
    popped_value = pop_back(list2, &result);
    if(result == SUCCESS) printf("POPPED: %d \n", popped_value);
    print_list(list2, HEAD_TO_TAIL);
    print_list(list2, TAIL_TO_HEAD);
    
    cleanup(&list2);

    DoubleList_t* list3 = init_list();
    result = push_front(list3, 1);
    head_value = peek_head(list3, &result);
    if(result == SUCCESS) printf("HEAD: %d \n", head_value);
    tail_value = peek_tail(list3, &result);
    if(result == SUCCESS) printf("TAIL: %d \n", tail_value);
    result = push_front(list3, 2);
    print_list(list3, HEAD_TO_TAIL);
    print_list(list3, TAIL_TO_HEAD);
    head_value = peek_head(list3, &result);
    if(result == SUCCESS) printf("HEAD: %d \n", head_value);
    tail_value = peek_tail(list3, &result);
    if(result == SUCCESS) printf("TAIL: %d \n", tail_value);

    popped_value = pop_front(list3, &result);
    if(result == SUCCESS) printf("POPPED: %d \n", popped_value);
    print_list(list3, HEAD_TO_TAIL);
    print_list(list3, TAIL_TO_HEAD);
    popped_value = pop_front(list3, &result);
    if(result == SUCCESS) printf("POPPED: %d \n", popped_value);
    print_list(list3, HEAD_TO_TAIL);
    print_list(list3, TAIL_TO_HEAD);

    cleanup(&list3);
}