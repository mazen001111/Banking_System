#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include "Account.h"

class HashTable {
public:
    HashTable();
    ~HashTable();

    void insert(Account* account);
    Account* search(int accountID);
    bool remove(int accountID);
    std::vector<Account*> getAll();
    int getCount() const;

private:
    int hashFunction(int id);
    static const int TABLE_SIZE = 101;
    std::vector<Account*> table[TABLE_SIZE];
    int count;
};

#endif