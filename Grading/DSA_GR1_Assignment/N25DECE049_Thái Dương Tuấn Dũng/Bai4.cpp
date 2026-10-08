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

Node* SortedInsert(Node* head, int val, bool trace) {
    Node* newNode = new Node(val);

    if (trace) cout << "Check: head == NULL ? " << (head == NULL ? "true" : "false");
    if (head == NULL || val <= head->data) {
        if (trace) cout << " -> insert at head\n";
        newNode->next = head;
        return newNode;
    }
    if (trace) cout << " | " << val << " <= " << head->data << " ? false -> search\n";

    Node* curr = head;
    int step = 1;
    while (true) {
        bool notNull = (curr->next != NULL);
        bool less = notNull && (curr->next->data < val);
        if (trace) {
            cout << "Step " << step++ << ": curr=[" << curr->data << "] curr->next=" << ::val(curr->next)
                 << "  (next!=NULL: " << (notNull ? "T" : "F");
            if (notNull) cout << ", " << curr->next->data << " < " << val << ": " << (less ? "T" : "F");
            cout << ")" << (less ? " -> move curr\n" : " -> stop\n");
        }
        if (!less) break;
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
    if (trace) cout << "Insert [" << val << "] between [" << curr->data << "] and "
                    << ::val(newNode->next) << "\n";
    return head;
}

int main() {
    cout << "=========== PROBLEM 4: SortedInsert ===========\n";
    int a4[] = {2, 5, 8};
    Node* l4 = buildList(a4, 3);
    cout << "Before: "; printList(l4);
    l4 = SortedInsert(l4, 6, true);
    cout << "After : "; printList(l4);
    freeList(l4);

    return 0;
}
