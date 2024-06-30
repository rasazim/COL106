/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

// #include "symnode.cpp"

//Write your code below this line

//helper

SymNode* heighter(SymNode* at,int height){
    at->height = height;
    SymNode* new_at=at, *par = at->par;
    if(at->left && at->right){
        if(at->left->height - at->right->height>1){
            if(at->left->left && at->left->right){
                if(at->left->left->height>=at->left->right->height){
                    new_at = at->LeftLeftRotation();
                    at->height-=2;
                }
                else{
                    new_at = at->LeftRightRotation();
                    new_at->height++;
                    at->height-=2;
                    new_at->left->height-=1;
                }
            }
            else if(at->left->left){
                new_at = at->LeftLeftRotation();
                at->height-=2;
            }
            else{
                new_at = at->LeftRightRotation();
                new_at->height++;
                at->height-=2;
                new_at->left->height-=1;
            }
        }
        else if(at->right->height - at->left->height>1){
            if(at->right->left && at->right->right){
                if(at->right->right->height>=at->right->left->height){
                    new_at = at->RightRightRotation();
                    at->height-=2;
                }
                else{
                    new_at = at->RightLeftRotation();
                    new_at->height++;
                    at->height-=2;
                    new_at->right->height-=1;
                }
            }
            else if(at->right->right){
                new_at = at->RightRightRotation();
                at->height-=2;
            }
            else{
                new_at = at->RightLeftRotation();
                new_at->height++;
                at->height-=2;
                new_at->right->height-=1;
            }
        }
    }
    else if(at->left){
        if(at->left->height > 0){
            if(at->left->left && at->left->right){
                if(at->left->left->height>=at->left->right->height){
                    new_at = at->LeftLeftRotation();
                    at->height-=2;
                }
                else{
                    new_at = at->LeftRightRotation();
                    new_at->height++;
                    at->height-=2;
                    new_at->left->height-=1;
                }
            }
            else if(at->left->left){
                new_at = at->LeftLeftRotation();
                at->height-=2;
            }
            else{
                new_at = at->LeftRightRotation();
                new_at->height++;
                at->height-=2;
                new_at->left->height-=1;
            }
        }
    }
    else if(at->right){
        if(at->right->height > 0){
            if(at->right->left && at->right->right){
                if(at->right->right->height>=at->right->left->height){
                    new_at = at->RightRightRotation();
                    at->height-=2;
                }
                else{
                    new_at = at->RightLeftRotation();
                    new_at->height++;
                    at->height-=2;
                    new_at->right->height-=1;
                }
            }
            else if(at->right->right){
                new_at = at->RightRightRotation();
                at->height-=2;
            }
            else{
                new_at = at->RightLeftRotation();
                new_at->height++;
                at->height-=2;
                new_at->right->height-=1;
            }
        }
    }
    if(par){
        if(par->left==at){
            par->left = new_at;
            new_at->par = par;
            if(par->right)
            return heighter(par,max(par->left->height,par->right->height)+1);
            else 
            return heighter(par,par->left->height+1);
        }
        else{
            par->right = new_at;
            new_at->par = par;
            if(par->left)
            return heighter(par,max(par->left->height,par->right->height)+1);
            else
            return heighter(par,par->right->height+1);
        }
    }
    else{
        new_at->par = NULL;
        return new_at;
    }
}

