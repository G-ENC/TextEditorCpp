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
};

template <typename T>
class BinarySearchTree{
    private:
        Node<T>* root = nullptr;

        // recursivly insert nodes obeying the rules of bst
        void insertNode(Node<T>*& root, T val){
            if(!root){
                root = new Node<T>(val);
            }else{
                if(root->data<=val){
                    insertNode(root->right, val);
                }else{
                    insertNode(root->left, val);
                }
            }
       }

        // recursivly prints binary tree inorder
        void printBinarySearchTree(Node<T>* root){
            if (root){
                printBinarySearchTree(root->left);
                cout<<root->data<<" ";
                printBinarySearchTree(root->right);
            }
        }

        public:
            void insert(T val){
                insertNode(root, val);
            }

            void print(){
                printBinarySearchTree(root);
            }
};

int main(){

    BinarySearchTree<int> bst;

    bst.insert(5);
    bst.insert(6);
    bst.insert(6);
    bst.insert(6);
    bst.insert(6);
    bst.insert(3);

    bst.print();

    return 0;
}