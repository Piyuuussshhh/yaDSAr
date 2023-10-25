#include "treenode.hpp"

namespace data {

    template <typename T>
    TreeNode<T>::TreeNode(const T& val)
        : value(val), right(nullptr), left(nullptr) {}

    template <typename T>
    T TreeNode<T>::get_value() {
        return this -> value;
    }

    template <typename T>
    TreeNode<T>::~TreeNode() {
        delete this -> right;
        delete this -> left;
    }
    
}