#include <iostream>
#include "Binary_tree.h"
#include "Complete_binary_tree.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    Binary_tree<int> tree{1,2,3,4,5};
    tree.inorderTraversal();
    cout<<endl;
    tree.preorderTraversal();
    cout<<endl;
    tree.postorderTraversal();
    cout<<endl;
    Complete_binary_tree<int> ct{1,2,3,4,5};
    ct.preorderTraversal();
    return 0;
}
