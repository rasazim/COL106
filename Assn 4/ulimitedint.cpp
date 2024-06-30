/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"


// #include<iostream>
// using namespace std;

int p10[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};

//helpers

// UnlimitedInt* gcd_uint(UnlimitedInt* num,UnlimitedInt* den);

void resize(int*& unlimitedInt,int new_cap,int size){
    int* temp = unlimitedInt;
    unlimitedInt=new int[new_cap];
    for(int i=0;i<size;i++){
        unlimitedInt[i]=temp[i];
    }
    delete[] temp;
    temp=NULL;
}

bool greater_unint(UnlimitedInt* i1,UnlimitedInt* i2){
    if(i1->get_capacity()==1 && i1->get_array()[0]==0 && i2->get_capacity()==1 && i2->get_array()[0]==0)return false;
    bool reverse=false;
    if(i1->get_sign()==-1){
        if(i2->get_sign()==-1){
            reverse=true;
        }
        else return false;
    }
    else{
        if(i2->get_sign()==-1){
            return true;
        }
    }
    if(i1->get_size()>i2->get_size())return !reverse;
    else if(i1->get_size()<i2->get_size())return reverse;
    else{
        int *unint1=i1->get_array(),*unint2=i2->get_array();
        for(int i=i1->get_capacity()-1;i>=0;i--){
            if(unint1[i]>unint2[i])return !reverse;
            else if(unint1[i]<unint2[i])return reverse;
        }
        return reverse;
    }
}

bool equals_unint(UnlimitedInt* i1,UnlimitedInt* i2){
    if(i1->get_capacity()==1 && i1->get_array()[0]==0 && i2->get_capacity()==1 && i2->get_array()[0]==0)return true;
    if(i1->get_sign()==i2->get_sign() && i1->get_size()==i2->get_size()){
        int *unint1=i1->get_array(),*unint2=i2->get_array();
        for(int i=i1->get_capacity()-1;i>=0;i--){
            if(unint1[i]!=unint2[i])return false;
        }
        return true;
    }
    return false;
}

UnlimitedInt* int_q(UnlimitedInt* rem,UnlimitedInt* div){
    int s=0,e=p10[9],m;
    UnlimitedInt *G,*G2,*M;
    for(;s<e;){
        m=(s+e)/2;
        M = new UnlimitedInt(m);
        G = UnlimitedInt::mul(div,M);
        G2 =UnlimitedInt::add(G,div);
        if(greater_unint(G,rem)){
            e=m;
        }
        else{
            if(greater_unint(G2,rem)){
                delete G;
                delete G2;
                return M;
            }
            s=m;
        }
        delete M;
        delete G;
        delete G2;
    }
    return new UnlimitedInt(s);
}


//Constructors

UnlimitedInt::UnlimitedInt(){
    this->sign = 1;
    this->size = 1;
    this->capacity = 1;
    this->unlimited_int=new int[this->capacity];
    unlimited_int[0]=0;
}

UnlimitedInt::UnlimitedInt(string s){
    this->size=s.size();
    this->sign=1;
    if(s[0]=='-'){
        this->size--;
        this->sign=-1;
    }
    this->capacity=(this->size-1)/9+1;
    this->unlimited_int = new int[this->capacity];
    int curr=0,p=0,pos=0;
    for(int i=s.size()-1,j=0;j<this->size;j++,i--){
        curr += (s[i]-'0')*p10[p++];
        if(p>=9){
            p=0;
            unlimited_int[pos++]=curr;
            curr=0;
        }
    }
    if(curr){
        unlimited_int[pos]=curr;
        pos++;
    }
}

