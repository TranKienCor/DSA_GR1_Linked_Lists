/**
 * Student Name: Nguyễn Văn Trãi
 * Student ID:   N25DECE085
 * Topic Set 1 - Group 1: Linked Lists (§4.1)
 * Section 4 - Analysis: Singly vs. Doubly Linked List Traversal Counter
 */

#include <iostream>
#include <iomanip>
#include <random>
#include <unistd.h>

using namespace std;

// Singly Linked List Node
struct SNode {
    int data;
    SNode* next;
    explicit SNode(int v) : data(v), next(nullptr) {}
};

// Doubly Linked List Node
struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    explicit DNode(int v) : data(v), prev(nullptr), next(nullptr) {}
};

/**
 * Linear search on Singly Linked List from Head.
 * Counter is incremented at the exact location of node traversal.
 */
bool searchSingly(SNode* head, int target, long long& counter) {
    SNode* current = head;
    while (current != nullptr) {
        if (current->data == target) {
            return true;
        }
        counter++; // exact location of node traversal (current = current->next)
        current = current->next;
    }
    return false;
}

/**
 * Linear search on Doubly Linked List from Head.
 * Counter is incremented at the exact location of node traversal.
 */
bool searchDoublyHead(DNode* head, int target, long long& counter) {
    DNode* current = head;
    while (current != nullptr) {
        if (current->data == target) {
            return true;
        }
        counter++; // exact location of node traversal (current = current->next)
        current = current->next;
    }
    return false;
}

/**
 * Bi-directional search on Doubly Linked List (searching from closest end).
 * Counter is incremented at the exact location of node traversal.
 */
bool searchDoublyBidirectional(DNode* head, DNode* tail, int target, int targetIndex, int n, long long& counter) {
    if (targetIndex < n / 2) {
        // Target is closer to head -> traverse forward
        DNode* current = head;
        while (current != nullptr) {
            if (current->data == target) {
                return true;
            }
            counter++; // exact location of node traversal (current = current->next)
            current = current->next;
        }
    } else {
        // Target is closer to tail -> traverse backward
        DNode* current = tail;
        while (current != nullptr) {
            if (current->data == target) {
                return true;
            }
            counter++; // exact location of node traversal (current = current->prev)
            current = current->prev;
        }
    }
    return false;
}

