#include "../ulimitedint.cpp"
#include "../ulimitedrational.cpp"

#include<iostream>
#include<fstream>
#include<chrono>
using namespace std::chrono;


int main(){
    ifstream f;
    f.open("tests.txt");
    int num_cases;
    f>>num_cases;
    system("cls");
    string a,b,sum,dif,pro,quo,rem;
    bool failed=false;
    int i;
    auto start = high_resolution_clock::now();
    auto time = start;
    for(i=0;i<num_cases;i++){
        f>>a;
        f>>b;
        f>>sum;
        f>>dif;
        f>>pro;
        f>>quo;
        f>>rem;
        UnlimitedInt *A,*B,*SUM,*DIF,*PRO,*QUO,*REM;
        A = new UnlimitedInt(a);
        B = new UnlimitedInt(b);
        SUM = UnlimitedInt::add(A,B);
        DIF = UnlimitedInt::sub(A,B);
        PRO = UnlimitedInt::mul(A,B);
        QUO = UnlimitedInt::div(A,B);
        REM = UnlimitedInt::mod(A,B);
        if(a != A->to_string() || b != B->to_string() || sum != SUM->to_string() || dif != DIF->to_string() || pro != PRO->to_string() || quo != QUO->to_string() || rem != REM->to_string()){
            failed=true;
            break;
        }
        system("cls");
        time = high_resolution_clock::now();
        cout<<"[";
        int l = ((i+1)*20)/num_cases;
        for(int j=0;j<l;j++)
        cout<<"x";
        for(int j=l;j<20;j++)
        cout<<"_";
        cout<<"] "<<(i+1)<<" of "<<num_cases<<endl<<"Time: "<<duration_cast<seconds>(time-start).count()<<" seconds";
    }
    if(failed){
        cout<<"Failed on Case:\n";
        cout<<"i: "<<i<<"\n";
        cout<<"a: "<<a<<"\n";
        cout<<"b: "<<b;
    }
    else cout<<"Passed";
    return 0;
}