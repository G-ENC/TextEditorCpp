#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

// Rope information: https://en.wikipedia.org/wiki/Rope_(data_structure)

class RopeNode{
    /*  rope node:
        a rope node has left and right child node,

        leaf nodes:
            hold a string and weight (length of string) attribute

        nodes that aren't leaf nodes:
            hold sum of the weights of all the leaves in its left subtree as an attribute
            also points to left and right child which can be leaf or another subtree-root */   
    public:
        string childNodeString;
        int nodeWeight;
        RopeNode* lChild;
        RopeNode* rChild;
};

class Rope{
    private:
        RopeNode* root = nullptr;
        
        //gets all the leaves from left to right and puts them in a vector
        vector<RopeNode*> collectRopeLeaf(RopeNode* root){
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
            vector<RopeNode*> ropeStringsVector;
            RopeNode* currentNode = root;

            while(currentNode){

                //to maintain currentNode to be non-null when reached to a leaf node,
                //currentNode is assigned to its parent's right child
                if(currentNode->lChild == nullptr && currentNode->rChild == nullptr){
                    ropeStringsVector.push_back(currentNode);
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
        




        //interface: 
        //  RopeNode* insertRopeString(int index, string str)
        //implementation: 
        //  do one split and concat






        //interface: 
        //  RopeNode* concatTwoRopes(RopeNode* lRopeRoot, RopeNode* rRopeRoot)
        //implementation: 
        //  create a new RopeRoot and set the left child as lRopeRoot and right child as rRopeRoot,
        //  also the weight of this new node should be the summed weights of the left subtree's leafs
        //  tree my need rebalacing after this opperation






        //interface: 
        RopeNode* splitRopeAtIndex(int index, RopeNode* ropeRoot){
        //implementation: 
        //  there are two cases to tackle:
        //      case1: provided index is at the last index of the string 
        //      case2: provided index is between the string
        //  
        //  to reduce the ricky second case we have to split that node, at the index, into two new nodes.
        //  after that we get that leaf node and all the leaf nodes right of it then create a new tree with those nodes, 
        //  also get all the leaf nodes left of that node then again create a new tree.
        //  
        //  steps:
        //      reduce the problem to case 1
        //      call collectLeafNodes, and iterate the list and create a Rope until we hit the node we got from calling getLeafAtIndex
        //      after hitting that node start creating a new tree iterate until vector is finsihed 
        //      rebalance the tree

            
            RopeNode* leafToSplit = getLeafAtIndex(index, ropeRoot);
            RopeNode* lLeafSplit = nullptr;
            RopeNode* rLeafSplit = nullptr;

            //at this point index should be altered as the corresponding char's index by getLeafAtIndex
            if(leafToSplit->childNodeString.length() != index){

                lLeafSplit->childNodeString = (leafToSplit->childNodeString).substr(0,index); //first half of the string not including the index
                rLeafSplit->childNodeString = (leafToSplit->childNodeString).substr(index); //second half, including index

                leafToSplit->childNodeString = nullptr;
                leafToSplit->nodeWeight = lLeafSplit->childNodeString.length();
                leafToSplit->lChild = lLeafSplit;
                leafToSplit->rChild = rLeafSplit;
            }

            //  right now the parent node of the leafToSplit could have a stale weight attribute
            //  this could be solved by not caring about it and letting the tree making step take 
            //  care of the weights once we have the leaf node vector

            vector<RopeNode*> leafVector = collectRopeLeaf(ropeRoot);

            bool atLeftSubTree = true;  // atLeftSubTree is true if we are left of the node we are spliting from
                                        // becomes false after we encouter the leaf node
            for (RopeNode* v: leafVector){
                if(v==rLeafSplit) atLeftSubTree = false;

                if(atLeftSubTree){
                    //make left tree by vector
                }else{

                }
            }            
        }

        //interface: RopeNode* constructRopeWithLeafs(RopeNode* leafNode, RopeNode* root)
        //implementation: must update the weights of the tree (should correspond to left subtree length). could use stack and a list like colectLeaf. 
        //Or recursion and find the weights level by level first the root --> collect leaves --> find lenght --> then the sub trees of it self --> until we hit a root


        //interface: gives the character at charIndex, this method is zero-indexed
        char getCharacterAtIndex(int charIndex, RopeNode* currentRopeNode){
            
            RopeNode* p = getLeafAtIndex(charIndex, currentRopeNode);
            return p->childNodeString[charIndex];
        }

        //interface: gives the node that has the charater at charIndex, 
        //           this method changes charIndex after being called
        RopeNode* getLeafAtIndex(int& charIndex, RopeNode* currentRopeNode){
            //implementation: 
                /*  if weight of the node is greater than the index and there is a left child go to left child, 
                if there is no left child then return the object that has that index. If index is greater than 
                node's weight, substract weight from index and go to right child*/

            //in case we have less characters than passed charIndex
            if(currentRopeNode == nullptr){
                return NULL;
            } 

            //  go to left child if index is less than node weight 
            //since that node index must reside at left side of the tree 
            if(charIndex < currentRopeNode->nodeWeight){
                if(currentRopeNode->lChild == nullptr){
                    return currentRopeNode;
                }else{
                    return getLeafAtIndex(charIndex, currentRopeNode->lChild);
                }

            //we must go right even when it is equal to current weight because of the zero-indexed string
            }else{
                charIndex -= currentRopeNode->nodeWeight;
                return getLeafAtIndex(charIndex, currentRopeNode->rChild);
            }
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

