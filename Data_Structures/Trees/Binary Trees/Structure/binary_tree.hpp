#pragma once

#include <vector>

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

    //     ~BinaryTree_l();
    // };

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

    // l stands for linked, as in with pointers.
    template <typename T = int>
    class BinaryTree {
    private:
        TreeNode<T>     *root;
        void            preorder_r(TreeNode<T> *);
        void            inorder_r(TreeNode<T> *);
        void            postorder_r(TreeNode<T> *);
        int             count_r(TreeNode<T> *);
        int             height_r(TreeNode<T> *);
        int             leaf_node_count_r(TreeNode<T> *);
        // postorder traversal of binary tree while freeing memory.
        void            delete_tree(TreeNode<T> *);
    public:
        BinaryTree(const T&);

        void            create_tree();

        void            preorder();
        void            inorder();
        void            postorder();
        void            levelorder();

        int             count();
        int             get_height();
        int             leaf_node_count();


        ~BinaryTree();
    };

} // namespace data

#include "binary_tree.cpp"