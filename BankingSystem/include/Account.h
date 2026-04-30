#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "LinkedList.h"
using namespace std;

struct Account {
    int    accountID;    // unique number assigned by the system, e.g. 1001
    string ownerName;    // full name of the customer
    double balance;      // current amount of money in the account
    string accountType;  // either "savings" or "current"
    LinkedList history;  // every transaction this account ever had, newest first
};

// prints one account's details to the screen in a clean format
void printAccount(const Account& acc);

#endif