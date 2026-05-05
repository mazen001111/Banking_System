#ifndef BST_H
#define BST_H

#include "Account.h"

class BST
{
private:
    struct Node
    {
        Account* account;
        Node* left;
        Node* right;

        Node(Account* acc)
        {
            account = acc;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    Node* insertHelper(Node* node, Account* account);
    void inorderHelper(Node* node);
    Account* searchHelper(Node* node, int id);
    Node* deleteHelper(Node* node, int id);
    Node* findMin(Node* node);
    void destroyTree(Node* node);

public:
    BST();
    ~BST();

    void insert(Account* account);
    void inorder();
    Account* searchByID(int id);
    void deleteNode(int id);
};

#endif
