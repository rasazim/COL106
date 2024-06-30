#include "stack_c.h"
#include<stdexcept>
#include<iostream>



Stack_C::Stack_C(){
    try{
        stk=new List();
    }
    catch(std::exception e){
        throw std::runtime_error("Out Of Memory");
    }
}

// Destructor
Stack_C::~Stack_C(){
    delete stk;
}

void Stack_C::push(int data){
    stk->insert(data);
}

int Stack_C::pop(){
    return stk->delete_tail();
}

int Stack_C::get_element_from_top(int idx){
    if(idx<0 || idx>=stk->get_size()){
        throw std::runtime_error("Index out of range");
    }
    Node *at = stk->get_head()->next;
    idx=stk->get_size()-idx-1;
    for(int i=0;i<idx;i++){
        at=at->next;
    }
    return at->get_value();
}

int Stack_C::get_element_from_bottom(int idx){
    if(idx<0 || idx>=stk->get_size()){
        throw std::runtime_error("Index out of range");
    }
    Node *at = stk->get_head()->next;
    for(int i=0;i<idx;i++){
        at=at->next;
    }
    return at->get_value();
}

void Stack_C::print_stack(bool top_or_bottom){
    if(stk->get_size()==0)return;
    if(top_or_bottom){
        Node *at = stk->get_head()->prev->prev,*head=stk->get_head();
        while(at!=head){
            std::cout<<at->get_value()<<"\n";
            at=at->prev;
        }
    }
    else{
        Node *at = stk->get_head()->next,*tail=stk->get_head()->prev;
        while(at!=tail){
            std::cout<<at->get_value()<<"\n";
            at=at->prev;
        }
    }
}

int Stack_C::add(){
    if(stk->get_size()<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = pop();
    int b = pop();
    int c = a+b;
    push(c);
    return c;
}

int Stack_C::subtract(){
    if(stk->get_size()<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = pop();
    int b = pop();
    int c = b-a;
    push(c);
    return c;
}

int Stack_C::multiply(){
    if(stk->get_size()<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = pop();
    int b = pop();
    int c = b*a;
    push(c);
    return c;
}

int Stack_C::divide(){
    if(stk->get_size()<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    int b = pop();
    int a = pop();
    int c=-1;
    if(b==0)throw std::runtime_error("Divide by Zero Error");
    c = (a-a%b)/b;
    if(a*b<0 && a%b!=0)c--;
    push(c);
    return c;
}

List* Stack_C::get_stack(){
    return stk;
}

int Stack_C::get_size(){
    return stk->get_size();
}