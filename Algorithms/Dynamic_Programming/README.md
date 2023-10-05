# Conventions:

1. The question is explained.
2. The intuition on how to solve is explained.
3. The actual functions are written with the following suffixes:
    - `<func name>_r()`: recursive implementation of the question. They are typically very slow with high time complexities. They are provided to be compared with the memoization and tabulation approaches.
    - `<func name>_td()`: memoization implementation of the question. Time-wise efficient but the stack overhead of recursive calls adds to its space complexity. `td` stands for Top-Down, which is the approach followed by memoization algorithms. They start from the top of the recurrence tree and travel downwards towards the base case.
    - `<func name>_bu()`: tabulation implementation of the question. Similar performance to memoization with respect to time, but it does away with the unnecessary stack overhead of the latter. Still has an O(N) space complexity of the dp vector. `bu` stands for Bottom-Up, which is the approach followed by tabulation algorithms. They start from the base case and make their way up to the required solution.
    - `opt_<func name>_bu()`: optimized tabulation implementation. It reduces the space complexity to O(1) in almost all cases by using variables for 1D problems, 1D vectors for 2D problems etc.
4. The main function runs all these algorithms and calculates the time it takes to execute each of them.

# The `dp.h` header:

This header contains all the header files I could possibly need for solving DP problems. Plus, it also contains logic to calculate the time taken by algorithm to execute.