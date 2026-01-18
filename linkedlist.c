#include <stdio.h>

typedef struct IntNode {
    int val;
    struct IntNode * next; // within the struct, no idea that IntNode_t is there yet
} IntNode_t;

void print_list(IntNode_t * head_ptr) {
    IntNode_t * curr_ptr = head_ptr;
    printf("List Nodes:");
    while (curr_ptr != NULL) {
        printf(" %d", curr_ptr->val);
        curr_ptr = curr_ptr->next;
    }
    printf("\n");
}

IntNode_t* reverse_list(IntNode_t* head) {
    return NULL;
}

// TODO: Is it common to just rely on the head_ptr as per previous?

void push_front(IntNode_t* head, int value) {
    return;
}

void push_back(IntNode_t* head, int value) {
    return;
}

int pop_back(IntNode_t* head) {
    return 0; // TODO
}

int pop_front(IntNode_t* head) {
    return 0;
}

int main() {
    IntNode_t node = {5, NULL};
    IntNode_t node2 = {10, NULL};
    IntNode_t node3 = {15, NULL};
    node.next = &node2;
    node2.next = &node3;
    IntNode_t *head = &node;
    print_list(head);

    IntNode_t * reversed = reverse_list(head);
    print_list(reversed);
}