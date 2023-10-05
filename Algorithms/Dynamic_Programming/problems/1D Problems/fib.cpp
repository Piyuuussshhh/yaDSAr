#include "../../headers/dp.h"

// Top Down Approach, Recursion + Memoization.
int fib_dp_td(int n, std::vector<int>& dp) {
    if (n <= 1) return n;

    if (dp[n] != INT_MIN) return dp[n];

    return dp[n] = fib_dp_td(n - 1, dp) + fib_dp_td(n - 2, dp);
}

// Bottom Up Approach, Tabulation.
int fib_dp_bu(int n) {
    int prev2 = 0, prev1 = 1, current;

    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

int main() {
    int n;
    std::cout << "Enter which fibonacci number you want: ";
    std::cin >> n;

    // ! TOP DOWN APPROACH
    Time start_time_td = Clock::now();

    std::vector<int> dp(n + 1, INT_MIN);
    std::cout << "With Bottom-up approach: " << fib_dp_td(n, dp) << "\t";

    Time end_time_td = Clock::now();

    std::cout << "Time taken: " << time_taken(start_time_td, end_time_td) << std::endl;

    // ! BOTTOM UP APPROACH
    Time start_time_bu = Clock::now();

    std::cout << "With Bottom-up approach: " << fib_dp_bu(n) << "\t";

    Time end_time_bu = Clock::now();
    std::cout << "Time taken: " << time_taken(start_time_bu, end_time_bu) << std::endl;

    return 0;
}