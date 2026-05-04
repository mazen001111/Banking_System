#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
    head  = nullptr;
    count = 0;
}
void LinkedList::addTransaction(Transaction t) {
    ListNode* newNode = new ListNode(t);
    // point the new node to whatever was previously first
    newNode->next = head;
    // the new node is now the first
    head  = newNode;
    count++;
}
// Why insert at head and not tail?
// Because the user always wants to see the MOST RECENT transactions first.
// The head is always the newest — no traversal needed to add new ones.
void LinkedList::printHistory() {
    if (head == nullptr) {
        cout << "No transactions recorded yet." << endl;
        return;
    }

    ListNode* current = head;
    int       index   = 1;
    while (current != nullptr) {
        cout << index << ". ";
        printTransaction(current->data);
        current = current->next;
        index++;
    }
}
void LinkedList::printLastN(int n) {
    ListNode* current = head;
    int printed = 0;
    while (current != nullptr && printed < n) {
        printTransaction(current->data);
        current = current->next;
        printed++;
    }
}
void LinkedList::clear() {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* toDelete = current;
        current = current->next;
        delete toDelete;    // free the memory of each node
    }
    head  = nullptr;
    count = 0;
}
int LinkedList::getCount() {
    return count;
}
LinkedList::~LinkedList() {
    clear();
}

