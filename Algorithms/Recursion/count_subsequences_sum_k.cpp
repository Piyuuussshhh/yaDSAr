// IO Functionality
#include <iostream>
// For INT_MAX INT_MIN
#include <limits.h>
// For max(), min(), abs()
#include <algorithm>
// For accumulate()
#include <numeric>
// For std::find()
#include <utility>

// Common STL Containers
#include <vector>
#include <stack>
#include <queue>
#include <map>

// ! QUESTION.
/*
    Return the total number of subsequences in arr[] that sum to k.
*/

/*
?   BASIC RECURSIVE BLUEPRINT FOR COUNTING SOLUTIONS:
    int f() {
        if (base_case) {
            return 1;
        }

        int l = f();
        int r = f();

        return l + r;
    }
*/

int count_subsequences_k(
    int idx,
    std::vector<int>& arr,
    int k,
    int sum
) {
    if (idx == arr.size()) {
        if (sum == k) {
            return 1;
        }
        return 0;
    }

    sum += arr[idx];
    int take = count_subsequences_k(idx + 1, arr, k, sum);

    sum -= arr[idx];
    int not_take = count_subsequences_k(idx + 1, arr, k, sum);

    return take + not_take;
}

int main() {
    std::vector<int> arr = {1, 2, 1};
    int k = 2;

    std::cout << count_subsequences_k(0, arr, k, 0) << std::endl;

    return 0;
}