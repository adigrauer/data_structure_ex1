#ifndef TREE_H
#define TREE_H

#include "treeNode.h"
#include <iostream>
#include <memory>

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
        Tree (const Tree<T>& Tree) = default;
        ~Tree() = default;
        
        void rrRotate (shared_ptr<TreeNode<T>> node); 
        void llRotate (shared_ptr<TreeNode<T>> node);
        void lrRotate (shared_ptr<TreeNode<T>> node);
        void rlRotate (shared_ptr<TreeNode<T>> node);

        //int height (shared_ptr<TreeNode<T>> node);
        int checkBalance (shared_ptr<TreeNode<T>> node);
        bool createBalance (shared_ptr<TreeNode<T>> node);
        
        void insert(shared_ptr<T> to_add);
        void remove(shared_ptr<T> to_remove);
        void deleteTree ();
        
        void inOrder (shared_ptr<TreeNode<T>> root);
        void reverseInOrder (shared_ptr<TreeNode<T>> root);
        void inOrderToArray (shared_ptr<TreeNode<T>> root, shared_ptr<TreeNode<T>> array, int* index);
        
        int getSize();

        shared_ptr<TreeNode<T>> getRoot();

        //////////////////////////////////////////
        //////////////////////////////////////////
        //////////////////////////////////////////

        shared_ptr<Tree<T>> merge(shared_ptr<Tree<T>> root_a, shared_ptr<Tree<T>> root_b);
        shared_ptr<TreeNode<T>> find (shared_ptr<T> to_find);
        shared_ptr<TreeNode<T>> findMinimalNode (shared_ptr<TreeNode<T>> root);
       
        shared_ptr<TreeNode<T>> TreeToArray(TreeNode<T> tree, int tree_size);
        shared_ptr<TreeNode<T>> mergeArrays(shared_ptr<TreeNode<T>> array_a, shared_ptr<TreeNode<T>> array_b, int size_a, int size_b);
        shared_ptr<TreeNode<T>> mergeArrayToTree(shared_ptr<TreeNode<T>> merge_array, int start, int end);
        shared_ptr<Tree<T>> mergeTrees(shared_ptr<Tree<T>> root_a, shared_ptr<Tree<T>> root_b);
        void print2DUtil(shared_ptr<TreeNode<T>> root, int space);
        void print2D(shared_ptr<TreeNode<T>> root);
        
        
};

template <class T>
Tree<T>::Tree() :
    size(0)
{
}


template <class T>
shared_ptr<TreeNode<T>> Tree<T>::getRoot(){
    return this->primary_root;
}

template <class T>
int Tree<T>::getSize(){
    return this->size;
}

template<class T>
shared_ptr<TreeNode<T>> Tree<T>::find (shared_ptr<T> to_find){
    shared_ptr<TreeNode<T>> temp = this->primary_root;
    while(temp != nullptr){
        if(*temp->getData() == *to_find){
            return temp;
        }
        else if(*temp->getData() > *to_find){
            temp = temp->getLeft();
        }
        else{
            temp = temp->getRight();
        }
    }
    return nullptr;
}

template<class T>
void Tree<T>::insert(shared_ptr<T> to_add)
{
    shared_ptr<TreeNode<T>> new_node(new TreeNode<T>(to_add)); 
    shared_ptr<TreeNode<T>> temp = this->getRoot();
    shared_ptr<TreeNode<T>> temp_update = nullptr;
    //find the parent of new node and update his father
    while(temp != nullptr){
        temp_update = temp;
        if (*temp->getData() > *to_add){
            temp = temp->getLeft();
        }
        else{
            temp = temp->getRight();
        }
    }
    //adi
    //update new node to be the sun of his father
    new_node->changeFather(temp_update);        //new node is the root
    if (temp_update == nullptr){
        this->primary_root = new_node;
    }
    //NOTE- NEED TO CHANGE THE COMPARE TO GENERIC!!!!!
    else if(*temp_update->getData() > *to_add){    //new node is left sun of his parent
        temp_update->changeLeft(new_node);
    }
    else{
        temp_update->changeRight(new_node);       //new node is right sun of his parent
    }
    //update tree size
    size++;
    //touring from the new leaf to the root in order to balance the tree
    while(temp_update != nullptr){
        temp_update->updateHeight();
        if(createBalance(temp_update)){ 
        //balance for temp_update or temp_update father???????????
            return;
        }
        temp_update = temp_update->getFather();
    }
}

