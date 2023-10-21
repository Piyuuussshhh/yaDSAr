#include <iostream>
#include <algorithm>

/*
    Given the height h of a strict binary tree, the:
        -> minimum number of nodes in it = 2 * h + 1.
        -> maximum number of nodes in it = 2^(h + 1) - 1
*/

int main() {
    int height;
    std::cout << "Enter height: ";
    std::cin >> height;

    std::cout << "Minimum number of nodes in strict binary tree: " << 2 * height + 1 << std::endl;
    std::cout << "Maximum number of nodes in strict binary tree: " << pow(2, height + 1) - 1.0 << std::endl;
}