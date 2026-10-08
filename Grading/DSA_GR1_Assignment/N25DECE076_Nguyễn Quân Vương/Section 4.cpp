#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct SNode {
    int data;
    SNode* next;
    SNode(int val) : data(val), next(nullptr) {}
};

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// Singly Linked List Search (Head Search)
int searchSinglyHead(SNode* head, int target, long long& traversals) {
    traversals = 0;
    SNode* curr = head;
    while (curr != nullptr) {
        if (curr->data == target) return curr->data;
        curr = curr->next; // Counter placed at exact traversal step
        traversals++;
    }
    return -1;
}

// Doubly Linked List Search (Head Search)
int searchDoublyHead(DNode* head, int target, long long& traversals) {
    traversals = 0;
    DNode* curr = head;
    while (curr != nullptr) {
        if (curr->data == target) return curr->data;
        curr = curr->next; // Counter placed at exact traversal step
        traversals++;
    }
    return -1;
}

// Doubly Linked List Search (Bi-directional Search)
int searchDoublyBiDirectional(DNode* head, DNode* tail, int target, int targetIndex, int n, long long& traversals) {
    traversals = 0;
    if (targetIndex < n / 2) { // Search from Head
        DNode* curr = head;
        while (curr != nullptr) {
            if (curr->data == target) return curr->data;
            curr = curr->next;
            traversals++;
        }
    } else { // Search from Tail
        DNode* curr = tail;
        while (curr != nullptr) {
            if (curr->data == target) return curr->data;
            curr = curr->prev;
            traversals++;
        }
    }
    return -1;
}

int main() {
    srand(time(0));
    int n = 10000;
    
    // Generate dataset
    vector<int> data(n);
    for (int i = 0; i < n; i++) data[i] = rand();

    // Build Singly List
    SNode* sHead = new SNode(data[0]);
    SNode* sCurr = sHead;
    for (int i = 1; i < n; i++) {
        sCurr->next = new SNode(data[i]);
        sCurr = sCurr->next;
    }

    // Build Doubly List
    DNode* dHead = new DNode(data[0]);
    DNode* dCurr = dHead;
    for (int i = 1; i < n; i++) {
        DNode* newNode = new DNode(data[i]);
        dCurr->next = newNode;
        newNode->prev = dCurr;
        dCurr = newNode;
    }
    DNode* dTail = dCurr;

    // Perform lookups on sample dataset to collect empirical traversals
    long long totalSinglyHead = 0;
    long long totalDoublyHead = 0;
    long long totalDoublyBi = 0;
    int numTests = 1000;

    for (int t = 0; t < numTests; t++) {
        int idx = rand() % n;
        int target = data[idx];
        
        long long trav = 0;
        searchSinglyHead(sHead, target, trav);
        totalSinglyHead += trav;

        searchDoublyHead(dHead, target, trav);
        totalDoublyHead += trav;

        searchDoublyBiDirectional(dHead, dTail, target, idx, n, trav);
        totalDoublyBi += trav;
    }

    cout << "=== EMPIRICAL RESULTS (Average Traversals over " << numTests << " searches) ===" << endl;
    cout << "Singly Linked List (Head Search): " << totalSinglyHead / numTests << endl;
    cout << "Doubly Linked List (Head Search): " << totalDoublyHead / numTests << endl;
    cout << "Doubly Linked List (Bi-directional): " << totalDoublyBi / numTests << endl;

    return 0;
}