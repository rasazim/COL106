#include<iostream>
#include<vector>

using namespace std;

class SET{

public:
vector<int> *data;
int size=0;

SET(){
    data=new vector<int>();
}

~SET(){
    delete data;
}

int insert(int a){
    if(size==0){
        data->push_back(a);
        return size=1;
    }
    auto s = data->begin();
    auto e = data->end()-1;
    auto m = s+(e-s)/2;
    for(;s<=e;m = s+(e-s)/2){
        if(*m==a) return size;
        else if(*m<a) s=m+1;
        else e=m-1;
    }
    data->insert(s,a);
    return ++size;
}

int del(int a){
    if(size==0)return 0;
    auto s = data->begin();
    auto e = data->end()-1;
    auto m = s+(e-s)/2;
    for(;s<=e;m = s+(e-s)/2){
        if(*m==a){
            data->erase(m,m+1);
            return --size;
        }
        else if(*m<a)s=m+1;
        else e=m-1;
    }
    return size;
}

int uni(SET *other){
    auto p1 = data->begin(),p2 = other->data->begin(), l1 = data->end(), l2 = other->data->end();
    vector<int> res;
    for(;p1<l1 || p2<l2;){
        if(p1<l1 && p2<l2){
            if(*p1<*p2)res.push_back(*(p1++));
            else if(*p1>*p2)res.push_back(*(p2++));
            else{
                res.push_back(*(p1++));
                p2++;
            }
        }
        else if(p1<l1) for(;p1<l1;)res.push_back(*(p1++));
        else for(;p2<l2;)res.push_back(*(p2++));
    }
    *data=res;
    return size=data->size();
}

int inter(SET *other){
    auto p1 = data->begin(),p2 = other->data->begin(), l1 = data->end(), l2 = other->data->end();
    vector<int> res;
    for(;p1<l1 && p2<l2;){
        if(*p1<*p2)p1++;
        else if(*p1>*p2)p2++;
        else{
            res.push_back(*(p1++));
            p2++;
        }
    }
    *data=res;
    return size=data->size();
}

int dif(SET *other){
    auto p1 = data->begin(),p2 = other->data->begin(), l1 = data->end(), l2 = other->data->end();
    vector<int> res;
    for(;p1<l1;){
        if(p2<l2){
            if(*p1<*p2)res.push_back(*(p1++));
            else if(*p1>*p2)p2++;
            else{
                p1++;
                p2++;
            }
        }
        else for(;p1<l1;)res.push_back(*(p1++));
    }
    *data=res;
    return size=data->size();
}

int symdif(SET *other){
    auto p1 = data->begin(),p2 = other->data->begin(), l1 = data->end(), l2 = other->data->end();
    vector<int> res;
    for(;p1<l1 || p2<l2;){
        if(p1<l1 && p2<l2){
            if(*p1<*p2)res.push_back(*(p1++));
            else if(*p1>*p2)res.push_back(*(p2++));
            else{
                p1++;
                p2++;
            }
        }
        else if(p1<l1) for(;p1<l1;)res.push_back(*(p1++));
        else for(;p2<l2;)res.push_back(*(p2++));
    }
    *data=res;
    return size=data->size();
}


bool contains(int a){
    if(size==0)return 0;
    auto s = data->begin();
    auto e = data->end()-1;
    auto m = s+(e-s)/2;
    for(;s<=e;m = s+(e-s)/2){
        if(*m==a)return true;
        else if(*m<a)s=m+1;
        else e=m-1;
    }
    return false;
}

void print(){
    if(size==0){
        cout<<"\n";
        return;
    }
    for(int i=0;i<size-1;i++){
        cout<<(*data)[i]<<",";
    }
    cout<<(*data)[size-1]<<"\n";
}


};


int main(){

    int T,data1,data2,code;
    int num_sets=0;

    vector<SET*> sets = *(new vector<SET*>());



    for(;cin>>code;){
        if(code == 6 || code == 9)
        cin>>data1;
        else cin>>data1>>data2;
        switch(code){
            //insert
            case 1:
            if(data1>=num_sets){
                sets.push_back(new SET());
                num_sets++;
            }
            cout<<sets[data1]->insert(data2)<<"\n";
            break;

            //delete
            case 2:
            if(data1>=num_sets)cout<<"-1\n";
            else cout<<sets[data1]->del(data2)<<"\n";
            break;

            //contains
            case 3:
            if(data1>=num_sets)cout<<"-1\n";
            else if(sets[data1]->contains(data2))cout<<"1\n";
            else cout<<"0\n";
            break;

            //union
            case 4:
            if(data1>=num_sets){
                sets.push_back(new SET());
                num_sets++;
            }
            if(data2>=num_sets){
                sets.push_back(new SET());
                num_sets++;
            }
            cout<<sets[data1]->uni(sets[data2])<<"\n";
            break;

            //intersection
            case 5:
            if(data1>=num_sets){
                sets.push_back(new SET());
                num_sets++;
            }
            if(data2>=num_sets){
                sets.push_back(new SET());
                num_sets++;
            }
            cout<<sets[data1]->inter(sets[data2])<<"\n";
            break;

            //size
            case 6:
            if(data1>=num_sets){
                sets.push_back(new SET());
                num_sets++;
            }
            cout<<sets[data1]->size<<"\n";
            break;

            //difference
            case 7:
            if(data1>=num_sets){
                sets.push_back(new SET());
                num_sets++;
            }
            if(data2>=num_sets){
                sets.push_back(new SET());
                num_sets++;
            }
            cout<<sets[data1]->dif(sets[data2])<<"\n";
            break;

            //symmetric difference
            case 8:
            if(data1>=num_sets){
                sets.push_back(new SET());
                num_sets++;
            }
            if(data2>=num_sets){
                sets.push_back(new SET());
                num_sets++;
            }
            cout<<sets[data1]->symdif(sets[data2])<<"\n";
            break;

            //print
            case 9:
            if(data1<num_sets){
                sets[data1]->print();
            }
            else cout<<"\n";
            break;

            default:
            return 0;
        }
    }
}