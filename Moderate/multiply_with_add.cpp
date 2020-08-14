#include<bits/stdc++.h>
using namespace std;

int multiply(int a,int b){
    int tempa=abs(a);
    int tempb=abs(b);
    if(tempa<tempb)
        return multiply(b,a);
    int sign=(a<0)^(b<0);
    int sum=0;
    for(int i=1;i<=tempb;i++){
        sum+=tempa;
    }
    if(sign) sum=-sum;
    return sum;
}

int main(){

    int a,b;
    cin>>a>>b;
    cout<<multiply(a,b)<<endl;
}