#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include<iostream>
#include<memory>


using std::shared_ptr;
using std::endl;
using std::cout;
using std::iostream;

template<class T>
class Tree {
    private:
        shared_ptr<TreeNode<T>> primary_root;
        int size;
    public:
        Tree ();
        
        /* Tree copy C'tor */
        Tree (const Tree& Tree) = default;
        
        /* Tree virtual D'tor */
        ~Tree() = default;
        void insert (shared_ptr<T> to_add);
        void remove(shared_ptr<T> to_remove);
        void deleteTree ();
        void rrRotate (shared_ptr<TreeNode<T>> root); 
        void lrRotate (shared_ptr<TreeNode<T>> root);
        void rlRotate (shared_ptr<TreeNode<T>> root);
        void llRotate (shared_ptr<TreeNode<T>> root);
        int height (shared_ptr<TreeNode<T>> node);
        int max(int height_a, int height_b);
        void inOrder (shared_ptr<TreeNode<T>> root);
        void reverseInOrder (shared_ptr<TreeNode<T>> root);
        void inOrderToArray (shared_ptr<TreeNode<T>> root, shared_ptr<TreeNode<T>> array, int* index);
        shared_ptr<Tree<T>> merge(shared_ptr<Tree<T>> root_a, shared_ptr<Tree<T>> root_b);
        shared_ptr<TreeNode<T>> find (shared_ptr<TreeNode<T>> root, shared_ptr<T> to_find);
        shared_ptr<TreeNode<T>> findMinimalNode (shared_ptr<TreeNode<T>> root);
        shared_ptr<TreeNode<T>> findFather (shared_ptr<TreeNode<T>> root, shared_ptr<T> to_find);
        int checkBalance (shared_ptr<TreeNode<T>> root);
        void createBalance (shared_ptr<TreeNode<T>> root);
        shared_ptr<TreeNode<T>> TreeToArray(TreeNode<T> tree, int tree_size);
        shared_ptr<TreeNode<T>> mergeArrays(shared_ptr<TreeNode<T>> array_a, shared_ptr<TreeNode<T>> array_b, int size_a, int size_b);
        shared_ptr<TreeNode<T>> mergeArrayToTree(shared_ptr<TreeNode<T>> merge_array, int start, int end);
        shared_ptr<Tree<T>> mergeTrees(shared_ptr<Tree<T>> root_a, shared_ptr<Tree<T>> root_b);
        void print2DUtil(shared_ptr<TreeNode<T>> root, int space);
        void print2D(shared_ptr<TreeNode<T>> root);






};

template<class T>
Tree<T>::Tree():
    size(0),
    primary_root(NULL)
{
}

template<class T>
void Tree<T>::insert(shared_ptr<T> to_add)
    {
        if (primary_root == NULL)
        {
            TreeNode<T> new_node(to_add);
            primary_root = shared_ptr<TreeNode<T>>(new_node); 
            return;
        }
        //need to figure how to use insert when root->data == to_add 
        else if (primary_root->data > to_add)
        {
            insert(primary_root->left_node, to_add);
            createBalance(primary_root);
        }
        else if (primary_root->data < to_add)
        {
            insert(primary_root->right_node, to_add);
            createBalance(primary_root);
        }
        return primary_root;
    }
template<class T>
void Tree<T>::remove(shared_ptr<T> to_remove)
{
    if (primary_root == NULL)
    {
        return;
    }
    shared_ptr<TreeNode<T>> father_node = findFather(to_remove);
    shared_ptr<TreeNode<T>> node_to_remove;
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
        shared_ptr<TreeNode<T>> current_minimal = findMinimalNode(node_to_remove->right_node);
        shared_ptr<T> copy_data = current_minimal->data;
        remove(current_minimal->data);
        node_to_remove->data = current_minimal->data;
        
    }
}

template<class T>
void Tree<T>::llRotate (shared_ptr<TreeNode<T>> root)
{
    TreeNode<T>* new_root = root->left_node;
    root->left_node = new_root->right_node;
    new_root->right_node = root;
    return new_root;
}

template<class T>
void Tree<T>::rrRotate (shared_ptr<TreeNode<T>> root)
{
    TreeNode<T>* new_root = root->right_node;
    root->right_node = new_root->left_node;
    new_root->left_node = root;
    return new_root;
}

template<class T>
void Tree<T>::lrRotate (shared_ptr<TreeNode<T>> root)
{
    TreeNode<T>* new_root = root->left_node;
    root->left = rrRotate(new_root);
    return llRotate(root);
}

template<class T>
void Tree<T>::rlRotate (shared_ptr<TreeNode<T>> root)
{
    TreeNode<T>* new_root = root->right_node;
    root->left = llRotate(new_root);
    return rrRotate(root);
}


template<class T>
int Tree<T>::height (shared_ptr<TreeNode<T>> node)
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
shared_ptr<TreeNode<T>> Tree<T>::findMinimalNode (shared_ptr<TreeNode<T>> root)
{
    while (root->left_node != NULL){
        root = root->left_node;
    }
    return root;
}

