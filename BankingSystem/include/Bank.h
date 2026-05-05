#ifndef BANK_H

#define BANK_H
#include <string>
#include "HashTable.h"
#include "BST.h"
#include "Account.h"

class Bank {
private:
    HashTable accounts;       // main storage — O(1) lookup
    BST sortedAccounts;       // secondary storage — sorted display

public:
    Bank();
    ~Bank();

    // account management
    void createAccount(std::string name, std::string type);
    void deleteAccount(int accountID);

    // money operations
    bool deposit(int accountID, double amount);
    bool withdraw(int accountID, double amount);
    bool transfer(int fromID, int toID, double amount);

    // information
    void search(int accountID);
    void displayAll();
    void printHistory(int accountID);

    // file operations
    void loadFromFile(std::string filename);
    void saveToFile(std::string filename);
};

#endif