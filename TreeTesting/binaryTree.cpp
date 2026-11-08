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

        /* recursive bst destroy
        set the pointer as nullptr beacuse root 
        is passed as refernce and no value for root 
        results in other functions to dismiss the case where root is non-assigned
        */
        void destroyTree(Node<T>*& root){
            if(root){
                destroyTree(root->left);
                destroyTree(root->right);
                delete root;
                root = nullptr;
            }
        }

        // recursive bst search
        bool searchTree(Node<T>* root, T val){
           if(root){
            if(root->data == val){
                return true;
            }
            else{
                if(root->data<val){
                    return searchTree(root->right, val);
                }else{
                    return searchTree(root->left, val);
                }
            }
           }
           return false;
        }

        Node<T>* max(Node<T>* root){
            if(!root->left){
                return root;
            }else{
                return max(root->left);
            }
        }
        
        Node<T>* min(Node<T>* root){
            if(!root->right){
                return root;
            }else{
                return max(root->right);
            }
        }
        
        Node<T>* predecessor(Node<T>* root){
            return max(root->right);
        }

        Node<T>* successor(Node<T>* root){
            return min(root->left);
        }

        public:
            void insert(T val){
                insertNode(root, val);
            }

            void insert(vector<T> val){
                for (auto i: val){
                    insertNode(root, i);
                }
            }

            void print(){
                printBinarySearchTree(root);
            }
            void destroy(){
                destroyTree(root);
            }            
            void find(T val){
                cout<<val<<(searchTree(root, val) ? " is in the tree" : " not in the tree");
            }

            Node<T>* getPredecessor(){
                return predecessor(root);
            }

            Node<T>* getSuccessor(){
                return successor(root);
            }

            ~BinarySearchTree(){
                destroyTree(root);
            }
};

int main(){

    BinarySearchTree<int> bst;

    vector<int> v = {1,2,3,4,9,7,6,5};

    bst.insert(v);

    bst.print();

    cout<<"\n"<<bst.getPredecessor()->data;


    return 0;
}