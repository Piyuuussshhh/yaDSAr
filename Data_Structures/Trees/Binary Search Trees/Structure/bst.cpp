#include <iostream>
#include <stack>

#include "bst.hpp"

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
        TreeNode<T> *temp = root;

        while (idx < size) {
            if (preorder[i] < temp -> value) {
                TreeNode<T> *new_node = new TreeNode(preorder[idx++]);
                temp -> left = new_node;
                stk.push(temp);
                temp = new_node;
            } else {
                int upper = 0;
                if (stk.empty()) {
                    upper = INT_MAX;
                } else {
                    upper = stk.top() -> value
                }

                if (preorder[idx] > temp -> value && preorder[idx] < upper) {
                    TreeNode<T> *new_node = new TreeNode(preorder[idx++]);
                    temp -> right = new_node;
                    temp = new_node;
                } else {
                    temp = stk.top();
                    stk.pop();
                }
            }
        }

        return this -> root;
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

        return left > right ? left + 1 : right + 1;
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
            return;
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
        return remove_r(this -> root);
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