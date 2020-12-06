//
// Created by tomot on 2020/10/14.
//

#ifndef BINARY_TREE_BINARY_TREE_H
#define BINARY_TREE_BINARY_TREE_H

#include <iostream>
#include <stack>
#include <iomanip>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

template<typename ElemType>
class Binary_tree {
private:
    struct Node {
        ElemType key{};
        int height{};
        Node *l_branch{};
        Node *r_branch{};

        explicit Node(const ElemType &key) : key(key) {}
    };

    Node *root;

    void destroy(Node *&n);

    //AVL:
    int height(const Node *n) const;

    Node *insert_AVL(Node *&n, const ElemType &key);


    Node *rightRotation(Node *root); //RR


    Node *leftRotation(Node *root);//LL


    Node *leftRightRotation(Node *root);//LR


    Node *rightLeftRotation(Node *root);//RL

    Node *remove(Node *&root, Node *z);

public:

    //constructors
    Binary_tree();

    Binary_tree(const std::initializer_list<int> &v);

    Binary_tree(const std::vector<int> &v);

    //destructor
    virtual ~Binary_tree();

    //BST.
    void insert_BST(const ElemType &key);

    Node *search(const ElemType &key);

    //AVL.
    int height() const;

    void insert_AVL(const ElemType &key);

    //traversals
    void inorderTraversal() const;

    void preorderTraversal() const;

    void postorderTraversal() const;

    void remove(const ElemType &key);
};

template<typename ElemType>
Binary_tree<ElemType>::Binary_tree(const std::initializer_list<int> &v):Binary_tree() {
    for (const auto &item : v) {
        insert_AVL(item);
    }
}

template<typename ElemType>
Binary_tree<ElemType>::Binary_tree():root(nullptr) {
}

template<typename ElemType>
Binary_tree<ElemType>::Binary_tree(const std::vector<int> &v) {
    for (const auto &item : v) {
        insert_AVL(item);
    }
}

template<typename ElemType>
typename Binary_tree<ElemType>::Node *Binary_tree<ElemType>::search(const ElemType &key) {
    auto p{root};
    while (p != nullptr && key != p->key) {
        if (key < p->key)
            p = p->l_branch;
        else
            p = p->r_branch;
    }
    return p;
}

template<typename ElemType>
void Binary_tree<ElemType>::insert_BST(const ElemType &key) {

    auto curr{root}, temp{root};;
    while (nullptr != curr) //遍历二叉树，找到应该插入的父节点
    {
        temp = curr;
        if (curr->key == key) {
            return;
        } else if (key > curr->key) {
            curr = curr->r_branch;
        } else {
            curr = curr->l_branch;
        }
    }
    if (temp == nullptr) {
        root = new Node{key};
    } else {
        if (key < temp->key) {
            temp->l_branch = new Node{key};
        } else {
            temp->r_branch = new Node{key};
        }
    }
}

template<typename ElemType>
void Binary_tree<ElemType>::inorderTraversal() const {
    if (root == nullptr)throw "error in inorderTraversal: root is null!";
    auto p{root};
    std::stack<Node *> s;
    while (!s.empty() || p != nullptr) {

        //I: 一直遍历到左子树下边, 边遍历边保存根节点到栈中.
        if (p != nullptr) {
            s.push(p);
            p = p->l_branch;
        }

            //II: 当p位空时, 说明已经到达左子树最下边, 这时需要出栈了.
        else {
            p = s.top();
            s.pop();
            cout << std::setw(4) << p->key;

            //进入右子树, 开始新的一轮左子树遍历(递归的自我实现)
            p = p->r_branch;
        }
    }
}

