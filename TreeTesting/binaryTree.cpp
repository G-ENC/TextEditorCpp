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
    It is loose at first and by elibstMinValueating edge cases and defining 
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

        // inserting nodes obeying the rules of bst 
        // (every node's right child is bigger, every left child is smaller than root)
        // I allowed for duplicates they reside right of the root
        void bstInsertValue(Node<T>*& root, T val){

            if(!root){
                root = new Node<T>(val);
            //the iteration is done by recursion
            }else{
                if(root->data<=val){
                    bstInsertValue(root->right, val);
                }else{
                    bstInsertValue(root->left, val);
                }
            }
       }

        void bstPrintInorder(Node<T>* root){
            if (root){
                bstPrintInorder(root->left);
                cout<<root->data<<" ";
                bstPrintInorder(root->right);
            }
        }

        /* recursive bst destroy
            set the pointer as nullptr beacuse root 
            is passed as refernce and no value for root 
            results in other functions to dismiss the case where root is non-assigned
        */
        void bstDestroyTree(Node<T>*& root){
            if(root){
                bstDestroyTree(root->left);
                bstDestroyTree(root->right);
                delete root;
                root = nullptr;
            }
        }

        bool bstSearchValue(Node<T>* root, T val){
           if(root){
            if(root->data == val){
                return true;
            }
            else{
                if(root->data<val){
                    return bstSearchValue(root->right, val);
                }else{
                    return bstSearchValue(root->left, val);
                }
            }
           }
           return false;
        }

        Node<T>* bstMaxValue(Node<T>* root){
            if(!root->right){
                return root;
            }else{
                return bstMaxValue(root->right);
            }
        }

        Node<T>* bstMinValue(Node<T>* root){
            if(!root->left){
                return root;
            }else{
                return bstMinValue(root->left);
            }
        }

        /*
            bstPredecessor gives the largest value that is smaller than the root,
            same for successor but gives visa versa

            there must exist a smaller value than root if bstPredecessor is called,
            same for successor but visa versa
        */
        Node<T>* bstPredecessor(Node<T>* root){
            assert(root->left);
            return bstMaxValue(root->left);
        }

        Node<T>* bstSuccessor(Node<T>* root){
            assert(root->right);
            return bstMinValue(root->right);
        }

        //height: number of edges on longest path 
        int bstHeight(Node<T>* root){
            if(!root) return -1;

            int lbstMaxValue = bstHeight(root->left);
            int rbstMaxValue = bstHeight(root->right);
            
            return std::max(lmax,rmax) + 1;  
        }

        Node<T>* bstRemoveValue(Node<T>*& root, T val){
            //this part needs more implemetation comment

            if(root==nullptr){
                return root;
            }

            //tree traversal using recursion
            if(root->data<val){
                root->right = bstRemoveValue(root->right, val);
            }else if(root->data>val){
                root->left = bstRemoveValue(root->left, val);
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
                //in 2 child case, we cange the root with its successor 
                //and remove that succsor from the tree, essentially just 
                //removing a node with 0 or 1 child
                    Node<T>* succ = bstSuccessor(root);
                    root->data = succ->data;
                    root->right = bstRemoveValue(root->right, succ->data);
                }
            }
            //after the traversal we pass root, this allows back-traversal, I think
            return root;
        }

        public:
            void insertValue(T val){
                bstInsertValue(root, val);
            }

            void insertVector(vector<T> val){
                for (auto i: val){
                    bstInsertValue(root, i);
                }
            }

            void printInorder(){
                bstPrintInorder(root);  
                cout<<"\n";
            }

            void destroy(){
                bstDestroyTree(root);
            }            

            bool checkValue(T val){
                cout<<val<<(bstSearchValue(root, val) ? " is in the tree" : " not in the tree");
                return bstSearchValue(root, val);
            }

            Node<T>* getPredecessor(){
                return bstPredecessor(root);
            }

            Node<T>* getSuccessor(){
                return successor(root);
            }

            int getHeight(){
                return bstHeight(root);
            }

            void removeValue(T val){
                bstRemoveValue(root, val);
            }

            ~BinarySearchTree(){
                bstDestroyTree(root);
            }
};

int main(){

    BinarySearchTree<int> bst;

    vector<int> v = {50,70,30,60,80,20,33,90,100};

    bst.insertVector(v);

    bst.printInorder();

    bst.removeValue(50);

    bst.printInorder();

    return 0;
}