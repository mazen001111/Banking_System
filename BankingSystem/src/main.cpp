#include <iostream>
#include "Bank.h"
#include "Utils.h"




using namespace std;

int main() {
    Bank bank;
    // Bank constructor automatically calls loadFromFile("data/accounts.txt")
    // so all saved accounts are loaded before the menu appears

    int choice;

    do {
        cout << "\n===============================" << endl;
        cout << "       BANKING SYSTEM MENU     "  << endl;
        cout << "===============================" << endl;
        cout << " 1. Create Account"              << endl;
        cout << " 2. Deposit"                     << endl;
        cout << " 3. Withdraw"                    << endl;
        cout << " 4. Transfer"                    << endl;
        cout << " 5. Search Account"              << endl;
        cout << " 6. Display All Accounts"        << endl;
        cout << " 7. View Transaction History"    << endl;
        cout << " 8. Delete Account"              << endl;
        cout << " 0. Exit"                        << endl;
        cout << "===============================" << endl;

        choice = Utils::getValidInt("Enter your choice: ");

        cout << endl;

        if (choice == 1) {
            string name = Utils::getValidString("Enter owner full name: ");
            string type = Utils::getValidString("Enter account type (savings / current): ");
            bank.createAccount(name, type);
        }
        else if (choice == 2) {
            int    id  = Utils::getValidInt   ("Enter account ID: ");
            double amt = Utils::getValidDouble("Enter deposit amount: ");
            bank.deposit(id, amt);
        }
        else if (choice == 3) {
            int    id  = Utils::getValidInt   ("Enter account ID: ");
            double amt = Utils::getValidDouble("Enter withdrawal amount: ");
            bank.withdraw(id, amt);
        }
        else if (choice == 4) {
            int    from = Utils::getValidInt   ("Enter source account ID: ");
            int    to   = Utils::getValidInt   ("Enter destination account ID: ");
            double amt  = Utils::getValidDouble("Enter transfer amount: ");
            bank.transfer(from, to, amt);
        }
        else if (choice == 5) {
            int id = Utils::getValidInt("Enter account ID to search: ");
            bank.search(id);
        }
        else if (choice == 6) {
            bank.displayAll();
        }
        else if (choice == 7) {
            int id = Utils::getValidInt("Enter account ID: ");
            bank.printHistory(id);
        }
        else if (choice == 8) {
            int id = Utils::getValidInt("Enter account ID to delete: ");
            bank.deleteAccount(id);
        }
        else if (choice != 0) {
            cout << "Invalid choice. Please enter a number from the menu." << endl;
        }

    } while (choice != 0);

    // Bank destructor automatically calls saveToFile("data/accounts.txt")
    // so all data is saved before the program closes
    cout << "Thank you for using the Banking System. Goodbye." << endl;
    return 0;
}