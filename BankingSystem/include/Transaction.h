#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>

struct Transaction {
    std::string timestamp;
    std::string type;
    double amount;
    double balanceAfter;
};

void printTransaction(const Transaction& t);

#endif