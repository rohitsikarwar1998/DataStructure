#include "bits/stdc++.h"
using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    int height;

    //constructor
    TreeNode(int val) : val(val), left(NULL), right(NULL), height(1) {}
};

class AVL
{
public:
    //root element of the tree
    TreeNode *root;

    // constructor
    AVL() : root(NULL) {}

    void deleteNode(int value){
        this->root=this->deleteNodeHelper(this->root,value);
    }
    void insert(int value){
        this->root=insertHelper(this->root,value);
    }
    void preOrder(TreeNode *root)
    {
        if (root != NULL)
        {
            cout << root->val << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }
    void inOrder(TreeNode *root)
    {
        if (root != NULL)
        {
            inOrder(root->left);
            cout << root->val << " ";
            inOrder(root->right);
        }
    }
private:

    int height(TreeNode *node)
    {
        if (node == NULL)
            return 0;
        return node->height;
    }

    TreeNode *leftRotate(TreeNode *y)
    {

        TreeNode *x = y->right;
        TreeNode *t2 = x->left;

        x->left = y;
        y->right = t2;

        //update the height of x and y
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    TreeNode *rightRotate(TreeNode *y)
    {

        TreeNode *x = y->left;
        TreeNode *t2 = x->right;

        x->right = y;
        y->left = t2;

        //update the height of x and y

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    int getBalanceFactor(TreeNode *node)
    {
        if (node == NULL)
            return 0;
        return height(node->left) - height(node->right);
    }

    //insert function

    TreeNode *insertHelper(TreeNode *root, int value)
    {

        TreeNode *newnode = new TreeNode(value);

        if (root == NULL)
            return newnode;

        if (value > root->val)
            root->right = insertHelper(root->right, value);
        else if (value < root->val)
            root->left = insertHelper(root->left, value);
        //duplicate values are not allowed
        else
            return root;

        root->height = max(height(root->left), height(root->right)) + 1;

        int balance = getBalanceFactor(root);

        if (balance < -1)
        {
            if (root->right->val < value)
                return leftRotate(root);
            else
            {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
        else if (balance > 1)
        {
            if (root->left->val > value)
                return rightRotate(root);
            else
            {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }

        return root;
    }

    //find the min value node in the right subtree
    //and it replaces the deleted node
    TreeNode *getMinValue(TreeNode *node)
    {

        TreeNode *cur = node;
        while (cur->left)
        {
            cur = cur->left;
        }
        return cur;
    }

    //delete node from the BST
    //then check for balance if it make tree unbalance then rebalance it


    TreeNode *deleteNodeHelper(TreeNode *root, int value)
    {

        if (root == NULL)
            return root;

        if (root->val > value)
            root->left = deleteNodeHelper(root->left, value);
        else if (root->val < value)
            root->right = deleteNodeHelper(root->right, value);
        else
        {
            if (!root->left || !root->right)
            {
                TreeNode *temp = root->left ? root->left : root->right;

                if (temp == NULL)
                {
                    temp = root;
                    return NULL;
                }
                else
                    *root = *temp;

                delete (temp);
            }
            else
            {
                //if found node has both child
                //then get inorder successor i.e minimum value node in
                //the right subtree

                TreeNode *minNode = getMinValue(root->right);
                root->val = minNode->val;
                // cout<<root->val<<endl;
                root->right = deleteNodeHelper(root->right, minNode->val);
            }
        }
        if (root == NULL)
            return root;

        //update height of the node
        root->height = max(height(root->left), height(root->right)) + 1;

        int balanceFactor = getBalanceFactor(root);

        //check whether this node is balance or not
        if (balanceFactor < -1)
        {

            //right right case
            if (root->right->val < value)
                return leftRotate(root);
            //right left case
            else
            {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
        else if (balanceFactor > 1)
        {
            //left left case
            if (root->left->val > value)
                return rightRotate(root);
            //left right case
            else
            {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }

        return root;
    }

};

int main()
{

    AVL tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(60);

    tree.deleteNode(10);
    tree.deleteNode(40);

    tree.preOrder(tree.root);
    cout << endl;
    tree.inOrder(tree.root);
}