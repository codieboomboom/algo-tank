#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct List List_t;

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

List_t *init_list();

List_t *create_list(int* elems, size_t nmemb);

void clear_list(List_t* list);

void destroy_list(List_t** list);

int peek_front(List_t* list, ErrorCode_t* err_status);
int peek_back(List_t* list, ErrorCode_t* err_status);
size_t get_size(List_t* list, ErrorCode_t* err_status);

ErrorCode_t push_back(List_t* list, int value);
ErrorCode_t push_front(List_t* list, int value);

int pop_front(List_t* list, ErrorCode_t* err_return);
int pop_back(List_t* list, ErrorCode_t* err_return);

void print(List_t* list, Order_t Order);

#endif