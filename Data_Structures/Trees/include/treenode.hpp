#pragma once

/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/
/*                                                  DEFINITION                                                    */
/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/

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

/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/
/*                                                IMPLEMENTATION                                                  */
/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/

namespace data {

    template <typename T>
    TreeNode<T>::TreeNode(const T& val)
        : left(nullptr), value(val), right(nullptr) {}

    template <typename T>
    T TreeNode<T>::get_value() {
        return this -> value;
    }

    template <typename T>
    TreeNode<T>::~TreeNode() {}

}