#pragma once

namespace data {

    // class BinaryTree;
    // class BST;

    template <typename T = int>
    class TreeNode {
    private:
        TreeNode<T>     *left;
        T               value;
        TreeNode<T>     *right;

        friend class BinaryTree<U>;
        friend class BST<U>;
    public:
        TreeNode(const T&);

        T               get_value();

        ~TreeNode();

    };

}

#include "treenode.cpp"