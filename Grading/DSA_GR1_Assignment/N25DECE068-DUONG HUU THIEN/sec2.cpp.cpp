#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

template<typename F>
double timeIt(F f) {
    double best = 1e18;
    for (int i = 0; i < 5; i++) {
        auto t0 = chrono::high_resolution_clock::now();
        f();
        auto t1 = chrono::high_resolution_clock::now();
        best = min(best, chrono::duration<double, milli>(t1 - t0).count());
    }
    return best;
}

struct Node {
    int data;
    Node* next;
};

void insertSorted(Node*& head, int value) {
    Node* newNode = new Node{value, nullptr};

    if (head == nullptr || value <= head->data) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* cur = head;
    while (cur->next != nullptr && cur->next->data < value) {
        cur = cur->next;
    }

    newNode->next = cur->next;
    cur->next = newNode;
}

void printList(const Node* head) {
    const Node* cur = head;
    while (cur != nullptr) {
        cout << cur->data;
        if (cur->next != nullptr) cout << ' ';
        cur = cur->next;
    }
    cout << '\n';
}

void destroyList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    int n;
    cin >> n;

    int* a = (n > 0) ? new int[n] : nullptr;
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Benchmark: build and free the sorted linked list, repeated 5 times.
    double ms = timeIt([&]() {
        Node* tempHead = nullptr;
        for (int i = 0; i < n; ++i) {
            insertSorted(tempHead, a[i]);
        }
        destroyList(tempHead);
    });

    // Build once more for the required sorted output.
    Node* head = nullptr;
    for (int i = 0; i < n; ++i) {
        insertSorted(head, a[i]);
    }

    printList(head);
    cout << "SortedLinkedList: " << ms << " ms\n";

    destroyList(head);
    delete[] a;
    return 0;
}