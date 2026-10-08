/**
 * Student Name: Nguyễn Văn Trãi
 * Student ID:   N25DECE085
 * Topic Set 1 - Group 1: Linked Lists (§4.1)
 * Section 2 - Implementation: Sorted Singly Linked List
 */

#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;

// Template provided by assignment to measure best runtime over 5 runs
template<typename F>
double timeIt(F f) {
    double best = 1e18;
    for (int i = 0; i < 5; i++) {
        auto t0 = chrono::high_resolution_clock::now();
        f();
        auto t1 = chrono::high_resolution_clock::now();
        best = min(best, chrono::duration<double, milli>(t1 - t0).count());
    }
    return best; // Return the fastest execution time in milliseconds out of 5 runs
}

// Node structure for Singly Linked List
struct Node {
    int data;
    Node* next;
    explicit Node(int val) : data(val), next(nullptr) {}
};

/**
 * Inserts a value into the sorted singly linked list maintaining ascending order.
 * Handles edge cases:
 * - Empty list: head is nullptr, new node becomes the head.
 * - Inserting at head: new value is smaller than head->data.
 * - Inserting in middle / tail: traverses until correct position is found.
 * - Duplicates: places equal values consecutively in stable order.
 */
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

/**
 * Traverses the list and prints values separated by a space.
 */
void printList(const Node* head) {
    const Node* curr = head;
    bool first = true;
    while (curr != nullptr) {
        if (!first) {
            cout << ' ';
        }
        cout << curr->data;
        first = false;
        curr = curr->next;
    }
    cout << '\n';
}

/**
 * Deallocates all nodes in the list to prevent memory leaks.
 */
void freeList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 0;
    if (!(cin >> n)) {
        return 0;
    }

    // Allocate raw array buffer for input (no STL containers)
    int* arr = nullptr;
    if (n > 0) {
        arr = new int[n];
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
    }

    // Maintain heads for each of the 5 benchmark runs so deallocation
    // does not taint execution time inside the measurement block.
    Node* runHeads[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    int currentRun = 0;

    double bestTime = timeIt([&]() {
        for (int i = 0; i < n; ++i) {
            insertSorted(runHeads[currentRun], arr[i]);
        }
        currentRun++;
    });

    // Output Line 1: sorted elements in ascending order
    printList(runHeads[0]);

    // Output Line 2: benchmark execution time
    cout << "SortedLinkedList: " << bestTime << " ms\n";

    // Clean up memory
    for (int i = 0; i < 5; ++i) {
        freeList(runHeads[i]);
    }
    delete[] arr;

    return 0;
}
