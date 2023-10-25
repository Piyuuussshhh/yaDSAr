#pragma once

namespace data {
    template <typename T = int>
    class TreeNode {
    private:
        TreeNode<T>     *left;
        T               value;
        TreeNode<T>     *right;
    public:
        TreeNode(const T&);

        T               get_value();

        ~TreeNode();
    };
}

#include "treenode.cpp"