/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"


ExprTreeNode::ExprTreeNode(){
    this->type=":=";
    this->val=NULL;
    this->evaluated_value=NULL;
    this->id="";
    this->left=NULL;
    this->right=NULL;
}

//Remember to delete any UnlimitedInt created in the parent method
ExprTreeNode::ExprTreeNode(string t,UnlimitedInt* v){
    this->type=t;
    UnlimitedInt* one=new UnlimitedInt(1);
    UnlimitedRational *vr = new UnlimitedRational(v,one);
    delete one;
    this->val=vr;
    this->evaluated_value=NULL;
    this->id="";
    this->left=NULL;
    this->right=NULL;
}

//do not delete the v passed in the parameter
ExprTreeNode::ExprTreeNode(string t,UnlimitedRational* v){
    this->type=t;
    this->val=v;
    this->evaluated_value=NULL;
    this->id="";
    this->left=NULL;
    this->right=NULL;
}

ExprTreeNode::~ExprTreeNode(){
    if(this->left)delete this->left;
    if(this->right)delete this->right;
    if(this->val)delete this->val;
    if(this->evaluated_value)delete this->evaluated_value;
}


