#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

// #include "avltree.h"
using namespace std;

// node struct
struct Node
{
    int data;
    int height;
    Node *left;
    Node *right;
};

Node *makeN(int data)
{
    Node *node = new Node();
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

// helper functions for main stuffs
int height(Node *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}
int getBalance(Node *node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}
Node *minvalnode(Node *node)
{
    Node *temp = node;

    while (temp->left != nullptr)
        temp = temp->left;

    return temp;
}

// helper functions for main
int max(int a, int b) { return a > b ? a : b; }
int stringtoint(string str) { return atoi(str.c_str()); }
void printIn(Node *node)
{
    if (node != nullptr)
    {
        printIn(node->left);
        cout << node->data << " ";
        printIn(node->right);
    }
}
void printPre(Node *node)
{
    if (node != nullptr)
    {
        cout << node->data << " ";
        printPre(node->left);
        printPre(node->right);
    }
}
void printPost(Node *node)
{
    if (node != nullptr)
    {
        printPost(node->left);
        printPost(node->right);
        cout << node->data << " ";
    }
}

// rotation functions for organisation
Node *rotateLeft(Node *x)
{
    Node *y = x->right;
    Node *branch = y->left;

    y->left = x;
    x->right = branch;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}
Node *rotateRight(Node *y)
{
    Node *x = y->left;
    Node *branch = x->right;

    x->right = y;
    y->left = branch;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}
Node *rotateRightLeft(Node *node)
{
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}
Node *rotateLeftRight(Node *node)
{
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

// binary insertion
Node *insert(Node *node, int data)
{
    // creates tree head
    if (node == nullptr)
        return (makeN(data));

    /* typical recursive binary insertion */
    // go left
    if (data < node->data)
        node->left = insert(node->left, data);
    // go right
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Equal keys not allowed
        return node;

    // update height before organisation
    node->height = 1 + max(height(node->left), height(node->right));

    // balance is needed for organisation method
    int balance = getBalance(node);

    if (balance > 1 and data > node->right->data) // right
        return rotateRight(node);
    if (balance < -1 and data < node->left->data) // left
        return rotateLeft(node);
    if (balance > 1 and data > node->left->data) // right left
        return rotateRightLeft(node);
    if (balance < -1 && data < node->right->data) // left right
        return rotateLeftRight(node);

    return node;
}

// delete from avl tree
Node *remove(Node *root, int data)
{
    // already been removed/never existed
    if (root == nullptr)
        return root;

    // go left recursively
    if (data < root->data)
        root->left = remove(root->left, data);
    // go right recursively
    else if (data > root->data)
        root->right = remove(root->right, data);

    else
    {
        if ((root->left == nullptr) || root->right == nullptr)
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            delete temp; // created with new so delete, don't free()
        }
        else
        {
            Node *temp = minvalnode(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
    }
    // case where tree had no children but root node
    if (root == nullptr)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    // balance is needed for organisation method
    int balance = getBalance(root);
    int leftBalance = getBalance(root->left);
    int rightBalance = getBalance(root->right);


    // right right case
    if (balance > 1 and leftBalance >=0)
        return rotateRight(root);
    if (balance == -2 and rightBalance <= 0)
        return rotateLeft(root);
    if (balance == -2 and leftBalance < 0)
        return rotateRightLeft(root);
    if (balance == 2 and rightBalance > 0)
        return rotateLeftRight(root);

    return root;
}

void createTree(int *a, int *d, int la, int ld)
{
    Node *head = nullptr;

    for (int i = 0; i < la; i++)
        head = insert(head, *(a + i));

    cout << "PRE Order: " << endl;
    printPre(head);
    cout << "\nIN Order: " << endl;
    printIn(head);
    cout << "\nPOST Order: " << endl;
    printPost(head);
    cout << endl;

    for (int i = 0; i < ld; i++)
        head = remove(head, *(d + i));

    cout << "PRE Order: " << endl;
    printPre(head);
    cout << "\nIN Order: " << endl;
    printIn(head);
    cout << "\nPOST Order: " << endl;
    printPost(head);
    cout << endl;
}

int main(void)
{
    string str = "";
    getline(cin, str);

    Node *head = nullptr;
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
    for (std::string each; getline(split, each, ' '); tokens.push_back(each))
        ;

    for (size_t i = 0; i < tokens.size() - 1; i++)
    {
        int length = tokens[i].length();

        if (tokens[i].at(0) == 'D')
            head = remove(head, stringtoint(tokens[i].substr(1, length)));
        else if (tokens[i].at(0) == 'A')
            head = insert(head, stringtoint(tokens[i].substr(1, length)));
        else
            exit(EXIT_FAILURE);
    }

    if (head == nullptr)
    {
        cout << "EMPTY" << endl;
        return 0;
    }

    switch ((int)(tokens[tokens.size() - 1].length()))
    {
    case 2:
        cout << "IN\node";
        printIn(head);
        break;
    case 3:
        cout << "PRE\node";
        printPre(head);
        break;
    case 4:
        cout << "POST\node";
        printPost(head);
        break;

    default:
        exit(EXIT_FAILURE);
    }
    cout << endl;

    return 0;
}