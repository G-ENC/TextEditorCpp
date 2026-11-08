#include <iostream>
#include <cassert>
#include <algorithm>

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

        void removeNodeBST(Node<T>*& root, T val){
            Node<T>* p = root;
            Node<T>* q = nullptr;


            while (p->data!=val && p != nullptr)
            {
                q = p;
                if(p->data<val){
                    p = p->right;
                }else{
                    p = p->left;
                }
            }

            if(p){
                if(p->left == nullptr && p->right == nullptr){
                    delete p;
                    p = nullptr;
                    cout<<"[:]"<<p->data<<endl;
                }else{
                    if(p->left == nullptr){
                        if(q->right == p){
                            q->right = p->right;
                        }else{
                            q->left = p->right;
                        }
                        delete p;
                        p=nullptr;
                    }else if(p->right == nullptr){
                        if(q->right == p){
                            q->right = p->left;
                        }else{
                            q->left = p->left;
                        }
                        delete p;
                        p=nullptr;
                    }else{
                        Node<T>* pred = predecessor(p);
                        p->data = pred->data;
                        removeNodeBST(pred, pred->data);
                    }
                }
                
            }
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
                removeNodeBST(root, val);
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

    bst.remove(100);

    bst.printInorder();

    return 0;
}