// Memory deallocation helpers
void freeSingly(SNode*& head) {
    while (head != nullptr) {
        SNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void freeDoubly(DNode*& head) {
    while (head != nullptr) {
        DNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 10000;
    int inputN = 0;
    int* dataset = nullptr;
    // If input is piped or redirected from file, read dataset from stdin
    if (!isatty(STDIN_FILENO) && (cin >> inputN) && inputN > 0) {
        n = inputN;
        dataset = new int[n];
        for (int i = 0; i < n; ++i) {
            cin >> dataset[i];
        }
    } else {
        // Generate n = 10,000 pseudo-random integers with a fixed seed for reproducibility
        dataset = new int[n];
        mt19937 rng(42);
        uniform_int_distribution<int> dist(1, 1000000);
        for (int i = 0; i < n; ++i) {
            dataset[i] = dist(rng);
        }
    }

    // Build Singly Linked List
    SNode* sHead = nullptr;
    SNode* sTail = nullptr;
    for (int i = 0; i < n; ++i) {
        SNode* newNode = new SNode(dataset[i]);
        if (!sHead) {
            sHead = newNode;
            sTail = newNode;
        } else {
            sTail->next = newNode;
            sTail = newNode;
        }
    }

    // Build Doubly Linked List
    DNode* dHead = nullptr;
    DNode* dTail = nullptr;
    for (int i = 0; i < n; ++i) {
        DNode* newNode = new DNode(dataset[i]);
        if (!dHead) {
            dHead = newNode;
            dTail = newNode;
        } else {
            newNode->prev = dTail;
            dTail->next = newNode;
            dTail = newNode;
        }
    }

    // 1. Singly Linked List (Head Search)
    long long totalTraversalsSingly = 0;
    for (int i = 0; i < n; ++i) {
        long long cnt = 0;
        searchSingly(sHead, dataset[i], cnt);
        totalTraversalsSingly += cnt;
    }
    double avgSingly = static_cast<double>(totalTraversalsSingly) / n;

    // 2. Doubly Linked List (Head Search)
    long long totalTraversalsDoublyHead = 0;
    for (int i = 0; i < n; ++i) {
        long long cnt = 0;
        searchDoublyHead(dHead, dataset[i], cnt);
        totalTraversalsDoublyHead += cnt;
    }
    double avgDoublyHead = static_cast<double>(totalTraversalsDoublyHead) / n;

    // 3. Doubly Linked List (Bi-directional Search from Closest End)
    long long totalTraversalsDoublyBi = 0;
    for (int i = 0; i < n; ++i) {
        long long cnt = 0;
        searchDoublyBidirectional(dHead, dTail, dataset[i], i, n, cnt);
        totalTraversalsDoublyBi += cnt;
    }
    double avgDoublyBi = static_cast<double>(totalTraversalsDoublyBi) / n;

    // Theoretical values
    double theoWorst = 10000.0;
    double theoAvgHead = 5000.0;
    double theoAvgBi = 2500.0;

    cout << "\n=========================================================================================\n";
    cout << "  Student: Nguyễn Văn Trãi (N25DECE085) - Section 4: Traversal Counter Comparison Table \n";
    cout << "=========================================================================================\n";
    cout << left << setw(8) << "n"
         << setw(38) << "Structure / Strategy"
         << setw(22) << "Empirical Traversals"
         << setw(19) << "Theoretical Worst"
         << setw(17) << "Theoretical Avg"
         << setw(15) << "Ratio (Emp/Avg)" << "\n";
    cout << "-----------------------------------------------------------------------------------------\n";

    cout << left << setw(8) << n
         << setw(38) << "Singly Linked List (Head Search)"
         << setw(22) << fixed << setprecision(1) << avgSingly
         << setw(19) << static_cast<int>(theoWorst)
         << setw(17) << static_cast<int>(theoAvgHead)
         << setw(15) << fixed << setprecision(4) << (avgSingly / theoAvgHead) << "\n";

    cout << left << setw(8) << n
         << setw(38) << "Doubly Linked List (Head Search)"
         << setw(22) << fixed << setprecision(1) << avgDoublyHead
         << setw(19) << static_cast<int>(theoWorst)
         << setw(17) << static_cast<int>(theoAvgHead)
         << setw(15) << fixed << setprecision(4) << (avgDoublyHead / theoAvgHead) << "\n";

    cout << left << setw(8) << n
         << setw(38) << "Doubly Linked List (Bi-directional)"
         << setw(22) << fixed << setprecision(1) << avgDoublyBi
         << setw(19) << static_cast<int>(theoWorst)
         << setw(17) << static_cast<int>(theoAvgBi)
         << setw(15) << fixed << setprecision(4) << (avgDoublyBi / theoAvgBi) << "\n";

    cout << "=========================================================================================\n\n";

    cout << "Written Analysis:\n"
         << "-----------------\n"
         << "In a Singly Linked List, nodes only store forward pointers (next). Therefore, all lookups\n"
         << "must initiate from the head node and proceed unidirectionally. For a uniform target distribution\n"
         << "across n elements, the target index i (0 <= i < n) is located at distance i from head. The\n"
         << "expected number of node traversals is the arithmetic mean: (1/n) * sum_{i=0}^{n-1} i = (n - 1) / 2\n"
         << "which approximates to n / 2 (5,000 for n = 10,000).\n\n"
         << "In a Doubly Linked List, each node maintains both forward (next) and backward (prev) pointers,\n"
         << "allowing traversal from either the head or tail. When the index or target proximity to either\n"
         << "boundary is known (or estimated), the search can dynamically initiate from the closer end:\n"
         << "- For indices i < n / 2: search forward from head, taking i traversals.\n"
         << "- For indices i >= n / 2: search backward from tail, taking (n - 1 - i) traversals.\n\n"
         << "The maximum distance to the closest boundary is halved from n - 1 to (n / 2) - 1. The average\n"
         << "number of traversals becomes:\n"
         << "  (1/n) * [ sum_{i=0}^{n/2-1} i + sum_{i=n/2}^{n-1} (n - 1 - i) ]\n"
         << "  = (2/n) * sum_{k=0}^{n/2-1} k = (2/n) * [ (n/2 - 1) * (n/2) / 2 ] ≈ n / 4 (2,500 for n = 10,000).\n\n"
         << "Thus, bidirectional search cuts the average traversal distance strictly in half (from n/2 to n/4),\n"
         << "achieving a 2x theoretical and empirical speedup.\n";

    // Clean up
    freeSingly(sHead);
    freeDoubly(dHead);
    delete[] dataset;

    return 0;
}
