// IO Functionality
#include <iostream>
// For INT_MAX INT_MIN
#include <limits.h>
// For max(), min(), abs()
#include <algorithm>

// Common STL Containers
#include <vector>
#include <stack>
#include <queue>
#include <map>

// ! QUESTION.
/*
    Print all subsequences in an array.
    A subsequence is a contiguous / non-contiguous subarray of arr such that it follows the order of elements as they occur.
*/

// ! INTUITION.
/*
    If arr = [3, 1, 2] and idx is initially 0.
    =================================================LEFT SUBTREE=================================================
    In the first call, vec = [3].
    Second call, vec = [3, 1].
    Third call, vec = [3, 1, 2].
    Fourth call, idx = arr.size(), therefore [3, 1, 2] is printed, we return to the third call.
    Continuing third call, vec = [3, 1].
    Fourth call, idx = arr.size(), therefore [3, 1] is printed, we return to the third call, then to second call.
    Continuing second call, vec = [3].
    Third call, vec = [3, 2].
    Fourth call, idx = arr.size(), therefore [3, 2] is printed, we return to the third call.
    Continuing third call, vec = [3].
    Fourth call, idx = arr.size(), therefore [3] is printed, we return to the third call then to second call, then to first call.
    ===============================================LEFT SUBTREE ENDS===============================================
    =================================================RIGHT SUBTREE=================================================
    First call, vec = [] {vec.pop_back() removes the [3]}.
    Second call, vec = [1].
    Third call, vec = [1, 2].
    Fourth call, idx = arr.size(), therefore [1, 2] is printed, we return to third call.
    Continuing third call, vec = [1].
    Fourth call, idx = arr.size(), therefore [1] is printed, we return to third call, then to second.
    Second call, vec = [] {vec.pop_back() removes the [1]}.
    Third call, vec = [2].
    Fourth call, idx = arr.size(), therefore [2] is printed, we return to third call.
    Continuing third call, vec = [] {vec.pop_back() removes the [2]}.
    Fourth call, idx = arr.size(), therefore [] is printed, we return to second, then first call.
    ==============================================RIGHT SUBTREE ENDS===============================================
    X=========X================X=============X======FUNCTION ENDS=========X============X================X=========X
*/

void print_array(std::vector<int>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        if (i == vec.size() - 1) {
            std::cout << vec[i];
        } else {
            std::cout << vec[i] << ", ";
        }
    }
}

void print_all_subsequences(int idx, std::vector<int>& vec, std::vector<int>& arr) {
    if (idx == arr.size()) {
        if (vec.size() == 0) {
            std::cout << "{}" << std::endl;
            return;
        }
        std::cout << "{"; print_array(vec); std::cout << "}" << std::endl;
        return;
    }

    // * Take element case.
    vec.push_back(arr[idx]);
    print_all_subsequences(idx + 1, vec, arr);
    // * Not take element case.
    vec.pop_back();
    print_all_subsequences(idx + 1, vec, arr);
}

int main() {
    std::vector<int> arr = {3, 1, 2};
    std::vector<int> vec;
    print_all_subsequences(0, vec, arr);
    return 0;
}