/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
// #include "heapnode.cpp"

//Write your code below this line

//helpers

void min_del(HeapNode* root){
    if(root){
        min_del(root->left);
        root->left = NULL;
        min_del(root->right);
        root->right = NULL;
        delete root;
    }
}



//Code 

MinHeap::MinHeap(){
    size = 0;
    root=NULL;
}

void MinHeap::push_heap(int num){
    int temp;
    if(size == 0){
        root=new HeapNode(num);
        size=1;
        return;
    }
    size++;
    int pos = 1<<30;
    for(;!(size & pos);)pos>>=1;
    pos>>=1;
    HeapNode *at=root;
    for(;pos!=1;){
        if((size & pos))
        at=at->right;
        else at=at->left;
        pos>>=1;
    }
    if((size & pos)){
        at->right = new HeapNode(num);
        at->right->par = at;
        at = at->right;
    }
    else{
        at->left = new HeapNode(num);
        at->left->par = at;    
        at=at->left;
    }
    if(at!=root)
    for(;at->val<at->par->val;){
        temp = at->val;
        at->val=at->par->val;
        at->par->val=temp;
        at = at->par;
        if(at==root)break;
    }
}

int MinHeap::get_min(){
    return root->val;
}

void MinHeap::pop(){
    int temp;
    if(size == 0){
        throw "Empty heap";
    }
    else if(size==1){
        delete root;
        root = NULL;
        size--;
        return;
    }
    int pos = 1<<30;
    for(;!(size & pos);)pos>>=1;
    pos>>=1;
    HeapNode *at=root;
    for(;pos!=1;){
        if((size & pos))
        at=at->right;
        else at=at->left;
        pos>>=1;
    }
    if((size & pos)) at=at->right;
    else at=at->left;
    root->val = at->val;
    if((size & pos)) at->par->right=NULL;
    else at->par->left=NULL;
    delete at;
    at = NULL;
    at = root;
    size--;
    for(;;){
        if(at->left){
            if(at->val > at->left->val){
                if(at->right){
                    if(at->val<=at->right->val || (at->val > at->right->val && at->left->val < at->right->val)){
                        temp = at->val;
                        at->val=at->left->val;
                        at->left->val=temp;
                        at = at->left;
                    }
                    else{
                        temp = at->val;
                        at->val=at->right->val;
                        at->right->val=temp;
                        at = at->right;
                    }
                }
                else{
                    temp = at->val;
                    at->val=at->left->val;
                    at->left->val=temp;
                    at = at->left;
                }
            }
            else{
                if(at->right){
                    if(at->val > at->right->val){
                        temp = at->val;
                        at->val=at->right->val;
                        at->right->val=temp;
                        at = at->right;
                    }
                    else break;
                }
                else break;
            }
        }
        else break;
    }
}

MinHeap::~MinHeap(){ 
    // min_del(root);
}


//debug
// #include <iostream>
// using namespace std;

// int main(){
//     MinHeap A;
//     A.push_heap(5);
//     A.push_heap(4);
//     A.push_heap(2);
//     A.push_heap(57);
//     A.push_heap(2);
//     A.push_heap(6);
//     A.push_heap(5);
//     A.push_heap(3);
//     A.push_heap(1);
//     cout<<A.get_min()<<endl;
//     A.pop();
//     cout<<A.get_min()<<endl;
//     A.pop();
//     cout<<A.get_min()<<endl;
//     A.pop();
//     cout<<A.get_min()<<endl;
//     A.pop();
//     cout<<A.get_min()<<endl;
//     A.pop();
//     cout<<A.get_min()<<endl;
//     A.pop();
//     cout<<A.get_min()<<endl;
//     A.pop();
//     cout<<A.get_min()<<endl;
//     A.pop();
//     cout<<A.get_min()<<endl;
//     A.pop();
// }