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

// Helper function to calculute time taken for an algorithm to run.
double time_taken(Time start, Time end) {
    auto duration_obj = std::chrono::duration_cast<Microseconds>(end - start);
    return duration_obj.count() / 1000.0;
}