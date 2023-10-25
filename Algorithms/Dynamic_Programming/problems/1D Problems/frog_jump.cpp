#include "../../include/dp.h"

// ! QUESTION
/*
    Frog on 1st step, wants to reach nth step.
        -> HEIGHT[i] is the height of the (i + 1)th stair, eg, HEIGHT[1] is the height of 2nd step from 1st step.
        -> Energy lost to jump from ith step to jth step is |HEIGHT[i] - HEIGHT[j]|.
        -> Can jump either 1 or 2 steps.

    Return minimum total energy required to reach nth stair.
*/

// ! INTUITION
/*
    * Cannot use greedy approach because we might miss out on the optimal solution.

    The energy taken to reach 1st (0th) step is 0.

    The minimum energy taken to reach the nth step will be:
        -> one_step = minimum energy taken to reach (n-1)th step + the energy to jump from there to nth step {abs(HEIGHT[n-1] - HEIGHT[n-2])}.
        -> two_steps = minimum energy taken to reach (n-2)th step + the energy to jump from there to nth step {abs(HEIGHT{n-1} - HEIGHT[n-3])}.
        -> min(one_step, two_steps).
*/

// Top down recursive approach.
int minimum_energy_r(int n, std::vector<int>& heights) {
    if (n == 0) return 0;

    int one_step = minimum_energy_r(n - 1, heights) + abs(heights[n] - heights[n - 1]);
    int two_steps = INT_MAX;
    if (n > 1) {
        two_steps = minimum_energy_r(n - 2, heights) + abs(heights[n] - heights[n - 2]);
    }

    return std::min(one_step, two_steps);
}

/*
    ! THE TRICK IS TO FIRST FIND THE RECURSIVE SOLUTION AND THEN CONVERT IT TO MEMOIZATION OR TABULATION SOLUTION.
*/

// Top down memoization approach.
int minimum_energy_td(int idx, std::vector<int>& heights, std::vector<int>& dp) {
    if (idx == 0) return 0;
    if (dp[idx] != INT_MAX) return dp[idx];

    int one_step = minimum_energy_td(idx - 1, heights, dp) + abs(heights[idx] - heights[idx - 1]);
    int two_steps = INT_MAX;
    if (idx > 1) {
        two_steps = minimum_energy_td(idx - 2, heights, dp) + abs(heights[idx] - heights[idx - 2]);
    }

    return dp[idx] = std::min(one_step, two_steps);
}

/*
    ! SOMETIMES TABULATION PREFERRED OVER MEMOIZATION AS THERE IS NO RECURSION.
*/

// Bottom up tabulation approach.
int minimum_energy_bu(int n, std::vector<int>& heights) {
    std::vector<int> dp(n, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        int one_step = dp[i - 1] + abs(heights[i] - heights[i - 1]);
        int two_step = INT_MAX;
        if (i > 1) {
            two_step = dp[i - 2] + abs(heights[i] - heights[i - 2]);
        }
        dp[i] = std::min(one_step, two_step);
    }

    return dp[n - 1];
}

/*
    ! BASICALLY WHAT IS HAPPENING ABOVE:

5th                           dp[i-2]+dp[i-1]=dp[i]
4th                   dp[i-2]+dp[i-1]=dp[i]
3rd           dp[i-2]+dp[i-1]=dp[i]
                 |      |     |
2nd   dp[i-2]+dp[i-1]=dp[i]   |
         |      |      |      |
1st   dp[i-1]=dp[i]    |      |
        |      |       |      |
?       0      1       2      3        4       5
        =========================================
        h[0]  h[1]    h[2]   h[3]     h[4]    h[5]
        -----------------------------------------
*       30    10      60     10       60      50
*/

// Optimized bottom up tabulation approach.
int minimum_energy_Obu(int n, std::vector<int>& heights) {
    int prev2 = 0, prev1, current;

    for (int i = 1; i <= n; i++) {
        int one_step = prev2 + abs(heights[i] - heights[i - 1]);
        int two_step = INT_MAX;
        if (i > 1) {
            two_step = prev1 + abs(heights[i] - heights[i - 2]);
        }
        current = std::min(one_step, two_step);
        prev1 = prev2;
        prev2 = current;
    }

    return prev2;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> heights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> heights[i];
    }

    // * ---------------------------------RECURSIVE APPROACH---------------------------------
    Time start_r = Clock::now();

    int step;
    std::cin >> step;
    if (step >= n) {
        return 0;
    }
    std::cout << "Minimum energy required to reach " << step + 1 << "th step: " << minimum_energy_r(step, heights) << "\t";

    Time end_r = Clock::now();
    std::cout << "Time taken: " << time_taken(start_r, end_r) << "ms" << std::endl;
    // * ------------------------------END OF RECURSIVE APPROACH-----------------------------

    // * ---------------------------------MEMOIZATION APPROACH---------------------------------
    Time start_td = Clock::now();

    std::vector<int> dp(n + 1, INT_MAX);
    std::cout << "Minimum energy required to reach " << step + 1 << "th step: " << minimum_energy_td(step, heights, dp) << "\t";

    Time end_td = Clock::now();
    std::cout << "Time taken: " << time_taken(start_td, end_td) << "ms" << std::endl;
    // * -----------------------------END OF MEMOIZATION APPROACH------------------------------

    // * ---------------------------------TABULATION APPROACH---------------------------------
    Time start_bu = Clock::now();

    std::cout << "Minimum energy required to reach " << step + 1 << "th step: " << minimum_energy_bu(step, heights) << "\t";

    Time end_bu = Clock::now();
    std::cout << "Time taken: " << time_taken(start_bu, end_bu) << "ms" << std::endl;
    // * -----------------------------END OF TABULATION APPROACH------------------------------

    // * ---------------------------------OPTIMIZED TABULATION APPROACH---------------------------------
    Time start_Obu = Clock::now();

    std::cout << "Minimum energy required to reach " << step + 1 << "th step: " << minimum_energy_Obu(step, heights) << "\t";

    Time end_Obu = Clock::now();
    std::cout << "Time taken: " << time_taken(start_Obu, end_Obu) << "ms" << std::endl;
    // * -----------------------------END OF OPTIMIZED TABULATION APPROACH------------------------------
}