/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    key = "";
    height = -1;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode::SymNode(string k){
    key = k;
    height = -1;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode *leftc = this->left;
    this->left = leftc->right;
    leftc->right = this;
    if(this->left)
    this->left->par = this;
    this->par=leftc;
    return leftc;
}

SymNode* SymNode::RightRightRotation(){
    SymNode *rightc = this->right;
    this->right = rightc->left;
    rightc->left = this;
    if(this->right)
    this->right->par = this;
    this->par=rightc; 
    return rightc;
}

SymNode* SymNode::LeftRightRotation(){
    this->left = this->left->RightRightRotation();
    this->left->par = this;
    return this->LeftLeftRotation();
}

SymNode* SymNode::RightLeftRotation(){
    this->right = this->right->LeftLeftRotation();
    this->right->par = this;
    return this->RightRightRotation();
}

SymNode::~SymNode(){
    this->left = NULL;
    this->right = NULL;
}