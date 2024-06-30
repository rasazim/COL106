#include "CubicProbing.h"

CubicProbing::CubicProbing(){
    M=0;
    bankStorage1d=std::vector<Account>(sizes[M],Account({"",-1}));
    size=0;
}

void CubicProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if(size+1>sizes[M]/2){
        resize(M+1);
    }
    int id_hash=hash(id);
    for(int i=0;;i++){
        if(bankStorage1d[(id_hash+((((i*i)%sizes[M])*i)%sizes[M]))%sizes[M]].balance==-1){
            bankStorage1d[(id_hash+((((i*i)%sizes[M])*i)%sizes[M]))%sizes[M]]=Account({id,count});
            break;
        }
    }
    size++;
}

std::vector<int> CubicProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std::vector<int> sorted(size);
    for(int i=0,c=0;i<sizes[M];i++){
        if(bankStorage1d[i].balance>0){
            sorted[c++]=bankStorage1d[i].balance;
        }
    };
    helper_topK(sorted,0,size);
    std::vector<int> ans(k);
    for(int i=0;i<k && i<ans.size();i++)ans[i]=sorted[i];
    return ans;// Placeholder return value
}

int CubicProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int id_hash=hash(id),at;
    for(int i=0;i<sizes[M];i++){
        at=(id_hash+((((i*i)%sizes[M])*i)%sizes[M]))%sizes[M];
        if(bankStorage1d[at].balance==-1)break;
        if(bankStorage1d[at].id==id)return bankStorage1d[at].balance;
    }
    return -1;
}

void CubicProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int id_hash=hash(id),at;
    for(int i=0;i<sizes[M];i++){
        at=(id_hash+((((i*i)%sizes[M])*i)%sizes[M]))%sizes[M];
        if(bankStorage1d[at].balance==-1)break;
        if(bankStorage1d[at].id==id){
            bankStorage1d[at].balance+=count;
            return;
        }
    }
    createAccount(id,count);
}

bool CubicProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int id_hash=hash(id),at;
    for(int i=0;i<sizes[M];i++){
        at=(id_hash+((((i*i)%sizes[M])*i)%sizes[M]))%sizes[M];
        if(bankStorage1d[at].balance==-1)break;
        if(bankStorage1d[at].id==id)return true;
    }
    return false;
}

bool CubicProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int id_hash=hash(id),at;
    for(int i=0;i<sizes[M];i++){
        at=(id_hash+((((i*i)%sizes[M])*i)%sizes[M]))%sizes[M];
        if(bankStorage1d[at].balance==-1)break;
        if(bankStorage1d[at].id==id){
            bankStorage1d[at].id="";
            bankStorage1d[at].balance=-2;
            size--;
            if(size<sizes[M]/8 && M>0){
                resize(M-1);
            }
            return true;
        }
    }
    return false;
}
int CubicProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int CubicProbing::hash(std::string id) {
    long long int hash=0;
    long long int a,b,c;
    a = ((((id[0]-'A')*26+(id[1]-'A'))*26+(id[2]-'A'))*26+(id[3]-'A'))%sizes[M];
    b = (((((((((id[4]-'0')*10)+(id[5]-'0'))*10+(id[6]-'0'))*10+(id[7]-'0'))*10)+(id[8]-'0'))*10+(id[9]-'0'))*10+(id[10]-'0'))%sizes[M];
    c = (((((((((((((id[12]-'0')*10)+(id[13]-'0'))*10+(id[14]-'0'))*10+(id[15]-'0'))*10)+(id[16]-'0'))*10+(id[17]-'0'))*10+(id[18]-'0'))*10)+(id[19]-'0'))*10+(id[20]-'0'))*10+(id[21]-'0'))%sizes[M];
    hash = (((a+b+c)*(a+b+c+1)*(a+b+c+2))/6)%sizes[M] + (((a+b)*(a+b+1))/2)%sizes[M] + a;


    return (hash%sizes[M]+sizes[M])%sizes[M];
}