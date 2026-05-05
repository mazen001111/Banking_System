#include <iostream>
#include "../include/Transaction.h"
using namespace std;

void printTransaction(const Transaction& t) {
    cout << "[" << t.timestamp << "] "
         << t.type
         << " | Amount: "            << t.amount
         << " EGP | Balance after: " << t.balanceAfter
         << " EGP" << endl;
}