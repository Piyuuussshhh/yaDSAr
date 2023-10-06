#pragma once

// IO Functionality
#include <iostream>
// For INT_MAX INT_MIN
#include <limits.h>
// For max(), min(), abs()
#include <algorithm>
// To check how fast our algorithms are.
#include <chrono>
// For accumulate().
#include <numeric>
// For std::find()
#include <utility>

// Common STL Containers
#include <vector>
#include <stack>
#include <queue>
#include <map>

// Simplified type names for time measuring data types.
typedef std::chrono::high_resolution_clock                              Clock;
typedef std::chrono::microseconds                                       Microseconds;
typedef std::chrono::time_point<std::chrono::high_resolution_clock>     Time;

// For 2D dp problems.
typedef std::vector<std::vector<int>>        Matrix;
#define INIT_VAL                             -1

// ? Helper functions for 2D dp problems:

void print_matrix(Matrix& mat) {
    for (const auto& i: mat) {
        for (const auto& j: i) {
            std::cout << j << "\t";
        }
        std::cout << "\n";
    } std::cout << "\n";
}

// Helper function to calculute time taken for an algorithm to run.
double time_taken(Time start, Time end) {
    auto duration_obj = std::chrono::duration_cast<Microseconds>(end - start);
    return duration_obj.count() / 1000.0;
}