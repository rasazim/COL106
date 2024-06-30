#include<bits/stdc++.h>
#include<fstream>
#include<random>

using namespace std;

vector<string> perms(string s){
    vector<string> ans;
    if(s.size()==1){
        ans.push_back(s);
        return ans;
    }
    for(int i=0,l=s.size();i<l;i++){
        string rest = s.substr(0,i)+s.substr(i+1,l-i-1);
        vector<string> _p = perms(rest);
        for(string a:_p)ans.push_back(s[i]+a);
    }
    return ans;
}

int main(){
    string first="ABCD";
    string third="456789";
    ofstream f;
    f.open("test_ids.txt");
    for(string a:perms(first)){
        for(string b:perms(third)){
            f<<a+"0000000_0123"+b<<endl;
        }
    }
    
}