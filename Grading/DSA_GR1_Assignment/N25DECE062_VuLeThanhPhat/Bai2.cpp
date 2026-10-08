#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

void insertSorted(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (head == nullptr || val < head->data) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* curr = head;
    while (curr->next != nullptr && curr->next->data < val) {
        curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
}

void freeList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void printList(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        cout << curr->data << (curr->next ? " " : "");
        curr = curr->next;
    }
    cout << "\n";
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    Node* head = nullptr;

    double ms = timeIt([&]() {
        freeList(head);
        for (int i = 0; i < n; i++) {
            insertSorted(head, arr[i]);
        }
    });

    printList(head);
    cout << "SortedLinkedList: " << ms << " ms\n";

    freeList(head);
    delete[] arr;

    return 0;
}
