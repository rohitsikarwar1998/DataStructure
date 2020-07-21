#include <bits/stdc++.h>
using namespace std;

enum Color
{
    RED,
    BLACK
};

struct Node
{
    int data;
    bool color;
    Node *left, *right, *parent;
    // constructor
    Node(int data)
    {
        this->data = data;
        left = right = parent = NULL;
        this->color = RED;
    }
};

// a class that represent RED BLACK TREE
class RBTree
{
private:
    Node *root;

protected:
    void rotateLeft(Node *&, Node *&);
    void rotateRight(Node *&, Node *&);
    void fixViolation(Node *&, Node *&);
    void fixDoubleBlack(Node*);
    void deleteNode(Node*);

public:
    //constructor
    RBTree()
    {
        root = NULL;
    }
    void insert(const int &);
    void inorder();
    void levelorder();
    void deleteNodeByValue(const int &);
};

// a recursive function to do inorder traversal
void inorderHelper(Node *root)
{
    if (root == NULL)
        return;
    inorderHelper(root->left);
    cout << root->data << " ";
    inorderHelper(root->right);
}

void levelorderHelper(Node* root){
    deque<Node* > que;
    que.push_back(root);
    while(!que.empty()){
        Node* cur=que.front();
        que.pop_front();
        cout<<cur->data<<" ";
        if(cur->left) que.push_back(cur->left);
        if(cur->right) que.push_back(cur->right);
    }
}

// A utility function for insert a new node with given
// data in BST

Node *BSTInsert(Node *root, Node *pt)
{
    if (root == NULL)
        return pt;
    if (pt->data > root->data)
    {
        root->right = BSTInsert(root->right, pt);
        root->right->parent = root;
    }
    else if (pt->data < root->data)
    {
        root->left = BSTInsert(root->left, pt);
        root->left->parent = root;
    }
    return root;
}

