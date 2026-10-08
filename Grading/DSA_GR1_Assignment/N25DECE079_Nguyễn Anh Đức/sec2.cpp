#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Node insertion logic maintaining ascending order
void insertSorted(Node*& head, int val) {
    Node* newNode = new Node(val);
    // Edge cases: Empty list or insertion before head
    if (!head || val < head->data) {
        newNode->next = head;
        head = newNode;
        return;
    }
    Node* curr = head;
    while (curr->next && curr->next->data <= val) {
        curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
}

// Traversal logic
void printList(Node* head) {
    Node* curr = head;
    while (curr) {
        cout << curr->data << (curr->next ? " " : "");
        curr = curr->next;
    }
    cout << "\n";
}

// Memory deallocation logic
void freeList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template<typename F>
double timeIt(F f) {
    double best = 1e18;
    for (int i = 0; i < 5; i++) {
        auto t0 = chrono::high_resolution_clock::now();
        f();
        auto t1 = chrono::high_resolution_clock::now();
        best = min(best, chrono::duration<double, milli>(t1 - t0).count());
    }
    return best; // Return fastest runtime in milliseconds
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    Node* head = nullptr; // Dòng 68
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        insertSorted(head, x);
    }

    printList(head);

    double elapsed = timeIt([&]() {
        // timeIt code
    });

    cout << "SortedLinkedList: " << elapsed << " ms\n";

    freeList(head);
    return 0;
}