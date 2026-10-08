#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

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

int searchSingly(SNode* head, int target, long long& traversals) {
    traversals = 0;
    SNode* current = head;
    while (current != nullptr) {
        if (current->data == target) return 1;
        current = current->next;
        traversals++;
    }
    return 0;
}

int searchDoublyHead(DNode* head, int target, long long& traversals) {
    traversals = 0;
    DNode* current = head;
    while (current != nullptr) {
        if (current->data == target) return 1;
        current = current->next;
        traversals++;
    }
    return 0;
}

int searchDoublyBidirectional(DNode* head, DNode* tail, int target, long long& traversals) {
    traversals = 0;
    DNode* forward = head;
    DNode* backward = tail;

    while (forward != nullptr && backward != nullptr) {
        if (forward->data == target || backward->data == target) return 1;
        if (forward == backward || forward->next == backward) break;

        forward = forward->next;
        backward = backward->prev;
        traversals++;
    }
    return 0;
}

int main() {
    int n = 10000;
    mt19937 rng(42);
    uniform_int_distribution<int> dist(1, 100000);

    vector<int> sampleData(n);
    for (int i = 0; i < n; i++) sampleData[i] = dist(rng);

    SNode* sHead = nullptr;
    SNode* sTail = nullptr;
    for (int val : sampleData) {
        SNode* node = new SNode(val);
        if (!sHead) sHead = sTail = node;
        else { sTail->next = node; sTail = node; }
    }

    DNode* dHead = nullptr;
    DNode* dTail = nullptr;
    for (int val : sampleData) {
        DNode* node = new DNode(val);
        if (!dHead) dHead = dTail = node;
        else {
            dTail->next = node;
            node->prev = dTail;
            dTail = node;
        }
    }

    long long totalTraversalsSingly = 0;
    long long totalTraversalsDoublyHead = 0;
    long long totalTraversalsDoublyBidi = 0;
    int numTrials = 1000;

    for (int i = 0; i < numTrials; i++) {
        int target = sampleData[dist(rng) % n];
        long long trav;

        searchSingly(sHead, target, trav);
        totalTraversalsSingly += trav;

        searchDoublyHead(dHead, target, trav);
        totalTraversalsDoublyHead += trav;

        searchDoublyBidirectional(dHead, dTail, target, trav);
        totalTraversalsDoublyBidi += trav;
    }

    double avgSingly = (double)totalTraversalsSingly / numTrials;
    double avgDoublyHead = (double)totalTraversalsDoublyHead / numTrials;
    double avgDoublyBidi = (double)totalTraversalsDoublyBidi / numTrials;

    cout << "========================================================================================\n";
    cout << "n      Structure / Strategy                    Empirical Traversals  Theo Worst Theo Avg Ratio\n";
    cout << "========================================================================================\n";
    cout << left << setw(7) << n << setw(40) << "Singly Linked List (Head Search)" 
         << setw(22) << avgSingly << setw(11) << 10000 << setw(9) << 5000 
         << fixed << setprecision(2) << avgSingly / 5000.0 << "\n";
    
    cout << left << setw(7) << n << setw(40) << "Doubly Linked List (Head Search)" 
         << setw(22) << avgDoublyHead << setw(11) << 10000 << setw(9) << 5000 
         << fixed << setprecision(2) << avgDoublyHead / 5000.0 << "\n";

    cout << left << setw(7) << n << setw(40) << "Doubly Linked List (Bi-directional)" 
         << setw(22) << avgDoublyBidi << setw(11) << 10000 << setw(9) << 2500 
         << fixed << setprecision(2) << avgDoublyBidi / 2500.0 << "\n";
    cout << "========================================================================================\n\n";

    cout << "WRITTEN ANALYSIS:\n";
    cout << "1. Singly Linked List vs Doubly Head Search:\n";
    cout << "   Both are restricted to unidirectional forward traversal starting from head.\n";
    cout << "   Thus, both exhibit average search traversals of ~n/2 (5,000 for n=10,000).\n\n";
    cout << "2. Advantage of Bidirectional Traversal in Doubly Linked List:\n";
    cout << "   By initiating search simultaneously from head (forward) and tail (backward),\n";
    cout << "   the search space is split into two halves meeting in the middle.\n";
    cout << "   The maximum distance any target can be from the closest boundary (head or tail) is n/2.\n";
    cout << "   Assuming uniform random distribution, the expected average distance to reach target\n";
    cout << "   is (n / 2) / 2 = n / 4 (2,500 traversals), effectively halving the average search cost.\n";

    return 0;
}
