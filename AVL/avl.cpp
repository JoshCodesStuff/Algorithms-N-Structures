#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

// #include "avltree.h"
using namespace std;

//node struct
struct node {
    int data;
    int height;
    node * left;
    node * right;
};

node* makeN(int data)
{
    node* n = new node();
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return(n);
}

//helper functions for main stuffs
int height(node *n)
{
    if (n == NULL)
        return 0;
    return n->height;
}
int getBalance(node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
node * minvalnode(node * n)
{
    node * temp = n;
    
    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}


//helper functions for main
int max(int a, int b){return a > b ? a:b;}
int stringtoint(string str){return atoi(str.c_str());}
void printIn(node * n)
{
    if (n != NULL)
    {
        printIn(n->left);
        cout << n->data << " ";
        printIn(n->right);
    }
}
void printPre(node * n){
    if(n != NULL)
    {
        cout << n->data << " ";
        printPre(n->left);
        printPre(n->right);
    }
}
void printPost(node * n){
    if (n != NULL)
    {
        printPost(n->left);
        printPost(n->right);
        cout << n->data << " ";
    }
}


//rotation functions for organisation
node* rotateLeft(node* x)
{
    node * y = x->right;
    node * branch = y->left;

    y->left = x;
    x->right = branch;

    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;

    return y;    
}
node* rotateRight(node* y)
{
    node * x = y->left;
    node * branch = x->right;
    
    x->right = y;
    y->left = branch;

    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;

    return x;
}
node* rotateRightLeft(node* n)
{
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}
node* rotateLeftRight(node* n)
{
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}


//binary insertion
node* insert(node * curr, int data)
{
    //creates tree head
    if(curr == NULL) {
        return (makeN(data));
    }

    if (data < curr->data)
        curr->left = insert(curr->left, data);
    else if (data > curr->data)
        curr->right = insert(curr->right, data);
    else // Equal keys not allowed
        return curr;

    // update height before organisation
    curr->height = 1 + max(height(curr->left),height(curr->right));

    // balance is needed for organisation method
    int bal = getBalance(curr);

    // right right case
    if (bal > 1 && data < curr->left->data)
        return rotateRight(curr);
    //left left rotation
    if (bal < -1 && data > curr->right->data)
        return rotateLeft(curr);
    //left right rotation
    if (bal > 1 && data > curr->left->data) 
        return rotateLeftRight(curr);
    // right left rotation
    if (bal < -1 && data < curr->right->data)
        return rotateRightLeft(curr);
    
    return curr;
}


//delete from bst
node* remove(node * curr, int val)
{
    //already been removed
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
            node* temp = curr->left ? curr->left : curr->right;

            if (temp == NULL)
            {
                temp = curr;
                curr = NULL;
            }
            else *curr = *temp;
            free(temp);
        }
        else {
            node * temp = minvalnode(curr->right);
            curr->data = temp->data;
            curr->right = remove(curr->right, temp->data);
        }
    }
    //case where tree had no children but root node
    if (curr==NULL)
        return curr;

    curr->height = 1+max(height(curr->left),height(curr->right));

    int bal = getBalance(curr);

    // 4 possible cases again for organisation
    if (bal > 1 && getBalance(curr->left) >= 0)
        return rotateRight(curr);
    
    //left right case
    if (bal > 1 && getBalance(curr->left) < 0)
        return rotateLeftRight(curr);
    
    if (bal < -1 && getBalance(curr->right) <= 0)
        return rotateLeft(curr);
    if (bal < -1 && getBalance(curr->right) > 0)
        return rotateRightLeft(curr);

    return curr;
}

void createTree (int * a, int * d, int la, int ld)
{
    node * head = NULL;

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

    node * head = NULL;
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
        printIn( head );
        break;
    case 3:
        printPre( head );
        break;
    case 4:
        printPost( head );
        break;
    
    default:
        exit(EXIT_FAILURE);
    }
    cout << endl;

    return 0;
}