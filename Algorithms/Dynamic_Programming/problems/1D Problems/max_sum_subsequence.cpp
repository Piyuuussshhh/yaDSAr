#include "../../include/dp.h"

// ! QUESTION.
/*
    Return the maximum sum out of all subsequences in array such that no two elements in the subsequence
    are adjacent in the original array.
*/

// TOP DOWN RECURSION APPROACH.
// ? TIME COMPLEXITY: O(2^N), SPACE COMPLEXITY: O(N)
int max_sum_of_subs_r(int idx, std::vector<int>& arr) {
    if (arr.size() == 0) return 0;
    if (idx < 0) {
        return 0;
    }
    if (idx == 0) {
        return arr[idx];
    }

    int take = arr[idx] + max_sum_of_subs_r(idx - 2, arr);
    int not_take = 0 + max_sum_of_subs_r(idx - 1, arr);

    return std::max(take, not_take);
}

// TOP DOWN MEMOIZATION APPROACH.
// ? TIME COMPLEXITY: O(N), SPACE COMPLEXITY: O(N) + O(N)
int max_sum_subs_td(int idx, std::vector<int>& arr, std::vector<int>& dp) {
    if (arr.size() == 0) return 0;
    if (idx < 0) {
        return 0;
    }
    if (idx == 0) {
        return arr[idx];
    }
    if (dp[idx] != -1) {
        return dp[idx];
    }

    int take = arr[idx] + max_sum_subs_td(idx - 2, arr, dp);
    int not_take = 0 + max_sum_subs_td(idx - 1, arr, dp);

    return dp[idx] = std::max(take, not_take);
}

// BOTTOM UP TABULATION APPROACH.
// ? TIME COMPLEXITY: O(N), SPACE COMPLEXITY: O(N)
int max_sum_subs_bu(std::vector<int>& arr) {
    if (arr.size() == 0) return 0;
    std::vector<int> dp(arr.size(), -1);
    dp[0] = arr[0];

    for (int i = 1; i < arr.size(); i++) {
        int take = arr[i];
        if (i > 1) {
            take += dp[i - 2];
        }
        int not_take = 0 + dp[i - 1];

        dp[i] = std::max(take, not_take);
    }

    return dp[dp.size() - 1];
}

// BOTTOM UP TABULATION APPROACH OPTIMIZED.
// ? TIME COMPLEXITY: O(N), SPACE COMPLEXITY: O(1)
int opt_max_sum_subs_bu(std::vector<int>& arr) {
    if (arr.size() == 0) return 0;
    int prev2 = 0, prev = arr[0], current;

    for (int i = 1; i < arr.size(); i++) {
        int take = arr[i];
        if (i > 1) {
            take += prev2;
        }
        int not_take = 0 + prev;

        current = std::max(take, not_take);

        prev2 = prev;
        prev = current;
    }

    return prev;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    // * ---------------------------------RECURSIVE APPROACH---------------------------------
    Time start_r = Clock::now();

    std::cout << "Max sum: " << max_sum_of_subs_r(arr.size() - 1, arr) << "\t";

    Time end_r = Clock::now();
    std::cout << "Time taken: " << time_taken(start_r, end_r) << "ms" << std::endl;
    // * ------------------------------END OF RECURSIVE APPROACH-----------------------------

    // * ---------------------------------MEMOIZATION APPROACH---------------------------------
    Time start_td = Clock::now();

    std::vector<int> dp(n, -1);
    std::cout << "Max sum: " << max_sum_subs_td(arr.size() - 1, arr, dp) << "\t";

    Time end_td = Clock::now();
    std::cout << "Time taken: " << time_taken(start_td, end_td) << "ms" << std::endl;
    // * -----------------------------END OF MEMOIZATION APPROACH------------------------------

    // * ---------------------------------TABULATION APPROACH---------------------------------
    Time start_bu = Clock::now();

    std::cout << "Max sum: " << max_sum_subs_bu(arr) << "\t";

    Time end_bu = Clock::now();
    std::cout << "Time taken: " << time_taken(start_bu, end_bu) << "ms" << std::endl;
    // * -----------------------------END OF TABULATION APPROACH------------------------------

    // * ---------------------------------OPTIMIZED TABULATION APPROACH---------------------------------
    Time start_Obu = Clock::now();

    std::cout << "Max sum: " << opt_max_sum_subs_bu(arr) << "\t";

    Time end_Obu = Clock::now();
    std::cout << "Time taken: " << time_taken(start_Obu, end_Obu) << "ms" << std::endl;
    // * -----------------------------END OF OPTIMIZED TABULATION APPROACH------------------------------
}