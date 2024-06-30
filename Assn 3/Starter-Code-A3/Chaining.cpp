#include "Chaining.h"



Chaining::Chaining(){
    bankStorage2d=std::vector<std::vector<Account>>(sizes[M]);
    for(int i=0;i<sizes[M];i++){
        bankStorage2d[i]=std::vector<Account>();
    }
    size=0;
}

void Chaining::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    if(size+1>sizes[M]/2){
        resize(M+1);
    }
    int id_hash=hash(id);
    bankStorage2d[id_hash].push_back(Account({id,count}));
    size++;
}

std::vector<int> Chaining::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std::vector<int> sorted(size);
    int i=0;
    for(auto &chain:bankStorage2d){
        for(Account &acc:chain)
        if(acc.balance>=0)sorted[i++]=acc.balance;
    }
    helper_topK(sorted,0,size);
    std::vector<int> ans(k);
    for(int i=0;i<k && i<ans.size();i++)ans[i]=sorted[i];
    return ans; // Placeholder return value
}

int Chaining::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int id_hash=hash(id);
    auto &chain=bankStorage2d[id_hash];
    for(Account &acc:chain)
    if(acc.id==id)return acc.balance;

    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int id_hash=hash(id);
    auto &chain=bankStorage2d[id_hash];
    for(Account &acc:chain)
    if(acc.id==id){
        acc.balance+=count;
        return;
    }
    createAccount(id,count);
}

bool Chaining::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int id_hash=hash(id);
    auto &chain=bankStorage2d[id_hash];
    for(Account &acc:chain)
    if(acc.id==id)return true;
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int id_hash=hash(id);
    auto &chain=bankStorage2d[id_hash];
    for(auto i=chain.begin();i<chain.end();i++)
    if(i->id==id){
        chain.erase(i);
        size--;
        if(size<sizes[M]/8 && M>0){
            resize(M-1);
        }
        return true;
    }
    return false; // Placeholder return value
}
int Chaining::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int Chaining::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE

    long long int hash=0;
    long long int a,b,c;
    a = ((((id[0]-'A')*26+(id[1]-'A'))*26+(id[2]-'A'))*26+(id[3]-'A'))%sizes[M];
    b = (((((((((id[4]-'0')*10)+(id[5]-'0'))*10+(id[6]-'0'))*10+(id[7]-'0'))*10)+(id[8]-'0'))*10+(id[9]-'0'))*10+(id[10]-'0'))%sizes[M];
    c = (((((((((((((id[12]-'0')*10)+(id[13]-'0'))*10+(id[14]-'0'))*10+(id[15]-'0'))*10)+(id[16]-'0'))*10+(id[17]-'0'))*10+(id[18]-'0'))*10)+(id[19]-'0'))*10+(id[20]-'0'))*10+(id[21]-'0'))%sizes[M];
    hash = (((a+b+c)*(a+b+c+1)*(a+b+c+2))/6)%sizes[M] + (((a+b)*(a+b+1))/2)%sizes[M] + a;


    return (hash%sizes[M]+sizes[M])%sizes[M]; // Placeholder return value
}

// IFSC0123456789a_0123456789

