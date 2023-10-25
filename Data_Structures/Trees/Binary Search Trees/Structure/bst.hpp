#pragma once

#include <concepts>
#include <vector>

#include "../include/treenode.hpp"

/*
    std::totally_ordered<T> ensures that T is a data type that has defined comparison operators.
    It's like traits in Rust.
*/

namespace data {

    template <typename T = int>
        requires std::totally_ordered<T>
    class BST {
    private:
        TreeNode<T>     *root;

        int             height_r(TreeNode<T> *) const;
        TreeNode<T>*    remove_r(TreeNode<T> *, const T&);
        TreeNode<T>*    inorder_predecessor(TreeNode<T> *) const;
        TreeNode<T>*    inorder_successor(TreeNode<T> *) const;

        void            delete_tree(TreeNode<T> *);
    public:
        BST();
        BST(const T&);

        TreeNode<T>*    create_BST_from_preorder(const std::vector<T>&);

        int             height() const;

        TreeNode<T>*    search(const T&) const;
        void            insert(const T&);
        void            remove(const T&);

        ~BST();
    };

}

#include "bst.cpp"