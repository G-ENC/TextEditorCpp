#include <iostream>

using namespace std;

/*
Thought:
        A data structer, in its core, just a heavly restricted object
    that is defined by simple rules and/or smaller objects.

        Nothing we do seems set in stone, not like a mathmatical notation.
    It is loose at first and by eliminating edge cases and defining 
    certain behaviours we can make a data structure. After making that
    data structer the APIs must provide suitable abstractions so the 
    downsides or advatages of the data structer is seperated from the 
    users decisions.
*/

//Templete of a node for tree data structure,
//one node has a data, left and right child
template <typename T>
class Node{
    public:
        T data;
        Node* left;
        Node* right;
    
    Node(T value):data(value), left(nullptr), right(nullptr){}
    Node():data(NULL), left(nullptr), right(nullptr){}
};

template <typename T>
class BinarySearchTree{
    public:
        Node<T>* root;

        // Node<T>* insertValue(Node<T>* root, T key){
        //     if(root==nullptr){
        //         return new Node<T>(key);
        //         cout<<"asdf";
        //     }
        //     if(key<=root->data){
        //         return insertValue(root->left, key);
        //     }else{
        //         return insertValue(root->right, key);
        //     }
        // }

        Node<T>* insert(Node<T>* root, T key){
            
            if(!root){
                return new Node<T>(key);
            }

            if(root->data<=key){
                root->right= insert(root->right, key);
            }else{
                root->left= insert(root->left, key);
            }
            
        }

        void printBinarySearchTree(Node<T>* root){
            if (root){
                printBinarySearchTree(root->left);
                cout<<root->data;
                printBinarySearchTree(root->right);
            }
        }

};

int main(){

    BinarySearchTree<int> bst;
    bst.insert(bst.root, 5);
    bst.insert(bst.root, 6);
    bst.insert(bst.root, 7);

    bst.printBinarySearchTree(bst.root);

    return 0;
}