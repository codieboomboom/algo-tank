#include <stdio.h>

typedef struct IntNode {
    int val;
    struct IntNode * next; // within the struct, no idea that IntNode_t is there yet
} IntNode_t;

void print_list(IntNode_t * head_ptr) {
    // Time complexity: O(n) as need to iterate once through a list of n elements
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
    // O(1) time as no need to iterate
    return;
}

void push_back(IntNode_t* head, int value) {
    // O(n) time
    return;
}

int pop_back(IntNode_t* head) {
    // O(n) time
    IntNode_t* curr = head;
    IntNode_t* prev = NULL;
    if (!head) return -1; // ERROR
    if (head && !head->next) {
        int val = head->val;
        head = NULL;
        return val;
    }
    // Keep moving until curr is the last node
    while (curr->next) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = NULL;
    return curr->val;
}

int pop_front(IntNode_t* head) {
    // O(1) time
    return 0;
}

void deduplicate_list(IntNode_t* head) {
    return;
}

IntNode_t* find_middle_node(IntNode_t* head) {
    
}

int main() {
    IntNode_t node = {5, NULL};
    IntNode_t node2 = {10, NULL};
    IntNode_t node3 = {15, NULL};
    IntNode_t node4 = {7, NULL};
    node.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    IntNode_t *head = &node;
    print_list(head);

    IntNode_t * reversed = reverse_list(head);
    print_list(reversed);

    int popped = pop_back(head);
    print_list(head);
    printf("%d\n", popped);

    int popped_again = pop_back(NULL);
    print_list(NULL);
    printf("%d\n", popped_again);

    // Segfault if pop &node4
    int poppidity_popped_again = pop_back(&node3);
    print_list(&node3);
    printf("%d\n", poppidity_popped_again);
}