#include <iostream>
#include "Account.h"
using namespace std;

void printAccount(const Account& acc) {
    cout << "-----------------------------"   << endl;
    cout << "Account ID   : " << acc.accountID   << endl;
    cout << "Owner        : " << acc.ownerName   << endl;
    cout << "Balance      : " << acc.balance     << " EGP" << endl;
    cout << "Account Type : " << acc.accountType << endl;
    cout << "-----------------------------"   << endl;
}