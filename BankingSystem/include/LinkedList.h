#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Transaction.h"

struct ListNode {
    Transaction data;
    ListNode* next;
    ListNode(Transaction t) : data(t), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;
    int count;

public:
    LinkedList();
    ~LinkedList();

    void addTransaction(Transaction t);
    void printHistory();
    void printLastN(int n);
    void clear();
    int getCount();
};

#endif