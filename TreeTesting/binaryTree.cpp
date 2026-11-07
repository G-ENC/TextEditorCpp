#include <iostream>

using namespace std;


//Templete of a node in tree data structure,
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
        Node<T>* root;

        Node<T>* deleteNode(Node<T>* current_node, T value){


            
        }
};

