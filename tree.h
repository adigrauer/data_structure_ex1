#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include<iostream>
#include<memory>

using std::shared_ptr;

template<class T>
class Tree {
    public:
        Tree ();
        
        /* Tree copy C'tor */
        Tree (const Tree& Tree) = default;
        
        /* Tree virtual D'tor */
        ~Tree() = default;
        TreeNode<T>* insert (TreeNode<T>* root, shared_ptr<T> to_add);
        TreeNode<T>* remove(TreeNode<T>* root, shared_ptr<T> to_remove);
        TreeNode<T> *rrRotate (TreeNode<T>* root); 
        TreeNode<T> *lrRotate (TreeNode<T>* root);
        TreeNode<T> *rlRotate (TreeNode<T>* root);
        TreeNode<T> *llRotate (TreeNode<T>* root);
        int max(int hight_a, int hight_b);
        void inOrder (TreeNode<T>* root);
        void reverseInOrder (TreeNode<T>* root);
        TreeNode<T> *merge(TreeNode<T>* root_a, TreeNode<T>* root_b);
        TreeNode<T> *find (TreeNode<T>* root, shared_ptr<T> to_find);
        TreeNode<T> *checkBalance (TreeNode<T>* root);
};



#endif /*TREE_H*/