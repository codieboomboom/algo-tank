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

List_t *init_list();

List_t *create_list(int* elements, size_t nmemb);

void clear_list(List_t* list);

void destroy_list(List_t** list);

int peek_front(List_t* list, ErrorCode_t* err_status);
int peek_back(List_t* list, ErrorCode_t* err_status);
size_t get_size(List_t* list, ErrorCode_t* err_status);

ErrorCode_t push_back(List_t* list, int value);
ErrorCode_t push_front(List_t* list, int value);

int pop_front(List_t* list, ErrorCode_t* err_status);
int pop_back(List_t* list, ErrorCode_t* err_status);

void print(List_t* list, Order_t order);