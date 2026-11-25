#include <stdio.h>

// Selection sort implementation
void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int max = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[max])
                max = j;
        }
        if (max != i) {
            int temp = arr[max];
            arr[max] = arr[i];
            arr[i] = temp;
        }
    }
}

int main() {
    int arr[] = {1,5,6,75,8,9,10};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Calling selection sort on arr
    sort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    return 0;
}
