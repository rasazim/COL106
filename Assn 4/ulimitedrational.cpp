/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
// #include<iostream>


//helpers

bool greater_unint(UnlimitedInt* i1,UnlimitedInt* i2);
bool equals_unint(UnlimitedInt* i1,UnlimitedInt* i2);


bool equals_unrat(UnlimitedRational* i1,UnlimitedRational* i2){
    string p1=i1->get_p_str(),p2=i2->get_p_str(),q1=i1->get_q_str(),q2=i2->get_q_str();
    bool s1=true,s2=true;
    if(p1[0]=='-'){
        s1=!s1;
        p1 = p1.substr(1);
    }
    if(q1[0]=='-'){
        s1=!s1;
        q1 = q1.substr(1);
    }
    if(p2[0]=='-'){
        s2=!s2;
        p2 = p2.substr(1);
    }
    if(q2[0]=='-'){
        s2=!s2;
        q2 = q2.substr(1);
    }
    return s1==s2 && p1==p2 && q1==q2;
}

UnlimitedInt* gcd_uint(UnlimitedInt* num,UnlimitedInt* den){
    UnlimitedInt *temp;
    if(greater_unint(den,num)){
        temp=den;
        den=num;
        num=temp;
    }
    temp = UnlimitedInt::mod(num,den);
    num=den;
    den=temp;
    if(den->get_capacity()==1 && den->get_array()[0]==0){
        int *unint=new int[num->get_capacity()],*ounint=num->get_array();
        for(int i=num->get_capacity()-1;i>=0;i--)unint[i]=ounint[i];
        return new UnlimitedInt(unint,num->get_capacity(),1,num->get_size());
    }
    temp = UnlimitedInt::mod(num,den);
    num = den;
    den = temp;
    if(den->get_capacity()==1 && den->get_array()[0]==0){
        delete den;
        return num;
    }
    for(;den->get_capacity()>1 || den->get_array()[0]!=0;){
        temp = UnlimitedInt::mod(num,den);
        delete num;
        num=den;
        den=temp;
        if(den->get_capacity()==1 && den->get_array()[0]==0){
            delete den;
            return num;
        }
    }
    return new UnlimitedInt();
}

//Constructors

UnlimitedRational::UnlimitedRational(){
    p = new UnlimitedInt();
    q = new UnlimitedInt(1);
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num,UnlimitedInt* den){
    if(den->get_capacity()==1 && den->get_array()[0]==0){
        p = new UnlimitedInt();
        q = new UnlimitedInt();
        return;
    }
    UnlimitedInt* gcd = gcd_uint(num,den);
    p = UnlimitedInt::div(num,gcd);
    q = UnlimitedInt::div(den,gcd);
}

UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    return p->to_string();
}

string UnlimitedRational::get_q_str(){
    return q->to_string();
}

string UnlimitedRational::get_frac_str(){
    return p->to_string()+"/"+q->to_string();
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational *i1,UnlimitedRational *i2){
    UnlimitedInt* p1 = i1->get_p(),*p2=i2->get_p(),*q1=i1->get_q(),*q2=i2->get_q();
    UnlimitedInt* temp1 = UnlimitedInt::mul(p1,q2),*temp2 = UnlimitedInt::mul(p2,q1),*temp3 = UnlimitedInt::mul(q1,q2);
    UnlimitedInt *temp4 = UnlimitedInt::add(temp1,temp2);
    delete temp1;
    delete temp2;
    UnlimitedRational *ans = new UnlimitedRational(temp4,temp3);
    delete temp3;
    delete temp4;
    return ans;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational *i1,UnlimitedRational *i2){
    UnlimitedInt* p1 = i1->get_p(),*p2=i2->get_p(),*q1=i1->get_q(),*q2=i2->get_q();
    UnlimitedInt* temp1 = UnlimitedInt::mul(p1,q2),*temp2 = UnlimitedInt::mul(p2,q1),*temp3 = UnlimitedInt::mul(q1,q2);
    UnlimitedInt *temp4 = UnlimitedInt::sub(temp1,temp2);
    delete temp1;
    delete temp2;
    UnlimitedRational *ans = new UnlimitedRational(temp4,temp3);
    delete temp3;
    delete temp4;
    return ans;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational *i1,UnlimitedRational *i2){
    UnlimitedInt* p1 = i1->get_p(),*p2=i2->get_p(),*q1=i1->get_q(),*q2=i2->get_q();
    UnlimitedInt* temp1 = UnlimitedInt::mul(p1,p2),*temp2 = UnlimitedInt::mul(q1,q2);
    UnlimitedRational *ans = new UnlimitedRational(temp1,temp2);
    delete temp1;
    delete temp2;
    return ans;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational *i1,UnlimitedRational *i2){
    UnlimitedInt* p1 = i1->get_p(),*p2=i2->get_p(),*q1=i1->get_q(),*q2=i2->get_q();
    UnlimitedInt* temp1 = UnlimitedInt::mul(p1,q2),*temp2 = UnlimitedInt::mul(p2,q1);
    UnlimitedRational *ans = new UnlimitedRational(temp1,temp2);
    delete temp1;
    delete temp2;
    return ans;
}




