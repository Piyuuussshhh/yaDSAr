#pragma once

namespace data {

    template <typename T = int>
    class TreeNode {
    public:
        TreeNode<T>     *left;
        T               value;
        TreeNode<T>     *right;

        TreeNode(const T&);

        T               get_value();

        ~TreeNode();

    };

}

#include "treenode.cpp"