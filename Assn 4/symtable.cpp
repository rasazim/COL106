/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//helper

void tab_delete(SymEntry* root){
    if(root->left)tab_delete(root->left);
    if(root->right)tab_delete(root->right);
    delete root;
}

SymbolTable::SymbolTable(){
    size=0;
    root=NULL;
}

SymbolTable::~SymbolTable(){
    if(root)tab_delete(root);
}

int SymbolTable::get_size(){
    return size;
}

SymEntry* SymbolTable::get_root(){
    return root;
}

void SymbolTable::insert(string k,UnlimitedRational* v){
    SymEntry *at=this->root;
    for(;at;){
        if(k>at->key){
            if(at->right){
                at=at->right;
            }
            else{
                at->right = new SymEntry(k,v);
                size++;
                return;
            }
        }
        else if(k<at->key){
            if(at->left){
                at=at->left;
            }
            else{
                at->left = new SymEntry(k,v);
                size++;
                return;
            }
        }
        else{
            delete at->val;
            at->val=v;
            return;
        }
    }
    root = new SymEntry(k,v);
}

void SymbolTable::remove(string k){
    SymEntry* at=this->root;
    SymEntry* parent=NULL,*other,*ot_par,*child;
    for(;at;){
        if(at->key==k){
            if(at->left && at->right){
                ot_par=at;
                other=at->left;
                for(;other->right;){
                    ot_par=other;
                    other=other->right;
                }
                at->key=other->key;
                at->val=other->val;
                at=other;
                parent=ot_par;
            }
            child=NULL;
            if(at->left)child=at->left;
            else if(at->right)child=at->right;
            if(parent){
                if(parent->right==at)parent->right=child;
                else parent->left=child;
            }
            else root=child;
            delete at;
            size--;
            return;
        }
        else if(at->key>k)
        {
            parent=at;
            at=at->left;
        }
        else{
            parent=at;
            at=at->right;
        }
    }
}

UnlimitedRational* SymbolTable::search(string k){
    SymEntry* at=this->root;
    for(;at;){
        if(at->key==k){
            return at->val;
        }
        else if(at->key>k)at=at->left;
        else at=at->right;
    }
    return NULL;
}