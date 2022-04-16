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
        void deleteTree (TreeNode<T>* root);
        TreeNode<T> *rrRotate (TreeNode<T>* root); 
        TreeNode<T> *lrRotate (TreeNode<T>* root);
        TreeNode<T> *rlRotate (TreeNode<T>* root);
        TreeNode<T> *llRotate (TreeNode<T>* root);
        int height (TreeNode<T>* node);
        int max(int height_a, int height_b);
        void inOrder (TreeNode<T>* root);
        void reverseInOrder (TreeNode<T>* root);
        Tree<T> *merge(Tree<T>* root_a, Tree<T>* root_b);
        TreeNode<T> *find (TreeNode<T>* root, shared_ptr<T> to_find);
        TreeNode<T> *findMinimalNode (TreeNode<T>* root);
        TreeNode<T> *findFather (TreeNode<T>* root, shared_ptr<T> to_find);
        int checkBalance (TreeNode<T>* root);
        TreeNode<T> *createBalance (TreeNode<T>* root);
};


template<class T>
TreeNode<T>* insert (TreeNode<T>* root, shared_ptr<T> to_add)
{
    if (root == NULL)
    {
        root = TreeNode<T> new_node(to_add);
        return root;
    }
    //need to figure how to use insert when root->data == to_add 
    else if (root->data > to_add)
    {
        root->left = insert(root->left_node, to_add);
        root = createBalance(root);
    }
    else if (root->data < to_add)
    {
        root->right = insert(root->right_node, to_add);
        root = createBalance(root);
    }
    return root;
}

template<class T>
TreeNode<T>* remove(TreeNode<T>* root, shared_ptr<T> to_remove)
{
    if (root == NULL)
    {
        return;
    }
    TreeNode<T>* father_node = findFather(to_remove);
    TreeNode<T>* node_to_remove;
    if (father_node->left_node->data == to_remove)
    {
        node_to_remove = father_node->left_node;
        //if the node to delete has no children
        if (node_to_remove->left_node == NULL && node_to_remove->right_node == NULL)
        {
            father_node->left_node = NULL;
            return;
        }
    }
    else
    {
        node_to_remove = father_node->right_node;
        //if the node to delete has no children
        if (node_to_remove->left_node == NULL && node_to_remove->right_node == NULL)
        {
            father_node->right_node = NULL;
            return;
        }
    }
    //if the node to delete has only one child on the right
    if (node_to_remove->left_node == NULL)
    {
        node_to_remove->data = node_to_remove->right_node->data;
        node_to_remove->right_node = NULL;
    }
    //if the node to delete has only one child on the left
    else if (node_to_remove->right_node == NULL)
    {
        node_to_remove->data = node_to_remove->left_node->data;
        node_to_remove->left_node = NULL;
    }
    //if reached this point than the node has two children
    else 
    {
        TreeNode<T>* current_minimal = findMinimalNode(node_to_remove->right_node);
        node_to_remove->data = current_minimal->data;
        remove(node_to_remove->right_node, current_minimal->data);
    }
}

template<class T>
TreeNode<T> *llRotate (TreeNode<T>* root)
{
    TreeNode<T>* new_root = root->left_node;
    root->left_node = new_root->right_node;
    new_root->right_node = root;
    return new_root;
}

template<class T>
TreeNode<T> *rrRotate (TreeNode<T>* root)
{
    TreeNode<T>* new_root = root->right_node;
    root->right_node = new_root->left_node;
    new_root->left_node = root;
    return new_root;
}

template<class T>
TreeNode<T> *lrRotate (TreeNode<T>* root)
{
    TreeNode<T>* new_root = root->left_node;
    root->left = rrRotate(new_root);
    return llRotate(root);
}

template<class T>
TreeNode<T> *rlRotate (TreeNode<T>* root)
{
    TreeNode<T>* new_root = root->right_node;
    root->left = llRotate(new_root);
    return rrRotate(root);
}


template<class T>
int height (TreeNode<T>* node)
{
    if (node == NULL)
    {
       return -1; 
    } 
    else
        {
            int right_height = height(node->right_node);
            int left_height = height(node->left_node);
            return max(left_height, right_height) + 1;
        }
}

template<class T>
TreeNode<T> *findMinimalNode (TreeNode<T>* root)
{
    while (root->left_node != NULL){
        root = root->left_node;
    }
    return root;
}

template<class T>
TreeNode<T> *createBalance (TreeNode<T>* root)
{
    int balance_factor = checkBalance(root);
    if (balance_factor > 1)
    {
        if (checkBalance(root->left_node) < 0) {
            root = lrRotate(root);
        }
        else {
            root = llRotate(root);
        }
    }
    else if (balance_factor < -1) 
    {
        if (checkBalance(root->right_node) > 0) {
            root = rlRotate(root);
        }
        else {
            root = rrRotate(root);
        }
    }
    return root;
}

template<class T>
int checkBalance (TreeNode<T>* root)
{
    return (height(root->left_node)) - (height(root->right_node));
}

#endif /*TREE_H*/