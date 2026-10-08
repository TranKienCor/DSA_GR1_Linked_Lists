#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

// --- Node Structures ---
struct SNode {
    int data;
    SNode* next;
    SNode(int val) : data(val), next(nullptr) {}
};

struct DNode {
    int data;
    DNode* next;
    DNode* prev;
    DNode(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// --- Search Functions with Traversal Counters ---

// 1. Singly Linked List: Head Search
int searchSingly(SNode* head, int target) {
    int traversals = 0;
    SNode* curr = head;
    while (curr != nullptr) {
        if (curr->data == target) return traversals;
        curr = curr->next;
        traversals++; // Exact location of traversal
    }
    return traversals;
}

// 2. Doubly Linked List: Head Search
int searchDoublyHead(DNode* head, int target) {
    int traversals = 0;
    DNode* curr = head;
    while (curr != nullptr) {
        if (curr->data == target) return traversals;
        curr = curr->next;
        traversals++; // Exact location of traversal
    }
    return traversals;
}

// 3. Doubly Linked List: Bi-directional Search (Two pointers converging)
int searchDoublyClosestEnd(DNode* head, DNode* tail, int targetIndex, int totalNodes) {
    int traversals = 0;

    if (targetIndex < totalNodes / 2) {
        // Closer to head: start from head and go forward
        DNode* curr = head;
        for (int i = 0; i < targetIndex; ++i) {
            curr = curr->next;
            traversals++;
        }
    } else {
        // Closer to tail: start from tail and go backward
        DNode* curr = tail;
        for (int i = totalNodes - 1; i > targetIndex; --i) {
            curr = curr->prev;
            traversals++;
        }
    }

    return traversals;
}

int main() {
    const int N = 10000;
    const int NUM_QUERIES = 1000;

    // Build unique sample dataset [1..10000]
    vector<int> data(N);
    for (int i = 0; i < N; ++i) data[i] = i + 1;

    // Shuffle dataset
    mt19937 rng(42);
    shuffle(data.begin(), data.end(), rng);

    // Build Singly Linked List
    SNode* sHead = new SNode(data[0]);
    SNode* sCurr = sHead;
    for (int i = 1; i < N; ++i) {
        sCurr->next = new SNode(data[i]);
        sCurr = sCurr->next;
    }

    // Build Doubly Linked List
    DNode* dHead = new DNode(data[0]);
    DNode* dCurr = dHead;
    for (int i = 1; i < N; ++i) {
        DNode* newNode = new DNode(data[i]);
        newNode->prev = dCurr;
        dCurr->next = newNode;
        dCurr = newNode;
    }
    DNode* dTail = dCurr;

    // Generate random lookup queries uniformly distributed over the dataset
    uniform_int_distribution<int> dist(1, N);
    vector<int> queries(NUM_QUERIES);
    for (int i = 0; i < NUM_QUERIES; ++i) {
        queries[i] = dist(rng);
    }

    // Run tests
    long long totalSingly = 0;
    long long totalDoublyHead = 0;
    long long totalDoublyBi = 0;

    for (int target : queries) {
        totalSingly += searchSingly(sHead, target);
        totalDoublyHead += searchDoublyHead(dHead, target);
        totalDoublyBi += searchDoublyClosestEnd(dHead, dTail, target - 1, N);
    }

    cout << "Average Singly (Head): " << (double)totalSingly / NUM_QUERIES << "\n";
    cout << "Average Doubly (Head): " << (double)totalDoublyHead / NUM_QUERIES << "\n";
    cout << "Average Doubly (Bi-dir): " << (double)totalDoublyBi / NUM_QUERIES << "\n";

    return 0;
}