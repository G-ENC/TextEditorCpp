#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cassert>

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

        RopeNode():childNodeString(""), nodeWeight(0), lChild(nullptr), rChild(nullptr){};
        RopeNode(string s, int nW):childNodeString(s), nodeWeight(nW), lChild(nullptr), rChild(nullptr){};
        RopeNode(string s, int nW, RopeNode* ln, RopeNode* rn): childNodeString(s), nodeWeight(nW), lChild(ln), rChild(rn){}

};

class Rope{
    private:
       
        RopeNode* root = nullptr;

        //  returns all the leaves from left to right and puts them in a vector, 
        //this method doesn't use the weights of the nodes so it can be called even if the weights are wrong
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
            vector<RopeNode*> ropeLeafVector;
            RopeNode* currentNode = root;

            while(currentNode){

                //to maintain currentNode to be non-null when reached to a leaf node,
                //currentNode is assigned to its parent's right child
                if(currentNode->lChild == nullptr && currentNode->rChild == nullptr){
                    ropeLeafVector.push_back(currentNode);
                    if(!ropeNodeStack.empty()){ //when the leaf node is passed as root, there might not be elements in stack
                        currentNode = ropeNodeStack.top()->rChild; //left child's sibling
                        ropeNodeStack.pop();
                    }else{
                        currentNode = nullptr;
                    }
    
                //traverse root until left most child is reached
                }else{
                    ropeNodeStack.push(currentNode);
                    currentNode = currentNode->lChild;
                }
            }
            return ropeLeafVector;
        }

        //interface: gives the node that has the charater at charIndex, 
        //           this method changes charIndex after being called and is zero-indexed
        RopeNode* getLeafAtIndex(int& charIndex, RopeNode* currentRopeNode){
            //implementation:
                /*  if weight of the node is greater than the index and there is a left child go to left child, 
                if there is no left child then return the object that has that index. If index is greater than 
                node's weight, substract weight from index and go to right child*/

            //in case we have less characters than passed charIndex
            if(currentRopeNode == nullptr){
                return nullptr;
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

        //interface: gives the character at charIndex, this method is zero-indexed
        char getCharacterAtIndex(int charIndex, RopeNode* currentRopeNode){
            
            RopeNode* p = getLeafAtIndex(charIndex, currentRopeNode);
            //get leaf at index changes the charIndex so passing it here should 
            //indicate the proper index of the leaf's string
            return p->childNodeString[charIndex];
        }

        //interface: prints leafs left to right
        void printRopeLeaf(RopeNode* root){
            //implamentation:
            //  collect leafs then print every leafs string
            vector<RopeNode*> leafs = collectRopeLeaf(root);
            for(RopeNode* l: leafs){
                cout<<"("<<l->childNodeString<<")";
            }
            cout<<"\n";
        }

        //this method wrong:
        //  merhod must return two roots,
        //  method must only concat and merge the right side of the idnex
        //  previous version found the left leaves and concated them which results in O(n) time
        //  also when the split occures the leaves shouldn't be found only the splited ndoes which may or may not be leaves
        //  this way the algo. is O(logn) but also requires a rebalance
        pair<vector<RopeNode*>, vector<RopeNode*>> splitRopeAtIndex(int index, RopeNode* ropeRoot){
        }

        RopeNode* insertRopeString(int index, string str, RopeNode* ropeRoot){
        }

        //passed rope nodes can be leaf nodes or a branch nodes
        RopeNode* concatTwoRopes(RopeNode* lRopeRoot, RopeNode* rRopeRoot){

        }

        //passed vector should be all leaf nodes, if not tree might need rebalancing idk
        RopeNode* makeRopeFromVector(vector<RopeNode*> leavesVector){
        }

        RopeNode* deleteNodesInRange(int firstIndex, int secondIndex, RopeNode* ropeRoot){
        }
        
        public:

            RopeNode* insertString(int index, string str){
                root = insertRopeString(index, str, root);
                return root;
            }

            void printRope(){
                printRopeLeaf(root);
            }
    };

int main(){
    Rope r;

    //input:
    r.insertString(0,"123");
    r.printRope();
    r.insertString(3,"456");
    r.printRope();
    r.insertString(6,"789");
    r.printRope();

}
/*
    -------------To do----------------
    build a working rope data structer, it must:

        rebalance
        ? report

    understand:
        what does it mean to balance a tree?

*/

