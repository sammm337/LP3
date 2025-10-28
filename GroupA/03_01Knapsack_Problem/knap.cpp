#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int knapsackDP(int W, const vector<int> & wt, const vector<int> & val, int n) {
    vector<vector<int> > dp(n + 1, vector<int>(W + 1));

    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (wt[i - 1] <= w) {
                dp[i][w] = max(
                    val[i - 1] + dp[i - 1][w - wt[i - 1]],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];
}

int main() {
    vector<int> val = {60, 100, 120};
    vector<int> wt = {10, 20, 30};
    int W = 50;
    int n = val.size();

    cout << "Knapsack Capacity: " << W << endl;
    cout << "Items (Value, Weight):" << endl;
    for(int i = 0; i < n; ++i) {
        cout << "  (" << val[i] << ", " << wt[i] << ")" << endl;
    }

    int maxValue = knapsackDP(W, wt, val, n);
    cout << "\nMaximum value in knapsack: " << maxValue << endl;

    return 0;
}
