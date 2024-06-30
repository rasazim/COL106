#include<iostream>
#include "stack_c.h"
using namespace std;

int main(){

Stack_C A;
cout<<"Created"<<endl;
A.push(2);
A.push(10);
A.push(-6);
A.push(4);
A.push(-15);
A.push(4);
A.push(5);
A.push(11);
A.push(-9);
A.push(-7);
A.print_stack(true);
cout<<A.get_size()<<endl;
cout<<"here"<<endl;
cout<<A.add()<<endl;
cout<<A.add()<<endl;
cout<<A.add()<<endl;
cout<<A.subtract()<<endl;
cout<<A.subtract()<<endl;
cout<<A.divide()<<endl;
cout<<A.divide()<<endl;
cout<<A.multiply()<<endl;
cout<<A.multiply()<<endl;
A.print_stack(true);
cout<<flush;


}