#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "LinkedList.h"

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
    int accountID;           // unique number assigned by Utils::generateID()
    std::string ownerName;   // full name of the customer
    double balance;          // current amount of money in the account (EGP)
    std::string accountType; // either "savings" or "current"
    LinkedList history;      // every transaction this account ever had

    // Default constructor
    Account() : accountID(0), balance(0.0) {}
};

void printAccount(const Account& acc);

#endif