#include <iostream>
#include <algorithm>

/*
    If we are given n UNLABELLED nodes, we can make:
            2nCn / (n+1)
    number of binary trees.
*/

typedef unsigned long long int VeryLong_t;

constexpr VeryLong_t factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }

    VeryLong_t fac = 1;
    for (int i = 2; i <= n; i++) {
        fac *= i;
    }
    return fac;
}

constexpr VeryLong_t nCr(int n, int r) {
    return (factorial(n) / (factorial(n - r) * factorial(r)));
}

int main() {
    int n;
    std::cout << "Enter the number of nodes: ";
    std::cin >> n;

    int catalan_number = (nCr(2 * n, n) / (n + 1));
    std::cout << "The number of binary trees possible: " << catalan_number << "\n";

    std::cout << "Number of binary trees with maximum height: " << std::pow(2, n - 1) << std::endl;
}