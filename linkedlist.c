#include <stdio.h>
#include <stdlib.h>

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

int push_front(IntNode_t** head, int value) {
    // O(1) time as no need to iterate
    // Does not make sense to have a nullptr for the ptr to headptr, considered as error
    if (!head) return -1;
    // Create a new node with the value
    IntNode_t* ptr_to_inserted_node = malloc(sizeof(IntNode_t));
    if (!ptr_to_inserted_node) return -1; // failure if not able to allocate more
    ptr_to_inserted_node->val = value;
    ptr_to_inserted_node->next = *head;
    *head = ptr_to_inserted_node; 
    return 0;
}

int push_back(IntNode_t** head, int value) {
    // Throw error because should at least have ptr to head
    if (!head) return -1;
    // If list is empty, simply push and return
    if (!(*head)) {
        IntNode_t* first_node = malloc(sizeof(IntNode_t));
        if (!first_node) return -1;
        first_node->val = value;
        first_node->next = NULL;
        *head = first_node;
        return 0;
    }
    // Otherwise: iterate till the end O(n) in worst case
    IntNode_t* curr = *head;
    while(curr->next) {
        curr = curr->next;
    }
    // Curr->next should be where to inject the new node
    IntNode_t *new_node = malloc(sizeof(IntNode_t));
    if (!new_node) return -1;
    new_node->val = value;
    new_node->next = curr->next;
    curr->next = new_node;
    
    return 0;
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

int pop_front(IntNode_t** head) {
    // O(1) time
    if (!head || !(*head)) return -1; // error if you supplement a null ptr or a ptr to null (cannot pop empty)

    IntNode_t* curr = *head;
    (*head) = curr->next; // the *head is a ptr to the next node or NULL (for single linkedlist) after pop
    // and we return the current node value now

    return curr->val;
}

void deduplicate_list(IntNode_t* head) {
    return;
}

IntNode_t* find_middle_node(IntNode_t* head) {
    
}

int cleanup_list(IntNode_t** head) {
    if (!head) return -1; // not a proper list to cleanup
    IntNode_t * curr = *head;
    IntNode_t * next;
    while(curr) {
        next = curr->next; // save next node
        free(curr);
        curr = next;
    }
    *head = NULL;
    return 0;
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

    printf("=====POP BACK TEST===============\n");
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

    printf("========POP FRONT TEST============\n");
    printf("POP NULL: \n");
    int pop_null = pop_front(NULL);
    printf("%d\n", pop_null);
    printf("POP PTR to NULL\n");
    IntNode_t * ptr_to_null = NULL;
    int pop_null2 = pop_front(NULL);
    printf("%d\n", pop_null2);
    printf("POP SINGLE NODE LIST\n");
    IntNode_t node_single = {20, NULL};
    IntNode_t *head_single = &node_single;
    print_list(head_single);
    int pop_single_front = pop_front(&head_single);
    printf("%d\n", pop_single_front);
    print_list(head_single);
    printf("POP A NORMAL LIST\n");
    print_list(head2);
    int pop_front_head = pop_front(&head2);
    printf("%d\n", pop_front_head);
    print_list(head2);

    printf("======PUSH FRONT=========\n");
    IntNode_t * listhead = NULL;
    print_list(listhead);
    push_back(&listhead, 3);
    push_front(&listhead, 1);
    push_back(&listhead, 2);
    print_list(listhead);
    int cleanup_result = cleanup_list(&listhead);
    print_list(listhead);
}