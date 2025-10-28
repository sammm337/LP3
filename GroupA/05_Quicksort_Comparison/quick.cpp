#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

void printArray(const vector<int>& arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortDeterministic(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortDeterministic(arr, low, pi - 1);
        quickSortDeterministic(arr, high, pi + 1);
    }
}

int partitionRandom(vector<int>& arr, int low, int high) {
    srand(time(NULL));
    int random = low + rand() % (high - low + 1);

    swap(arr[random], arr[high]);

    return partition(arr, low, high);
}

void quickSortRandomized(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionRandom(arr, low, high);
        quickSortRandomized(arr, low, pi - 1);
        quickSortRandomized(arr, high, pi + 1);
    }
}

int main() {
    vector<int> arr1 = {10, 7, 8, 9, 1, 5};
    vector<int> arr2 = arr1;

    cout << "Original array: ";
    printArray(arr1);

    cout << "\nSorting with Deterministic QuickSort...\n";
    quickSortDeterministic(arr1, 0, arr1.size() - 1);
    cout << "Sorted array: ";
    printArray(arr1);

    cout << "\nSorting with Randomized QuickSort...\n";
    quickSortRandomized(arr2, 0, arr2.size() - 1);
    cout << "Sorted array: ";
    printArray(arr2);
    
    vector<int> sortedArr = {1, 2, 3, 4, 5, 6, 7};
    cout << "\nTesting Deterministic on sorted array (worst case O(n^2)): ";
    quickSortDeterministic(sortedArr, 0, sortedArr.size() - 1);
    printArray(sortedArr);
    
    sortedArr = {1, 2, 3, 4, 5, 6, 7};
    cout << "Testing Randomized on sorted array (average case O(n log n)): ";
    quickSortRandomized(sortedArr, 0, sortedArr.size() - 1);
    printArray(sortedArr);

    return 0;
}
