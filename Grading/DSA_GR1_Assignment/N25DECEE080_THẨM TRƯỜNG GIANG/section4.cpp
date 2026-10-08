#include <iostream>
#include <vector>
#include <iomanip>
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
    DNode* next;
    DNode* prev;
    DNode(int val) : data(val), next(nullptr), prev(nullptr) {}
};

long long singlyTraversals = 0;
long long doublyHeadTraversals = 0;
long long doublyBiTraversals = 0;

int searchSingly(SNode* head, int index) {
    SNode* current = head;
    for (int i = 0; i < index && current != nullptr; ++i) {
        // Embedded counter incremented at exact location of node traversal
        current = current->next;
        singlyTraversals++;
    }
    return current ? current->data : -1;
}

int searchDoublyHead(DNode* head, int index) {
    DNode* current = head;
    for (int i = 0; i < index && current != nullptr; ++i) {
        // Embedded counter incremented at exact location of node traversal
        current = current->next;
        doublyHeadTraversals++;
    }
    return current ? current->data : -1;
}

int searchDoublyBi(DNode* head, DNode* tail, int n, int index) {
    // Determine closest end based on index
    if (index <= n / 2) {
        DNode* current = head;
        for (int i = 0; i < index && current != nullptr; ++i) {
            // Embedded counter incremented at exact location of node traversal
            current = current->next;
            doublyBiTraversals++;
        }
        return current ? current->data : -1;
    } else {
        DNode* current = tail;
        for (int i = n - 1; i > index && current != nullptr; --i) {
            // Embedded counter incremented at exact location of node traversal
            current = current->prev;
            doublyBiTraversals++;
        }
        return current ? current->data : -1;
    }
}

int main() {
    srand((unsigned)time(0));
    const int n = 10000;
    
    SNode* sHead = nullptr;
    SNode* sTail = nullptr;
    
    DNode* dHead = nullptr;
    DNode* dTail = nullptr;
    
    // Populate lists with 10,000 random integers
    for (int i = 0; i < n; ++i) {
        int val = rand();
        
        SNode* sNew = new SNode(val);
        if (!sHead) {
            sHead = sNew;
            sTail = sNew;
        } else {
            sTail->next = sNew;
            sTail = sNew;
        }
        
        DNode* dNew = new DNode(val);
        if (!dHead) {
            dHead = dNew;
            dTail = dNew;
        } else {
            dTail->next = dNew;
            dNew->prev = dTail;
            dTail = dNew;
        }
    }
    
    // Perform 10,000 uniform random searches
    int numSearches = 10000;
    for (int i = 0; i < numSearches; ++i) {
        int randomIndex = rand() % n;
        searchSingly(sHead, randomIndex);
        searchDoublyHead(dHead, randomIndex);
        searchDoublyBi(dHead, dTail, n, randomIndex);
    }
    
    double sAvg = (double)singlyTraversals / numSearches;
    double dhAvg = (double)doublyHeadTraversals / numSearches;
    double dbAvg = (double)doublyBiTraversals / numSearches;
    
    cout << "--------------------------------------------------------------------------------------------------\n";
    cout << setw(10) << "n" 
         << setw(40) << "Structure / Strategy" 
         << setw(20) << "Empirical Traversals" 
         << setw(20) << "Theoretical Worst" 
         << setw(20) << "Theoretical Avg" 
         << setw(25) << "Ratio (Empirical/Avg)\n";
    cout << "--------------------------------------------------------------------------------------------------\n";
    
    cout << setw(10) << n 
         << setw(40) << "Singly Linked List (Head Search)" 
         << setw(20) << fixed << setprecision(1) << sAvg 
         << setw(20) << "10,000" 
         << setw(20) << "5,000" 
         << setw(25) << setprecision(4) << (sAvg / 5000.0) << "\n";
         
    cout << setw(10) << n 
         << setw(40) << "Doubly Linked List (Head Search)" 
         << setw(20) << fixed << setprecision(1) << dhAvg 
         << setw(20) << "10,000" 
         << setw(20) << "5,000" 
         << setw(25) << setprecision(4) << (dhAvg / 5000.0) << "\n";
         
    cout << setw(10) << n 
         << setw(40) << "Doubly Linked List (Bi-directional)" 
         << setw(20) << fixed << setprecision(1) << dbAvg 
         << setw(20) << "10,000" 
         << setw(20) << "2,500" 
         << setw(25) << setprecision(4) << (dbAvg / 2500.0) << "\n";
    cout << "--------------------------------------------------------------------------------------------------\n";
    
    // Cleanup memory
    SNode* sCurr = sHead;
    while (sCurr) {
        SNode* next = sCurr->next;
        delete sCurr;
        sCurr = next;
    }
    
    DNode* dCurr = dHead;
    while (dCurr) {
        DNode* next = dCurr->next;
        delete dCurr;
        dCurr = next;
    }
    
    return 0;
}
