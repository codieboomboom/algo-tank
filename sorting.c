#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// This version is so much headache...
// void insertion_sort(int* arr, size_t nmemb) {
//     if (nmemb < 2) {
//         // NO sorting needed
//         return;
//     }
//     // Iterate through each cards starting from the 2nd one
//     for (size_t key_idx = 1; key_idx < nmemb; key_idx++) {
//         size_t compare_idx = key_idx-1;
//         int key = arr[key_idx];
//         while (compare_idx >= 0 && key < arr[compare_idx]) {
//             // since key is less than this compare_idx element, we shift element to the right
//             // We do the shift from the left to the right (starting compare_idx from key_idx) so no need to worry about overwrite
//             arr[compare_idx+1] = arr[compare_idx];
//             compare_idx--;
//         }
//         arr[compare_idx+1] = key;
//     }
//     return;
// }

void insertion_sort(int* arr, size_t nmemb) {
    if (nmemb < 2) return;
    for (size_t key_idx = 1; key_idx < nmemb; key_idx++) {
        size_t insert_idx = key_idx;
        int key = arr[key_idx];
        // We test first before we lower, this ensure insert_idx will at most be 0 and never underflow
        while (insert_idx > 0 && key < arr[insert_idx-1]) {
            arr[insert_idx] = arr[insert_idx-1];
            insert_idx--;
        }
        arr[insert_idx] = key; // if insert_idx = 1 and the key less than arr[1-1] or arr[0], then insert_idx has updated to 0 so now we are safe...
    }
}

void insertion_sort2(int* arr, size_t nmemb) {
    if (nmemb > INT_MAX) {
        printf("This algo will not work for nmemb > INT_MAX, please use insertion_sort version instead!");
        return;
    }
    if (nmemb < 2) return;
    for (size_t key_idx=1; key_idx < nmemb; key_idx++) {
        int compare_idx = key_idx-1; // a bit painful...
        int key = arr[key_idx];
        while (compare_idx >=0 && key < arr[compare_idx]) {
            arr[compare_idx+1] = arr[compare_idx];
            compare_idx--;
        }
        arr[compare_idx+1] = key; // either compare_idx has already become negative (last iter above is when compare_idx=0) or the compare_idx is finally less than key, prompting us
        // to insert at compare_idx+1
    }
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
    insertion_sort2(arr3, arr3_len);
    print_array(arr3, arr3_len);
    bubble_sort(arr3, arr3_len);
    print_array(arr3, arr3_len);

    int arr4[] = {1};
    size_t arr4_len = sizeof(arr4)/sizeof(arr4[0]);
    bubble_sort(arr4, arr4_len);
    print_array(arr4, arr4_len);    
    return 0;
}