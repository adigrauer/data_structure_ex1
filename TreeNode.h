#ifndef TREENODE_H
#define TREENODE_H

#include<iostream>
#include<memory>

using std::shared_ptr;

template<class T>
class TreeNode {
    private:
        shared_ptr<TreeNode<T>> left_node;
        shared_ptr<TreeNode<T>> right_node;
        shared_ptr<T> data;
        //shared_ptr<TreeNode<T>> father;
    public:
    TreeNode (shared_ptr<T> data);
        
    /* Tree copy C'tor */
    TreeNode (const TreeNode& tree_node) = default;
        
    /* Tree virtual D'tor */
    ~TreeNode() = default;
};
template<class T>
TreeNode<T>::TreeNode (shared_ptr<T> data){

}

template<class T>
TreeNode<T>::TreeNode (shared_ptr<T> data): 
    data(data),
    left_node(NULL),
    right_node(NULL)
{
}


#endif /*TREENODE_H*/