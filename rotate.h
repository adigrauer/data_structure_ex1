#include "tree.h"
#include "treeNode.h"

template<class T>
void inOrder (TreeNode<T>* root){
    if(root == NULL){
        return;
    }
    inOrder(root->left_node);
    //function
    inOrder(root->right_node);
}

template <class T>
void inOrderToArray (TreeNode<T>* root, TreeNode<T>* array, int* index){
    if(root == NULL){
        return;
    }
    inOrderToArray(root->left_node);
    array[*index] = root;
    (*index)++;
    inorder(root->right_node);
}

template<class T>
void reverseInOrder (TreeNode<T>* root){
    if(root == NULL){
        return;
    }
    reverseInOrder(root->right_node);
    //function
    reverseInOrder(root->left_node);
}

template<class T>
int max(int hight_a, int hight_b){
    return hight_a > hight_b ? hight_a : hight_b;
}



template<class T>
TreeNode<T>* find (TreeNode<T>* root, shared_ptr<T> to_find){
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
TreeNode<T>* findFather(TreeNode<T>* root, shared_ptr<T> to_find){
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
TreeNode<T>* TreeToArray(TreeNode<T> tree, int tree_size){
    TreeNode<T>* tree_array = new TreeNode<T>[tree_size];
    int index = 0;
    inOrderToArray (tree, tree_array, &index);
    return tree_array;
}

template<class T>
TreeNode<T>* mergeArrays(TreeNode<T>* array_a, TreeNode<T>* array_b, int size_a, int size_b){
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
TreeNode<T>* mergeArrayToTree(TreeNode<T>* merge_array, int start, int end){
    int mid = (start+end)/2;
    TreeNode<T> new_root(merge_array[mid]);
    new_root->left_node = mergeArrayToTree(TreeNode<T>* merge_array, int start, int mid-1);
    new_root->right_node = mergeArrayToTree(TreeNode<T>* merge_array, int mid+1, int end);
    delete merge_array;
    return new_root;
}

template<class T>
TreeNode<T>* mergeTrees(TreeNode<T>* root_a, TreeNode<T>* root_b){
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
void print2DUtil(TreeNode<T>* root, int space){
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
void print2D(TreeNode<T>* root){
    print2DUtil(root, 0);
}

