#pragma once

#include <iostream>
// #include <vector>
#include <queue>

#include "../../include/treenode.hpp"

/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/
/*                                                  DEFINITION                                                    */
/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/

namespace data {

    #define NULL_VALUE -1

    // template <typename T = int>
    // class BinaryTree_v {
    // private:
    //     /*
    //         Here, the following formulae are used to represent a binary tree:
    //             for an element at index i:
    //                 -> its left child is at index = 2 * i.
    //                 -> its right child is at index = 2 * i + 1.
    //                 -> its parent is at index floor(i / 2).
    //     */
    //     std::vector<T> tree;
    // public:
    //     BinaryTree_v(std::vector<T>);

    //     void preorder();
    //     void inorder();
    //     void postorder();

    //     ~BinaryTree_v();
    // };

    template <typename T = int>
    class BinaryTree {
    private:
        TreeNode<T>     *root;

        void            preorder_r(TreeNode<T> *) const;
        void            inorder_r(TreeNode<T> *) const;
        void            postorder_r(TreeNode<T> *) const;
        int             count_r(TreeNode<T> *) const;
        int             height_r(TreeNode<T> *) const;
        int             leaf_node_count_r(TreeNode<T> *) const;
        // postorder traversal of binary tree while freeing memory.
        void            delete_tree(TreeNode<T> *);
    public:
        BinaryTree(const T&);

        void            create_tree();

        void            preorder() const;
        void            inorder() const;
        void            postorder() const;
        void            levelorder() const;

        int             count() const;
        int             get_height() const;
        int             leaf_node_count() const;

        ~BinaryTree();
    };

} // namespace data

/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/
/*                                                IMPLEMENTATION                                                  */
/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/

namespace data {

    template <typename T>
    BinaryTree<T>::BinaryTree(const T& val) {
        this -> root = new TreeNode(val);
    }

    /*---x---x---x---x---x---x---x---x---x---x---x---x---x---x*/
    /*                      Tree creation                     */
    //! WHAT IF T IS std::string AND YOU WANT TO ENTER NULL, THEN THIS CODE WILL CRASH.
    template <typename T>
    void BinaryTree<T>::create_tree() {
        std::queue<TreeNode<T> *> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode<T> *node = q.front();
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
            preorder_r(node -> left);
            preorder_r(node -> right);
        }
    }

    template <typename T>
    void BinaryTree<T>::inorder_r(TreeNode<T> *node) const {
        if (node) {
            inorder_r(node -> left);
            std::cout << node -> value << " ";
            inorder_r(node -> right);
        }
    }

    template <typename T>
    void BinaryTree<T>::postorder_r(TreeNode<T> *node) const {
        if (node) {
            postorder_r(node -> left);
            postorder_r(node -> right);
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
            TreeNode<T> *node = q.front();
            q.pop();

            if (node -> left) {
                std::cout << node -> left -> value << " ";
                q.push(node -> left);
            } else {
                std::cout << "-1 ";
            }
            if (node -> right) {
                std::cout << node -> right -> value << " ";
                q.push(node -> right);
            } else {
                std::cout << "-1 ";
            }
        } std::cout << "\n";
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
        right = count_r(node -> right);

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
            return 0;
        }

        int left = leaf_node_count_r(node -> left);
        int right = leaf_node_count_r(node -> right);

        if (!(node -> left) && !(node -> right)) {
            return left + right + 1;
        }

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
        if (!node) {
            return;
        }

        delete_tree(node -> right);
        delete_tree(node -> left);

        if (node) {
            delete node;
            node = nullptr;
        }

        return;
    }

    template <typename T>
    BinaryTree<T>::~BinaryTree() {
        delete_tree(root);
    }
    /*---x---x---x---x---x---x---x---x---x---x---x---x---x---x*/
    /*---x---x---x---x---x---x---x---x---x---x---x---x---x---x*/

} // namespace data