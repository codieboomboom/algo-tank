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
    if (!head || !(head->next)) {
        // NULL ptr passed in or single node only
        // No work to be done
        return head;
    }

    // Otherwise
    IntNode_t* curr = head;
    IntNode_t* prev = NULL;
    IntNode_t* next = NULL;

    while(curr) {
        // Save the current's next node first
        next = curr->next;
        // The current's next node should point to previous node (to reverse)
        curr->next = prev;
        // Move the prev node on to curr node as well
        prev = curr;
        // Move on (fwd direction)
        curr = next;
    }

    return prev; // as curr would now be NULL
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

int pop_back(IntNode_t** head) {
    // The double pointer is used instead of single pointer because for single pointer
    // the local copy of it does not propagate outside of this function
    // O(n) time
    if (!head || !(*head)) return -1; // ERROR: the head ptr should not be NULL and ptr to head ptr too shall not be null
    
    IntNode_t* curr = *head;
    IntNode_t* prev = NULL;

    if (curr && !curr->next) {
        // Only 1 element
        *head = NULL;
        return curr->val;
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
    // First LL
    IntNode_t *head = &node;
    print_list(head);
    // Second LL
    IntNode_t* head2 = &node4;
    print_list(head2);
    // LL that is null
    IntNode_t* head3 = NULL;
    print_list(head3);

    IntNode_t * reversed = reverse_list(head);
    print_list(reversed);

    int popped = pop_back(&head);
    print_list(head);
    printf("%d\n", popped);

    printf("\n\n");
    print_list(head2);
    int poppidity_popped_again = pop_back(&head2);
    print_list(head2);
    printf("%d\n", poppidity_popped_again);

    printf("\n\n");
    int popped_again = pop_back(&head3); // why cannot pop_back(NULL)? In fact does NULL address means anything?
    print_list(head3);
    printf("%d\n", popped_again);

    printf("\n\n");
    int popped_again_NULL = pop_back(NULL);
    printf("%d\n", popped_again_NULL);
}