UnlimitedInt::UnlimitedInt(int i){
    this->sign=1;
    if(i<0){
        this->sign=-1;
        i=~i+1;
    }
    if(i<p10[9]){
        this->capacity=1;
        this->size=1;
        for(int j=8;j>=0;j--){
            if(i>=p10[j]){
                this->size=j+1;
                break;
            }
        }
        unlimited_int = new int[this->capacity];
        unlimited_int[0]=i;
    }
    else{
        this->capacity=2;
        this->size=10;
        unlimited_int = new int[this->capacity];
        unlimited_int[0]=i%p10[9];
        unlimited_int[1]=i/p10[9];
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    this->unlimited_int=ulimited_int;
    this->capacity=cap;
    this->sign=sgn;
    this->size=sz;
}

//Destructor

UnlimitedInt::~UnlimitedInt(){
    delete[] unlimited_int;
}

//get methods

int* UnlimitedInt::get_array(){
    return this->unlimited_int;
}

int UnlimitedInt::get_capacity(){
    return this->capacity;
}

int UnlimitedInt::get_size(){
    return this->size;
}

int UnlimitedInt::get_sign(){
    return this->sign;
}

//static arithmetic functions

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    int *unint;
    int sgn=1,sz,cap;
    if(i1->sign==-1){
        if(i2->sign==-1){
            sgn=-1;
        }
        else{
            i1->sign=1;
            UnlimitedInt *ans = sub(i2,i1);
            i1->sign=-1;
            return ans;
        }
    }
    else{
        if(i2->sign==-1){
            i2->sign=1;
            UnlimitedInt *ans = sub(i1,i2);
            i2->sign=-1;
            return ans;
        }
    }
    cap = max(i1->capacity,i2->capacity);
    unint=new int[cap];
    int d1,d2,carry=0;
    for(int i=0;i<cap;i++){
        d1=0;d2=0;
        if(i<i1->capacity)d1=i1->unlimited_int[i];
        if(i<i2->capacity)d2=i2->unlimited_int[i];
        unint[i]=d1+d2+carry;
        carry=0;
        if(unint[i]>=p10[9]){
            unint[i]-=p10[9];
            carry=1;
        }
    }
    if(carry){
        resize(unint,cap+1,cap);
        unint[cap++]=1;
        sz = 9*(cap-1)+1;
    }
    else{
        sz = 9*(cap-1);
        for(int j=8;j>=0;j--){
            if(unint[cap-1]>=p10[j]){
                sz+=j+1;
                break;
            }
        }
        if(sz==0)sz=1;
    }
    return new UnlimitedInt(unint,cap,sgn,sz);
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    int *unint;
    int sgn=1,sz,cap;
    if(i1->sign==-1){
        if(i2->sign==-1){
            sgn=-1;
        }
        else{
            i2->sign=-1;
            UnlimitedInt* ans = add(i1,i2);
            i2->sign=1;
            return ans;
        }
    }
    else{
        if(i2->sign==-1){
            i2->sign=1;
            UnlimitedInt* ans = add(i1,i2);
            i2->sign=-1;
            return ans;
        }
    }
    if(sgn==1 && greater_unint(i2,i1)){
        sgn=-1;
        UnlimitedInt* temp=i1;
        i1=i2;
        i2=temp;
        temp=NULL;
    }
    else if(sgn==-1 && greater_unint(i1,i2)){
        sgn=1;
        UnlimitedInt* temp=i1;
        i1=i2;
        i2=temp;
        temp=NULL;
    }

    cap = max(i1->capacity,i2->capacity);
    unint = new int[cap];
    
    int d1,d2,carry=0;
    for(int i = 0;i<cap;i++){
        d1=0;
        d2=0;
        if(i<i1->capacity)d1=i1->unlimited_int[i];
        if(i<i2->capacity)d2=i2->unlimited_int[i];
        unint[i]=d1-d2+carry;
        carry=0;
        if(unint[i]<0){
            unint[i]+=p10[9];
            carry=-1;
        }
    }
    for(;unint[cap-1]==0 && cap>1;) cap--;
    resize(unint,cap,cap);
    sz = 9*(cap-1);
    for(int j=8;j>=0;j--){
        if(unint[cap-1]>=p10[j]){
            sz+=j+1;
            break;
        }
    }
    if(sz==0)sz=1;
    return new UnlimitedInt(unint,cap,sgn,sz);
}


UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1,UnlimitedInt* i2){
    if((i1->capacity==1 && i1->unlimited_int[0]==0 ) || (i2->capacity==1 && i2->unlimited_int[0]==0)){
        int* unint = new int[1];
        unint[0]=0;
        return new UnlimitedInt(unint,1,0,1);
    }
    int cap,sz,sgn=i1->sign*i2->sign;
    long long int carry,dig;
    cap=i1->capacity+i2->capacity;
    long long int *unlint=new long long int [i1->capacity*(i2->capacity+1)];
    int* unint = new int[cap];
    for(int i=0;i<i1->capacity;i++){
        carry=0;
        for(int j=0;j<i2->capacity;j++){
            dig = ((long long int)(i1->unlimited_int[i]))*((long long int)(i2->unlimited_int[j]))+carry;
            unlint[i*(i2->capacity+1) + j]=dig%((long long int)(p10[9]));
            carry=dig/((long long int)(p10[9]));
        }
        unlint[i*(i2->capacity+1) + i2->capacity]=carry;
    }
    carry=0;
    for(int i=0;i<i1->capacity+i2->capacity;i++){
        unint[i]=carry;
        carry=0;
        for(int j=max(0,i-i2->capacity);j<=i && j<i1->capacity;j++){
            unint[i]+=unlint[j*i2->capacity + i];
            if(unint[i]>=p10[9]){
                carry++;
                unint[i]-=p10[9];
            }
        }
    }
    delete[] unlint;
    for(;unint[cap-1]==0 && cap>1;) cap--;
    resize(unint,cap,cap);
    sz = 9*(cap-1);
    for(int j=8;j>=0;j--){
        if(unint[cap-1]>=p10[j]){
            sz+=j+1;
            break;
        }
    }
    if(sz==0)sz=1;
    return new UnlimitedInt(unint,cap,sgn,sz);
}


UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1,UnlimitedInt* i2){
    int sgn=i1->sign*i2->sign;
    UnlimitedInt *zero=new UnlimitedInt();
    if(equals_unint(i2,zero)) throw "Division by Zero Error.";
    int s1=i1->sign;
    int s2=i2->sign;
    i1->sign=1;
    i2->sign=1;
    UnlimitedInt* rem = zero;
    UnlimitedInt* quo = new UnlimitedInt();
    quo->capacity = i1->capacity;
    delete[] quo->unlimited_int;
    quo->unlimited_int=new int[quo->capacity];
    for(int i=0;i<quo->capacity;i++)quo->unlimited_int[i]=0;
    UnlimitedInt* temp,*temp2,*ten=new UnlimitedInt(p10[9]),*q;
    for(int i=i1->capacity-1;i>=0;i--){
        temp=mul(rem,ten);
        delete rem;
        rem=temp;
        rem->unlimited_int[0] = i1->unlimited_int[i];
        if(rem->capacity==1){
            for(int j=8;j>=0;j--){
                if(rem->unlimited_int[0]>=p10[j]){
                    rem->size=j+1;
                    break;
                }
            }
            if(rem->size==0)rem->size=1;
        }
        q = int_q(rem,i2);
        temp2 = mul(i2,q);
        temp = sub(rem,temp2);
        delete rem;
        rem = temp;
        quo->unlimited_int[i]=q->unlimited_int[0];
        delete q;
        delete temp2;
    }
    quo->sign=sgn;
    if(sgn==-1 && (rem->capacity>1 || rem->unlimited_int[0]!=0)){
        temp=new UnlimitedInt(1);
        temp2 = UnlimitedInt::sub(quo,temp);
        delete temp;
        delete quo;
        quo=temp2;
    }
    delete rem;
    delete ten;
    i1->sign=s1;
    i2->sign=s2;
    for(;quo->unlimited_int[quo->capacity-1]==0 && quo->capacity>1;)quo->capacity--;
    resize(quo->unlimited_int,quo->capacity,quo->capacity);
    return quo;
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1,UnlimitedInt* i2){
    int sgn=i1->sign*i2->sign;
    UnlimitedInt *zero=new UnlimitedInt();
    if(equals_unint(i2,zero)) throw "Division by Zero Error.";
    int s1=i1->sign;
    int s2=i2->sign;
    i1->sign=1;
    i2->sign=1;
    UnlimitedInt* rem = zero;
    UnlimitedInt* temp,*temp2,*ten=new UnlimitedInt(p10[9]),*q;
    for(int i=i1->capacity-1;i>=0;i--){
        temp=mul(rem,ten);
        delete rem;
        rem=temp;
        rem->unlimited_int[0] = i1->unlimited_int[i];
        if(rem->capacity==1){
            for(int j=8;j>=0;j--){
                if(rem->unlimited_int[0]>=p10[j]){
                    rem->size=j+1;
                    break;
                }
            }
            if(rem->size==0)rem->size=1;
        }
        q = int_q(rem,i2);
        temp2 = mul(i2,q);
        temp = sub(rem,temp2);
        delete rem;
        rem = temp;
        delete q;
        delete temp2;
    }
    if(sgn==-1 && (rem->capacity>1 || rem->unlimited_int[0]!=0)){
        temp=sub(i2,rem);
        delete rem;
        rem=temp;
    }
    delete ten;
    i1->sign=s1;
    i2->sign=s2;
    return rem;
}

string UnlimitedInt::to_string(){
    if(this->capacity==1 && this->unlimited_int[0]==0)return "0";
    string res="";
    if(this->sign==-1)res="-";
    int c=0;
    res+=std::to_string(this->unlimited_int[this->capacity-1]);
    for(int i=this->capacity-2;i>=0;i--){
        c=0;
        for(int j=8;j>=0;j--){
            if(this->unlimited_int[i]>=p10[j]){
                c=j+1;
                break;
            }
        }
        for(int j=0;j<9-c;j++)res+="0";
        if(this->unlimited_int[i]!=0)
        res+=std::to_string(this->unlimited_int[i]);
    }
    return res;
}

// #include<iostream>
// using namespace std;

// int main(){
//     string a1 = "41"; string b1 = "43";
//     UnlimitedInt* a = new UnlimitedInt(a1);
//     UnlimitedInt* b = new UnlimitedInt(b1);
//     UnlimitedInt* ans = UnlimitedInt::add(a,b);
//     delete a; delete b;
//     cout<<ans->to_string()<<endl;
// }

// int main(){
//     UnlimitedInt A("999999999999999999");
//     UnlimitedInt B("999999999999999999");
//     cout<<A.to_string()<<endl;
//     // UnlimitedInt D = *(UnlimitedInt::sub(UnlimitedInt::mul(&A,&B),new UnlimitedInt(1)));
//     UnlimitedInt C = *(UnlimitedInt::mul(&A,&B));
//     // UnlimitedRational E(&B,&A);
//     // UnlimitedInt C = *(int_q(&B,&A));
//     // B.get_array()[0]=100;
//     // std::cout<<equals_unint(&A,&B);
//     // int* a = C.get_array();
//     // int cap = C.get_capacity();
//     // int sg=C.get_sign();
//     cout<<C.to_string();
//     cout<<'\n';
// }
