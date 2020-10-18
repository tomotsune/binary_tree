//
// Created by tomot on 2020/10/18.
//

#ifndef BINARY_TREE_COMPLETE_BINARY_TREE_H
#define BINARY_TREE_COMPLETE_BINARY_TREE_H

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

template<typename ElemType>
class Complete_binary_tree {
private:
    int size;
    ElemType *root;
public:
    Complete_binary_tree(const std::initializer_list<ElemType> &v);
    void preorderTraversal() const;
    virtual ~Complete_binary_tree();
};

template<typename ElemType>
Complete_binary_tree<ElemType>::Complete_binary_tree(const std::initializer_list<ElemType> &v)
        :size(v.size()),root{new ElemType[size]} {
    int index{};
    for (const auto &item : v) {
        root[++index];
    }
}

template<typename ElemType>
Complete_binary_tree<ElemType>::~Complete_binary_tree() {
    delete [] root;
}

template<typename ElemType>
void Complete_binary_tree<ElemType>::preorderTraversal() const {

}

#endif //BINARY_TREE_COMPLETE_BINARY_TREE_H
