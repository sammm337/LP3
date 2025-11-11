#include <iostream>
#include <vector>
using namespace std;

// Function to solve 0-1 Knapsack using Dynamic Programming
int knapsack(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for(int i = 1; i <= n; i ++){
        for(int w = 1; w <= W; w ++){
            if(wt[i - 1] <= w){
                dp[i][w] = max(dp[i - 1][w - wt[i - 1]] + val[i - 1] , dp[i - 1][w]);
            }else{
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[n][W];
}

int main() {
    int n = 4;                            // number of items
    vector<int> val = {10, 40, 30, 50};   // values of items
    vector<int> wt  = {5, 4, 6, 3};       // weights of items
    int W = 10;                           // maximum weight capacity

    cout << "Maximum value in Knapsack = "
         << knapsack(W, wt, val, n) << endl;

    return 0;
}
