#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int* arr, size_t nmemb) {
    if (nmemb < 2) {
        // NO sorting needed
        return;
    }
    for (size_t key_idx = 1; key_idx <= nmemb-1; key_idx++) {
        int key = *(arr+key_idx);
        for (size_t pos_idx = key_idx; pos_idx >0; pos_idx--) {
            // Compare the key with each previous postion
            if (key < *(arr+pos_idx-1)) {
                *(arr+pos_idx) = *(arr+pos_idx-1);
            }
            else {
                *(arr+pos_idx) = key; // Dind't work
                break;
            }
        }
    }
    return;
}

void bubble_sort(int* arr, size_t nmemb) {
    if (nmemb < 2) return; // nothing to sort
    // Imagine bubble up until surface
    // If there are n-elements, we need max n-1 passes
    for (size_t offset_rightmost = 0; offset_rightmost < nmemb-1; offset_rightmost++) {
        // Each of the outer loop basically fix/stabilise 1 position on the rightmost of the array
        for (size_t idx = 0; idx < nmemb - offset_rightmost - 1; idx++) {
            // The index should exclude the position to be stabilized out (end before that)
            // as we need to refer 1 position in front as well
            if (*(arr+idx) > *(arr+idx+1)) {
                // swap
                int temp = *(arr+idx+1);
                *(arr+idx+1) = *(arr+idx);
                *(arr+idx) = temp;
            }
        }
    }

    return;
}

void print_array(int* arr, size_t nmemb) {
    printf("Array: ");
    for (size_t idx = 0; idx < nmemb; idx++) {
        printf("%d ", *(arr+idx));
    }
    printf("\n");
}

int main() {
    int arr[] = {-1,3,-2,1,2,10,5};
    size_t arr_len = sizeof(arr)/sizeof(arr[0]);
    insertion_sort(arr, arr_len);
    print_array(arr, arr_len);
    bubble_sort(arr, arr_len);
    print_array(arr, arr_len);

    // int arr2[] = NULL; // in standard C there is no such thing as empty array

    int arr3[] = {3, 2, 1};
    size_t arr3_len = sizeof(arr3)/sizeof(arr3[0]);
    bubble_sort(arr3, arr3_len);
    print_array(arr3, arr3_len);

    int arr4[] = {1};
    size_t arr4_len = sizeof(arr4)/sizeof(arr4[0]);
    bubble_sort(arr4, arr4_len);
    print_array(arr4, arr4_len);    
    return 0;
}