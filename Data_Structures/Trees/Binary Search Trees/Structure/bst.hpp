#pragma once

#include <iostream>
#include <concepts>
#include <vector>
#include <stack>
#include <climits>

#include "../../include/treenode.hpp"


/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/
/*                                                  DEFINITION                                                    */
/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/

namespace data {

    /*
        std::totally_ordered<T> ensures that T is a data type that has defined comparison operators.
        It's like traits in Rust.
    */

    template <typename T = int>
        requires std::totally_ordered<T>
    class BST {
    private:
        TreeNode<T>     *root;

        void            inorder_r(const TreeNode<T> *) const;
        int             height_r(TreeNode<T> *) const;
        TreeNode<T>*    remove_r(TreeNode<T> *, const T&);
        TreeNode<T>*    inorder_predecessor(TreeNode<T> *) const;
        TreeNode<T>*    inorder_successor(TreeNode<T> *) const;

        void            delete_tree(TreeNode<T> *);
    public:
        BST();
        BST(const T&);

        TreeNode<T>*    create_BST_from_preorder(const std::vector<T>&);

        void            inorder() const;

        int             height() const;

        TreeNode<T>*    search(const T&) const;
        void            insert(const T&);
        void            remove(const T&);

        ~BST();
    };

}

/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/
/*                                                IMPLEMENTATION                                                  */
/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/

namespace data {

    template <typename T>
    BST<T>::BST()
        : root(nullptr) {}

    template <typename T>
    BST<T>::BST(const T& val) {
        root = new TreeNode(val);
    }

    template <typename T>
    TreeNode<T>* BST<T>::create_BST_from_preorder(const std::vector<T>& preorder) {
        int size = preorder.size();
        std::stack<TreeNode<T> *> stk;
        int idx = 0;

        this -> root = new TreeNode(preorder[idx++]);
        TreeNode<T> *node = root;

        while (idx < size) {
            if (preorder[idx] < node -> value) {
                TreeNode<T> *new_node = new TreeNode(preorder[idx++]);
                node -> left = new_node;
                stk.push(node);
                node = new_node;
            } else {
                int upper = 0;
                if (stk.empty()) {
                    upper = INT_MAX;
                } else {
                    upper = stk.top() -> value;
                }

                if (preorder[idx] > node -> value && preorder[idx] < upper) {
                    TreeNode<T> *new_node = new TreeNode(preorder[idx++]);
                    node -> right = new_node;
                    node = new_node;
                } else {
                    node = stk.top();
                    stk.pop();
                }
            }
        }

        return this -> root;
    }

    template <typename T>
    void BST<T>::inorder_r(const TreeNode<T> *node) const {
        if (!node) {
            return;
        }

        inorder_r(node -> left);
        std::cout << node -> value << " ";
        inorder_r(node -> right);
    }

    template <typename T>
    void BST<T>::inorder() const {
        return inorder_r(this -> root);
        std::cout << "\n";
    }

    template <typename T>
    TreeNode<T>* BST<T>::search(const T& val) const {
        TreeNode<T>* node = this -> root;

        while (node) {
            if (val == node -> value) {
                return node;
            } else if (val < node -> value) {
                node = node -> left;
            } else {
                node = node -> right;
            }
        }

        return nullptr;
    }

    template <typename T>
    void BST<T>::insert(const T& val) {
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
    }

    template <typename T>
    int BST<T>::height_r(TreeNode<T> *node) const {
        if (!node) {
            return 0;
        }

        int left = 0, right = 0;
        left = height_r(node -> left);
        right = height_r(node -> right);

        return node -> height = left > right ? left + 1 : right + 1;
    }

    template <typename T>
    int BST<T>::height() const {
        return height_r(root);
    }

    template <typename T>
    TreeNode<T>* BST<T>::inorder_predecessor(TreeNode<T> *node) const {
        while (node && node -> right) {
            node = node -> right;
        }

        return node;
    }

    template <typename T>
    TreeNode<T>* BST<T>::inorder_successor(TreeNode<T> *node) const {
        while (node && node -> left) {
            node = node -> left;
        }

        return node;
    }

    template <typename T>
    TreeNode<T>* BST<T>::remove_r(TreeNode<T> *node, const T& key) {
        if (!node) {
            return nullptr;
        }

        if (!(node -> left) && !(node -> right)) {
            if (node == this -> root) {
                this -> root = nullptr;
            }

            delete node;
            return nullptr;
        }

        if (key < node -> value) {
            node -> left = remove_r(node -> left, key);
        } else if (key > node -> value) {
            node -> right = remove_r(node -> right, key);
        } else {
            if (height_r(node -> left) > height_r(node -> right)) {
                TreeNode<T> *predecessor = inorder_predecessor(node -> left);
                node -> value = predecessor -> value;
                node -> left = remove_r(node -> left, predecessor -> value);
            } else {
                TreeNode<T> *successor = inorder_successor(node -> right);
                node -> value = successor -> value;
                node -> right = remove_r(node -> right, successor -> value);
            }
        }

        return node;
    }

    template <typename T>
    void BST<T>::remove(const T& val) {
        remove_r(this -> root, val);
    }

    template <typename T>
    void BST<T>::delete_tree(TreeNode<T> *node) {
        if (!node) {
            return;
        }

        delete_tree(node -> right);
        delete_tree(node -> left);

        delete node;
    }

    template <typename T>
    BST<T>::~BST() {
        delete_tree(this -> root);
    }
}