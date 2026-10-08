#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

void insertSorted(Node*& head, int value) {
    Node* newNode = new Node(value);
    if (head == nullptr || value <= head->data) {
        newNode->next = head;
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next != nullptr && current->next->data <= value)
        current = current->next;
    newNode->next = current->next;
    current->next = newNode;
}

void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data;
        if (head->next != nullptr) cout << ' ';
        head = head->next;
    }
    cout << '\n';
}

void deleteList(Node*& head) {
    while (head != nullptr) {
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
    return best;
}

int main() {
    int n;
    cin >> n;
    int* values = (n > 0) ? new int[n] : nullptr;
    for (int i = 0; i < n; i++) cin >> values[i];

    Node* head = nullptr;
    double bestTime = timeIt([&]() {
        deleteList(head);
        for (int i = 0; i < n; i++) insertSorted(head, values[i]);
    });

    printList(head);
    cout << "SortedLinkedList: " << bestTime << " ms\n";
    deleteList(head);
    delete[] values;
    return 0;
}