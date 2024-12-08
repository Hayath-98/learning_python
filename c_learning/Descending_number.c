#include <stdio.h>

// Function to perform Bubble Sort in descending order
void bubbleSortDescending(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        // Track if any swapping happened in the inner loop
        int swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            // Swap if the current element is smaller than the next element
            if (arr[j] < arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        // If no elements were swapped, the array is sorted
        if (swapped == 0)
            break;
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int m;
    printf("Enter size of elements");
    scanf("%d",&m);
    int arr[m];
    printf("Enter a number of elements");
    for(int i=0;i<m;i++)
    scanf("%d",&arr[i]);
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    bubbleSortDescending(arr, n);

    printf("Sorted array in descending order:\n");
    printArray(arr, n);

    return 0;
}
