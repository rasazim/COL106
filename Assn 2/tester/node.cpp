#include "node.h"
#include<stdexcept>

Node::Node(bool sentinel){
    is_sentinel=sentinel;
    next=NULL;
    prev=NULL;
    value=-1;
}

Node::Node(int v, Node* nxt, Node* prv){
    is_sentinel=false;
    next=nxt;
    prev=prv;
    value=v;
}

bool Node::is_sentinel_node(){
    return is_sentinel;
}

int Node::get_value(){
    return value;
}