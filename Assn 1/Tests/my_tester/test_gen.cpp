#include<vector>
#include<set>
#include<iostream>
#include<fstream>
#include<random>
#include<algorithm>
#include<nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

typedef long long ll;


struct operation{
    int type=1,data1=-1,data2=-1;
};

class test{
    public:
    vector<set<int>> sets;
    vector<int> counts;
    vector<operation> inserts,operations;
    string input="",output;
    ll set_order,size_order,set_size,operations_size,old_set_size;

    test(ll set_order=100,ll size_order=100,ll operations_size=100){
        this->set_order=set_order;
        this->size_order=size_order;
        this->operations_size=operations_size;
        set_size = rand()%(set_order*10)+1;
        counts=vector<int>(set_size,0);
        for(ll i=0;i<set_size;i++){
            set<int> A;
            ll l=rand()%(size_order*10)+1;
            for(ll j=0;j<l;j++){
                operation B;
                int a=rand();
                A.insert(a);
                B.type=1;
                B.data1=i;
                B.data2=a;
                inserts.push_back(B);
            }
            auto iter = A.begin();
            for(int j=0;j<l/3;j++){
                operation B;
                B.type=1;
                B.data1=i;
                B.data2=*iter;
                iter++;
                inserts.push_back(B);
            }
            sets.push_back(A);
        }
        old_set_size=set_size;

        for(ll i=0;i<operations_size;i++){
            operation A;
            A.type=rand()%9+1;
            set<int>::iterator iter;
            ll l;
            switch(A.type){
                case 2:
                A.data1 = rand()%(3*set_size/2);
                if(A.data1<set_size){
                    if(sets[A.data1].empty())A.data2=rand();
                    else switch(rand()%4){
                        case 0:
                        A.data2=*sets[A.data1].begin();
                        break;
                        case 1:
                        A.data2=*sets[A.data1].rbegin();
                        break;
                        case 2:
                        iter = sets[A.data1].begin();
                        l=rand()%sets[A.data1].size();
                        for(ll j=0;j<l;j++)
                        iter++;
                        A.data2=*iter;
                        break;
                        case 3:
                        A.data2 = rand();
                    }
                }
                else A.data2 = rand();
                break;
                case 3:
                A.data1 = rand()%(3*set_size/2);
                if(A.data1<set_size){
                    ll l;
                    set<int>::iterator iter;
                    if(sets[A.data1].empty())A.data2=rand();
                    else switch(rand()%4){
                        case 0:
                        A.data2=*sets[A.data1].begin();
                        break;
                        case 1:
                        A.data2=*sets[A.data1].rbegin();
                        break;
                        case 2:
                        iter = sets[A.data1].begin();
                        l=rand()%sets[A.data1].size();

                        for(ll j=0;j<l;j++)
                        iter++;
                        A.data2=*iter;
                        break;
                        case 3:
                        A.data2 = rand();
                    }
                }
                else A.data2=rand();
                break;

                case 4:

                case 5:

                case 7:

                case 8:
                A.data1 = rand()%(3*set_size/2);
                if(A.data1>set_size){
                    A.data1=set_size;
                    set_size++;
                    sets.push_back(set<int>());
                }
                A.data2 = rand()%(3*set_size/2);
                if(A.data2>set_size){
                    A.data2=set_size;
                    set_size++;
                    sets.push_back(set<int>());
                }
                break;

                
                case 6:
                A.data1 = rand()%(3*set_size/2);
                if(A.data1>set_size){
                    A.data1=set_size;
                    set_size++;
                    sets.push_back(set<int>());
                }
                break;
                
                case 9:
                A.data1 = rand()%(3*set_size/2);
            }
            operations.push_back(A);
        }
        solve();
        stringise_input();
    }

    void stringise_input(){
        for(operation A:inserts){
            switch(A.type){
                case 6:
                case 9:
                input+=to_string(A.type)+" "+to_string(A.data1)+"\n";
                break;
                default:
                input+=to_string(A.type)+" "+to_string(A.data1)+" "+to_string(A.data2)+"\n";
            }
        }
        for(operation A:operations){
            switch(A.type){
                case 6:
                case 9:
                input+=to_string(A.type)+" "+to_string(A.data1)+"\n";
                break;
                default:
                input+=to_string(A.type)+" "+to_string(A.data1)+" "+to_string(A.data2)+"\n";
            }
        }
    }

