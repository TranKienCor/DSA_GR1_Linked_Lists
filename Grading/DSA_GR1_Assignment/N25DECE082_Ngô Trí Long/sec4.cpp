#include <iostream>
#include <vector>

using namespace std;

// Singly Linked List Node structure
struct SinglyNode {
    int data;
    SinglyNode* next;
    SinglyNode(int val) : data(val), next(nullptr) {}
};

// Doubly Linked List Node structure
struct DoublyNode {
    int data;
    DoublyNode* prev;
    DoublyNode* next;
    DoublyNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

int main() {
    int n = 10000;
    vector<int> data(n);
    for (int i = 0; i < n; ++i) {
        data[i] = i + 1;
    }

    // Build Singly Linked List
    SinglyNode* sHead = nullptr;
    SinglyNode* sTail = nullptr;
    for (int i = 0; i < n; ++i) {
        SinglyNode* newNode = new SinglyNode(data[i]);
        if (!sHead) {
            sHead = sTail = newNode;
        } else {
            sTail->next = newNode;
            sTail = newNode;
        }
    }

    // Build Doubly Linked List
    DoublyNode* dHead = nullptr;
    DoublyNode* dTail = nullptr;
    for (int i = 0; i < n; ++i) {
        DoublyNode* newNode = new DoublyNode(data[i]);
        if (!dHead) {
            dHead = dTail = newNode;
        } else {
            dTail->next = newNode;
            newNode->prev = dTail;
            dTail = newNode;
        }
    }

    // 1. Singly Linked List (Head Search) Empirical Measurement
    long long singlyHeadCount = 0;
    for (int i = 0; i < n; ++i) {
        int target = data[i];
        SinglyNode* current = sHead;
        while (current != nullptr) {
            singlyHeadCount++; // Counter increment at exact location of node traversal[cite: 12]
            if (current->data == target) break;
            current = current->next;
        }
    }
    double singlyHeadAvg = (double)singlyHeadCount / n;

    // 2. Doubly Linked List (Head Search) Empirical Measurement
    long long doublyHeadCount = 0;
    for (int i = 0; i < n; ++i) {
        int target = data[i];
        DoublyNode* current = dHead;
        while (current != nullptr) {
            doublyHeadCount++; // Counter increment at exact location of node traversal[cite: 12]
            if (current->data == target) break;
            current = current->next;
        }
    }
    double doublyHeadAvg = (double)doublyHeadCount / n;

    // 3. Doubly Linked List (Bi-directional) Empirical Measurement
    long long doublyBiCount = 0;
    for (int i = 0; i < n; ++i) {
        int target = data[i];
        // If element is in the first half, search from head; otherwise, search from tail
        if (i < n / 2) {
            DoublyNode* current = dHead;
            while (current != nullptr) {
                doublyBiCount++; // Counter increment[cite: 12]
                if (current->data == target) break;
                current = current->next;
            }
        } else {
            DoublyNode* current = dTail;
            while (current != nullptr) {
                doublyBiCount++; // Counter increment[cite: 12]
                if (current->data == target) break;
                current = current->prev; // Traversing backwards using prev pointer
            }
        }
    }
    double doublyBiAvg = (double)doublyBiCount / n;

    // Output empirical results
    cout << "Singly Linked List (Head Search) Avg Traversals: " << singlyHeadAvg << "\n";
    cout << "Doubly Linked List (Head Search) Avg Traversals: " << doublyHeadAvg << "\n";
    cout << "Doubly Linked List (Bi-directional) Avg Traversals: " << doublyBiAvg << "\n";

    // Memory clean up (Fixed type name from Sing* to SinglyNode*)
    while (sHead) { SinglyNode* t = sHead; sHead = sHead->next; delete t; }
    while (dHead) { DoublyNode* t = dHead; dHead = dHead->next; delete t; }

    return 0;
}
