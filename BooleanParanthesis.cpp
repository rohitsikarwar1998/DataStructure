#include "bits/stdc++.h"
using namespace std;



int countParans(string &exp,int ans,unordered_map<string,int>& dp){

    // cout<<exp<<endl;
    if(exp.length()==0) return 0;
    if(exp.length()==1) {
        return ans==(int)(exp[0]-'0') ?1:0;
        // cout<<ans<<" "<<exp<<" "<<temp<<endl;
        // return temp;
    }

    string temp=exp;
    temp+=(ans+'0');

    if(dp.find(temp)!=dp.end()) return dp[temp];

    int result=0;

    for(int i=1;i<exp.length();i+=2){

        string left=exp.substr(0,i);
        string right=exp.substr(i+1,exp.length());

        int lefttrue=countParans(left,1,dp);
        int righttrue=countParans(right,1,dp);
        int leftfalse=countParans(left,0,dp);
        int rightfalse=countParans(right,0,dp);

        int total=(lefttrue+leftfalse)*(righttrue+rightfalse);

        int totalTrue=0;
        if(exp[i]=='^'){
            // if(ans) 
                totalTrue=(lefttrue*rightfalse)+(leftfalse*righttrue);
            // else 
            //     result+=(lefttrue*righttrue)+(lefttrue*righttrue);
        }
        else if(exp[i]=='|'){
            // if(ans) 
            totalTrue=(lefttrue*righttrue)+(lefttrue*rightfalse)+(leftfalse*righttrue);
            // else result+=(leftfalse*rightfalse);
        }
        else if(exp[i]=='&'){
            // if(ans) 
            totalTrue=(lefttrue*righttrue);
            // else result+=(leftfalse*rightfalse)+(lefttrue*rightfalse)+(leftfalse*righttrue);
        }
        int subWays=ans?totalTrue:total-totalTrue;
        result+=subWays;

    }

    dp[temp]=result;

    return result;
}

int countParanthesis(string &exp,int ans){

    unordered_map<string,int> dp;
    return countParans(exp,ans,dp);
}

int main(){

    string exp="0&0&0&1^1|0";
    int result=0;
    result= countParanthesis(exp,1);
    cout<<result<<endl;

}