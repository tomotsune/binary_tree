//
// Created by tomot on 2020/10/14.
//

#ifndef BINARY_TREE_BINARY_TREE_H
#define BINARY_TREE_BINARY_TREE_H

#include <iostream>
#include <stack>
#include <iomanip>

using std::cout;
using std::cin;
template<typename ElemType>
struct Node {
    ElemType data{};
    Node<ElemType> *l_branch{}, r_branch{};
};

template<typename ElemType>
class Binary_tree {
private:
    Node<ElemType> *root;
public:
    Binary_tree();

    void inorderTraversal() const;

    void preorderTraversal() const;

    void postorderTraversal() const;
};

template<typename ElemType>
Binary_tree<ElemType>::Binary_tree():root(nullptr) {
}

template<typename ElemType>
void Binary_tree<ElemType>::inorderTraversal() const {
    if (root == nullptr)throw "error in inorderTraversal: tree is null!";
    auto p{root};
    std::stack<Node<ElemType> *> s;
    while (!s.empty() || p != nullptr) {

        //I: 一直遍历到左子树下边, 边遍历边保存根节点到栈中.
        while (p != nullptr) {
            s.push(p);
            p = p->l_branch;
        }

        //II: 当p位空时, 说明已经到达左子树最下边, 这时需要出栈了.
        if (!s.empty()) {
            p = s.top();
            s.pop();
            cout << std::setw(4) << p->data;

            //进入右子树, 开始新的一轮左子树遍历(递归的自我实现)
            p = p->r_branch;
        }
    }
}

template<typename ElemType>
void Binary_tree<ElemType>::preorderTraversal() const {
    if (root == nullptr)throw "error in inorderTraversal: tree is null!";
    auto p{root};
    std::stack<Node<ElemType> *> s;
    while (!s.empty() || p != nullptr) {

        //I: 一直遍历到左子树下边, 边遍历边保存根节点到栈中.
        while (p != nullptr) {
            cout << std::setw(4) << p->data;
            s.push(p);
            p = p->l_branch;
        }

        //II: 当p位空时, 说明已经到达左子树最下边, 这时需要出栈了.
        if (!s.empty()) {
            p = s.top();
            s.pop();
            //cout<<std::setw(4)<<p->data;

            //进入右子树, 开始新的一轮左子树遍历(递归的自我实现)
            p = p->r_branch;
        }
    }
}

template<typename ElemType>
void Binary_tree<ElemType>::postorderTraversal() const {
    if (root == nullptr)throw "error in postorderTraversal: tree is null!";
    auto p{root};
    std::stack<Node<ElemType> *> s;

    //pCur: 当前访问结点, pLastVisit: 上次访问结点.
    auto pCur{root};
    Node<ElemType> *pLastVisit{};

    //先把pCur移动到左子树最下边.
    while (pCur != nullptr) {
        s.push(pCur);
        pCur = pCur->l_branch;
    }
    while (!s.empty()) {
        //pCur指空, 遍历到左子树底端.
        pCur = s.top();
        s.pop();

        //一个右子树被访问的前提是: 无右子树或右子树已被访问过.
        if (pCur->r_branch == nullptr || pCur->r_branch = pLastVisit) {
            cout << std::setw(4) << pCur->data;

            //修改最近被访问过的结点.
            pLastVisit = pCur;
        } else {

            //根结点再次入栈.
            s.push(pCur);

            //进入右子树, 而可肯定右子树一定不为空.
            pCur = pCur->r_branch;
            while (pCur != nullptr) {
                s.push(pCur);
                pCur = pCur->l_branch;
            }
        }
    }
}


#endif //BINARY_TREE_BINARY_TREE_H
