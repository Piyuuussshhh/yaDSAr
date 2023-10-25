#include "../../include/dp.h"

// ! Question.
/*
    Count the number of unique ways to reach the bottom right corner of a matrix_tMatrix_t from the top left corner.
    You can only move down or to the right.
    ie, [0, 0] to [m - 1, n - 1] for an MxN matrix_tMatrix_t.
*/

// ! Intuition.
/*
    In top down recursion approach, we move from the bottom right corner to the top left corner, and the directions in
    which we can move have also been reversed, now left and up.

    Base cases:
        -> if you reach the top left corner, you return 1 because you have reached the destination with a unique path.
        -> if you exceed the boundaries of the matrix_tMatrix_t, you return 0 because that is an invalid path.

    Now, initially, the recursion will first go upwards directly with no lefts until it goes out of bounds {where the fn returns 0},
    and then it keeps going left until it reaches the destination. The final fn call returns 1, and we keep returning until we reach the
    cell below the top right corner.

    Now, from here, we move left. Then we move up again, then keep moving left until we reach destination. This is another unique path.

    Therefore, like this, we keep finding unique paths.

    * In bottom up approach, if the previous row or previous column is used in computation, we can optimize
    * the space complexity of the solution.
*/

// TOP DOWN RECURSIVE APPROACH.
//? TIME COMPLEXITY: O(2^(m * n));      SPACE COMPLEXITY: O((m - 1) + (n - 1)) {Big O of path length.}
int count_paths_r(int row, int col) {
    if (row == 0 && col == 0) {
        return 1;
    }
    if (row < 0 || col < 0) {
        return 0;
    }

    int up = count_paths_r(row - 1, col);
    int left = count_paths_r(row, col - 1);

    return up + left;
}

// TOP DOWN MEMOIZATION APPROACH.
//? TIME COMPLEXITY: O(m * n);      SPACE COMPLEXITY: O((m - 1) + (n - 1)) + O(m * n) {Big O of path length + dp array}
int count_paths_td(int row, int col, Matrix_t& dp) {
    if (row == 0 && col == 0) {
        return 1;
    }
    if (row < 0 || col < 0) {
        return 0;
    }
    if (dp[row][col] != INIT_VAL) {
        return dp[row][col];
    }

    int up = count_paths_r(row - 1, col);
    int left = count_paths_r(row, col - 1);

    return dp[row][col] = up + left;
}

// BOTTOM UP TABULATION APPROACH.
//? TIME COMPLEXITY: O(m * n);      SPACE COMPLEXITY: O(m * n);
int count_paths_bu(int m, int n) {
    Matrix_t dp(m, std::vector<int>(n, INIT_VAL));

    dp[0][0] = 1;

    for (int row = 0; row < m; row++) {
        for (int col = 0; col < n; col++) {
            if (row == 0 && col == 0) continue;

            int up = 0, left = 0;
            if (row > 0) {
                up = dp[row - 1][col];
            }
            if (col > 0) {
                left = dp[row][col - 1];
            }

            dp[row][col] = up + left;
        }
    }

    // print_matrix_tMatrix_t(dp);

    return dp[m - 1][n - 1];
}

// OPTIMIZED BOTTOM UP TABULATION APPROACH.
//? TIME COMPLEXITY: O(m * n);      SPACE COMPLEXITY: O(n);
int opt_count_paths_bu(int m, int n) {
    std::vector<int> prev(n, 1);

    for (int row = 1; row < m; row++) {
        std::vector<int> temp(n, 0);
        for (int col = 0; col < n; col++) {
            if (row == 0 && col == 0) continue;

            int up = 0, left = 0;
            if (row > 0) {
                up = prev[col];
            }
            if (col > 0) {
                left = temp[col - 1];
            }

            temp[col] = up + left;
        }

        prev = temp;
    }

    return prev[n - 1];
}

// BEST SOLUTION: COMBINATORICS METHOD APPROACH.
//? TIME COMPLEXITY: O(m - 1) OR O(n - 1) => O(N);       SPACE COMPLEXITY: O(1)
int best_count_paths(int m, int n, bool is_row) {
    int x = m + n - 2;
    int r = 0;
    if (is_row) {
        r = m - 1;
    } else r = n - 1;

    double res = 1;

    for (int i = 1; i <= r; i++) {
        res = (res * (x - r + i)) / i;
    }

    return (int) res;
}

/*
 *  Observation 1:
    In any path:
        -> the number of rights you take is n - 1.
        -> the number of times you travel down is m - 1.
    Therefore, total number of cells in the path :=> (m - 1) + (n - 1)
                                                 :=> m + n - 2

 *  Observation 2:
    Let x = m + n - 2, and let r = m - 1 OR r = n - 1.
    Then the total number of unique paths is nothing but :=> wCr.

*/

int main() {
    int m, n;
    std::cin >> m >> n;

    // * ---------------------------------RECURSIVE APPROACH---------------------------------
    Time start_r = Clock::now();

    std::cout << "No. of unique paths: " << count_paths_r(m - 1, n - 1) << "\t";

    Time end_r = Clock::now();
    std::cout << "Time taken: " << time_taken(start_r, end_r) << "ms" << std::endl;
    // * ------------------------------END OF RECURSIVE APPROACH-----------------------------

    // * ---------------------------------MEMOIZATION APPROACH---------------------------------
    Time start_td = Clock::now();

    Matrix_t dp(m, std::vector<int>(n, INIT_VAL));
    std::cout << "No. of unique paths: " << count_paths_td(m - 1, n - 1, dp) << "\t";

    Time end_td = Clock::now();
    std::cout << "Time taken: " << time_taken(start_td, end_td) << "ms" << std::endl;
    // * -----------------------------END OF MEMOIZATION APPROACH------------------------------

    // * ---------------------------------TABULATION APPROACH---------------------------------
    Time start_bu = Clock::now();

    std::cout << "No. of unique paths: " << count_paths_bu(m, n) << "\t";

    Time end_bu = Clock::now();
    std::cout << "Time taken: " << time_taken(start_bu, end_bu) << "ms" << std::endl;
    // * -----------------------------END OF TABULATION APPROACH------------------------------

    // * ---------------------------------OPTIMIZED TABULATION APPROACH---------------------------------
    Time start_Obu = Clock::now();

    std::cout << "No. of unique paths: " << opt_count_paths_bu(m, n) << "\t";

    Time end_Obu = Clock::now();
    std::cout << "Time taken: " << time_taken(start_Obu, end_Obu) << "ms" << std::endl;
    // * -----------------------------END OF OPTIMIZED TABULATION APPROACH------------------------------
    // * ---------------------------------COMBINATORICS APPROACH---------------------------------

    char r;
    std::cout << "Calc via rows -> y; Calc via columns -> n: ";
    std::cin >> r;

    bool is_row;
    if (r == 'y') is_row = true;
    else is_row = false;

    Time start_b = Clock::now();

    std::cout << "No. of unique paths: " << best_count_paths(m, n, is_row) << "\t";

    Time end_b = Clock::now();
    std::cout << "Time taken: " << time_taken(start_b, end_b) << "ms" << std::endl;
    // * -----------------------------END OF COMBINATORICS APPROACH------------------------------

    std::cout << "Ignore the time taken by the combinatorics method. IDK why it's supposedly taking longer, but its time complexity IS O(N).\n";
}