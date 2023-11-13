#pragma once

#include <vector>

#include "../../include/treenode.hpp"

/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/
/*                                                  DEFINITION                                                    */
/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/

namespace data {

    template <typename T = int>
        requires std::totally_ordered<T>
    class AVLTree {
    private:
        TreeNode<T> *root;

        int height_r(TreeNode<T> *) const;
        int balance_factor_r(TreeNode<T> *) const;
    public:
        AVLTree(const T&);

        int height() const;

        void insert(const T&);
    };

}

/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/
/*                                                IMPLEMENTATION                                                  */
/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/

namespace data {

    template <typename T>
    AVLTree<T>::AVLTree(const T& val) {
        root = new TreeNode(val);
    }

    template <typename T>
    int AVLTree<T>::height_r(TreeNode<T> *node) const {
        if (!node) {
            return 0;
        }

        int left = 0, right = 0;
        left = height_r(node -> left);
        right = height_r(node -> right);

        return node -> height = left > right ? left + 1 : right + 1;
    }

    template <typename T>
    int AVLTree<T>::height() const {
        return height_r(root);
    }

    template <typename T>
    void AVLTree<T>::insert(const T& val) {
        TreeNode<T> *prev = nullptr, *node = this -> root;

        while (node) {
            prev = node;
            if (val == node -> value) {
                return;
            } else if (val < node -> value) {
                node = node -> left;
            } else {
                node = node -> right;
            }
        }

        TreeNode<T> *new_node = new TreeNode(val);
        if (new_node -> value < prev -> value) {
            prev -> left = new_node;
        } else {
            prev -> right = new_node;
        }

        // So that the height of each node is recalculated.
        auto __discard__ = this -> height();
    }

    template <typename T>
    int AVLTree<T>::balance_factor_r(TreeNode<T> *node) const {
        if (!node) {
            return 0;
        }

        int left = node -> left ? node -> left -> height : 0;
        int right = node -> right ? node -> right -> height : 0;

        return left - right;
    }

}