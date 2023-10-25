#include <iostream>
#include <queue>

#include "binary_tree.hpp"

namespace data {

    template <typename T>
    BinaryTree<T>::BinaryTree(const T& val)
        : root(val) {}

    /*---x---x---x---x---x---x---x---x---x---x---x---x---x---x*/
    /*                      Tree creation                     */
    template <typename T>
    void BinaryTree<T>::create_tree() {
        std::queue<TreeNode<T> *> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode<T> *node = q.top();
            q.pop();

            T val;
            std::cout << "Enter left child value of \'" << node -> value << "\' (-1 for NULL): ";
            std::cin >> val;

            if (val != NULL_VALUE) {
                node -> left = new TreeNode(val);
                q.push(node -> left);
            }

            std::cout << "Enter right child value of \'" << node -> value << "\' (-1 for NULL): ";
            std::cin >> val;

            if (val != NULL_VALUE) {
                node -> right = new TreeNode(val);
                q.push(node -> right);
            }
        }
    }
    /*---x---x---x---x---x---x---x---x---x---x---x---x---x---x*/

    /*---x---x---x---x---x---x---x---x---x---x---x---x---x---x*/
    /*                    Tree traversals                     */
    template <typename T>
    void BinaryTree<T>::preorder_r(TreeNode<T> *node) const {
        if (node) {
            std::cout << node -> value << " ";
            preorder(node -> left);
            preorder(node -> right);
        }
    }

    template <typename T>
    void BinaryTree<T>::inorder_r(TreeNode<T> *node) const {
        if (node) {
            inorder(node -> left);
            std::cout << node -> value << " ";
            inorder(node -> right);
        }
    }

    template <typename T>
    void BinaryTree<T>::postorder_r(TreeNode<T> *node) const {
        if (node) {
            postorder(node -> left);
            postorder(node -> right);
            std::cout << node -> value << " ";
        }
    }

    template <typename T>
    void BinaryTree<T>::preorder() const {
        preorder_r(root);
        std::cout << "\n";
    }

    template <typename T>
    void BinaryTree<T>::inorder() const {
        inorder_r(root);
        std::cout << "\n";
    }

    template <typename T>
    void BinaryTree<T>::postorder() const {
        postorder_r(root);
        std::cout << "\n";
    }

    template <typename T>
    void BinaryTree<T>::levelorder() const {
        std::queue<TreeNode<T> *> q;
        q.push(root);
        std::cout << root -> value << " ";

        while (!q.empty()) {
            TreeNode<T> *node = q.top();
            q.pop();

            if (node -> left) {
                std::cout << node -> left -> value << " ";
                q.push(node -> left);
            } else {
                std::cout << "-1 ";
            }
            if (node -> right) {
                std::cout << node -> left -> value << " ";
                q.push(node -> left);
            } else {
                std::cout << "-1 ";
            }
        }
    }
    /*---x---x---x---x---x---x---x---x---x---x---x---x---x---x*/

    /*---x---x---x---x---x---x---x---x---x---x---x---x---x---x*/
    /*                     Count & Height                     */
    template <typename T>
    int BinaryTree<T>::count_r(TreeNode<T> *node) const {
        if (!node) {
            return 0;
        }

        int left = 0, right = 0;
        left = count_r(node -> left);
        right - count_r(node -> right);

        return left + right + 1;
    }

    template <typename T>
    int BinaryTree<T>::count() const {
        return count_r(root);
    }

    template <typename T>
    int BinaryTree<T>::height_r(TreeNode<T> *node) const {
        if (!node) {
            return 0;
        }

        int left = 0, right = 0;
        left = height_r(node -> left);
        right = height_r(node -> right);

        return left > right ? left + 1 : right + 1;
    }

    template <typename T>
    int BinaryTree<T>::get_height() const {
        return height_r(root);
    }
    /*---x---x---x---x---x---x---x---x---x---x---x---x---x---x*/

    /*---x---x---x---x---x---x---x---x---x---x---x---x---x---x*/
    /*                        Leaf Nodes                      */
    template <typename T>
    int BinaryTree<T>::leaf_node_count_r(TreeNode<T> *node) const {
        if (!node) {
            return 1;
        }

        int left = leaf_node_count_r(node -> left);
        int right = leaf_node_count_r(node -> left);

        return left + right;
    }

    template <typename T>
    int BinaryTree<T>::leaf_node_count() const {
        return leaf_node_count_r(root);
    }

    /*---x---x---x---x---x---x---x---x---x---x---x---x---x---x*/
    /*                      Tree deletion                     */
    template <typename T>
    void BinaryTree<T>::delete_tree(TreeNode<T> *node) {
        delete_tree(node -> right);
        delete_tree(node -> left);

        delete node;
    }

    template <typename T>
    BinaryTree<T>::~BinaryTree() {
        delete_tree(root);
    }
    /*---x---x---x---x---x---x---x---x---x---x---x---x---x---x*/
    /*---x---x---x---x---x---x---x---x---x---x---x---x---x---x*/

} // namespace data
