#include "stack_a.h"
#include<stdexcept>
#include<iostream>

Stack_A::Stack_A(){
    size=0;
}

void Stack_A::push(int data){
    if(size>=1024){
        throw std::runtime_error("Stack Full");
    }
    else stk[size++]=data;
}

int Stack_A::pop(){
    if(size<=0){
        throw std::runtime_error("Empty Stack");
    }
    return stk[--size];
}

int Stack_A::get_element_from_top(int idx){
    if(idx<0 || idx>=size){
        throw std::runtime_error("Index out of range");
    }
    return stk[size-idx-1];
}

int Stack_A::get_element_from_bottom(int idx){
    if(idx<0 || idx>=size){
        throw std::runtime_error("Index out of range");
    }
    return stk[idx];
}

void Stack_A::print_stack(bool top_or_bottom){
    if(size==0)return;
    if(top_or_bottom){
        for(int i=size-1;i>=0;i--){
            std::cout<<stk[i]<<"\n";
        }
    }
    else{
        for(int i=0;i<size;i++){
            std::cout<<stk[i]<<"\n";
        }
    }
}

int Stack_A::add(){
    if(size<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = pop();
    int b = pop();
    push(b+a);
    return stk[size-1];
}

int Stack_A::subtract(){
    if(size<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = pop();
    int b = pop();
    push(b-a);
    return stk[size-1];
}

int Stack_A::multiply(){
    if(size<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = pop();
    int b = pop();
    push(b*a);
    return stk[size-1];
}

int Stack_A::divide(){
    if(size<2){
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

int* Stack_A::get_stack(){
    return stk;
}

int Stack_A::get_size(){
    return size;
}