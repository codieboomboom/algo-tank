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
    return NULL; //TODO
}

void cleanup(DoubleList_t* list);