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

        RopeNode():childNodeString(""), nodeWeight(0), lChild(nullptr), rChild(nullptr){};
        RopeNode(string s, int nW):childNodeString(s), nodeWeight(nW), lChild(nullptr), rChild(nullptr){};
        RopeNode(string s, int nW, RopeNode* ln, RopeNode* rn): childNodeString(s), nodeWeight(nW), lChild(ln), rChild(rn){}

};

class Rope{
    private:
       
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
        
        //interface:
        // void printRope(RopeNode* root)
        //implemenation
        // https://andrewlock.net/creating-an-ascii-art-tree-in-csharp/


        //bug: left of the string is lost after multiple inserts
        //bug: inserting at index 0 creates new " () "

        //given sub-string is inserted into the index within the whole string
        RopeNode* insertRopeString(int index, string str, RopeNode* ropeRoot){
            //implementation:
            //  do one split and concat

            // should splitRopeAtIndex return two roots or leaf nodes? advatage of 
            // returining two leaf node vectors is that I dont have to refind the leafs,
            // but returning two vector this way might be not intuitive
            
            //testing if resolving the nullptr here solves the problem for splitRopeAtIndex seg fault
            if(ropeRoot == nullptr){
                ropeRoot = new RopeNode(str, str.length());
                return ropeRoot;

            }else{
                pair<vector<RopeNode*>, vector<RopeNode*>> splitRope = splitRopeAtIndex(index, ropeRoot);//split the tree into left and right tree from the index
                RopeNode* insertNode = new RopeNode(str, str.length());
               
                splitRope.first.push_back(insertNode); // append new entry to left tree
                splitRope.first.insert(splitRope.first.end(), splitRope.second.begin(), splitRope.second.end());  // merge left and right tree leafs
                
                //idk if this is the best way
                RopeNode* root = makeRopeFromVector(splitRope.first);

                
                return root;
            }
       }

        //passed rope nodes can be leaf nodes or a branch nodes
        RopeNode* concatTwoRopes(RopeNode* lRopeRoot, RopeNode* rRopeRoot){

            //implementation: 
            //  create a new RopeRoot and set the left child as lRopeRoot and right child as rRopeRoot,
            //  also the weight of this new node should be the summed weights of the left subtree's leafs
            //  tree might need rebalacing after this opperation
            
            vector<RopeNode*> leftLeaves = collectRopeLeaf(lRopeRoot); 
            int leftLeafWeights = 0;
            for(RopeNode* v: leftLeaves){
                leftLeafWeights += v->nodeWeight;   //find the weight of the node
            }

            RopeNode* root = new RopeNode("", leftLeafWeights, lRopeRoot, rRopeRoot);
            return root;
        }

        //note: there might be a bug here or/and in concat
        //passed vector should be all leaf nodes, if not tree might need rebalancing idk
        RopeNode* makeRopeFromVector(vector<RopeNode*> leavesVector){
            //implementation:
                
                //  while there is more than one node in fisrtNodeVecor or secondNodeVector continue to concat 

                //  we have to take two nodes each time and concat those then get a brand new 
                //  pair so we are not appending to the same root tree

                //  two vectors should exist let v1 and v2, v1 has the inital leaves we are concatinating 
                //  and v2 has the results we get from concatnation
                
                //  then we treat v1 as empty and start concatinating v2 and writing the results to v1
                
                //  we should continue until either one has only one node after concatination
                vector<RopeNode*> firstNodeVector = leavesVector;
                vector<RopeNode*> secondNodeVector;
                vector<RopeNode*> temp;

                // we don't know if the total concatnation will be even or odd so we should check for both vectors
                while(firstNodeVector.size() != 1 && secondNodeVector.size() != 1){

                    if(!firstNodeVector.empty()){
                        temp = firstNodeVector;
                    }else{
                        temp = secondNodeVector;
                    }

                    for(RopeNode*v : firstNodeVector) cout<<"first vec:"<<v->childNodeString<<endl;
                    for(RopeNode*v : secondNodeVector) cout<<"second vec:"<<v->childNodeString<<endl;
                    for(RopeNode*v : temp) cout<<"temp:"<<v->childNodeString<<endl;
                    
                    for(int i = 0; i + 1 < temp.size() ; i += 2){ //get a brand new pair of nodes by incrementing i by 2

                        //there is a bug here:
                        if(i + 3 == temp.size() && temp.size() % 2 == 1){ //when there is odd number of nodes final node cannot 
                                                                        //be written, this part accommodates for that
                        cout<<"inner loop: "<<temp[i+2]->childNodeString;

                            if(temp == firstNodeVector){//bug: nothing is being appended here
                                    //should this be a conact(i dont think so) or a push_back,
                                    //if the method be is push back then a second iteration must be done so that there is only one tree root at the end 
                                    //so this shouldn't be in a if statement 
                                    secondNodeVector.push_back(temp[i+2]);
                                }else{
                                    firstNodeVector.push_back(temp[i+2]);
                                }

                        }else{
                            if(temp == firstNodeVector){ //every turn we want to write to the other vector
                                cout<<temp[i]->childNodeString<<" "<<temp[i+1]->childNodeString;
                                secondNodeVector.push_back(concatTwoRopes(temp[i], temp[i+1]));
                                for(RopeNode*v : secondNodeVector) cout<<"second vec:"<<v->nodeWeight<<endl;
                            }else{
                                firstNodeVector.push_back(concatTwoRopes(temp[i], temp[i+1]));
                            }
                        }
                        
                    }

                    if(temp == firstNodeVector){
                        firstNodeVector.clear();
                    }else{
                        secondNodeVector.clear();
                    }
                    // cout<<"~~~";
                    // for(RopeNode*v : firstNodeVector) cout<<"first vec:"<<v->childNodeString<<endl;
                    // for(RopeNode*v : secondNodeVector) cout<<"second vec:"<<v->childNodeString<<endl;
                    // for(RopeNode*v : temp) cout<<"temp:"<<v->childNodeString<<endl;
 
                }
                
                return firstNodeVector.size() == 1 ? firstNodeVector[0] : secondNodeVector[0];
        }

