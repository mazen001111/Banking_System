#include <iostream>
#include "BST.h"
using namespace std;

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    destroyTree(root);
}

void BST::destroyTree(Node* node)
{
    if (node == nullptr)
        return;

    destroyTree(node->left);
    destroyTree(node->right);

    // Important:
    // The BST only deletes its own nodes.
    // It does NOT delete the Account itself because the account may also be used
    // by the hash table or another data structure.
    delete node;
}

void BST::insert(Account* account)
{
    if (account == nullptr)
        return;

    root = insertHelper(root, account);
}

BST::Node* BST::insertHelper(Node* node, Account* account)
{
    if (node == nullptr)
    {
        return new Node(account);
    }

    if (account->accountID < node->account->accountID)
    {
        node->left = insertHelper(node->left, account);
    }
    else if (account->accountID > node->account->accountID)
    {
        node->right = insertHelper(node->right, account);
    }
    else
    {
        cout << "Duplicate account ID not inserted: "
             << account->accountID << endl;
    }

    return node;
}

void BST::inorder()
{
    if (root == nullptr)
    {
        cout << "No accounts to display." << endl;
        return;
    }

    inorderHelper(root);
}

void BST::inorderHelper(Node* node)
{
    if (node == nullptr)
        return;

    inorderHelper(node->left);

    // This uses the printAccount function from Account.cpp
    printAccount(*(node->account));

    inorderHelper(node->right);
}

Account* BST::searchByID(int id)
{
    return searchHelper(root, id);
}

Account* BST::searchHelper(Node* node, int id)
{
    if (node == nullptr)
        return nullptr;

    if (id == node->account->accountID)
    {
        return node->account;
    }
    else if (id < node->account->accountID)
    {
        return searchHelper(node->left, id);
    }
    else
    {
        return searchHelper(node->right, id);
    }
}

void BST::deleteNode(int id)
{
    root = deleteHelper(root, id);
}

BST::Node* BST::deleteHelper(Node* node, int id)
{
    if (node == nullptr)
    {
        cout << "Account ID not found in BST: " << id << endl;
        return nullptr;
    }

    if (id < node->account->accountID)
    {
        node->left = deleteHelper(node->left, id);
    }
    else if (id > node->account->accountID)
    {
        node->right = deleteHelper(node->right, id);
    }
    else
    {
        // Case 1: no child
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            return nullptr;
        }

        // Case 2: only right child
        else if (node->left == nullptr)
        {
            Node* temp = node->right;
            delete node;
            return temp;
        }

        // Case 2: only left child
        else if (node->right == nullptr)
        {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Case 3: two children
        else
        {
            Node* minNode = findMin(node->right);

            // Replace current account pointer with the smallest account
            // in the right subtree
            node->account = minNode->account;

            // Delete the duplicate node from the right subtree
            node->right = deleteHelper(node->right, minNode->account->accountID);
        }
    }

    return node;
}

BST::Node* BST::findMin(Node* node)
{
    while (node != nullptr && node->left != nullptr)
    {
        node = node->left;
    }

    return node;
}
