#include "tree.h"
#include "treeNode.h"

int main()  
{  
    Tree<int> tree;
    int x1 = 20;
    shared_ptr<int> x1_tree(&x1);
    tree.insert(x1_tree);
    int x2 = 4; 
    shared_ptr<int>x2_tree(&x2);
    tree.insert(x2_tree);
    int x3 = 26;
    shared_ptr<int>x3_tree(&x3);
    tree.insert(x3_tree);
    int x4 = 3;
    shared_ptr<int>x4_tree(&x4);
    tree.insert(x4_tree);
    int x5 = 9;
    shared_ptr<int>x5_tree(&x5);
    tree.insert(x5_tree);
    int x6 = 15;
    shared_ptr<int>x6_tree(&x6);
    tree.insert(x6_tree);

    tree.print2D(tree.getRoot());
    /*
    //Inorder traversal for above tree : 4 5 8 11 12 17 18 
    cout << "Inorder traversal for the AVL tree is: \n";  
    tree.inOrder(root);  
    root = deleteNode(root, 5);  
    cout << "\nInorder traversal after deletion of node 5: \n";  
    inOrder(root);  
    */
    return 0;  
}