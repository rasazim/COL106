#ifndef CUBICPROBING_H
#define CUBICPROBING_H

#include "BaseClass.h"

class CubicProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    CubicProbing();
    
    
private:

    int size=0;
    int M=0;
    int sizes[14] = {59,131,257,509,1019,2063,4091,8209,16361,32771,65537,131063,262151,524261};


    void helper_topK(std::vector<int> &ans,int s,int e){
        if(e-s<=1)
        return;
        int m = (s+e)/2;
        helper_topK(ans,s,m);
        helper_topK(ans,m,e);
        std::vector<int> copy(e-s,-1);
        int p1=s,p2=m,l1=m,l2=e,c=0;
        for(;p1<l1 && p2<l2;){
            if(ans[p1]>ans[p2])copy[c++]=ans[p1++];
            else copy[c++]=ans[p2++];
        }
        for(;p1<l1;)copy[c++]=ans[p1++];
        for(;p2<l2;)copy[c++]=ans[p2++];
        for(int i=s;i<e;i++)ans[i]=copy[i-s];
    }
    
    void resize(int new_M){
        M = new_M;
        std::vector<Account> new_bank(sizes[M],Account({"",-1}));
        for(Account &acc:bankStorage1d){
            if(acc.id!=""){
                int id_hash=hash(acc.id);
                for(int i=0;i<sizes[M];i++){
                    if(new_bank[(id_hash+((((i*i)%sizes[M])*i)%sizes[M]))%sizes[M]].balance<0){
                        new_bank[(id_hash+((((i*i)%sizes[M])*i)%sizes[M]))%sizes[M]]=Account({acc.id,acc.balance});
                        break;
                    }
                }
            }
        }
        bankStorage1d=new_bank;
    }


    // Other data members and functions specific to Quadratic Probing
};

#endif  // CUBICPROBING_H