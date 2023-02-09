#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

// #include "avltree.h"
using namespace std;

//node struct
struct Node {
    int data;
    int height;
    Node * left;
    Node * right;
};

Node* makeN(int data)
{
    Node* node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

//helper functions for main stuffs
int height(Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}
int getBalance(Node *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}
Node * minvalnode(Node * node)
{
    Node * temp = node;
    
    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}


//helper functions for main
int max(int a, int b){return a > b ? a:b;}
int stringtoint(string str){return atoi(str.c_str());}
void printIn(Node * node)
{
    if (node != NULL)
    {
        printIn(node->left);
        cout << node->data << " ";
        printIn(node->right);
    }
}
void printPre(Node * node){
    if(node != NULL)
    {
        cout << node->data << " ";
        printPre(node->left);
        printPre(node->right);
    }
}
void printPost(Node * node){
    if (node != NULL)
    {
        printPost(node->left);
        printPost(node->right);
        cout << node->data << " ";
    }
}


//rotation functions for organisation
Node *rotateLeft(Node* x)
{
    Node *y = x->right;
    Node *branch = y->left;

    y->left = x;
    x->right = branch;

    x->height = 1 + max(height(x->left),height(x->right));
    y->height = 1 + max(height(y->left),height(y->right));

    return y;    
}
Node *rotateRight(Node* y)
{
    Node *x = y->left;
    Node *branch = x->right;
    
    x->right = y;
    y->left = branch;

    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;

    return x;
}
Node *rotateRightLeft(Node* node)
{
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}
Node *rotateLeftRight(Node* node)
{
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}


//binary insertion
Node *insert(Node * node, int data)
{
    //creates tree head
    if(node == NULL) 
        return (makeN(data));

    /* typical recursive binary insertion */
    //go left
    if (data < node->data)
        node->left = insert(node->left, data);
    //go right
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Equal keys not allowed
        return node;

    // update height before organisation
    node->height = 1 + max(height(node->left),height(node->right));

    // balance is needed for organisation method
    int b = getBalance(node);
    int lb = getBalance(node->left);
    int rb = getBalance(node->right);

    // right right case
    if (b==2 && lb==1)
        return rotateRight(node);
    //left left rotation
    else if (b==-2 && rb==-1)
        return rotateLeft(node);
    //left right rotation
    else if (b==-2 && lb==1) 
        return rotateRightLeft(node);
    // right left rotation
    else if (b==2 && lb==-1)
        return rotateLeftRight(node);
    
    return node;
}


//delete from bst
Node *remove(Node * curr, int val)
{
    //already been removed/never existed
    if (curr==NULL) return curr;

    //go left recursively
    if (val < curr->data)
        curr->left = remove(curr->left,val);
    //go right recursively
    else if (val > curr->data)
        curr->right = remove(curr->right,val);

    else
    {
        if ((curr->left == NULL)||curr->right == NULL)
        {
            Node* temp = curr->left ? curr->left : curr->right;

            if (temp == NULL)
            {
                temp = curr;
                curr = NULL;
            }
            else *curr = *temp;
            free(temp);
        }
        else {
            Node * temp = minvalnode(curr->right);
            curr->data = temp->data;
            curr->right = remove(curr->right, temp->data);
        }
    }
    //case where tree had no children but root node
    if (curr==NULL)
        return curr;

    curr->height = 1 + max(height(curr->left),height(curr->right));

    // balance is needed for organisation method
    int b = getBalance(curr);
    int lb = getBalance(curr->left);
    int rb = getBalance(curr->right);

    // right right case
    if (b==2 && lb==1)
        return rotateRight(curr);
    //left left rotation
    else if (b==-2 && rb==-1)
        return rotateLeft(curr);
    //left right rotation
    else if (b==-2 && lb==1) 
        return rotateRightLeft(curr);
    // right left rotation
    else if (b==2 && lb==-1)
        return rotateLeftRight(curr);
    
    return curr;
}

void createTree (int * a, int * d, int la, int ld)
{
    Node * head = NULL;

    for (int i = 0; i < la; i++)
        head = insert(head, *(a+i));

    cout << "PRE Order: " << endl;
    printPre(head);
    cout << "\nIN Order: " << endl;
    printIn(head);
    cout << "\nPOST Order: " << endl;
    printPost(head);
    cout << endl;

    for (int i = 0; i < ld; i++)
        head = remove(head, *(d+i));

    cout << "PRE Order: " << endl;
    printPre(head);
    cout << "\nIN Order: " << endl;
    printIn(head);
    cout << "\nPOST Order: " << endl;
    printPost(head);
    cout << endl;
}

int main (void)
{
    string str = "";
    getline(cin,str);

    Node * head = NULL;
    // int a [] = 
    // {
    //     66, 24, 39, 93,
    //     64, 90, 94, 96,
    //     89, 11, 19, 79,
    //     41, 87, 59, 88,
    //     18, 16, 50, 72,
    //     58, 70, 21, 29,
    //     15, 54, 33, 26,
    //     62, 25, 17, 81
    // };
    // int d [] = 
    // {
    //     89, 19, 64, 21,
    //     58, 17, 50, 93
    // };
 
    // createTree(a, d, 32, 8);

    istringstream split(str);
    vector<std::string> tokens;
    for (std::string each; getline(split, each, ' '); tokens.push_back(each));

    for (size_t i = 0; i < tokens.size()-1; i++)
    {
        int length = tokens[i].length();

        if (tokens[i].at(0)=='D')
            head = remove(  head, stringtoint( tokens[i].substr(1,length) )  );
        else if (tokens[i].at(0)=='A')
            head = insert(  head, stringtoint( tokens[i].substr(1,length) )  );
        else
            exit(EXIT_FAILURE);
    }

    if (head == NULL)
    {
        cout << "EMPTY" << endl;
        return 0;
    }

    switch ((int)( tokens[tokens.size()-1].length() ))
    {
    case 2:
        cout << "IN\node";
        printIn( head );
        break;
    case 3:
        cout << "PRE\node";
        printPre( head );
        break;
    case 4:
        cout << "POST\node";
        printPost( head );
        break;
    
    default:
        exit(EXIT_FAILURE);
    }
    cout << endl;

    return 0;
}