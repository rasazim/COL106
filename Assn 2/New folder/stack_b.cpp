#include "stack_b.h"
#include<stdexcept>
#include<iostream>

void resize(bool expand,int *&stk,int &capacity,int size){
    if(expand){
        capacity=capacity*2;
    }
    else{
        capacity/=2;
    }
        int *new_stk;
        try{
            new_stk=new int[capacity];
        }
        catch(std::exception e){
            throw std::runtime_error("Out of Memory");
        }
        for(int i=0;i<size;i++){
            new_stk[i]=stk[i];
        }
        delete[] stk;
        stk=new_stk;
}

Stack_B::Stack_B(){
    capacity=1024;
    try{
        stk=new int[capacity];
    }
    catch(std::exception e){
        throw std::runtime_error("Out of Memory");
    }
    size=0;
}

Stack_B::~Stack_B(){
    delete[] stk;
}

void Stack_B::push(int data){
    if(size>=capacity){
        resize(true,stk,capacity,size);
    }  
    stk[size++]=data;
}

int Stack_B::pop(){
    if(size<=0){
        throw std::runtime_error("Empty Stack");
    }
    if(size-1<=capacity/4 && capacity>1024){
        resize(false,stk,capacity,size);
    }
    return stk[--size];
}

int Stack_B::get_element_from_top(int idx){
    if(idx<0 || idx>=size){
        throw std::runtime_error("Index out of range");
    }
    return stk[size-idx-1];
}

int Stack_B::get_element_from_bottom(int idx){
    if(idx<0 || idx>=size){
        throw std::runtime_error("Index out of range");
    }
    return stk[idx];
}

void Stack_B::print_stack(bool top_or_bottom){
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

int Stack_B::add(){
    if(size<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = pop();
    int b = pop();
    push(b+a);
    return stk[size-1];
}

int Stack_B::subtract(){
    if(size<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = pop();
    int b = pop();
    push(b-a);
    return stk[size-1];
}

int Stack_B::multiply(){
    if(size<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    int a = pop();
    int b = pop();
    push(b*a);
    return stk[size-1];
}

int Stack_B::divide(){
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

int* Stack_B::get_stack(){
    return stk;
}

int Stack_B::get_size(){
    return size;
}