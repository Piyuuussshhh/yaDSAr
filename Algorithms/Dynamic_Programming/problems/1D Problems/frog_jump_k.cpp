#include "../../headers/dp.h"

// ! QUESTION
/*
    Frog jump but the amount the frog can jump is k, ie, it is variable.
*/

// ! INTUITION
/*
    Same as before, one small modification.
    Since k is variable, we have to iterate from 1 to k to get all possible values of jump costs.

    * We store the value we get in a variable step, whose value will be the minimum of the calculated value
    * in this iteration and the most minimum value up until now.

    We also check that we don't access invalid indices.
*/

int minimizeCost(int n, int k, std::vector<int> &height){
    std::vector<int> dp(n, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        int step = INT_MAX;
        for (int j = 1; j <= k; j++) {
            // We check i - j >= 0 because it can lead to wrong indices. eg, i = 1, k = 3, so dp[1 - 2] is possible.
            if (i - j >= 0) {
                int cost_k = dp[i - j] + abs(height[i] - height[i - j]);
                step = std::min(step, cost_k);
            }
        }
        dp[i] = step;
    }

    return dp[n - 1];
}

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> heights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> heights[i];
    }

    Time start = Clock::now();

    std::cout << "Answer: " << minimizeCost(n, k, heights) << "\t";

    Time end = Clock::now();

    std::cout << "Time taken: " << time_taken(start, end) << std::endl;
}