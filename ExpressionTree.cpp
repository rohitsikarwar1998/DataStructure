#include "bits/stdc++.h"
using namespace std;


struct TreeNode{
    char val;
    TreeNode* left;
    TreeNode* right;

    //initialize values for newnode
    TreeNode(char val){
        this->val=val;
        this->left=NULL;
        this->right=NULL;
    }
};


int findRootIndex(string &expression){

    int rootIndex=-1;
    int len=expression.length();
    list<pair<int ,char> >stk;

    for(int i=0;i<len;i++){

        if(expression[i]==')'){
            while((stk.back().second)!='(')
                stk.pop_back();
            stk.pop_back();
        }

        else stk.push_back({i,expression[i]});

    }

    for(auto p:stk){
        // cout<<p.second<<" ";

        if(p.second=='+' || p.second=='-') rootIndex=p.first;

        else if(p.second=='/' || p.second=='*' ) {
            if(rootIndex==-1) rootIndex=p.first;
            else if(expression[rootIndex]!='-' && expression[rootIndex]!='+') 
                rootIndex=p.first;
        }

        else if(p.second=='^') {
            if(rootIndex==-1) rootIndex=p.first;
        }

    }

    return rootIndex;

}

string findChildString(string &expression,int start,int end){

    list<char>temp;

    for(int i=start;i<=end;i++) temp.push_back(expression[i]);

    if(temp.back()==')') {
        temp.pop_back();
        temp.pop_front();
    }

    return string(temp.begin(),temp.end());
}


TreeNode* constructExpresionTree(string &expression){

    int len=expression.size();
    if(len==1) return new TreeNode(expression[0]);

    int rootIndex=findRootIndex(expression);
    
    TreeNode* newnode=new TreeNode(expression[rootIndex]);

    string left=findChildString(expression,0,rootIndex-1);
    string right=findChildString(expression,rootIndex+1,len-1);

    newnode->left=constructExpresionTree(left);
    newnode->right=constructExpresionTree(right);

    return newnode;
}

string inorder(TreeNode* root){
    if(root==NULL) return "";

    string ans="";
    
    string left=inorder(root->left);
    string right=inorder(root->right);

    auto buildAnswer=[&]{
        ans+=left;
        ans+=root->val;
        ans+=right;
    };

    if(left.length()!=0) {
        ans+="(";
        buildAnswer();
        ans+=")";
    }
    else buildAnswer();

    return ans;

}


int main(){

    string expression
    cin>>expression;
    TreeNode* root=constructExpresionTree(expression);
    cout<<inorder(root)<<endl;
}