#include <bits/stdc++.h>
using namespace std;

struct Node
{
    char data;
    bool isEnd;
    //  l-less , e- equal , g-greater
    Node *l, *e, *g;

    Node(char val) : data(val), isEnd(false), l(NULL), e(NULL), g(NULL) {}
};

class TST
{
public:
    Node* root;
    TST():root(NULL){};

    void insert(string word){
        root=insert_helper(root,word,0);
    }
    bool search(string word){
        return search_helper(root,word,0);
    }
    void print(){
        print_helper(root,"");
    }
private:
    Node* insert_helper(Node* root,string& word,int index){

        if(index>=word.size()) return NULL;
        if(root==NULL){
            root=new Node(word[index]);
            root->e=insert_helper(root->e,word,index+1);
            if(index==word.size()-1) root->isEnd=true;
            return root;
        }
        if(word[index]<root->data)
            root->l=insert_helper(root->l,word,index);
        else if(word[index]>root->data)
            root->g=insert_helper(root->g,word,index);
        else 
            root->e=insert_helper(root->e,word,index+1);

        return root;

    }

    bool search_helper(Node* root,string& word,int index){
        if(root==NULL) return false;
        if(index==word.size()) return false;

        if(word[index]==root->data){
            if(index==word.size()-1) return root->isEnd ;
            return search_helper(root->e,word,index+1);
        }
        else if(word[index]>root->data)
            return search_helper(root->g,word,index);
        return search_helper(root->l,word,index);
    }

    void print_helper(Node* root,string temp){
        if(root==NULL) return ;
        print_helper(root->l,temp);
        temp.push_back(root->data);
        if(root->isEnd) cout<<temp<<endl;
        print_helper(root->e,temp);
        temp.pop_back();
        print_helper(root->g,temp);
    }
};


int main(){

     TST *treeNode=new TST();
     treeNode->insert("r");
     treeNode->insert("hello");
     treeNode->insert("rohitsikarwar");

     cout<<treeNode->search("r")<<endl;
     cout<<treeNode->search("rohitsikar")<<endl;
     cout<<treeNode->search("hel")<<endl;

     treeNode->print();
}