    void solve(){
        
        for(operation A:operations){
            vector<int> temp;
            switch(A.type){
                case 2:
                if(A.data1<old_set_size){
                    sets[A.data1].erase(A.data2);
                    output+=to_string(sets[A.data1].size())+"\n";
                }
                else output+="-1\n";
                break;

                case 3:
                if(A.data1<old_set_size){
                    output+=to_string(sets[A.data1].count(A.data2))+"\n";
                }
                else output+="-1\n";
                break;

                case 4:
                if(A.data1>old_set_size){
                    A.data1=old_set_size;
                    old_set_size++;
                }
                if(A.data2>old_set_size){
                    A.data2=old_set_size;
                    old_set_size++;
                }
                temp=vector<int>();
                set_union(sets[A.data1].begin(),sets[A.data1].end(),sets[A.data2].begin(),sets[A.data2].end(),inserter(temp,temp.end()));
                sets[A.data1]=set<int>(temp.begin(),temp.end());
                
                output+=to_string(sets[A.data1].size())+"\n";

                break;

                case 5:
                if(A.data1>old_set_size){
                    A.data1=old_set_size;
                    old_set_size++;
                }
                if(A.data2>old_set_size){
                    A.data2=old_set_size;
                    old_set_size++;
                }
                temp=vector<int>();
                set_intersection(sets[A.data1].begin(),sets[A.data1].end(),sets[A.data2].begin(),sets[A.data2].end(),inserter(temp,temp.end()));
                sets[A.data1]=set<int>(temp.begin(),temp.end());
                
                output+=to_string(sets[A.data1].size())+"\n";
                break;

                case 6:
                if(A.data1>old_set_size){
                    A.data1=old_set_size;
                    old_set_size++;
                }

                output+=to_string(sets[A.data1].size())+"\n";

                break;

                case 7:
                if(A.data1>old_set_size){
                    A.data1=old_set_size;
                    old_set_size++;
                }
                if(A.data2>old_set_size){
                    A.data2=old_set_size;
                    old_set_size++;
                }
                temp=vector<int>();
                set_difference(sets[A.data1].begin(),sets[A.data1].end(),sets[A.data2].begin(),sets[A.data2].end(),inserter(temp,temp.end()));
                sets[A.data1]=set<int>(temp.begin(),temp.end());
                
                output+=to_string(sets[A.data1].size())+"\n";
                break;

                case 8:
                if(A.data1>old_set_size){
                    A.data1=old_set_size;
                    old_set_size++;
                }
                if(A.data2>old_set_size){
                    A.data2=old_set_size;
                    old_set_size++;
                }
                temp=vector<int>();
                set_symmetric_difference(sets[A.data1].begin(),sets[A.data1].end(),sets[A.data2].begin(),sets[A.data2].end(),inserter(temp,temp.end()));
                sets[A.data1]=set<int>(temp.begin(),temp.end());
                
                output+=to_string(sets[A.data1].size())+"\n";
                break;

                case 9:
                if(A.data1>=old_set_size){
                    output+="\n";
                }
                else{
                    if(sets[A.data1].empty()){
                        output+="\n";
                    }
                    else{
                        for(auto i=sets[A.data1].begin();i!=sets[A.data1].end();i++){
                            if(i!=prev(sets[A.data1].end()))output+=to_string(*i)+",";
                            else output+=to_string(*i)+"\n";
                        }
                    }
                }
                break;
            }
        }
    }

};


int main(){
    ofstream fout;
    ifstream fin;
    int T;
    cout<<"How many tests?: ";
    cin>>T;
    while(T--){
        test A(1,1,1);
        fout.open("test-"+to_string(T)+".txt",ios::out | ios::trunc);
        fout<<A.input;
        fout.close();
        system(("main.exe < test-"+ to_string(T) +".txt > res-"+to_string(T)+".txt").c_str());
        string rec_input="";
        fin.open("res-"+to_string(T)+".txt",ios::in);
        getline(fin,rec_input,'c');
        if(rec_input!=A.output)
        {
            cout<<"broke";
            cout<<rec_input<<"\n\n\n\n";
            cout<<A.output;
            break;
        }
    }
}