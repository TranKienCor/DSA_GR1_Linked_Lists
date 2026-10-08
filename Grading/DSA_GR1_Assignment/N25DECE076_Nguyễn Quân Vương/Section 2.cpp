#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Distinct function for node insertion in ascending order
void insertSorted(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (head == nullptr || head->data >= val) {
        newNode->next = head;
        head = newNode;
        return;
    }
    
    Node* current = head;
    while (current->next != nullptr && current->next->data < val) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
}

// Traversal logic
void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << (current->next ? " " : "");
        current = current->next;
    }
    cout << "\n";
}

// Deallocation logic
void freeList(Node*& head) {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

// timeIt template provided by prompt
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

    double elapsedTime = timeIt([&]() {
        freeList(head); // Reset list for each run
        for (int i = 0; i < n; i++) {
            insertSorted(head, arr[i]);
        }
    });

    printList(head);
    cout << "SortedLinkedList: " << elapsedTime << " ms\n";

    freeList(head);
    delete[] arr;
    return 0;
}