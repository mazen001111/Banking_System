#include "Transaction.h"

struct ListNode {
    Transaction data;
    ListNode*   next;
    ListNode(Transaction t) : data(t), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;  // points to the most recent transaction
    int       count; // how many transactions are stored

public:
    LinkedList();           // constructor: head = nullptr, count = 0
    ~LinkedList();          // destructor: free all nodes

    void addTransaction(Transaction t);  // insert at head (newest first)
    void printHistory();                 // print all transactions from newest to oldest
    void printLastN(int n);              // print only the most recent n transactions
    void clear();                        // delete all nodes, reset to empty
    int  getCount();                     // return number of transactions
};