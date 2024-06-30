#include<vector>
#include<iostream>
#include<fstream>
#include<chrono>

using namespace std;
#define M 65537

int hash_(std::string id){
    // IMPLEMENT YOUR CODE HERE
    long long int hash=0;
    long long int a,b,c;
    a = ((((id[0]-'A')*26+(id[1]-'A'))*26+(id[2]-'A'))*26+(id[3]-'A'))%M;
    b = (((((((((id[4]-'0')*10)+(id[5]-'0'))*10+(id[6]-'0'))*10+(id[7]-'0'))*10)+(id[8]-'0'))*10+(id[9]-'0'))*10+(id[10]-'0'))%M;
    c = (((((((((((((id[12]-'0')*10)+(id[13]-'0'))*10+(id[14]-'0'))*10+(id[15]-'0'))*10)+(id[16]-'0'))*10+(id[17]-'0'))*10+(id[18]-'0'))*10)+(id[19]-'0'))*10+(id[20]-'0'))*10+(id[21]-'0'))%M;
    hash = (((a+b+c)*(a+b+c+1)*(a+b+c+2))/6)%M + (((a+b)*(a+b+1))/2)%M + a;
    
    return (hash%M+M)%M;
     // Placeholder return value
}

// int hash_(std::string id){
//     long long int hash =0;
//     long long int a=0,b=0,c=0;
//     for(int i=0;i<4;i++)a+=(i+1)*(id[i]-'A')%M;
//     for(int i=4;i<11;i++)b+=(i-3)*(id[i]-'0')%M;
//     for(int i=12;i<22;i++)c+=(i-11)*(id[i]-'0')%M;
//     hash = (((a+b+c)*(a+b+c+1)*(a+b+c+2))/6)%M + (((a+b)*(a+b+1))/2)%M + a;
//     return (hash%M+M)%M;
// }

// int hash_(std::string id){
//     int hf=0;
//     int k=1;
//     for(char c:id){
//         hf += + k*c %M;
//         k++;
//     }
//     return hf%M;
// }

int main(){

    ifstream f;
    f.open("test_ids.txt");
    string id;
    vector<bool> reached(M,false);
    int cols=0;
    // auto start = chrono::high_resolution_clock::now();
    while(f>>id){
        int i = hash_(id);
        int c=0;
        while(reached[(i+((((c%M)*(c%M))%M)*(c%M)))%M]){
            cols++;
            c++;
        }
        reached[(i+((((c%M)*(c%M))%M)*(c%M)))%M]=true;
        // if(reached[i])cols++;
        // else reached[i]=true;
    }
    f.close();
        // auto end=chrono::high_resolution_clock::now();
        // auto time = chrono::duration_cast<chrono::microseconds>(end-start);
        // cout<<flush<<"Prime: "<<p<<endl<<"Collisions: "<<cols<<endl<<"Time: "<<time.count();}
    cout<<cols<<endl;
    return 0;
}