void RBTree::rotateLeft(Node *&root, Node *&pt)
{
    Node *pt_right = pt->right;
    pt->right = pt_right->left;
    if (pt->right != NULL)
    {
        pt->right->parent = pt;
    }
    pt_right->parent = pt->parent;
    if (pt->parent == NULL)
        root = pt_right;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;
    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

void RBTree::rotateRight(Node *&root, Node *&pt)
{
    Node *pt_left = pt->left;
    pt->left = pt_left->right;
    if (pt->left != NULL)
        pt->left->parent = pt;
    pt_left->parent = pt->parent;
    if (pt->parent == NULL)
        root=pt_left;
    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;
    else
        pt->parent->right = pt_left;

    pt->parent = pt_left;
    pt_left->right = pt;
}

//this function fixes violation caused by bst insertion

void RBTree::fixViolation(Node *&root, Node *&pt)
{
    Node *pt_parent = NULL;
    Node *pt_grand_parent = NULL;
    while (root != pt && (pt->color != BLACK) && (pt->parent->color == RED))
    {
        pt_parent = pt->parent;
        pt_grand_parent = pt->parent->parent;

        if (pt_parent == pt_grand_parent->left)
        {
            Node *pt_uncle = pt_grand_parent->right;

            //uncle's color is red

            if (pt_uncle != NULL && pt_uncle->color == RED)
            {

                pt_parent->color = BLACK;
                pt_uncle->color = BLACK;
                pt_grand_parent->color = RED;
                pt = pt_grand_parent;
            }
            // uncle's color is BLACK
            else
            {

                if (pt == pt_parent->right)
                {
                    rotateLeft(root, pt_parent);
                    pt = pt_parent;
                    pt_parent = pt->parent;
                }

                rotateRight(root, pt_grand_parent);
                swap(pt_parent->color, pt_grand_parent->color);
                pt = pt_parent;
            }
        }

        else
        {

            Node *pt_uncle = pt_grand_parent->left;

            //uncle of color red
            if (pt_uncle != NULL && pt_uncle->color == RED)
            {
                pt_grand_parent->color = RED;
                pt_parent->color = BLACK;
                pt_uncle->color = BLACK;
                pt = pt_grand_parent;
            }

            else
            {

                if (pt == pt_parent->left)
                {
                    rotateRight(root, pt_parent);
                    pt = pt_parent;
                    pt_parent = pt->parent;
                }

                rotateLeft(root, pt_grand_parent);
                swap(pt_parent->color, pt_grand_parent->color);
                pt = pt_parent;
            }
        }
    }
    root->color = BLACK;
}

Node* successor(Node* x){
    Node*temp=x;
    while(temp->left!=NULL)
        temp=temp->left;
    return temp;
}

// find node that replaces deleted node
Node* BSTreplace(Node* x){
    //when both child are exits
    if(x->left!=NULL and x->right!=NULL){
        return successor(x->right);
    }
    //when leaf node 
    if(x->left==NULL and x->right==NULL) 
         return NULL;
    //when single child
    if(x->left)
       return x->left;
    return x->right;
}

void RBTree::deleteNode(Node* v){

    Node* u=BSTreplace(v);
    //true when u and v both are black 
    bool uvBlack=((u==NULL or u->color==BLACK) and (v->color==BLACK));

    Node* parent =v->parent;

    if(u==NULL){
        if(v==root) root=NULL;
        else {
            if(uvBlack){
                //v is black 
                //u is null so consider it as black 
                //double black condition occur
                fixDoubleBlack(v);
            }
            else {
                
                Node* sibling=NULL;
                if(v==v->parent->left)
                   sibling=v->parent->right;
                else 
                   sibling =v->parent->left;
                if(sibling !=NULL) 
                   sibling ->color=RED;
            }

            //delete v from the tree 
            if(v==v->parent->left)
                v->parent->left=NULL;
            else 
                v->parent->right=NULL;

        }
        delete v;
        return ;
    }
    
    if(v->left==NULL or v->right==NULL){

        if(v==root){

            v->data=u->data;
            v->left=v->right=NULL;
            delete u;
        }
        else {

            // detach v from the tree and move u up
            if(v==v->parent->left)
                parent->left=u;
            else parent->right=u;
            delete v;

            u->parent=parent;
            if(uvBlack){
                fixDoubleBlack(u);
            }
            else {
                u->color=BLACK;
            }
        }
        return ;
    }

    // if v has both child 
    // swap value with successor and recur delete for u
    int temp=v->data;
    v->data=u->data;
    u->data=temp;
    deleteNode(u);
}

void RBTree::fixDoubleBlack(Node* x){
    if(x==root)
       return ;

    Node* sibling=NULL,*parent=x->parent;
    if(x==parent->left)
       sibling=parent->right;
    else 
       sibling =parent->left;
    if(sibling ==NULL){
        fixDoubleBlack(parent);
    }
    else {
        if(sibling->color==RED){
            parent->color=RED;
            sibling->color=BLACK;
            if(sibling==parent->left)
                rotateRight(root,parent);
            else 
                rotateLeft(root,parent);
            fixDoubleBlack(x);
        }
        else {
            //sibling is black
            if((sibling->left&&sibling->left->color==RED)||(sibling->right&&sibling->right->color==RED)){
                //atleast 1 red children
                if(sibling->left&&sibling->left->color==RED){
                    if(sibling==parent->left){
                        //left left
                        sibling->left->color=sibling->color;
                        sibling->color=parent->color;
                        rotateRight(root,parent);
                    }
                    else {
                        //right left
                        sibling->left->color=parent->color;
                        rotateRight(root,sibling);
                        rotateLeft(root,parent);
                    }
                }
                else {
                    if(sibling==parent->left){
                        //left right
                        sibling->right->color=parent->color;
                        rotateLeft(root,sibling);
                        rotateRight(root,parent);
                    }
                    else {
                        //right right
                        sibling->right->color=sibling->color;
                        sibling->color=parent->color;
                        rotateLeft(root,parent);
                    }
                }
                parent->color=BLACK;
            }
            else {
                //2 black child 
                sibling->color=RED;
                if(parent->color==BLACK)
                    fixDoubleBlack(parent);
                else 
                    parent->color=BLACK;
            }
        }
    }
}

void RBTree::insert(const int &data)
{
    Node *pt = new Node(data);
    //Do a normal BST insert
    root = BSTInsert(root, pt);
    //fix red black tree violation
    fixViolation(root, pt);
}

Node* search(Node* root,int val){
    if(root==NULL) return NULL;
    if(root->data==val) return root;
    if(val>root->data) return search(root->right,val);
    return search(root->left,val);
}

void RBTree::deleteNodeByValue(const int &value){
    if(root==NULL) 
       return ;
    Node* v=search(root,value);
    if(v==NULL) cout<<"Not found"<<endl;
    else {
        deleteNode(v);
    }
}

void RBTree::inorder()
{
    inorderHelper(root);
}

void RBTree::levelorder(){
    levelorderHelper(root);
}

int main()
{
    RBTree tree;
    tree.insert(7);
    tree.insert(6);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    tree.insert(0);

    tree.deleteNodeByValue(4);
    tree.deleteNodeByValue(5);
    tree.deleteNodeByValue(6);
    tree.deleteNodeByValue(7);

    tree.inorder();
    cout<<endl;
    tree.levelorder();
}