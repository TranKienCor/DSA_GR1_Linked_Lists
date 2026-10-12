#include <iostream>
#include <string>
using namespace std;

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int v) : data(v), prev(NULL), next(NULL) {}
};

DNode* buildDList(const int a[], int n) {
    DNode* head = NULL;
    DNode* tail = NULL;
    for (int i = 0; i < n; i++) {
        DNode* p = new DNode(a[i]);
        if (head == NULL) head = tail = p;
        else { tail->next = p; p->prev = tail; tail = p; }
    }
    return head;
}

void printDList(DNode* head) {
    cout << "Forward : NULL";
    DNode* p = head;
    DNode* last = NULL;
    while (p != NULL) { cout << " <-> [" << p->data << "]"; last = p; p = p->next; }
    cout << " <-> NULL\n";
    cout << "Backward: NULL";
    while (last != NULL) { cout << " <-> [" << last->data << "]"; last = last->prev; }
    cout << " <-> NULL\n";
}

DNode* InsertBefore(DNode* head, int target, int newValue) {
    DNode* curr = head;
    while (curr != NULL && curr->data != target)
        curr = curr->next;

    if (curr == NULL) {
        cout << "Target " << target << " not found. List unchanged.\n";
        return head;
    }

    DNode* newNode = new DNode(newValue);
    newNode->prev = curr->prev;
    newNode->next = curr;

    if (curr->prev == NULL)
        head = newNode;
    else
        curr->prev->next = newNode;

    curr->prev = newNode;
    return head;
}

void freeDList(DNode* head) {
    while (head != NULL) { DNode* t = head; head = head->next; delete t; }
}

int main() {
    cout << "=========== PROBLEM 3: Doubly InsertBefore ===========\n";
    int a3[] = {7, 9, 12};
    DNode* d3 = buildDList(a3, 3);
    cout << "Initial list:\n"; printDList(d3);

    cout << "\n-- Normal case: insert 8 before 9\n";
    d3 = InsertBefore(d3, 9, 8);
    printDList(d3);

    cout << "\n-- Edge case 1: insert 3 before head (7)\n";
    d3 = InsertBefore(d3, 7, 3);
    printDList(d3);

    cout << "\n-- Edge case 2: insert 50 before 100 (not in list)\n";
    d3 = InsertBefore(d3, 100, 50);
    printDList(d3);
    freeDList(d3);

    return 0;
}
