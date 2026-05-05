#include "../include/LinkedList.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList() {
    head  = nullptr;
    count = 0;
}

void LinkedList::addTransaction(Transaction t) {
    ListNode* newNode = new ListNode(t);
    newNode->next = head;
    head  = newNode;
    count++;
}

void LinkedList::printHistory() {
    if (head == nullptr) {
        cout << "No transactions recorded yet." << endl;
        return;
    }

    ListNode* current = head;
    int index = 1;
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
        delete toDelete;
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