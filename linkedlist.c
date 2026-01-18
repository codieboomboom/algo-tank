#include <stdio.h>

typedef struct IntNode {
    int val;
    struct IntNode * next;
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

int main() {
    IntNode_t node = {5, NULL};
    IntNode_t node2 = {10, NULL};
    IntNode_t node3 = {15, NULL};
    node.next = &node2;
    node2.next = &node3;
    print_list(&node);
}