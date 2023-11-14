#pragma once

#include <concepts>

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

        void ll_rotate(TreeNode<T> *);
        void lr_rotate(TreeNode<T> *);
        void rr_rotate(TreeNode<T> *);
        void rl_rotate(TreeNode<T> *);

        void delete_tree(TreeNode<T> *);
    public:
        AVLTree();
        AVLTree(const T&);

        int height() const;

        void insert(const T&);
        void remove(const T&);

        ~AVLTree();
    };

}

/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/
/*                                                IMPLEMENTATION                                                  */
/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/

namespace data {

    template <typename T>
    AVLTree<T>::AVLTree() {
        this -> root = nullptr;
    }

    template <typename T>
    AVLTree<T>::AVLTree(const T& val) {
        this -> root = new TreeNode(val);
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
    int AVLTree<T>::balance_factor_r(TreeNode<T> *node) const {
        if (!node) {
            return 0;
        }

        int left = node -> left ? node -> left -> height : 0;
        int right = node -> right ? node -> right -> height : 0;

        return left - right;
    }

    template <typename T>
    void AVLTree<T>::ll_rotate(TreeNode<T> *node) {
        if (!node) {
            return;
        }

        TreeNode<T> *new_root = node -> left;
        TreeNode<T> *rchild_of_new_root = new_root -> right;

        new_root -> right = node;
        node -> left = rchild_of_new_root;

        if (this -> root == node) {
            this -> root = new_root;
        }
    }

    template <typename T>
    void AVLTree<T>::lr_rotate(TreeNode<T> *node) {
        if (!node) {
            return;
        }

        TreeNode<T> *lchild = node -> left;
        TreeNode<T> *new_root = lchild -> right;

        lchild -> right = new_root -> left;
        node -> left = new_root -> right;

        new_root -> left = lchild;
        new_root -> right = node;

        if (this -> root == node) {
            this -> root = new_root;
        }
    }

    template <typename T>
    void AVLTree<T>::rr_rotate(TreeNode<T> *node) {
        if (!node) {
            return;
        }

        TreeNode<T> *new_root = node -> right;
        TreeNode<T> *lchild_of_new_root = new_root -> left;

        new_root -> left = node;
        node -> right = lchild_of_new_root;

        if (this -> root == node) {
            this -> root = new_root;
        }
    }

    template <typename T>
    void AVLTree<T>::rl_rotate(TreeNode<T> *node) {
        if (!node) {
            return;
        }

        TreeNode<T> *rchild = node -> right;
        TreeNode<T> *new_root = rchild -> left;

        rchild -> left = new_root -> right;
        node -> right = new_root -> left;

        new_root -> right = rchild;
        new_root -> left = node;

        if (this -> root == node) {
            this -> root = new_root;
        }
    }

    template <typename T>
    void AVLTree<T>::insert(const T& val) {
        TreeNode<T> *prev = nullptr, *node = this -> root;

        // If user calls default constructor and inserts an element,
        if (!(this -> root)) {
            this -> root = new TreeNode(val);
            return;
        }

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

        // ! THIS IS WRONG. NEED TO RE-IMPLEMENT.
        // TODO: rotation(prev) is wrong logic. Not necessary that we always perform rotations at prev only.

        /*
            We calculate height so that we get the new heights of each node's subtree
            to see if any rotations are required.
        */
        auto __discard__ = this -> height();

        if (
            balance_factor_r(prev) == 2 &&
            balance_factor_r(prev -> left) == 1
        ) {
            ll_rotate(prev);
        }
        if (
            balance_factor_r(prev) == 2 &&
            balance_factor_r(prev -> left) == -1
        ) {
            lr_rotate(prev);
        }
        if (
            balance_factor_r(prev) == -2 &&
            balance_factor_r(prev -> right) == -1
        ) {
            rr_rotate(prev);
        }
        if (
            balance_factor_r(prev) == -2 &&
            balance_factor_r(prev -> right) == 1
        ) {
            rl_rotate(prev);
        }

        // So that the height of each node is recalculated after all the rotations.
        __discard__ = this -> height();
    }

    template <typename T>
    void AVLTree<T>::delete_tree(TreeNode<T> *node) {
        if (!node) {
            return;
        }

        delete_tree(node -> right);
        delete_tree(node -> left);

        delete node;
    }

    template <typename T>
    AVLTree<T>::~AVLTree() {
        delete_tree(this -> root);
    }

}