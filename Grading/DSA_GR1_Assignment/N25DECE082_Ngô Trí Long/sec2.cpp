#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;

// Define the Node structure for the Sorted Singly Linked List
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

// Insert a node in ascending order (handles edge cases: empty list, insert at head, middle/tail, and duplicates)
void insertSorted(Node*& head, int val) {
    Node* newNode = new Node(val);
    
    // Edge case: empty list or insertion at the head (value is smaller than or equal to head)
    if (head == nullptr || head->data >= val) {
        newNode->next = head;
        head = newNode;
        return;
    }
    
    // Traverse the list to find the correct sorted position
    Node* current = head;
    while (current->next != nullptr && current->next->data < val) {
        current = current->next;
    }
    
    // Insert the new node right after current
    newNode->next = current->next;
    current->next = newNode;
}

// Traverse and print list elements separated by spaces
void printList(Node* head) {
    Node* current = head;
    bool first = true;
    while (current != nullptr) {
        if (!first) {
            cout << " ";
        }
        cout << current->data;
        first = false;
        current = current->next;
    }
    cout << "\n";
}

// Deallocation logic to free memory and prevent memory leaks
void freeList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Provided timeIt template to measure the best runtime across 5 runs
template<typename F>
double timeIt(F f) {
    double best = 1e18;
    for (int i = 0; i < 5; ++i) {
        auto t0 = chrono::high_resolution_clock::now();
        f();
        auto t1 = chrono::high_resolution_clock::now();
        best = min(best, chrono::duration<double, milli>(t1 - t0).count());
    }
    return best; // Return the fastest execution time in milliseconds
}

int main() {
    // Optimize standard I/O operations for performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    // Read the input array of integers
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    Node* head = nullptr;
    
    // Measure the runtime using the timeIt template
    double elapsed_ms = timeIt([&]() {
        Node* tempHead = nullptr;
        for (int i = 0; i < n; ++i) {
            insertSorted(tempHead, arr[i]);
        }
        freeList(tempHead);
        
        // Build the final sorted linked list
        head = nullptr;
        for (int i = 0; i < n; ++i) {
            insertSorted(head, arr[i]);
        }
    });
    
    // Output line 1: sorted list elements in ascending order
    printList(head);
    
    // Output line 2: SortedLinkedList execution time
    cout << "SortedLinkedList: " << elapsed_ms << " ms\n";
    
    // Free allocated memory on the heap
    freeList(head);
    delete[] arr;
    
    return 0;
}
