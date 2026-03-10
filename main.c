#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int cmp_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/**
adaptive_stalin_sort - sort an array using the adaptive Stalin sort algorithm.
@arr:  input array of integers
@n:    number of elements in arr

Return: a pointer to a newly allocated sorted array (same length as arr).
The caller is responsible for freeing it. If n == 0, returns NULL.
*/
int* adaptive_stalin_sort(const int *arr, int n) {
    if (n <= 0)
        return NULL;

    // Allocate temporary storage (worst case we need space for all elements)
    int *ordered = malloc(n * sizeof(int));
    int *remaining = malloc(n * sizeof(int));
    if (!ordered || !remaining) {
        free(ordered);
        free(remaining);
        return NULL;  // allocation failure
    }

    // Phase 1: Stalin scan
    int ord_size = 0;
    int rem_size = 0;

    ordered[ord_size++] = arr[0];   // first element always kept

    for (int i = 1; i < n; i++) {
        if (arr[i] >= ordered[ord_size - 1]) {
            ordered[ord_size++] = arr[i];
        } else {
            remaining[rem_size++] = arr[i];
        }
    }

    // Phase 2: sort the remaining elements
    qsort(remaining, rem_size, sizeof(int), cmp_int);

    // Phase 3: merge the two sorted sequences
    int *result = malloc(n * sizeof(int));
    if (!result) {
        free(ordered);
        free(remaining);
        return NULL;
    }

    int i = 0, j = 0, k = 0;
    while (i < ord_size && j < rem_size) {
        if (ordered[i] <= remaining[j])
            result[k++] = ordered[i++];
        else
            result[k++] = remaining[j++];
    }

    // Copy any leftovers
    while (i < ord_size)
        result[k++] = ordered[i++];
    while (j < rem_size)
        result[k++] = remaining[j++];

    // Clean up temporary arrays
    free(ordered);
    free(remaining);

    return result;
}



// A simple test
int main() {
    int test_arrays[][12] = {
        {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {10, -5, 0, 3, -1, 7, 2},
        {}
    };
    int sizes[] = {11, 5, 5, 7, 0};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);

    for (int t = 0; t < num_tests; t++) {
        int n = sizes[t];
        printf("Original: ");
        for (int i = 0; i < n; i++)
            printf("%d ", test_arrays[t][i]);
        printf("\n");

        int *sorted = adaptive_stalin_sort(test_arrays[t], n);
        if (n == 0) {
            printf("Sorted: (empty)\n\n");
            continue;
        }
        if (!sorted) {
            printf("Sorting failed (allocation error).\n\n");
            continue;
        }

        printf("Sorted:   ");
        for (int i = 0; i < n; i++)
            printf("%d ", sorted[i]);
        printf("\n\n");

        free(sorted);
    }

    return 0;
}