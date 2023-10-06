#include "../../headers/dp.h"

// ! QUESTION.
/*
    You have a Nx3 matrix. You have to sum an element from each row such that two adjacent rows' selected elements
    don't belong to the same column, and return the maximum sum.
    eg. Matrix = [
        [1, 2, 5],
        [3, 1, 1],
        [3, 3, 3],
    ]
    * The maximum sum will be 5 + 3 + 3 = 11 {[0, 2] + [1, 0] + ([2, 1] or [2, 2])}.
*/

// ! INTUITION
/*
 !  ANALOGY TO NINJA JUMPING: COLUMNS ARE ACTIVITIES, ROWS ARE DAYS.
 *  Intuition of the recursion:
        -> Let's start from last row. Here we can pick any column, we have three choices. Hence the for loop.
        -> We could've taken the largest element in this row, but that's greedy approach, it doesn't always work.

        -> The total points we earn on this day would be the 2 available choices plus the points earned until now.
        -> Since we are at the last row, we pass the column we chose and calculate from there.

 ?      Base case:
        -> Once we reach the first row, we can find the maximum element excluding the element in the column from last row.
        -> Then we return that max element to the previous call, where the merit points earned is calculated for that row.
        -> Once this is done for both available choices, we take the maximum value from them and return it to the previous call.

 *  Intuition for memoization:
        -> We create a N*4 matrix dp {N rows, 4 columns because you have 3 original columns plus the initial column value} // ! WHAT DO ITS FINAL VALUES SIGNIFY??
        -> For every maximum point value we get, we store it in the [row][last_column] index.
*/


#define ACTIVITIES_PLUS_INIT                 4

// TOP DOWN RECURSION APPROACH.
int max_points_r(
    int row,
    int last_column,
    Matrix& points
) {
    if (row == 0) {
        int max_points = INT_MIN;
        for (int i = 0; i < 3; i++) {
            if (i != last_column) {
                max_points = max_points > points[0][i] ? max_points : points[0][i];
            }
        }
        return max_points;
    }

    int max_points = INT_MIN;
    for (int col = 0; col < 3; col++) {
        if (col != last_column) {
            int merit = points[row][col] + max_points_r(row - 1, col, points);
            max_points = max_points > merit ? max_points : merit;
        }
    }

    return max_points;
}

// TOP DOWN MEMOIZATION APPROACH.
//? TIME COMPLEXITY: O((4 * N) * 3) ~ O(N);     SPACE COMPLEXITY: O(4 * N) + O(N).
int max_points_td(
    int row,
    int last_column,
    Matrix& points,
    Matrix& dp
) {
    if (row == 0) {
        int max_points = INT_MIN;
        for (int i = 0; i < 3; i++) {
            if (i != last_column) {
                max_points = max_points > points[0][i] ? max_points : points[0][i];
            }
        }
        return dp[row][last_column] = max_points;
    }
    if (dp[row][last_column] != -1 && last_column != INIT_VAL) {
        return dp[row][last_column];
    }

    int max_points = INT_MIN;
    for (int col = 0; col < 3; col++) {
        if (col != last_column) {
            int merit = points[row][col] + max_points_r(row - 1, col, points);
            max_points = max_points > merit ? max_points : merit;
        }
    }

    return dp[row][last_column] = max_points;
}

// BOTTOM UP TABULATION APPROACH.
//? TIME COMPLEXITY: O((4 * N) * 3) >> O(N);     SPACE COMPLEXITY: O(4 * N) >> O(N).
int max_points_bu(Matrix& points) {
    Matrix dp(points.size(), std::vector<int>(4, -1));

    dp[0][0] = std::max(points[0][1], points[0][2]);
    dp[0][1] = std::max(points[0][0], points[0][2]);
    dp[0][2] = std::max(points[0][0], points[0][1]);
    dp[0][3] = std::max(points[0][0], std::max(points[0][1], points[0][2]));

    for (int row = 1; row < points.size(); row++) {
        for (int last_column = 0; last_column < 4; last_column++) {
            dp[row][last_column] = 0;
            for (int col = 0; col < 3; col++) {
                if (last_column != col) {
                    int merit = points[row][col] + dp[row - 1][col];
                    dp[row][last_column] = std::max(dp[row][last_column], merit);
                }
            }
        }
    }

    print_matrix(dp);

    return dp[points.size() - 1][3];
}

// OPTIMIZED BOTTOM UP TABULATION APPROACH.
//? TIME COMPLEXITY: O((4 * N) * 3) >> O(N);     SPACE COMPLEXITY: O(4) >> O(N).
int opt_max_points_bu(Matrix& points) {
    std::vector<int> prev_row(4, -1);

    prev_row[0] = std::max(points[0][1], points[0][2]);
    prev_row[1] = std::max(points[0][0], points[0][2]);
    prev_row[2] = std::max(points[0][0], points[0][1]);
    prev_row[3] = std::max(points[0][0], std::max(points[0][1], points[0][2]));

    for (int row = 1; row < points.size(); row++) {
        std::vector<int> temp(4, 0);
        for (int last_column = 0; last_column < 4; last_column++) {
            temp[last_column] = 0;
            for (int col = 0; col < 3; col++) {
                if (last_column != col) {
                    int merit = points[row][col] + prev_row[col];
                    temp[last_column] = std::max(temp[last_column], merit);
                }
            }
        }
        prev_row = temp;
    }

    return prev_row[3];
}

int main() {
    int n;
    std::cin >> n;

    Matrix points(n, std::vector<int>(3));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            std::cin >> points[i][j];
        }
    }

    // * ---------------------------------RECURSIVE APPROACH---------------------------------
    Time start_r = Clock::now();

    std::cout << "Max merit points: " << max_points_r(points.size() - 1, INIT_VAL, points) << "\t";

    Time end_r = Clock::now();
    std::cout << "Time taken: " << time_taken(start_r, end_r) << "ms" << std::endl;
    // * ------------------------------END OF RECURSIVE APPROACH-----------------------------

    // * ---------------------------------MEMOIZATION APPROACH---------------------------------
    Time start_td = Clock::now();

    Matrix dp(n, std::vector<int>(ACTIVITIES_PLUS_INIT, -1));
    std::cout << "Max merit points: " << max_points_td(points.size() - 1, INIT_VAL, points, dp) << "\t";

    Time end_td = Clock::now();
    std::cout << "Time taken: " << time_taken(start_td, end_td) << "ms" << std::endl;
    // * -----------------------------END OF MEMOIZATION APPROACH------------------------------

    // * ---------------------------------TABULATION APPROACH---------------------------------
    Time start_bu = Clock::now();

    std::cout << "Max merit points: " << max_points_bu(points) << "\t";

    Time end_bu = Clock::now();
    std::cout << "Time taken: " << time_taken(start_bu, end_bu) << "ms" << std::endl;
    // * -----------------------------END OF TABULATION APPROACH------------------------------

    // * ---------------------------------OPTIMIZED TABULATION APPROACH---------------------------------
    Time start_Obu = Clock::now();

    std::cout << "Max merit points: " << opt_max_points_bu(points) << "\t";

    Time end_Obu = Clock::now();
    std::cout << "Time taken: " << time_taken(start_Obu, end_Obu) << "ms" << std::endl;
    // * -----------------------------END OF OPTIMIZED TABULATION APPROACH------------------------------
}