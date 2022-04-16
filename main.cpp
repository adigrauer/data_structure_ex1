#include "tree.h"
#include "TreeNode.h"

int main()  
{  
    Tree<int> tree();

    int x = 12;
    tree->size; 
    root = insert(root, 8);  
    root = insert(root, 18);  
    root = insert(root, 5);  
    root = insert(root, 11);  
    root = insert(root, 17);  
    root = insert(root, 4);  
     
    //Inorder traversal for above tree : 4 5 8 11 12 17 18 
    cout << "Inorder traversal for the AVL tree is: \n";  
    tree.inOrder(root);  
    root = deleteNode(root, 5);  
    cout << "\nInorder traversal after deletion of node 5: \n";  
    inOrder(root);  
   
    return 0;  
}