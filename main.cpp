#include "tree.h"
#include "treeNode.h"

int main()  
{  
    //create tree1//
    ///////////////
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

    //print tree1//
    ///////////////
    cout << "print Tree1 before delete" << endl;
    tree1.print2D(tree1.getRoot());
    cout << endl;

    //create tree2//
    ///////////////
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
    int x7 = 7;
    shared_ptr<int>x7_tree(new int(x7));
    tree2.insert(x7_tree);
    
    //print tree2//
    ///////////////
    cout << "print Tree2" << endl;
    tree2.print2D(tree2.getRoot());
    cout << endl;

    //create and print merge tree from tree1 and tree2//
    ////////////////////////////////////////////////////
    cout << "print merge tree" << endl;
    shared_ptr<Tree<int>> mergefinal = mergeTrees(tree1, tree2);
    mergefinal->print2D(mergefinal->getRoot());
   
    //destroy merge tree//
    //////////////////////
    mergefinal->destroyTree(mergefinal->getRoot());
    //destroy tree1//
    /////////////////
    tree1.destroyTree(tree1.getRoot());
    //destroy tree2//
    ////////////////
    tree2.destroyTree(tree2.getRoot());

    
/*

    //Inorder traversal//
    /////////////////////
    cout << "Inorder traversal for the AVL tree is: \n";  
    tree1.inOrder(tree1.getRoot()); 
    cout << "\n"; 
    //ReverseInorder traversal//
    ////////////////////////////
    cout << "ReverseInorder traversal for the AVL tree is: \n";  
    tree1.reverseInOrder(tree1.getRoot());
    cout << "\n";

    //tree delete nodes//
    /////////////////////
    tree1.remove(x6_tree); 
    cout << "print Tree1 after delete=6" << endl;
    tree1.print2D(tree1.getRoot());
    cout << endl;
 
    tree1.remove(x4_tree);
    cout << "print Tree1 after delete=4" << endl;
    tree1.print2D(tree1.getRoot());
    cout << endl;

*/
    return 0;  
}

/*
//internal prints for debuge merge functions/
/////////////////////////////////////////////
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
*/

