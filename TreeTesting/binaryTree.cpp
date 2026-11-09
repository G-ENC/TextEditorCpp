#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

/*
Thought:
    --about ds
        A data structer, in its core, just a heavly restricted object
    that is defined by simple rules and/or smaller objects.

        Nothing we do seems set in stone, not like a mathmatical notation.
    It is loose at first and by eliminating edge cases and defining 
    certain behaviours we can make a data structure. After making that
    data structer the APIs must provide suitable abstractions so the 
    downsides or advatages of the data structer is seperated from the 
    user's decisions.

    --about user abstraction
        First I tried writing every function in two parts first one used the root varible
    which I am trying to not make it explicitly mutable by the user of functions. So I opted for 
    two function decleritaions for essentially the same function, first uses a pointer refernce 
    and the API in public function excludes that and just passes the other varibles which are
    passed in main. I will try to use 'this' keyword to eliviate double decleriation like this.
*/

/* --------- To Do ------------
ice tea fusetea shephthali
    to do: understand recursive implemetation of bst remove function, particularly 
            why are we defining returning the root at the end
    to do: rewrite all the funcitons as public but include the root by 
            using this and delete the double function delceriation of both in public and in private
    to do: try writing the rope after every method works
    to do: try unit control test
    to do: write approriate comments in functions
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

       //print BST,
    //    void printBST(Node<T>* root){
    //         if(!root) return;
            
    //         cout<< root->data

    //    }

        // recursivly prints binary tree inorder
        void printBSTInorder(Node<T>* root){
            if (root){
                printBSTInorder(root->left);
                cout<<root->data<<" ";
                printBSTInorder(root->right);
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
            if(!root->right){
                return root;
            }else{
                return max(root->right);
            }
        }

        Node<T>* min(Node<T>* root){
            if(!root->left){
                return root;
            }else{
                return min(root->left);
            }
        }

        /*
            predecessor gives the largest value that is smaller than the root,
            same for successor but gives visa versa

            there must exist a smaller value than root if predecessor is called,
            same for successor but visa versa
        */
        Node<T>* predecessor(Node<T>* root){
            assert(root->left);
            return max(root->left);
        }

        Node<T>* successor(Node<T>* root){
            assert(root->right);
            return min(root->right);
        }

        int heightBST(Node<T>* root){
            if(!root) return -1;

            int lmax = heightBST(root->left);
            int rmax = heightBST(root->right);
            
            return std::max(lmax,rmax) + 1;  
        }

        //recursivly deletes the node with passed val
        Node<T>* deleteNode(Node<T>*& root, T val){

            if(root==nullptr){
                return root;
            }

            //tree traversal using recursion
            if(root->data<val){
                root->right = deleteNode(root->right, val);
            }else if(root->data>val){
                root->left = deleteNode(root->left, val);
            }else{
                //1 or 0 child case
                if(root->left == nullptr){
                    Node<T>* temp = root->right;
                    delete root;
                    return temp;
                }else if(root->right == nullptr){
                    Node<T>* temp = root->left;
                    delete root;
                    return temp;
                }else{
                //2 child case
                    Node<T>* succ = successor(root);
                    root->data = succ->data;
                    root = deleteNode(root, succ->data);
                }
            }
            //after the traversal we pass root, this allows back-traversal I think
            return root;
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
            void printInorder(){
                printBSTInorder(root);
                cout<<"\n";
            }
            void destroy(){
                destroyTree(root);
            }            
            void check(T val){
                cout<<val<<(searchTree(root, val) ? " is in the tree" : " not in the tree");
            }

            Node<T>* getPredecessor(){
                return predecessor(root);
            }

            Node<T>* getSuccessor(){
                return successor(root);
            }

            int getHeight(){
                return heightBST(root);
            }

            void remove(T val){
                deleteNode(root, val);
            }

            ~BinarySearchTree(){
                destroyTree(root);
            }
};

int main(){

    BinarySearchTree<int> bst;

    vector<int> v = {50,70,30,60,80,20,33,90,100};

    bst.insert(v);

    bst.printInorder();

    bst.remove(31);

    bst.printInorder();

    return 0;
}