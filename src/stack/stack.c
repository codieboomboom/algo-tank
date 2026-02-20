#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "stack.h"

struct Stack {
    List_t* internal_list; // underlying implementation is list
};

static StackError_t convert_list_err_to_stack_err(ListError_t err) {
    StackError_t stack_err;
    switch (err) {
        case LIST_SUCCESS:
            stack_err = STACK_SUCCESS;
            break;
        case LIST_ERROR_NOT_EXIST:
            stack_err = STACK_NOT_EXIST;
            break;
        case LIST_ERROR_EMPTY:
            stack_err = STACK_EMPTY;
            break;
        case LIST_ERROR_ALLOC_FAILED:
            stack_err = STACK_ALLOC_FAILED;
            break;
        default:
            stack_err = STACK_NOT_IMPLEMENTED;
            break;
    }

    return stack_err;
}

Stack_t* init_stack(void) {
    List_t* _list = init_list();
    if (!_list) return NULL;

    Stack_t* stack = calloc(1, sizeof(Stack_t));
    if (!stack) return NULL;

    stack->internal_list = _list;
    return stack;
}

void destroy_stack(Stack_t** stack) {
    if (!stack || !(*stack)) return;

    destroy_list(&((*stack)->internal_list));
    free(*stack);
    *stack = NULL;
}

int stack_peek(const Stack_t* stack, StackError_t* err) {
    *err = STACK_SUCCESS;
    if (!stack) {
        *err = STACK_NOT_EXIST;
        return -1;
    }

    ListError_t err_list;
    int value = peek_back(stack->internal_list, &err_list); // top of stack is at the back
    *err = convert_list_err_to_stack_err(err_list);
    return value;
}

size_t stack_size(const Stack_t* stack, StackError_t* err) {
    *err = STACK_SUCCESS;
    if (!stack) {
        *err = STACK_NOT_EXIST;
        return 0;
    }

    ListError_t err_list = LIST_SUCCESS;
    size_t nmemb = list_size(stack->internal_list, &err_list);
    *err = convert_list_err_to_stack_err(err_list);
    return nmemb;
}

StackError_t stack_push(Stack_t* stack, int value) {
    if (!stack) {
        return STACK_NOT_EXIST;
    }

    return convert_list_err_to_stack_err(push_back(stack->internal_list, value));
}

int stack_pop(Stack_t* stack, StackError_t* err){
    *err = STACK_SUCCESS;
    if (!stack) {
        *err = STACK_NOT_EXIST;
        return -1;
    }

    ListError_t err_list;
    int value = pop_back(stack->internal_list, &err_list); // top of stack is at the back
    *err = convert_list_err_to_stack_err(err_list);
    return value;
}