#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Bank.h"
#include "Utils.h"
#include "Transaction.h"
#include "Account.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "BST.h"
using namespace std;


// ─────────────────────────────────────────
//  Constructor & Destructor
// ─────────────────────────────────────────

Bank::Bank() {
    loadFromFile("data/accounts.txt");
}

Bank::~Bank() {
    saveToFile("data/accounts.txt");
}


// ─────────────────────────────────────────
//  File Operations
// ─────────────────────────────────────────

void Bank::loadFromFile(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No existing data file found. Starting with empty system." << endl;
        return;
    }

    string line;
    int    maxID = 1000;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, name, balanceStr, type;

        getline(ss, idStr,      '|');
        getline(ss, name,       '|');
        getline(ss, balanceStr, '|');
        getline(ss, type,       '|');

        Account acc;
        acc.accountID   = stoi(idStr);     // convert string "1001" to integer 1001
        acc.ownerName   = name;
        acc.balance     = stod(balanceStr); // convert string "5000.00" to double
        acc.accountType = type;

        accounts.insert(acc);
        sortedAccounts.insert(acc);

        if (acc.accountID > maxID) maxID = acc.accountID;
    }

    file.close();

    // tell the ID generator to start from the next available ID
    Utils::setNextID(maxID + 1);

    cout << "Data loaded successfully." << endl;
}

void Bank::saveToFile(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open file to save data." << endl;
        return;
    }

    vector<Account> all;
    accounts.getAll(all); // get every account from the hash table

    for (Account& acc : all) {
        file << acc.accountID   << "|"
             << acc.ownerName   << "|"
             << acc.balance     << "|"
             << acc.accountType << "\n";
    }

    file.close();
    cout << "Data saved successfully." << endl;
}


// ─────────────────────────────────────────
//  Account Management
// ─────────────────────────────────────────

void Bank::createAccount(string name, string type) {
    // validate account type
    if (type != "savings" && type != "current") {
        cout << "Error: account type must be 'savings' or 'current'." << endl;
        return;
    }

    // generate a unique ID
    int newID = Utils::generateID();

    // build the Account object
    Account acc;
    acc.accountID   = newID;
    acc.ownerName   = name;
    acc.balance     = 0.0;
    acc.accountType = type;

    // insert into BOTH data structures
    accounts.insert(acc);        // hash table: for fast lookup
    sortedAccounts.insert(acc);  // BST: for sorted display

    cout << "Account created successfully!" << endl;
    cout << "Your account ID is: " << newID  << endl;
    cout << "Starting balance  : 0.00 EGP"   << endl;
}

void Bank::deleteAccount(int accountID) {
    // check the account exists before trying to delete
    Account* acc = accounts.search(accountID);
    if (acc == nullptr) {
        cout << "Error: no account found with ID " << accountID << endl;
        return;
    }

    // warn if there is still money in the account
    if (acc->balance > 0) {
        cout << "Warning: account still has " << acc->balance
             << " EGP. Deleting anyway." << endl;
    }

    // remove from both data structures
    accounts.remove(accountID);
    sortedAccounts.deleteNode(accountID);

    cout << "Account " << accountID << " deleted successfully." << endl;
}


// ─────────────────────────────────────────
//  Money Operations
// ─────────────────────────────────────────

bool Bank::deposit(int accountID, double amount) {
    // step 1: find the account
    Account* acc = accounts.search(accountID);
    if (acc == nullptr) {
        cout << "Error: account " << accountID << " not found." << endl;
        return false;
    }

    // step 2: validate the amount
    if (amount <= 0) {
        cout << "Error: deposit amount must be greater than zero." << endl;
        return false;
    }

    // step 3: update balance
    acc->balance += amount;

    // step 4: record the transaction in the account's linked list
    Transaction t;
    t.type         = "deposit";
    t.amount       = amount;
    t.balanceAfter = acc->balance;
    t.timestamp    = Utils::getCurrentTime();
    acc->history.addTransaction(t);

    cout << "Deposited " << amount       << " EGP successfully." << endl;
    cout << "New balance: " << acc->balance << " EGP" << endl;
    return true;
}

bool Bank::withdraw(int accountID, double amount) {
    // step 1: find the account
    Account* acc = accounts.search(accountID);
    if (acc == nullptr) {
        cout << "Error: account " << accountID << " not found." << endl;
        return false;
    }

    // step 2: validate the amount
    if (amount <= 0) {
        cout << "Error: withdrawal amount must be greater than zero." << endl;
        return false;
    }

    // step 3: check for overdraft — cannot withdraw more than balance
    if (amount > acc->balance) {
        cout << "Error: insufficient funds."               << endl;
        cout << "Requested : " << amount       << " EGP"  << endl;
        cout << "Available : " << acc->balance << " EGP"  << endl;
        return false;
    }

    // step 4: update balance
    acc->balance -= amount;

    // step 5: record the transaction
    Transaction t;
    t.type         = "withdraw";
    t.amount       = amount;
    t.balanceAfter = acc->balance;
    t.timestamp    = Utils::getCurrentTime();
    acc->history.addTransaction(t);

    cout << "Withdrew " << amount          << " EGP successfully." << endl;
    cout << "New balance: " << acc->balance << " EGP" << endl;
    return true;
}

bool Bank::transfer(int fromID, int toID, double amount) {
    // step 1: find both accounts
    Account* from = accounts.search(fromID);
    Account* to   = accounts.search(toID);

    if (from == nullptr) {
        cout << "Error: source account " << fromID << " not found." << endl;
        return false;
    }
    if (to == nullptr) {
        cout << "Error: destination account " << toID << " not found." << endl;
        return false;
    }
    if (fromID == toID) {
        cout << "Error: cannot transfer to the same account." << endl;
        return false;
    }
    if (amount <= 0) {
        cout << "Error: transfer amount must be greater than zero." << endl;
        return false;
    }
    if (from->balance < amount) {
        cout << "Error: insufficient funds in account " << fromID << endl;
        cout << "Available: " << from->balance << " EGP" << endl;
        return false;
    }

    // step 2: move the money
    from->balance -= amount;
    to->balance   += amount;

    // step 3: record on the sender's history
    Transaction t1;
    t1.type         = "transfer_out";
    t1.amount       = amount;
    t1.balanceAfter = from->balance;
    t1.timestamp    = Utils::getCurrentTime();
    from->history.addTransaction(t1);

    // step 4: record on the receiver's history
    Transaction t2;
    t2.type         = "transfer_in";
    t2.amount       = amount;
    t2.balanceAfter = to->balance;
    t2.timestamp    = Utils::getCurrentTime();
    to->history.addTransaction(t2);

    cout << "Transferred " << amount << " EGP from account "
         << fromID << " to account " << toID << " successfully." << endl;
    return true;
}


// ─────────────────────────────────────────
//  Information
// ─────────────────────────────────────────

void Bank::search(int accountID) {
    Account* acc = accounts.search(accountID);
    if (acc == nullptr) {
        cout << "Error: no account found with ID " << accountID << endl;
        return;
    }
    printAccount(*acc);
}

void Bank::displayAll() {
    cout << "========== All Accounts (sorted by ID) ==========" << endl;
    sortedAccounts.inorder(); // BST in-order traversal — always sorted ascending
}

void Bank::printHistory(int accountID) {
    Account* acc = accounts.search(accountID);
    if (acc == nullptr) {
        cout << "Error: no account found with ID " << accountID << endl;
        return;
    }
    cout << "===== Transaction History — Account "
         << accountID << " =====" << endl;
    acc->history.printHistory();
}