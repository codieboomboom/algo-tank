#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct List List_t;

typedef enum ListError{
    LIST_SUCCESS,
    LIST_ERROR_NOT_IMPLEMENTED,
    LIST_ERROR_NOT_EXIST,
    LIST_ERROR_INCONSISTENT_PTR,
    LIST_ERROR_EMPTY,
    LIST_ERROR_ALLOC_FAILED
} ListError_t;

typedef enum Order{
    HEAD_TO_TAIL,
    TAIL_TO_HEAD,
} Order_t;

List_t *init_list(void);

List_t *create_list(const int* elements, size_t nmemb);

void clear_list(List_t* list);

void destroy_list(List_t** list);

int peek_front(const List_t* list, ListError_t* err_status);
int peek_back(const List_t* list, ListError_t* err_status);
size_t list_size(const List_t* list, ListError_t* err_status);

ListError_t push_back(List_t* list, int value);
ListError_t push_front(List_t* list, int value);

int pop_front(List_t* list, ListError_t* err_status);
int pop_back(List_t* list, ListError_t* err_status);

void print(const List_t* list, Order_t order);

#endif
