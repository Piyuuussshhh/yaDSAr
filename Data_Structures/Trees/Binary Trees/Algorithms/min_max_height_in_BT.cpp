#include <iostream>
#include <cmath>

/*
    Given n number of nodes in a binary tree, the:
        -> minimum height of the tree = log base 2 (n + 1) - 1
        -> maximum height of the tree = n - 1.
*/

int main() {
    int n;
    std::cout << "Enter number of nodes: ";
    std::cin >> n;

    std::cout << "Minimum height of binary tree: " << log2(n + 1) - 1 << "\n";
    std::cout << "Maximum height of binary tree: " << n - 1 << std::endl;
}