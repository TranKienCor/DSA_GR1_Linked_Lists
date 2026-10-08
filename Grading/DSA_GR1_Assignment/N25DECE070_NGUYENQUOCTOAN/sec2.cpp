#include <iostream>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Node {
    int data;
    Node* next;

    explicit Node(int value) : data(value), next(nullptr) {}
};

void insertSorted(Node*& head, int value) {
    Node* newNode = new Node(value);

    if (head == nullptr || value <= head->data) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->data <= value) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void printList(const Node* head) {
    const Node* current = head;
    bool first = true;

    while (current != nullptr) {
        if (!first) {
            cout << ' ';
        }
        cout << current->data;
        first = false;
        current = current->next;
    }
    cout << '\n';
}

void clearList(Node*& head) {
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n) || n < 0 || n > 1000000) {
        return 0;
    }

    int* values = (n > 0) ? new int[n] : nullptr;
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    double bestMs = timeIt([&]() {
        Node* testHead = nullptr;
        for (int i = 0; i < n; ++i) {
            insertSorted(testHead, values[i]);
        }
        clearList(testHead);
    });

    Node* head = nullptr;
    for (int i = 0; i < n; ++i) {
        insertSorted(head, values[i]);
    }

    printList(head);
    cout << fixed << setprecision(3)
         << "SortedLinkedList: " << bestMs << " ms\n";

    clearList(head);
    delete[] values;

    return 0;
}
