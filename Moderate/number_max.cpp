#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int a,b;
    cin>>a>>b;

    // below logic fails for negative numbers
    // bool k=a/b;
    // cout<<a*k+b*(!k)<<endl;

    auto flip=[](int bit){
        return 1^bit;
    };

    auto sign=[&flip](int num){
        return flip((num>>31)&0x1);
    };

    int sa=sign(a);
    int sb=sign(b);
    int sc=sign(a-b);

    int sign_of_a = sa^sb;
    int sign_of_c=  flip(sign_of_a);

    int k=sign_of_a*sa +sign_of_c*sc;
    int q=flip(k);

    cout<<a*k+b*q<<endl; 


}