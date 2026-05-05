#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>   // C++17 — no platform headers needed
#include "Bank.h"
#include "Utils.h"
using namespace std;


// ─────────────────────────────────────────
//  Constructor & Destructor
// ─────────────────────────────────────────

Bank::Bank() {
    loadFromFile("data/accounts.txt");
}

Bank::~Bank() {
    saveToFile("data/accounts.txt");
    // NOTE: HashTable destructor already deletes all Account* pointers.
    // Do NOT delete them here — that would be a double-free crash.
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

        // create the account on the HEAP with new
        // so the pointer stays valid for both HashTable and BST
        Account* acc = new Account();
        acc->accountID   = stoi(idStr);
        acc->ownerName   = name;
        acc->balance     = stod(balanceStr);
        acc->accountType = type;

        accounts.insert(acc);       // HashTable takes Account*
        sortedAccounts.insert(acc); // BST takes Account*

        if (acc->accountID > maxID) maxID = acc->accountID;
    }

    file.close();
    Utils::setNextID(maxID + 1);
    cout << "Data loaded successfully." << endl;
}

void Bank::saveToFile(string filename) {
    // Ensure the "data/" directory exists before writing.
    // std::filesystem works on Windows, Linux, and Mac — no platform headers needed.
    filesystem::create_directories("data");

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open file to save data." << endl;
        return;
    }

    // getAll() returns vector<Account*>
    vector<Account*> all = accounts.getAll();

    for (Account* acc : all) {
        file << acc->accountID   << "|"
             << acc->ownerName   << "|"
             << acc->balance     << "|"
             << acc->accountType << "\n";
    }

    file.close();
    cout << "Data saved successfully." << endl;
}


// ─────────────────────────────────────────
//  Account Management
// ─────────────────────────────────────────

void Bank::createAccount(string name, string type) {
    if (type != "savings" && type != "current") {
        cout << "Error: account type must be 'savings' or 'current'." << endl;
        return;
    }

    // allocate on the heap — one pointer shared by both data structures
    Account* acc = new Account();
    acc->accountID   = Utils::generateID();
    acc->ownerName   = name;
    acc->balance     = 0.0;
    acc->accountType = type;

    accounts.insert(acc);       // HashTable stores the pointer
    sortedAccounts.insert(acc); // BST stores the same pointer

    cout << "Account created successfully!" << endl;
    cout << "Your account ID is : " << acc->accountID << endl;
    cout << "Starting balance   : 0.00 EGP"            << endl;
}

void Bank::deleteAccount(int accountID) {
    Account* acc = accounts.search(accountID);
    if (acc == nullptr) {
        cout << "Error: no account found with ID " << accountID << endl;
        return;
    }

    if (acc->balance > 0) {
        cout << "Warning: account still has " << acc->balance
             << " EGP. Deleting anyway." << endl;
    }

    // Remove from BST first.
    // BST::deleteNode only deletes the BST Node wrapper — NOT the Account* itself.
    sortedAccounts.deleteNode(accountID);

    // Remove from HashTable.
    // HashTable::remove DOES delete the Account* internally.
    // This must happen AFTER the BST removal so the pointer is still valid
    // when the BST traverses to find it.
    accounts.remove(accountID);

    cout << "Account " << accountID << " deleted successfully." << endl;
}


// ─────────────────────────────────────────
//  Money Operations
// ─────────────────────────────────────────

bool Bank::deposit(int accountID, double amount) {
    Account* acc = accounts.search(accountID);
    if (acc == nullptr) {
        cout << "Error: account " << accountID << " not found." << endl;
        return false;
    }
    if (amount <= 0) {
        cout << "Error: deposit amount must be greater than zero." << endl;
        return false;
    }

    acc->balance += amount;

    Transaction t;
    t.type         = "deposit";
    t.amount       = amount;
    t.balanceAfter = acc->balance;
    t.timestamp    = Utils::getCurrentTime();
    acc->history.addTransaction(t);

    cout << "Deposited "    << amount       << " EGP successfully." << endl;
    cout << "New balance: " << acc->balance << " EGP"              << endl;
    return true;
}

bool Bank::withdraw(int accountID, double amount) {
    Account* acc = accounts.search(accountID);
    if (acc == nullptr) {
        cout << "Error: account " << accountID << " not found." << endl;
        return false;
    }
    if (amount <= 0) {
        cout << "Error: withdrawal amount must be greater than zero." << endl;
        return false;
    }
    if (amount > acc->balance) {
        cout << "Error: insufficient funds."              << endl;
        cout << "Requested : " << amount       << " EGP" << endl;
        cout << "Available : " << acc->balance << " EGP" << endl;
        return false;
    }

    acc->balance -= amount;

    Transaction t;
    t.type         = "withdraw";
    t.amount       = amount;
    t.balanceAfter = acc->balance;
    t.timestamp    = Utils::getCurrentTime();
    acc->history.addTransaction(t);

    cout << "Withdrew "     << amount       << " EGP successfully." << endl;
    cout << "New balance: " << acc->balance << " EGP"              << endl;
    return true;
}

bool Bank::transfer(int fromID, int toID, double amount) {
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
        cout << "Available: " << from->balance << " EGP"          << endl;
        return false;
    }

    from->balance -= amount;
    to->balance   += amount;

    Transaction t1;
    t1.type         = "transfer_out";
    t1.amount       = amount;
    t1.balanceAfter = from->balance;
    t1.timestamp    = Utils::getCurrentTime();
    from->history.addTransaction(t1);

    Transaction t2;
    t2.type         = "transfer_in";
    t2.amount       = amount;
    t2.balanceAfter = to->balance;
    t2.timestamp    = Utils::getCurrentTime();
    to->history.addTransaction(t2);

    cout << "Transfer successful!" << endl;
    cout << "Transferred : " << amount        << " EGP"  << endl;
    cout << "From account: " << fromID        << endl;
    cout << "To account  : " << toID          << endl;
    cout << "New balance (source)     : " << from->balance << " EGP" << endl;
    cout << "New balance (destination): " << to->balance   << " EGP" << endl;
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
    if (accounts.getCount() == 0) {
        cout << "No accounts in the system." << endl;
        return;
    }

    cout << "\n===============================" << endl;
    cout << "       ALL ACCOUNTS (sorted)   "  << endl;
    cout << "===============================" << endl;

    // BST inorder traversal prints accounts sorted by accountID
    sortedAccounts.inorder();

    cout << "Total accounts: " << accounts.getCount() << endl;
}

void Bank::printHistory(int accountID) {
    Account* acc = accounts.search(accountID);
    if (acc == nullptr) {
        cout << "Error: no account found with ID " << accountID << endl;
        return;
    }

    cout << "\n--- Transaction History for Account " << accountID << " ---" << endl;
    cout << "Owner: " << acc->ownerName << endl;

    if (acc->history.getCount() == 0) {
        cout << "No transactions recorded yet." << endl;
        return;
    }

    acc->history.printHistory();
    cout << "Total transactions: " << acc->history.getCount() << endl;
}