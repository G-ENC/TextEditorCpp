#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

// Rope information: https://en.wikipedia.org/wiki/Rope_(data_structure)
//                   https://medium.com/underrated-data-structures-and-algorithms/rope-data-structure-e623d7862137

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

        RopeNode():childNodeString(NULL), nodeWeight(NULL), lChild(nullptr), rChild(nullptr){};
        RopeNode(string s, int nW):childNodeString(s), nodeWeight(nW), lChild(nullptr), rChild(nullptr){};
        RopeNode(string s, int nW, RopeNode* ln, RopeNode* rn): childNodeString(s), nodeWeight(nW), lChild(ln), rChild(rn){}

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
        //  RopeNode* createTreeFromVector
        //implementation:
        //  concat until the vector only has 1 element



        //interface: 
        RopeNode* concatTwoRopes(RopeNode* lRopeRoot, RopeNode* rRopeRoot){

        //implementation: 
        //  create a new RopeRoot and set the left child as lRopeRoot and right child as rRopeRoot,
        //  also the weight of this new node should be the summed weights of the left subtree's leafs
        //  tree might need rebalacing after this opperation
            
            vector<RopeNode*> leftLeaves = collectRopeLeaf(lRopeRoot);
            int leftLeafWeights = 0;

            for(RopeNode* v: leftLeaves){
                leftLeafWeights += v->nodeWeight;
            }

            RopeNode* root = new RopeNode(NULL, leftLeafWeights, lRopeRoot, lRopeRoot);
            
            return root;
        }

        RopeNode* makeRopeFromVector(vector<RopeNode*> leavesVector){
            //implementation:
                //  while there is more than one leaf node in the leavesVector continue to concat 
                //  we have to take two nodes each time and concat those then get a brand new 
                // pair so we are not appending to the same root tree
                //  two vectors should exist let v1 and v2, v1 has the leaves we are concatinating and v2 has the results we get from concatnation
                //  then we treat the v1 as empty and start concatinating v2 and writing the results to v1
                //  we should continue until either one has only one value after concatination
                vector<RopeNode*> firstLeavesVector = leavesVector;
                vector<RopeNode*> secondLeavesVector;
                vector<RopeNode*> temp;

                // we don't know if the total concatnation will be even or odd so we should check for both vectors
                while(firstLeavesVector.size() != 1 && secondLeavesVector.size() != 1){
                    
                    if(!firstLeavesVector.empty()){
                        temp = firstLeavesVector;
                    }else{
                        temp = secondLeavesVector;
                    }

                    for(int i = 0; i+1 < temp.size() ; i++){
                        //every turn we want to write to the other vector
                        if(!firstLeavesVector.empty()){
                            secondLeavesVector.push_back(concatTwoRopes(temp[i], temp[i+1]));
                        }else{
                            firstLeavesVector.push_back(concatTwoRopes(temp[i], temp[i+1]));
                        }
                    }

                    if(temp == firstLeavesVector){
                        firstLeavesVector.clear();
                    }else{
                        secondLeavesVector.clear();
                    }
                }
        }





        //interface: split the tree from corrseponding index, that index resides in the new left subtree
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

            //at this point index should be altered as the corresponding node's char index by getLeafAtIndex
            if(leafToSplit->childNodeString.length() != index+1){

                string leftString = (leafToSplit->childNodeString).substr(0,index); //first half of the string not including the index
                string rightString = (leafToSplit->childNodeString).substr(index); //second half, including index
                leafToSplit->childNodeString = nullptr;

                lLeafSplit = new RopeNode(leftString, leftString.length());
                rLeafSplit = new RopeNode(rightString, rightString.length());

                leafToSplit->nodeWeight = lLeafSplit->childNodeString.length();
                leafToSplit->lChild = lLeafSplit;
                leafToSplit->rChild = rLeafSplit;
            }

            //  right now the parent node of the leafToSplit could have a stale weight attribute
            //  this could be solved by not caring about it and letting the tree making step take 
            //  care of the weights once we have the leaf node vector

            vector<RopeNode*> leafVector = collectRopeLeaf(ropeRoot);

            bool atLeftLeaf = true; // atLeftLeaf is true if we are left of the node we are spliting from
                                    // becomes false after we encouter the leaf node
            for (RopeNode* v: leafVector){
                //here the case where the node doesn't split haven't been tackled
                if(v == rLeafSplit || v == leafToSplit) atLeftLeaf = false;

                if(atLeftLeaf){
                    //write a funciton to make/add node provided a root

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
            //get leaf at index changes the charIndex so passing it here should 
            //indicate the proper index of the leaf's string
            return p->childNodeString[charIndex];
        }
       
        //interface: gives the node that has the charater at charIndex, 
        //           this method changes charIndex after being called
        //           and is zero-indexed
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