// SymNode* height_ins(SymNode* at,int height,bool dir_left,bool new_dir_left){
//     at->height = height;
//     SymNode* new_at=at, *par = at->par;
//     if(at->left && at->right){
//         if(at->left->height - at->right->height>1){
//             if(dir_left){
//                 new_at = at->LeftLeftRotation();
//                 at->height-=2;
//             }
//             else{
//                 new_at = at->LeftRightRotation();
//                 new_at->height++;
//                 at->height-=2;
//                 new_at->left->height-=1;
//             }
//         }
//         else if(at->right->height - at->left->height>1){
//             if(dir_left){
//                 new_at = at->RightLeftRotation();
//                 new_at->height++;
//                 at->height-=2;
//                 new_at->right->height-=1;
//             }
//             else{
//                 new_at = at->RightRightRotation();
//                 at->height-=2;
//             }
//         }
//     }
//     else if(at->left){
//         if(at->left->height>0){
//             if(dir_left){
//                 new_at = at->LeftLeftRotation();
//                 at->height-=2;
//             }
//             else{
//                 new_at = at->LeftRightRotation();
//                 new_at->height++;
//                 at->height-=2;
//                 new_at->left->height-=1;
//             }
//         }
//     }
//     else if(at->right){
//         if(at->right->height>0){
//             if(dir_left){
//                 new_at = at->RightLeftRotation();
//                 new_at->height++;
//                 at->height-=2;
//                 new_at->right->height-=1;
//             }
//             else{
//                 new_at = at->RightRightRotation();
//                 at->height-=2;
//             }
//         }
//     }
//     if(par){
//         if(par->left==at){
//             par->left = new_at;
//             new_at->par = par;
//             if(par->right)
//             return height_ins(par,max(par->left->height,par->right->height)+1,new_dir_left,true);
//             else 
//             return height_ins(par,par->left->height+1,new_dir_left,true);
//         }
//         else{
//             par->right = new_at;
//             new_at->par = par;
//             if(par->left)
//             return height_ins(par,max(par->left->height,par->right->height)+1,new_dir_left,false);
//             else
//             return height_ins(par,par->right->height+1,new_dir_left,false);
//         }
//     }
//     else{
//         new_at->par = NULL;
//         return new_at;
//     }
// }

// SymNode* height_rem(SymNode* at,int height,bool dir_left,bool new_dir_left){
//     at->height = height;
//     SymNode* new_at=at, *par = at->par;
//     if(at->left && at->right){
//         if(at->left->height - at->right->height>1){
//             if(dir_left){
//                 new_at = at->LeftLeftRotation();
//                 at->height-=2;
//             }
//             else{
//                 new_at = at->LeftRightRotation();
//                 new_at->height++;
//                 at->height-=2;
//                 new_at->left->height-=1;
//             }
//         }
//         else if(at->right->height - at->left->height>1){
//             if(dir_left){
//                 new_at = at->RightLeftRotation();
//                 new_at->height++;
//                 at->height-=2;
//                 new_at->right->height-=1;
//             }
//             else{
//                 new_at = at->RightRightRotation();
//                 at->height-=2;
//             }
//         }
//     }
//     else if(at->left){
//         if(at->left->height>0){
//             if(dir_left){
//                 new_at = at->LeftLeftRotation();
//                 at->height-=2;
//             }
//             else{
//                 new_at = at->LeftRightRotation();
//                 new_at->height++;
//                 at->height-=2;
//                 new_at->left->height-=1;
//             }
//         }
//     }
//     else if(at->right){
//         if(at->right->height>0){
//             if(dir_left){
//                 new_at = at->RightLeftRotation();
//                 new_at->height++;
//                 at->height-=2;
//                 new_at->right->height-=1;
//             }
//             else{
//                 new_at = at->RightRightRotation();
//                 at->height-=2;
//             }
//         }
//     }
// }

void deleter(SymNode* root){
    if(!root)return;
    deleter(root->left);
    deleter(root->right);
    delete root;
}




//code

SymbolTable::SymbolTable(){
    size=0;
    root=NULL;
}

void SymbolTable::insert(string k){
    if(size==0){
        root = new SymNode(k);
        root->height = 0;
        size=1;
        return;
    }
    SymNode *at = root,*par = NULL;
    for(;at;){
        par = at;
        if(at->key < k){
            at = at->right;

        }
        else if(at->key > k){
            at = at->left;
        }
        else return;
    }
    size++;
    if(par->key<k){
        par->right = new SymNode(k);
        par->right->par=par;
        at = par->right;
    }
    else{
        par->left = new SymNode(k);
        par->left->par=par;
        at = par->left;
    }
    root = heighter(at,0);
}

