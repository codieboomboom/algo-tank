#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct Stack Stack_t;

typedef enum StackError {
    STACK_SUCCESS,
    STACK_NOT_IMPLEMENTED,
    STACK_NOT_EXIST,
    STACK_EMPTY,
    STACK_ALLOC_FAILED,
    STACK_BAD_FORMAT,
} StackError_t;

Stack_t* init_stack(void);

void destroy_stack(Stack_t** stack);

int stack_peek(const Stack_t* stack, StackError_t* err);

size_t stack_size(const Stack_t* stack, StackError_t* err);

StackError_t stack_push(Stack_t* stack, int value);

int stack_pop(Stack_t* stack, StackError_t* err);

#endif