template<class T>
void Tree<T>::createBalance (shared_ptr<TreeNode<T>> root)
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
int Tree<T>::checkBalance (shared_ptr<TreeNode<T>> root)
{
    return (height(root->left_node)) - (height(root->right_node));
}

template<class T>
void Tree<T>::inOrder (shared_ptr<TreeNode<T>> root){
    if(root == NULL){
        return;
    }
    inOrder(root->left_node);
    //function
    inOrder(root->right_node);
}

template <class T>
void Tree<T>::inOrderToArray (shared_ptr<TreeNode<T>> root, shared_ptr<TreeNode<T>> array, int* index){
    if(root == NULL){
        return;
    }
    inOrderToArray(root->left_node);
    array[*index] = root;
    (*index)++;
    inorder(root->right_node);
}

template<class T>
void Tree<T>::reverseInOrder (shared_ptr<TreeNode<T>> root){
    if(root == NULL){
        return;
    }
    reverseInOrder(root->right_node);
    //function
    reverseInOrder(root->left_node);
}

template<class T>
int Tree<T>::max(int hight_a, int hight_b){
    return hight_a > hight_b ? hight_a : hight_b;
}



template<class T>
shared_ptr<TreeNode<T>> Tree<T>::find (shared_ptr<TreeNode<T>> root, shared_ptr<T> to_find){
    if(root == NULL){
        return NULL;
    }
    else if(root->data == to_find){
        return root;
    }
    else if(root->data > to_find){
        return find(root->left_node, to_find);
    }
    else {
       return find(root->right_node, to_find); 
    }
}

template<class T>
shared_ptr<TreeNode<T>> Tree<T>::findFather(shared_ptr<TreeNode<T>> root, shared_ptr<T> to_find){
    if(root == NULL){
        return NULL;
    }
    else if(root->left_node->data == to_find || root->right_node->data == to_find){
        return root;
    }
    else if(root->data > to_find){
        return findFather(root->left_node, to_find);
    }
    else {
       return FindFather(root->right_node, to_find); 
    }
}

template <class T>
shared_ptr<TreeNode<T>> Tree<T>::TreeToArray(TreeNode<T> tree, int tree_size){
    shared_ptr<TreeNode<T>> tree_array = new TreeNode<T>[tree_size];
    int index = 0;
    inOrderToArray (tree, tree_array, &index);
    return tree_array;
}

template<class T>
shared_ptr<TreeNode<T>> Tree<T>::mergeArrays(shared_ptr<TreeNode<T>> array_a, shared_ptr<TreeNode<T>> array_b, int size_a, int size_b){
    TreeNode<T>* merge_array = new TreeNode<T>[size_a + size_b];
    int index_a = 0, index_b = 0, index_merge = 0;
    while(index_a < size_a && index_b < size_b){
        if(array_a[index_a] < array_b[index_b]){
            merge_array[index_merge] = array_a[index_a];
            index_a++;
        }
        else{
            merge_array[index_merge] = array_b[index_b];
            index_b++; 
        }
        index_merge++;
    }
    while(index_a < size_a){
        merge_array[index_merge] = array_a[index_a];
        index_a++;
        index_merge++;
    }
    while(index_b < size_b){
        merge_array[index_merge] = array_b[index_b];
        index_b++;
        index_merge++;
    }
    return merge_array;
}

template <class T>
shared_ptr<TreeNode<T>> Tree<T>::mergeArrayToTree(shared_ptr<TreeNode<T>> merge_array, int start, int end){
    int mid = (start+end)/2;
    TreeNode<T> new_root(merge_array[mid]);
    new_root->left_node = mergeArrayToTree(merge_array, start, mid-1);
    new_root->right_node = mergeArrayToTree( merge_array, mid+1, end);
    delete merge_array;
    return new_root;
}

template<class T>
shared_ptr<Tree<T>> Tree<T>::mergeTrees(shared_ptr<Tree<T>> root_a, shared_ptr<Tree<T>> root_b){
    int index = 0;
    TreeNode<T>* array_a = TreeToArray(root_a, root_a->size);
    deleteTree();
    TreeNode<T>* array_b = TreeToArray(root_b, root_b->size);
    deleteTree();
    TreeNode<T> merge_array = mergeArrays(array_a, array_b, root_a->size, root_b->size);
    delete array_a;
    delete array_b;
    TreeNode<T>* new_tree = mergeArrayToTree(merge_array, 0, root_a->size + root_b->size -1);
}

#define COUNT 10
template<class T>
void Tree<T>::print2DUtil(shared_ptr<TreeNode<T>> root, int space){
    if (root == NULL)
        return;
    space += COUNT;
    print2DUtil(root->right, space);
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->data<<"\n";
    print2DUtil(root->left, space);
}
 
template <class T>
void Tree<T>::print2D(shared_ptr<TreeNode<T>> root){
    print2DUtil(root, 0);
}

#endif /*TREE_H*/


