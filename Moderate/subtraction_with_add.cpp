#include<bits/stdc++.h>
using namespace std;

int negates(int num){
    int value=0;
    int sign=num<0?1:-1;
    while(num!=0){
        if(sign<0 && sign+num<0) sign=-1;
        if(sign>0 && sign+num>0) sign=1;
        value+=sign;
        num+=sign;
        sign+=sign;
    }
    return value;
}

int main(){

    int a;
    cin>>a;
    cout<<negates(a)<<endl;
}