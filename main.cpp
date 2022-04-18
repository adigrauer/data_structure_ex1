#include "tree.h"
#include "treeNode.h"

int main()  
{  
    Tree<int> tree1;
    int x1 = 1;
    shared_ptr<int> x1_tree(new int(x1));
    tree1.insert(x1_tree);
    int x2 = 2; 
    shared_ptr<int>x2_tree(new int(x2));
    tree1.insert(x2_tree);
    int x3 = 3;
    shared_ptr<int>x3_tree(new int(x3));
    tree1.insert(x3_tree);

    Tree<int> tree2;
    int x4 = 4;
    shared_ptr<int>x4_tree(new int(x4));
    tree2.insert(x4_tree);
    int x5 = 5;
    shared_ptr<int>x5_tree(new int(x5));
    tree2.insert(x5_tree);
    int x6 = 6;
    shared_ptr<int>x6_tree(new int(x6));
    tree2.insert(x6_tree);
    
    cout << "Tree1" << endl;
    tree1.print2D(tree1.getRoot());
    cout << endl;
    cout << "Tree2" << endl;
    tree2.print2D(tree2.getRoot());
    cout << endl;

    /*
    Tree<int> merge = mergeTrees(tree1, tree2);
    cout << "mergeTree" << endl;
    merge.print2D(merge.getRoot());
    cout << endl;
    */
   /*
    shared_ptr<TreeNode<int>>* array1 = tree1.TreeToArray();
    cout << "print array1- checking if inOrderToArray+TreeToArray works" << endl;
    for (int i=0; i<3; i++){
        cout << "array[" << i << "] = " <<  " data " << *(array1[i]->getData()) << " l= " << (array1[i]->getLeft()) << 
        " r= " << (array1[i]->getRight()) <<  " f= " << (array1[i]->getFather())<< endl;
    }
    cout << endl;

    shared_ptr<TreeNode<int>>* array2 = tree2.TreeToArray();
    cout << "print array2- checking if inOrderToArray+TreeToArray works" << endl;
    for (int i=0; i<3; i++){
        cout << "array[" << i << "] = " <<  " data " << *(array2[i]->getData()) << " l= " << (array2[i]->getLeft()) << 
        " r= " << (array2[i]->getRight()) <<  " f= " << (array2[i]->getFather())<< endl;
    }
    cout << endl;

    shared_ptr<TreeNode<int>>* merge = mergeArrays(array1, array2, tree1.getSize(), tree2.getSize());
    cout << "print merge- checking if mergeArrays works" << endl;
    for (int i=0; i<6; i++){
        cout << "array[" << i << "] = " <<  " data " << *(merge[i]->getData()) << " l= " << (merge[i]->getLeft()) << 
        " r= " << (merge[i]->getRight()) <<  " f= " << (merge[i]->getFather())<< endl;
    }
    cout << endl;

    cout << "mergeTree- before" << endl;
    Tree<int> mergetree = mergeArrayToTree(merge, 0, tree1.getSize()+tree2.getSize()-1);
    cout << "mergeTree- after" << endl;
    mergetree.print2D(mergetree.getRoot());
    */
    cout << "mergeTrees- final" << endl;
    shared_ptr<Tree<int>> mergefinal = mergeTrees(tree1, tree2);
    mergefinal->print2D(mergefinal->getRoot());
    /*
    //Inorder traversal for above tree : 4 5 8 11 12 17 18 
    cout << "Inorder traversal for the AVL tree is: \n";  
    tree.inOrder(tree.getRoot()); 
    cout << "\n"; 
    cout << "ReverseInorder traversal for the AVL tree is: \n";  
    tree.reverseInOrder(tree.getRoot());
    cout << "\n";
*/
    //tree.remove(x4_tree);  
    //cout << "\nInorder traversal after deletion of node 5: \n";  
    //tree.inOrder(tree.getRoot()); 
    //cout << "\ntree after deletion of node 5: \n"; 

    return 0;  
}

