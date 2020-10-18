//
// Created by tomot on 2020/10/18.
//

#ifndef BINARY_TREE_COMPLETE_BINARY_TREE_H
#define BINARY_TREE_COMPLETE_BINARY_TREE_H

#include <iostream>
#include <stack>
#include <iomanip>

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
        :size(v.size()), root{new ElemType[v.size()]} {
    int index{};
    for (const auto &item : v) {
        root[++index]=item;
    }
}

template<typename ElemType>
Complete_binary_tree<ElemType>::~Complete_binary_tree() {
    delete[] root;
}

template<typename ElemType>
void Complete_binary_tree<ElemType>::preorderTraversal() const {
    if (root == nullptr)throw "error in preorderTraversal: tree is null!";
    std::stack<char> s;
    int index{1};
    /*   while (!st.empty() || parentindex <= len - 1) {
           while (parentindex <= len - 1) {
               st.push(parentindex);
               cout << arr[parentindex] << " ";
               parentindex = parentindex * 2 + 1;
           }
           parentindex = st.top();
           parentindex = parentindex * 2 + 2;
           st.pop();
       }*/
    while (!s.empty() || index <= size) {
        if (index <= size) {
            cout << std::setw(4) << root[index];
            s.push(index);
            index = index * 2;
        }else{
            index = s.top();
            s.pop();
            //进入右子树, 开始新的一轮左子树遍历(递归的自我实现)
            index = index*2+1;
        }
    }

}

#endif //BINARY_TREE_COMPLETE_BINARY_TREE_H
