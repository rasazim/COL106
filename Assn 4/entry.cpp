/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry(){
    this->left=NULL;
    this->right=NULL;
    this->key="";
    this->val=NULL;
}

SymEntry::SymEntry(string k,UnlimitedRational* v){
    this->left=NULL;
    this->right=NULL;
    this->key=k;
    this->val=v;
}

SymEntry::~SymEntry(){
    if(this->val)delete this->val;
}