template<typename ElemType>
void Binary_tree<ElemType>::preorderTraversal() const {
    if (root == nullptr)throw "error in preorderTraversal: root is null!";
    auto p{root};
    std::stack<Node *> s;
    while (!s.empty() || p != nullptr) {

        //I: 一直遍历到左子树下边, 边遍历边保存根节点到栈中.
        if (p != nullptr) {
            cout << std::setw(4) << p->key;
            s.push(p);
            p = p->l_branch;
        }

            //II: 当p位空时, 说明已经到达左子树最下边, 这时需要出栈了.
        else {
            p = s.top();
            s.pop();
            //cout<<std::setw(4)<<p->key;

            //进入右子树, 开始新的一轮左子树遍历(递归的自我实现)
            p = p->r_branch;
        }
    }
}

/*
 * 根节点在访问完右节点后访问 ,需要在判断出栈的结点类型.
 */
template<typename ElemType>
void Binary_tree<ElemType>::postorderTraversal() const {
    if (root == nullptr)throw "error in postorderTraversal: root is null!";
    auto p{root};
    std::stack<Node *> s;

    //pCur: 当前访问结点, pLastVisit: 上次访问结点.
    auto pCur{root};
    Node *pLastVisit{};

    //先把pCur移动到左子树最下边.
    while (pCur != nullptr) {
        s.push(pCur);
        pCur = pCur->l_branch;
    }
    //pCur指空, 遍历到左子树底端 .
    while (!s.empty()) {
        pCur = s.top();
        s.pop();

        //一个右子树被访问的前提是: 无右子树或右子树已被访问过.
        if (pCur->r_branch == nullptr || pCur->r_branch == pLastVisit) {

            //访问结点, 修改最近被访问过的结点.
            cout << std::setw(4) << pCur->key;
            pLastVisit = pCur;

        } else {
            //根结点再次入栈.
            s.push(pCur);

            //进入右子树
            pCur = pCur->r_branch;

            //尝试进入右子树的左分支.
            while (pCur != nullptr) {
                s.push(pCur);
                pCur = pCur->l_branch;
            }
        }
    }
}

template<typename ElemType>
int Binary_tree<ElemType>::height(const Node *n) const {
    if (n != nullptr) {
        return n->height;
    }
    return 0;
}

template<typename ElemType>
int Binary_tree<ElemType>::height() const {
    return height(root);
}

//LL
template<typename ElemType>
typename Binary_tree<ElemType>::Node *Binary_tree<ElemType>::rightRotation(Node *root) {
    auto sub_root{root->l_branch};

    root->l_branch = sub_root->r_branch;
    sub_root->r_branch = root;

    root->height = std::max(height(root->l_branch), height(root->r_branch)) + 1;//旋转后变为子节点, 优先更新.
    sub_root->height = std::max(height(sub_root->l_branch), height(sub_root->r_branch)) + 1;

    return sub_root;
}

//RR
template<typename ElemType>
typename Binary_tree<ElemType>::Node *Binary_tree<ElemType>::leftRotation(Node *root) {
    auto sub_root{root->r_branch};

    root->r_branch = sub_root->l_branch;
    sub_root->l_branch = root;

    root->height = std::max(height(root->l_branch), height(root->r_branch)) + 1;//旋转后变为子节点, 优先更新.
    sub_root->height = std::max(height(sub_root->l_branch), height(sub_root->r_branch)) + 1;

    return sub_root;
}

//LR
template<typename ElemType>
typename Binary_tree<ElemType>::Node *Binary_tree<ElemType>::leftRightRotation(Node *root) {
    root->l_branch = leftRotation(root->l_branch);
    return rightRotation(root);
}

//RL
template<typename ElemType>
typename Binary_tree<ElemType>::Node *Binary_tree<ElemType>::rightLeftRotation(Node *root) {
    root->r_branch = rightRotation(root->r_branch);
    return leftRotation(root);
}

