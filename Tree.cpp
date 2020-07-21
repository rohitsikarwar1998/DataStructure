#include "bits/stdc++.h"
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *par;
    
    TreeNode(int val,TreeNode* par)
    {
        this->val = val;
        this->left = NULL;
        this->right = NULL;
        this->par=par;
    }
};

class BST
{
public:
    TreeNode *head;
    BST()
    {
        this->head = NULL;
    }
    void insert(int value)
    {
        head = insertHelper(head,NULL, value);
    }
    TreeNode *insertHelper(TreeNode *cur, TreeNode* par,int value)
    {
        if (cur == NULL)
            return new TreeNode(value,par);
        if (cur->val < value)
            cur->right = insertHelper(cur->right,cur, value);
        else
            cur->left = insertHelper(cur->left,cur, value);
        return cur;
    }
    void printInorder()
    {
        printInorderHelper(head);
        cout << endl;
    }
    void printInorderHelper(TreeNode *head)
    {
        if (head == NULL)
            return;
        printInorderHelper(head->left);
        cout << head->val << " ";
        printInorderHelper(head->right);
    }
};

list<list<int>> weaveLists(list<int> &first, list<int> &second, list<int> &prefix)
{

    // cout << first.size() << " " << second.size() << endl;
    list<list<int>> weaves;

    if (first.empty() || second.empty())
    {

        list<int> r(prefix);
        r.insert(r.end(), first.begin(), first.end());
        r.insert(r.end(), second.begin(), second.end());
        weaves.push_back(std::move(r));
        return weaves;
    }

    prefix.push_back(first.front());
    first.pop_front();
    weaves.splice(weaves.end(), weaveLists(first, second, prefix));
    first.push_front(prefix.back());
    prefix.pop_back();

    prefix.push_back(second.front());
    second.pop_front();
    weaves.splice(weaves.end(), weaveLists(first, second, prefix));
    second.push_front(prefix.back());
    prefix.pop_back();

    return weaves;
}

list<list<int>> BSTSubsequences(TreeNode *root)
{

    // cout << root->val << endl;
    list<list<int>> results;
    if (root == NULL)
    {
        results.emplace_back();
        return results;
    }

    list<int> prefix;
    prefix.push_back(root->val);

    list<list<int>> first = BSTSubsequences(root->left);
    list<list<int>> second = BSTSubsequences(root->right);

    // cout<<first.size()<<" "<<second.size()<<endl;

    for (auto &f : first)
    {
        for (auto &s : second)
        {

            auto joins = weaveLists(f, s, prefix);
            results.splice(results.end(), move(joins));
            assert(prefix.size() == 1 && prefix.front() == root->val);
        }
    }

    return results;
}

TreeNode* findNode(TreeNode* root,int value){
    if(root==NULL) return NULL;
    if(root->val==value) return root;
    if(root->val<value) return findNode(root->right,value);
    return findNode(root->left,value);
}

TreeNode* findLeftMost(TreeNode* root){
    if(!root->left) return root;
    return findLeftMost(root->left);
}

TreeNode* findParent(TreeNode* root){
    if(!root->par) return NULL;
    if(root->par->left==root) return root->par;
    return findParent(root->par);
}

TreeNode* findInorderSuccessor(TreeNode* root,int value){
    if(root==NULL) return NULL;
    TreeNode* found=findNode(root,value);
    if(found->right==NULL) {
        return findParent(found);
    }
    return findLeftMost(found->right);
}

int main()
{
    BST *tree = new BST();
    int arr[] = {5,2,6,1,4,8};
    for (auto num : arr)
    {
        tree->insert(num);
    }
    // list<list<int>> results = BSTSubsequences(tree->head);

    // for (auto &l : results)
    // {
    //     for (auto num : l)
    //         cout << num << " ";
    //     cout << endl;
    // }
    TreeNode* result=findInorderSuccessor(tree->head,5);
    if(result==NULL) cout<<"NULL"<<endl;
    else cout<<result->val<<endl;
    tree->printInorder();
}