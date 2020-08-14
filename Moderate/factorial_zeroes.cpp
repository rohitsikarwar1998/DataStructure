#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n;
    cin>>n;

    // vector<int> hash(n+1,0);
    // int zeroCount=0;
    // for(int i=1;i<=n;i++){
    //     if(hash[i]) continue;
    //     for(int j=i+1;j<=n;j++){
    //         if(hash[j]) continue;
    //         if(i*j%10==0){
    //             zeroCount++;
    //             hash[i]=1;
    //             hash[j]=1;
    //         }
    //     }
    // }


    int zeroCount=0;

    for(int i=5;i>n/5;i*=5){
        zeroCount+=n/i;
    }

    cout<<zeroCount<<endl;

}