void SymbolTable::remove(string k){
    SymNode* at = root, *par, *suc;
    for(;at;){
        if(at->key == k){
            size--;
            if(at->left && at->right){
                suc = at->right;
                for(;suc->left;) suc = suc->left;
                at->key = suc->key;
                at->address = suc->address;
                k = suc->key;
                at = suc;
                continue;
            }
            else if(at->left){
                par = at->par;
                if(par){
                    if(par->right==at){
                        par->right = at->left;
                        delete at;
                        if(par->left){
                            root = heighter(par,max(par->left->height,par->right->height)+1);
                        }
                        else{
                            root = heighter(par,par->right->height+1);
                        }
                    }
                    else{
                        par->left = at->left;
                        delete at;
                        if(par->right){
                            root = heighter(par,max(par->left->height,par->right->height)+1);
                        }
                        else{
                            root = heighter(par,par->left->height+1);
                        }
                    }
                }
                else{
                    root=at->left;
                    delete at;
                }
            }
            else if(at->right){
                par = at->par;
                if(par){
                    if(par->right==at){
                        par->right = at->right;
                        delete at;
                        if(par->left){
                            root = heighter(par,max(par->left->height,par->right->height)+1);
                        }
                        else{
                            root = heighter(par,par->right->height+1);
                        }
                    }
                    else{
                        par->left = at->right;
                        delete at;
                        if(par->right){
                            root = heighter(par,max(par->left->height,par->right->height)+1);
                        }
                        else{
                            root = heighter(par,par->left->height+1);
                        }
                    }
                }
                else{
                    root=at->right;
                    delete at;
                }
            }
            else{
                par = at->par;
                if(par){
                    if(par->right==at){
                        delete at;
                        par->right = NULL;
                        if(par->left){
                            root = heighter(par,par->left->height+1);
                        }
                        else{
                            root = heighter(par,0);
                        }
                    }
                    else{
                        delete at;
                        par->left = NULL;
                        if(par->right){
                            root = heighter(par,par->right->height+1);
                        }
                        else{
                            root = heighter(par,0);
                        }
                    }
                }
                else{
                    delete at;
                    root=NULL;
                }
            }
            return;
        }
        else if(at->key > k) at = at->left;
        else at = at->right;
    }
    // throw "Not found";
}

int SymbolTable::search(string k){
    SymNode* at = root;
    for(;at;){
        if(at->key == k) return at->address;
        else if(at->key > k) at = at->left;
        else at = at->right;
    }
    return -2;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* at = root;
    for(;at;){
        if(at->key == k){
            at->address = idx;
            return;
        }
        else if(at->key > k) at = at->left;
        else at = at->right;
    }
    throw "Not found";
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    deleter(root);
    root=NULL;
}



//debug

// #include <bits/stdc++.h>

// void print_bst(SymNode* root){
//     deque<pair<int,SymNode*>> A;
//     pair<int,SymNode*> at;
//     A.push_back(make_pair(0,root));
//     int d = 0;
//     for(;!A.empty();){
//         at = A.front();
//         A.pop_front();
//         if(at.first > d){
//             d++;
//             cout<<endl;
//         }
//         cout<<at.second->key<<"("<<at.second->height<<") ";
//         if(at.second->left)
//         A.push_back(make_pair(d+1,at.second->left));
//         if(at.second->right)
//         A.push_back(make_pair(d+1,at.second->right));
//     }
//     cout<<endl<<endl;
// }


// int main(){
//     SymbolTable A;
//     A.insert("e");
//     print_bst(A.get_root());
//     A.insert("b");
//     print_bst(A.get_root());
//     A.insert("c");
//     print_bst(A.get_root());
//     A.insert("d");
//     print_bst(A.get_root());
//     A.insert("a");
//     print_bst(A.get_root());
//     A.remove("c");
//     print_bst(A.get_root());
//     A.remove("b");
//     print_bst(A.get_root());
// }