template<class T>
void Tree<T>::llRotate (shared_ptr<TreeNode<T>> node)
{
    shared_ptr<TreeNode<T>> temp = node->getRight();
    node->changeRight(temp->getLeft());
    if(temp->getLeft() != nullptr){
        temp->getLeft()->changeFather(node);
    }
    temp->changeFather(node->getFather());
    if(node->getFather() == nullptr){               //node is the root of the tree
        this->primary_root = temp;
    }                  
    else if (node == node->getFather()->getRight()){ //node is right sun
        node->getFather()->changeRight(temp);
    }
    else{                                           //node is left sun
        node->getFather()->changeLeft(temp);
    }
    temp->changeLeft(node);
    node->changeFather(temp);
    temp->updateHeight();
    node->updateHeight();
}

template<class T>
void Tree<T>::rrRotate (shared_ptr<TreeNode<T>> node)
{
    shared_ptr<TreeNode<T>> temp = node->getLeft();
    node->changeLeft(temp->getRight());
    if(temp->getRight() != nullptr){
        temp->getRight()->changeFather(node);
    }
    temp->changeFather(node->getFather());
    if(node->getFather() == nullptr){                //node is the root of the tree
        this->primary_root = temp;
    }                  
    else if (node == node->getFather()->getRight()){ //node is right sun
        node->getFather()->changeRight(temp);
    }
    else{                                            //node is left sun
        node->getFather()->changeLeft(temp);
    }
    temp->changeRight(node);
    node->changeFather(temp);
    temp->updateHeight();
    node->updateHeight();
}

template<class T>
void Tree<T>::lrRotate (shared_ptr<TreeNode<T>> node)
{
    shared_ptr<TreeNode<T>> temp = node->getLeft();
    rrRotate(temp);
    llRotate(node);
}

template<class T>
void Tree<T>::rlRotate (shared_ptr<TreeNode<T>> node)
{
    shared_ptr<TreeNode<T>> temp = node->getRight();
    llRotate(temp);
    rrRotate(node);
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
bool Tree<T>::createBalance (shared_ptr<TreeNode<T>> node)
{
    int balance_factor = checkBalance(node);
    if (balance_factor == 2)
    {
        if(checkBalance(node->getLeft()) == -1){
            lrRotate(node);
            return true;
        }
        else if(checkBalance(node->getLeft()) >= 0){
            llRotate(node);
            return true;
        }
    }
    else if (balance_factor == -2) 
    {
        if(checkBalance(node->getRight()) <= 0)  {
            rrRotate(node);
            return true;
        }
        else if (checkBalance(node->getRight()) == 1) {
            rlRotate(node);
            return true;
        }
    }
    return false;
}

template<class T>
int Tree<T>::checkBalance (shared_ptr<TreeNode<T>> node)
{
    int left_height = -1, right_height = -1;
    if(node->getLeft() != nullptr){
        left_height = node->getLeft()->getHeight();
    }
    if(node->getRight() != nullptr){
        right_height = node->getRight()->getHeight();
    }
    return left_height - right_height;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

template<class T>
void Tree<T>::inOrder (shared_ptr<TreeNode<T>> root){
    if(root == NULL){
        return;
    }
    inOrder(root->left_node);
    //function
    inOrder(root->right_node);
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
    // need to add balance!!!!!!!!!!
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
    print2DUtil(root->getRight(), space);
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<*(root->getData()) <<"\n";
    print2DUtil(root->getLeft(), space);
}
 
template <class T>
void Tree<T>::print2D(shared_ptr<TreeNode<T>> root){
    print2DUtil(root, 0);
}
#endif /*TREE_H*/


