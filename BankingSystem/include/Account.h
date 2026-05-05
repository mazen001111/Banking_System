#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "LinkedList.h"
using namespace std;

// ─────────────────────────────────────────
//  Account — represents one bank account.
//
//  Every account is stored in TWO places:
//    1. HashTable  — for fast O(1) lookup by ID
//    2. BST        — for sorted display by ID
//  Both structures hold a POINTER to the same
//  Account object, so a balance update in one
//  is automatically visible in the other.
// ─────────────────────────────────────────

struct Account {

    int         accountID;    // unique number assigned by Utils::generateID(), e.g. 1001
    string ownerName;    // full name of the customer, e.g. "Ahmed Mohamed"
    double      balance;      // current amount of money in the account (EGP)
    string accountType;  // either "savings" or "current"
    LinkedList  history;      // every transaction this account ever had, newest first

    // Default constructor — initialises numeric fields to safe values.
    // Without this, accountID and balance would contain garbage memory.
    Account() : accountID(0), balance(0.0) {}
};

// Prints one account's details to the screen in a clean, readable format.
// Declared here so both Account.cpp and BST.cpp can use it.
void printAccount(const Account& acc);

#endif