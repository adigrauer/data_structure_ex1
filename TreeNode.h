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
        int height;
        shared_ptr<T> data;
        //shared_ptr<TreeNode<T>> father;
    public:

};



#endif /*TREENODE_H*/