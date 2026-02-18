#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct Stack Stack_t;

typedef enum StackError {
    STACK_SUCCESS,
    STACK_NOT_IMPLEMENTED,
    STACK_NOT_EXIST,
    STACK_EMPTY,
    STACK_ALLOC_FAILED
} StackError_t;

Stack_t init_stack(void);

void destroy_stack(Stack_t* stack, StackError_t* err);

int peek(const Stack_t* stack, StackError_t* err);

size_t get_size(const Stack_t* stack, StackError_t* err);

StackError_t push(Stack_t* stack, int value);

int pop(Stack_t* stack, StackError_t* err);

#endif
