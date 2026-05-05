#include "HashTable.h"

HashTable::HashTable() : count(0) {
}

HashTable::~HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (auto& acc : table[i]) {
            delete acc;
        }
        table[i].clear();
    }
}

int HashTable::hashFunction(int id) {
    return id % TABLE_SIZE;
}

void HashTable::insert(Account* account) {
    if (search(account->accountID) != nullptr) {
        return;  // Duplicate check - do not insert if exists
    }
    int index = hashFunction(account->accountID);
    table[index].push_back(account);
    count++;
}

Account* HashTable::search(int accountID) {
    int index = hashFunction(accountID);
    for (auto& acc : table[index]) {
        if (acc->accountID == accountID) {
            return acc;
        }
    }
    return nullptr;
}

bool HashTable::remove(int accountID) {
    int index = hashFunction(accountID);
    auto& bucket = table[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if ((*it)->accountID == accountID) {
            delete *it;
            bucket.erase(it);
            count--;
            return true;
        }
    }
    return false;
}

std::vector<Account*> HashTable::getAll() {
    std::vector<Account*> all;
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (auto& acc : table[i]) {
            all.push_back(acc);
        }
    }
    return all;
}

int HashTable::getCount() const {
    return count;
}
