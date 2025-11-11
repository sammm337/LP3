#include <iostream>
#include <cstdlib> 
#include <ctime>   
using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // deterministic pivot (last element)
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Deterministic Quick Sort
void quickSortDeterministic(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortDeterministic(arr, low, pi - 1);
        quickSortDeterministic(arr, pi + 1, high);
    }
}

// Randomized Partition
int randomizedPartition(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]); 
    return partition(arr, low, high);
}

// Randomized Quick Sort
void quickSortRandomized(int arr[], int low, int high) {
    if (low < high) {
        int pi = randomizedPartition(arr, low, high);
        quickSortRandomized(arr, low, pi - 1);
        quickSortRandomized(arr, pi + 1, high);
    }
}

// Utility to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    srand(time(0)); // seed for randomness

    int arr1[] = {11, 7, 7, 9, 1, 5};
    int arr2[] = {10, 7, 5, 9, 1, 5};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    cout << "Original Array: ";
    printArray(arr1, n);

    quickSortDeterministic(arr1, 0, n - 1);
    cout << "\nAfter Deterministic Quick Sort: ";
    printArray(arr1, n);

    quickSortRandomized(arr2, 0, n - 1);
    cout << "\nAfter Randomized Quick Sort: ";
    printArray(arr2, n);

    return 0;
}
