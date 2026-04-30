#ifndef BANK_H
#define BANK_H

#include <string>
#include "HashTable.h"
#include "BST.h"
#include "Account.h"
using namespace std;

class Bank {
private:
    HashTable accounts;       // main storage — O(1) lookup by accountID
    BST       sortedAccounts; // secondary storage — sorted display by accountID

public:
    // constructor: loads data from file on startup
    Bank();

    // destructor: saves data to file on exit
    ~Bank();

    // account management
    void createAccount(string name, string type);
    void deleteAccount(int accountID);

    // money operations
    bool deposit (int accountID, double amount);
    bool withdraw(int accountID, double amount);
    bool transfer(int fromID, int toID, double amount);

    // information
    void search      (int accountID);
    void displayAll  ();
    void printHistory(int accountID);

    // file operations (called automatically by constructor/destructor) 
    void loadFromFile(string filename);
    void saveToFile  (string filename);
};

#endif