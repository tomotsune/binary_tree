#include <iostream>
#include <vector>
#include "Binary_tree.h"
#include "Complete_binary_tree.h"
#include "stdlib.h"
[[maybe_unused]] void test2();
int main() {
    test2();
    return 0;
}

[[maybe_unused]] void test1() {
    Binary_tree<int> tree{1, 2, 3, 4, 5};
    cout << "height:" << std::setw(4) << tree.height() << endl;
    cout << "中序: ";
    tree.inorderTraversal();
    cout << endl;
    cout << "先序: ";
    tree.preorderTraversal();
    cout << endl;
    cout << "后续: ";
    tree.postorderTraversal();
    cout << endl;
    cout << "----------------";
    cout << endl;
    cout << "Q_2: ";
    Complete_binary_tree<int> ct{1, 2, 3, 4, 5};
    ct.preorderTraversal();
}



void test2() {

    cout << "please init a AVL: " << endl;

    std::vector<int> nums;
    int n;
    while(cin>>n){
        nums.push_back(n);
        if (getchar() == '\n')  break;
    }

    Binary_tree<int> tree{nums};
    while (true) {
        cout << "1. output inorderTraversal" << endl;
        cout << "2. insert " << endl;
        cout << "3. search" << endl;
        cout << "4. remove" << endl;
        cout << "0. exit" << endl;
        int a;
        cin >> a;
        switch (a) {
            case 1:
                tree.inorderTraversal();
                break;
            case 2:
                cin >> a;
                tree.insert_AVL(a);
                break;
            case 3:
                cin >> a;
                cout << "--> " << tree.search(a) << endl;
                break;
            case 4:
                cin >> a;
                tree.remove(a);
                break;
            case 0:
                exit(0);

        }
    }


}
