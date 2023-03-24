#include "syscall.h"

#define MAXN (100)

// swap two elements in an array
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// bubble sort function with function pointer argument
void bubbleSort(int arr[], int n, int (*compare)(int, int)) {
    int i = 0, j = 0;
    int swapped = 0;
    
    for (i = 0; i < n - 1; ++i) {
        swapped = 0;
        
        for (j = 0; j < n - i - 1; ++j) {
            if (compare(arr[j], arr[j + 1])) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        }
    }
}

// comparison function for ascending order
int ascending(int a, int b) {
    return a > b;
}

// comparison function for descending order
int descending(int a, int b) {
    return a < b;
}

int main() {
    int n, arr[MAXN + 1], order, temp, i, j;
    do {
        PrintString("Enter n (0 <= n <= 100): ");
        n = ReadInt();
        if (n < 0 || n > 100) {
            PrintString("Please try again\n!");
        }
    } while (n < 0 || n > 100);

    for (i = 0; i < n; i++) {
        PrintString("Enter arr[");
        PrintInt(i);
        PrintString("]: ");

        arr[i] = ReadInt();
    }

    PrintString("\n");

    bubbleSort(arr, n, ascending);
    PrintString("Sorted array ascending: ");
    for (i = 0; i < n; i++) {
        PrintInt(arr[i]);
        PrintChar(' ');
    }

    PrintString("\n");

    bubbleSort(arr, n, descending);
    PrintString("Sorted array descending: ");
    for (i = 0; i < n; i++) {
        PrintInt(arr[i]);
        PrintChar(' ');
    }
}