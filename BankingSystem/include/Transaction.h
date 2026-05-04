#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
using namespace std;

struct Transaction {
    string timestamp;
    string type;
    double amount;
    double balanceAfter;
};

void printTransaction(const Transaction& t);

#endif