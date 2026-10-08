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
    return best; // Return the fastest execution time in milliseconds out of 5 runs
}

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Node insertion logic (insertSorted)
void insertSorted(Node*& head, int val) {
    Node* newNode = new Node(val);
    
    // Handle empty list or inserting at the head
    if (head == nullptr || head->data >= val) {
        newNode->next = head;
        head = newNode;
        return;
    }
    
    // Traverse to find the proper insertion point
    Node* current = head;
    while (current->next != nullptr && current->next->data < val) {
        current = current->next;
    }
    
    // Insert new node after 'current'
    newNode->next = current->next;
    current->next = newNode;
}

// Traversal logic
void printList(Node* head) {
    Node* current = head;
    bool first = true;
    while (current != nullptr) {
        if (!first) cout << " ";
        cout << current->data;
        first = false;
        current = current->next;
    }
    cout << "\n";
}

// Deallocation logic
void clearList(Node*& head) {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

int main() {
    int n;
    if (!(cin >> n)) return 0;
    
    if (n < 0) return 0;

    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    Node* head = nullptr;
    
    auto processList = [&]() {
        // Clear list before each run to ensure proper measurement
        clearList(head);
        for (int i = 0; i < n; ++i) {
            insertSorted(head, arr[i]);
        }
    };
    
    double bestTime = timeIt(processList);
    
    // Print the list resulting from the last run
    printList(head);
    cout << "SortedLinkedList: " << bestTime << " ms\n";
    
    // Final cleanup
    clearList(head);
    delete[] arr;
    
    return 0;
}
