#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// Rope information: https://en.wikipedia.org/wiki/Rope_(data_structure)

/*
rope node:
    a rope node has left and right child node,

    leaf nodes:
        hold a string and weight (length of string) attribute

    nodes that aren't leaf nodes:
        hold sum of the weights of all the leaves in its left subtree as an attribute
        also points to left and right child which can be leaf or another tree
*/
class RopeNode{
    public:
        string childNodeString;
        int nodeWeight;
        RopeNode* lChild;
        RopeNode* rChild;
};

class Rope{
    private:
        RopeNode* root;
        
        vector<string> collectRopeLeaf(RopeNode* root){

            /*
            implementation:
                Tranverse the tree until hitting the left most leaf,
                while doing this add each node to a stack excluding the leaf node.

                After adding the leaf to a list, pop the element from the stack which
                is the parent of the leaf node that we just added, and traverse that nodes
                right subtree's left spine.

                Continue to add the nodes as you traverse until there is nothing in the stack to assign.
            */

            stack<RopeNode*> ropeNodeStack;
            vector<string> ropeStringsVector;
            RopeNode* currentNode = root;

            while(currentNode){

                //to maintain currentNode to be non-null when reached to a leaf node,
                //currentNode is assigned to its parent's right child
                if(currentNode->lChild == nullptr && currentNode->rChild == nullptr){
                    ropeStringsVector.push_back(currentNode->childNodeString);
                    currentNode = ropeNodeStack.top()->rChild; //left child's sibling
                    ropeNodeStack.pop();
        
                //traverse root until left most child is reached
                }else{
                    ropeNodeStack.push(currentNode);
                    currentNode = currentNode->lChild;
                }
            }

            return ropeStringsVector;
        }



};

/*
    -------------To do----------------
    build a working rope data structer, it must:
        collect leaves
        rebalance
        insert
        index
        concat 
        cplit
        remove
        ? report
        printed in pretty way

    understand:
        what does it mean to balance a tree?
        what is a rope is?

        uniuon 
        int,

        struct{
        int string
        }
        
*/

