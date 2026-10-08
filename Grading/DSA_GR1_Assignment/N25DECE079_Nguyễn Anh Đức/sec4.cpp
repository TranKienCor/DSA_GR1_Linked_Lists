#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

// 1. Singly Linked List Node
struct SNode {
    int data;
    SNode* next;
    SNode(int val) : data(val), next(nullptr) {}
};

// 2. Doubly Linked List Node
struct DNode {
    int data;
    DNode* next;
    DNode* prev;
    DNode(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// -----------------------------------------------------------------
// SEARCH FUNCTIONS WITH TRAVERSAL COUNTERS
// -----------------------------------------------------------------

// Singly Linked List Search (Head Search)
int searchSLL(SNode* head, int target, long long& traversals) {
    traversals = 0;
    SNode* curr = head;
    while (curr != nullptr) {
        if (curr->data == target) return 1; // Found
        
        traversals++;
        curr = curr->next;
    }
    return 0; // Not found
}

// Doubly Linked List Search (Head Search - Unidirectional)
int searchDLLHead(DNode* head, int target, long long& traversals) {
    traversals = 0;
    DNode* curr = head;
    while (curr != nullptr) {
        if (curr->data == target) return 1; // Found

        traversals++;
        curr = curr->next;
    }
    return 0; // Not found
}

// Doubly Linked List Search (Bi-directional Search)
int searchDLLBidirectional(DNode* head, DNode* tail, int target, int targetIndex, int totalSize, long long& traversals) {
    traversals = 0;

    if (targetIndex < totalSize / 2) {
        DNode* curr = head;
        while (curr != nullptr) {
            if (curr->data == target) return 1;
            
            traversals++;
            curr = curr->next;
        }
    } 
    else {
        DNode* curr = tail;
        while (curr != nullptr) {
            if (curr->data == target) return 1;
            
            traversals++;
            curr = curr->prev;
        }
    }
    return 0;
}

// -----------------------------------------------------------------
// MAIN BENCHMARK & DATASET SETUP
// -----------------------------------------------------------------
int main() {
    const int N = 10000;
    vector<int> dataset(N);
    
    // Create 1000 random elements
    mt19937 rng(42);
    for (int i = 0; i < N; i++) {
        dataset[i] = rng() % 100000;
    }

    // Build Singly Linked List & Doubly Linked List
    SNode* sHead = nullptr;
    SNode* sTail = nullptr;
    DNode* dHead = nullptr;
    DNode* dTail = nullptr;

    for (int i = 0; i < N; i++) {
        // Build SLL
        SNode* newSNode = new SNode(dataset[i]);
        if (!sHead) sHead = sTail = newSNode;
        else { sTail->next = newSNode; sTail = newSNode; }

        // Build DLL
        DNode* newDNode = new DNode(dataset[i]);
        if (!dHead) dHead = dTail = newDNode;
        else {
            dTail->next = newDNode;
            newDNode->prev = dTail;
            dTail = newDNode;
        }
    }

    // Test case
    long long totalTraversalsSLL = 0;
    long long totalTraversalsDLLHead = 0;
    long long totalTraversalsDLLBi = 0;

    for (int i = 0; i < N; i++) {
        long long countSLL = 0, countDLLHead = 0, countDLLBi = 0;
        int target = dataset[i]; // Tìm phần tử ở chỉ số i

        searchSLL(sHead, target, countSLL);
        searchDLLHead(dHead, target, countDLLHead);
        searchDLLBidirectional(dHead, dTail, target, i, N, countDLLBi);

        totalTraversalsSLL += countSLL;
        totalTraversalsDLLHead += countDLLHead;
        totalTraversalsDLLBi += countDLLBi;
    }

    // Empirical Average Traversals
    double avgSLL = (double)totalTraversalsSLL / N;
    double avgDLLHead = (double)totalTraversalsDLLHead / N;
    double avgDLLBi = (double)totalTraversalsDLLBi / N;

    cout << "=== SECTION 4 ANALYSIS RESULTS (N = " << N << ") ===\n";
    cout << "1. SLL (Head Search)         - Empirical Avg Traversals: " << avgSLL << "\n";
    cout << "2. DLL (Head Search)         - Empirical Avg Traversals: " << avgDLLHead << "\n";
    cout << "3. DLL (Bi-directional Search)- Empirical Avg Traversals: " << avgDLLBi << "\n";

    return 0;
}