template<typename ElemType>
typename Binary_tree<ElemType>::Node *Binary_tree<ElemType>::insert_AVL(Node *&n, const ElemType &key) {
    if (n == nullptr) {//寻找到插入位置.
        n = new Node{key};
    } else if (key < n->key) {    //-->L
        n->l_branch = insert_AVL(n->l_branch, key);
        if (height(n->l_branch) - height(n->r_branch) == 2) {
            if (key < n->l_branch->key)
                n = rightRotation(n);
        } else if (key > n->l_branch->key)
            n = leftRightRotation(n);

    } else if (key > n->key) {//-->R
        n->r_branch = insert_AVL(n->r_branch, key);
        if (height(n->r_branch) - height(n->l_branch) == 2) { //失衡.
            if (key > n->r_branch->key)
                n = leftRotation(n);
            else if (key < n->r_branch->key)
                n = rightLeftRotation(n);
        }
    }

    n->height = std::max(height(n->l_branch), height(n->r_branch)) + 1;
    return n;
}

template<typename ElemType>
void Binary_tree<ElemType>::destroy(Node *&n) {
    if (n != nullptr) {
        destroy(n->l_branch);
        destroy(n->r_branch);
        delete n;
        n = nullptr;
    }
}

template<typename ElemType>
Binary_tree<ElemType>::~Binary_tree() {
    destroy(root);
}

template<typename ElemType>
void Binary_tree<ElemType>::insert_AVL(const ElemType &key) {
    insert_AVL(root, key);
}

template<typename ElemType>
typename Binary_tree<ElemType>::Node *Binary_tree<ElemType>::remove(Node *&root, Node *z) {
    if (root == nullptr && z == nullptr)return nullptr;
    if (z->key < root->key) {
        root->l_branch = remove(root->l_branch, z);
        if (height(root->r_branch) - height(root->l_branch) == 2) {
            auto r{root->r_branch};
            if (height(r->l_branch) > height(r->r_branch))
                root = rightLeftRotation(root);
            else
                root = rightLeftRotation(root);
        }
    } else if (z->key > root->key)// 待删除的节点在"tree的右子树"中
    {
        root->r_branch = remove(root->r_branch, z);
        // 删除节点后，若AVL树失去平衡，则进行相应的调节。
        if (height(root->l_branch) - height(root->r_branch) == 2) {
            Node *l = root->l_branch;
            if (height(l->r_branch) > height(l->l_branch))
                root = leftRightRotation(root);
            else
                root = leftRotation(root);
        }
    } else    // tree是对应要删除的节点。
    {
        // tree的左右孩子都非空
        if ((root->l_branch != NULL) && (root->r_branch != NULL)) {
            if (height(root->l_branch) > height(root->r_branch)) {
                // 如果tree的左子树比右子树高；
                // 则(01)找出tree的左子树中的最大节点
                //   (02)将该最大节点的值赋值给tree。
                //   (03)删除该最大节点。
                // 这类似于用"tree的左子树中最大节点"做"root"的替身；
                // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
                //Node *max = maximum(root->l_branch);
                Node *max = root->l_branch->l_branch->height>root->l_branch->r_branch->height?root->l_branch->l_branch:root->l_branch->r_branch;
                root->key = max->key;
                root->l_branch = remove(root->l_branch, max);
            } else {
                // 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                // 则(01)找出tree的右子树中的最小节点
                //   (02)将该最小节点的值赋值给tree。
                //   (03)删除该最小节点。
                // 这类似于用"tree的右子树中最小节点"做"root"的替身；
                // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
                //Node *min = maximum(root->r_branch);
                Node *min = root->r_branch->l_branch->height<root->r_branch->r_branch->height?root->r_branch->l_branch:root->r_branch->r_branch;
                root->key = min->key;
                root->r_branch = remove(root->r_branch, min);
            }
        } else {
            Node *tmp = root;
            root = (root->l_branch != NULL) ? root->l_branch : root->r_branch;
            delete tmp;
        }
    }

    return root;
}

template<typename ElemType>
void Binary_tree<ElemType>::remove(const ElemType &key) {
    remove(root, search(key));
}


#endif //BINARY_TREE_BINARY_TREE_H
