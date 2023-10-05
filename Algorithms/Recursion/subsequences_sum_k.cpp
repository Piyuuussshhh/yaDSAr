// IO Functionality
#include <iostream>
// For INT_MAX INT_MIN
#include <limits.h>
// For max(), min(), abs()
#include <algorithm>
// For accumulate().
#include <numeric>
// For std::find()
#include <utility>

// Common STL Containers
#include <vector>
#include <stack>
#include <queue>
#include <map>

// ! QUESTION
/*
    Print all the subsequences of an array which sum up to k.
*/

/*
    arr = [1, 2, 1]; k = 3.
    First call, sum = 1, idx = 0, vec = [1].
    Second call, sum = 3, idx = 1, vec = [1, 2].
    Third call, sum == k, therefore [1, 2] printed, return to second call.
    Continuing second call, vec = [1] {vec.pop_back() removes 2}.
    Third call, sum = 1, idx = 2, vec = [1, 1].
    Fourth call, idx == arr.size(), we return to third call, then second call, then first call.
    Continuing first call, sum = 0, idx = 0, vec = []. {vec.pop_back() removes 1}.
    Second call

*/

void print_array(std::vector<int>& vec) {
    if (vec.empty()) {
        std::cout << "{}";
        return;
    }
    for (int i = 0; i < vec.size(); i++) {
        if (i == vec.size() - 1) {
            std::cout << vec[i];
        } else {
            std::cout << vec[i] << ", ";
        }
    }
}

void print_subs_k(
    int idx,                // The index of element we want to take or not take in subsequence.
    std::vector<int>& vec,  // Subsequence array.
    std::vector<int>& arr,  // Original array.
    int k,                  // Target Sum.
    int sum                 // Calculated sum in each recursive call.
) {
    if (idx == arr.size()) {
        if (sum == k) {
            std::cout << "Answer = {"; print_array(vec); std::cout << "}" << std::endl;
        }
        return;
    }
    // Optimization.
    if (sum > k) {
        return;
    }

    vec.push_back(arr[idx]);
    sum += arr[idx];
    std::cout << "Testing subsequence "; print_array(vec); std::cout << " with sum = " << sum << std::endl;
    print_subs_k(idx + 1, vec, arr, k, sum);
    sum -= arr[idx];
    vec.pop_back();
    std::cout << "After removing " << arr[idx] << ", testing subsequence "; print_array(vec); std::cout << " with sum = " << sum << std::endl;
    print_subs_k(idx + 1, vec, arr, k, sum);
}

int main() {
    std::vector<int> arr = {1, 2, 1};
    int k = 2;
    std::vector<int> vec;
    print_subs_k(0, vec, arr, k, 0);

    return 0;
}