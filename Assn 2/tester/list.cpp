#include "list.h"
#include <stdexcept>


List::List(){
    try{
        sentinel_head=new Node(true);
        sentinel_tail=new Node(true);
    }
    catch(std::exception e){
        throw std::runtime_error("Out of Memory");
    }
    sentinel_head->next=sentinel_tail;
    sentinel_tail->prev=sentinel_head;
    sentinel_head->prev=sentinel_tail;
    sentinel_tail->next=sentinel_head;
    size=0;
}

List::~List(){
    Node* at=sentinel_head;
    while(at!=sentinel_tail){
        at=at->next;
        delete at->prev;
    }
    delete sentinel_tail;
}

void List::insert(int v){
    Node* temp;
    try{
        temp=new Node(v,sentinel_tail,sentinel_tail->prev);
    }
    catch(std::exception e){
        throw std::runtime_error("Out of Memory");
    }
    temp->prev->next=temp;
    sentinel_tail->prev=temp;
    size++;
}

int List::delete_tail(){
    if(size==0)throw std::runtime_error("Empty Stack");
    Node* temp = sentinel_tail->prev;
    temp->prev->next = sentinel_tail;
    sentinel_tail->prev=temp->prev;
    int v=temp->get_value();
    delete temp;
    size--;
    return v;
}

int List::get_size(){
    return size;
}

Node* List::get_head(){
    return sentinel_head;
}


