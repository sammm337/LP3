#include <iostream>
#include <vector>

using namespace std;

long long fibRecursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

long long fibIterative(int n) {
    if (n <= 1) {
        return n;
    }

    long long a = 0;
    long long b = 1;
    long long temp;

    for (int i = 2; i <= n; ++i) {
        temp = a + b;
        a = b;
        b = temp;
    }

    return b;
}

int main() {
    int n = 10;

    cout << "Calculating Fibonacci for n = " << n << endl;
    cout << "Iterative (O(n)) result: " << fibIterative(n) << endl;
    cout << "Recursive (O(2^n)) result: " << fibRecursive(n) << endl;

    n = 40;
    cout << "\nCalculating Fibonacci for n = " << n << endl;
    cout << "Iterative (O(n)) result: " << fibIterative(n) << endl;
    cout << "Calculating recursive (O(2^n)) for n=40... (this will take time)" << endl;
    cout << "Recursive (O(2^n)) result: " << fibRecursive(n) << endl;

    return 0;
}
