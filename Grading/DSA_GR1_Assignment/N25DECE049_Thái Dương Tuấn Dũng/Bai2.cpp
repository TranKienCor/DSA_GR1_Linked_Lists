#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int v) : data(v), next(NULL) {}
};

Node* buildList(const int a[], int n) {
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 0; i < n; i++) {
        Node* p = new Node(a[i]);
        if (head == NULL) head = tail = p;
        else { tail->next = p; tail = p; }
    }
    return head;
}

void printList(Node* head) {
    Node* p = head;
    cout << "head";
    while (p != NULL) { cout << " -> [" << p->data << "]"; p = p->next; }
    cout << " -> NULL\n";
}

string val(Node* p) {
    if (p == NULL) return "NULL";
    return to_string(p->data);
}

void freeList(Node* head) {
    while (head != NULL) { Node* t = head; head = head->next; delete t; }
}

Node* buildCircular(const int a[], int n) {
    Node* head = buildList(a, n);
    if (head == NULL) return NULL;
    Node* t = head;
    while (t->next != NULL) t = t->next;
    t->next = head;
    return head;
}

void printCircular(Node* head) {
    if (head == NULL) { cout << "(empty)\n"; return; }
    Node* p = head;
    cout << "head";
    do { cout << " -> [" << p->data << "]"; p = p->next; } while (p != head);
    cout << " -> (back to [" << head->data << "])\n";
}

Node* InsertHead(Node* head, int newValue, bool trace) {
    Node* newNode = new Node(newValue);
    if (trace) cout << "Step 1: create newNode [" << newValue << "]\n";

    if (head == NULL) {
        newNode->next = newNode;
        if (trace) cout << "List empty: newNode points to itself\n";
        return newNode;
    }

    Node* tail = head;
    if (trace) cout << "Step 2: tail = [" << tail->data << "]\n";
    while (tail->next != head) {
        tail = tail->next;
        if (trace) cout << "        move tail -> [" << tail->data << "]\n";
    }
    if (trace) cout << "        tail->next == head, stop at [" << tail->data << "]\n";

    newNode->next = head;
    if (trace) cout << "Step 3: newNode->next = head -> [" << head->data << "]\n";
    tail->next = newNode;
    if (trace) cout << "Step 4: tail [" << tail->data << "]->next = newNode [" << newValue << "]\n";
    head = newNode;
    if (trace) cout << "Step 5: head = newNode [" << newValue << "]\n";
    return head;
}

void freeCircular(Node* head) {
    if (head == NULL) return;
    Node* p = head->next;
    while (p != head) { Node* t = p; p = p->next; delete t; }
    delete head;
}

int main() {
    cout << "=========== PROBLEM 2: Circular InsertHead ===========\n";
    int a2[] = {10, 20, 30};
    Node* c2 = buildCircular(a2, 3);
    cout << "Before: "; printCircular(c2);
    c2 = InsertHead(c2, 5, true);
    cout << "After : "; printCircular(c2);
    freeCircular(c2);

    return 0;
}
