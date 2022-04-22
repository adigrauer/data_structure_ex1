#include "tree.h"
#include "treeNode.h"

void general_test1();
void insert_test2();
void insert_test3();
void insert_test4();
void merge_test5();
void treeToArray();

int main(){  
    //general_test1();
    //insert_test2();
    //insert_test3();
    //insert_test4();
    //merge_test5();
    treeToArray();
    return 0;  
}

void treeToArray(){
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
    int x11 = 11;
    shared_ptr<int>x11_tree(new int(x11));
    tree1.insert(x11_tree);
    int x32 = 32;
    shared_ptr<int>x32_tree(new int(x32));
    tree1.insert(x32_tree);
    int x40 = 40;
    shared_ptr<int>x40_tree(new int(x40));
    tree1.insert(x40_tree);
    int x45 = 45;
    shared_ptr<int>x45_tree(new int(x45));
    tree1.insert(x45_tree);
    int x0 = 0;
    shared_ptr<int>x0_tree(new int(x0));
    tree1.insert(x0_tree);
    int x8 = 8;
    shared_ptr<int>x8_tree(new int(x8));
    tree1.insert(x8_tree);
    //shared_ptr<TreeNode<int>>* array1 = tree1.TreeToArray();
    int size = tree1.getSize();
    cout << "size need to be 9 output = " << size << endl;
    tree1.remove(x1_tree);
    size = tree1.getSize();
    cout << "size need to be 8 output = " << size << endl;
    /*
    cout << "print array1- checking if inOrderToArray+TreeToArray works" << endl;
    for (int i=0; i<3; i++){
        cout << "array[" << i << "] = " <<  " data " << *(array1[i]->getData()) << " l= " << (array1[i]->getLeft()) << 
        " r= " << (array1[i]->getRight()) <<  " f= " << (array1[i]->getFather())<< endl;
    }
    */
    cout <<  "done"<< endl;
    return;
}
/*
void general_test1(){
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
   
    //tree delete nodes//
    /////////////////////
    mergefinal->remove(x6_tree); 
    cout << "print Tree1 after delete=6" << endl;
    tree1.print2D(mergefinal->getRoot());
    cout << endl;
 
    mergefinal->remove(x4_tree); 
    cout << "print Tree1 after delete=6" << endl;
    tree1.print2D(mergefinal->getRoot());
    cout << endl;

    //destroy merge tree//
    //////////////////////
    mergefinal->destroyTree(mergefinal->getRoot());
    //destroy tree1//
    /////////////////
    tree1.destroyTree(tree1.getRoot());
    //destroy tree2//
    ////////////////
    tree2.destroyTree(tree2.getRoot());
}

void insert_test2(){
    Tree<double> tree;
    double x30 = 30;
    shared_ptr<double>x30_tree(new double(x30));
    tree.insert(x30_tree);
    double x5 = 5;
    shared_ptr<double>x5_tree(new double(x5));
    tree.insert(x5_tree);
    double x35 = 35;
    shared_ptr<double>x35_tree(new double(x35));
    tree.insert(x35_tree);
    double x32 = 32;
    shared_ptr<double>x32_tree(new double(x32));
    tree.insert(x32_tree);
    double x40 = 40;
    shared_ptr<double>x40_tree(new double(x40));
    tree.insert(x40_tree);
    cout << "print Tree" << endl;
    tree.print2D(tree.getRoot());
    cout << endl;
    double x45 = 45;
    shared_ptr<double>x45_tree(new double(x45));
    tree.insert(x45_tree);
    cout << "print cheack insert x=45" << endl;
    tree.print2D(tree.getRoot());
    cout << endl;
    tree.destroyTree(tree.getRoot());
}

void insert_test3(){
    Tree<double> tree;
    double x13 = 13;
    shared_ptr<double>x13_tree(new double(x13));
    tree.insert(x13_tree);
    double x10 = 10;
    shared_ptr<double>x10_tree(new double(x10));
    tree.insert(x10_tree);
    double x15 = 15;
    shared_ptr<double>x15_tree(new double(x15));
    tree.insert(x15_tree);
    double x5 = 5;
    shared_ptr<double>x5_tree(new double(x5));
    tree.insert(x5_tree);
    double x11 = 11;
    shared_ptr<double>x11_tree(new double(x11));
    tree.insert(x11_tree);
    double x16 = 16.00;
    shared_ptr<double>x16_tree(new double(x16));
    tree.insert(x16_tree);
    double x4 = 4;
    shared_ptr<double>x4_tree(new double(x4));
    tree.insert(x4_tree);
    double x6 = 6;
    shared_ptr<double>x6_tree(new double(x6));
    tree.insert(x6_tree);

    cout << "print Tree" << endl;
    tree.print2D(tree.getRoot());
    cout << endl;
    
    double x7 = 7;
    shared_ptr<double>x7_tree(new double(x7));
    tree.insert(x7_tree);
    cout << "print cheack insert x=7" << endl;
    tree.print2D(tree.getRoot());
    cout << endl;
    
    tree.destroyTree(tree.getRoot());
}

void insert_test4(){
    Tree<double> tree;
    double x5 = 5;
    shared_ptr<double>x5_tree(new double(x5));
    tree.insert(x5_tree);
    double x2 = 2;
    shared_ptr<double>x2_tree(new double(x2));
    tree.insert(x2_tree);
    double x7 = 7;
    shared_ptr<double>x7_tree(new double(x7));
    tree.insert(x7_tree);
    double x1 = 1;
    shared_ptr<double>x1_tree(new double(x1));
    tree.insert(x1_tree);
    double x4 = 4;
    shared_ptr<double>x4_tree(new double(x4));
    tree.insert(x4_tree);
    double x6 = 6;
    shared_ptr<double>x6_tree(new double(x6));
    tree.insert(x6_tree);
    double x9 = 9;
    shared_ptr<double>x9_tree(new double(x9));
    tree.insert(x9_tree);
    double x16 = 16;
    shared_ptr<double>x16_tree(new double(x16));
    tree.insert(x16_tree);
    double x3 = 3;
    shared_ptr<double>x3_tree(new double(x3));
    tree.insert(x3_tree);

    cout << "print Tree" << endl;
    tree.print2D(tree.getRoot());
    cout << endl;
    
    double x15 = 15;
    shared_ptr<double>x15_tree(new double(x15));
    tree.insert(x15_tree);
    cout << "print cheack insert x=15" << endl;
    tree.print2D(tree.getRoot());
    cout << endl;
    
    tree.destroyTree(tree.getRoot());
}

void merge_test5(){
    Tree<double> tree1;
    double x5 = 5;
    shared_ptr<double>x5_tree(new double(x5));
    tree1.insert(x5_tree);
    double x2 = 2;
    shared_ptr<double>x2_tree(new double(x2));
    tree1.insert(x2_tree);
    double x7 = 7;
    shared_ptr<double>x7_tree(new double(x7));
    tree1.insert(x7_tree);
    double x1 = 1;
    shared_ptr<double>x1_tree(new double(x1));
    tree1.insert(x1_tree);
    double x15 = 15;
    shared_ptr<double>x15_tree(new double(x15));
    tree1.insert(x15_tree);

    Tree<double> tree2;
    double x4 = 4;
    shared_ptr<double>x4_tree(new double(x4));
    tree2.insert(x4_tree);
    double x6 = 6;
    shared_ptr<double>x6_tree(new double(x6));
    tree2.insert(x6_tree);
    double x9 = 9;
    shared_ptr<double>x9_tree(new double(x9));
    tree2.insert(x9_tree);
    double x16 = 16;
    shared_ptr<double>x16_tree(new double(x16));
    tree2.insert(x16_tree);
    double x3 = 3;
    shared_ptr<double>x3_tree(new double(x3));
    tree2.insert(x3_tree);

    cout << "print Tree1" << endl;
    tree1.print2D(tree1.getRoot());
    cout << endl;

    cout << "print Tree2" << endl;
    tree2.print2D(tree2.getRoot());
    cout << endl;
    
    cout << "print merge tree" << endl;
    shared_ptr<Tree<double>> mergefinal = mergeTrees(tree1, tree2);
    mergefinal->print2D(mergefinal->getRoot());

    mergefinal->destroyTree(mergefinal->getRoot());
    tree1.destroyTree(tree1.getRoot());
    tree2.destroyTree(tree2.getRoot());
}

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