        //interface: split the tree from corrseponding index, that index resides in the new left subtree
        //           returns a pair<leafs of left tree, leafs of right tree>
        //           this fucntion is 1 indexed
        pair<vector<RopeNode*>, vector<RopeNode*>> splitRopeAtIndex(int index, RopeNode* ropeRoot){
            //implementation: 
            //  there are two cases to tackle:
            //      case1: provided index is at the last index of the string 
            //      case2: provided index is between the string
            //  
            //  to reduce the tricky second case we have to split that node, at the index, into two new nodes.
            //  after that we get that leaf node and all the leaf nodes right of it then create a new tree with those nodes, 
            //  also get all the leaf nodes left of that node then again create a new tree.
            //  
            //  steps:
            //      reduce the problem to case 1
            //      call collectLeafNodes, and iterate the vector and split the vector at the node we got from getLeafAtIndex
            //      return the leaf nodes of left (including the leaf at that index) and right in vector pairs

            //what to do when this value is null?
            RopeNode* leafToSplit = getLeafAtIndex(index, ropeRoot);
            RopeNode* lLeafSplit = nullptr;
            RopeNode* rLeafSplit = nullptr;

            //at this point index should be altered as the corresponding node's char index, by getLeafAtIndex

            if(index != 0){ //case 2
                string leftString = (leafToSplit->childNodeString).substr(0,index); //first half of the string not including the index

                string rightString = (leafToSplit->childNodeString).substr(index); //second half, including index
                leafToSplit->childNodeString = "";

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

            vector<RopeNode*> leftLeaves;
            vector<RopeNode*> rightLeaves;
            
            for (RopeNode* v: leafVector){  // getting the left leaves and right leaves
                if(v == rLeafSplit || v == leafToSplit) atLeftLeaf = false;
                atLeftLeaf == true ? leftLeaves.push_back(v) : rightLeaves.push_back(v);
            }

            return make_pair(leftLeaves,rightLeaves);
        }

        //interface: gives the character at charIndex, this method is zero-indexed
        char getCharacterAtIndex(int charIndex, RopeNode* currentRopeNode){
            
            RopeNode* p = getLeafAtIndex(charIndex, currentRopeNode);
            //get leaf at index changes the charIndex so passing it here should 
            //indicate the proper index of the leaf's string
            return p->childNodeString[charIndex];
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

        public:
            RopeNode* root = nullptr;

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

    string str = "chud";

    r.root = new RopeNode(str, str.length(),nullptr, nullptr);    
    r.root->lChild = new RopeNode(str, str.length(), nullptr, nullptr);
    r.root->rChild = new RopeNode(str, str.length(), nullptr, nullptr); 

    //input:
    r.insertString(4,"123");
    r.printRope();
    //output:
    // (chud)(123)

    //input:
    // r.insertString(3,"chud");
    // r.printRope();
    // r.insertString(2,"chud");
    // r.printRope();
    // r.insertString(1,"chud");
    // r.printRope();
    //output:
    // (chu)(chud)(d)(chud)
    // (ch)(chud)(u)(chud)
    // (c)(chud)(h)(chud)
}
/*
    -------------To do----------------
    build a working rope data structer, it must:

        rebalance

        remove
        ? report
        printed in pretty way

    understand:
        what does it mean to balance a tree?

    write public methods to use the rope and find the bugs in the code
*/

