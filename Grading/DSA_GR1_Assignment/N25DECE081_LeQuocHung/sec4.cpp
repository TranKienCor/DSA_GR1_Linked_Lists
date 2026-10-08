#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

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

int searchSingly(SNode* head, int target, long long& traversals) {
    SNode* curr = head;
    int index = 0;
    while (curr != nullptr) {
        if (curr->data == target) return index;
        curr = curr->next;
        traversals++; 
        index++;
    }
    return -1;
}

int searchDoublyHead(DNode* head, int target, long long& traversals) {
    DNode* curr = head;
    int index = 0;
    while (curr != nullptr) {
        if (curr->data == target) return index;
        curr = curr->next;
        traversals++; 
        index++;
    }
    return -1;
}

int searchDoublyBidirectional(DNode* head, DNode* tail, int targetIndex, int listSize, long long& traversals) {
    if (targetIndex < listSize / 2) {
        DNode* curr = head;
        for (int i = 0; i < targetIndex; ++i) {
            curr = curr->next;
            traversals++; 
        }
        return curr->data;
    } else {
        DNode* curr = tail;
        for (int i = listSize - 1; i > targetIndex; --i) {
            curr = curr->prev;
            traversals++; 
        }
        return curr->data;
    }
}

int main() {
    const int n = 10000;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, n - 1);

    std::vector<int> data(n);
    for (int i = 0; i < n; ++i) {
        data[i] = i;
    }
    std::shuffle(data.begin(), data.end(), gen);

    SNode* sHead = new SNode(data[0]);
    SNode* sCurr = sHead;

    DNode* dHead = new DNode(data[0]);
    DNode* dCurr = dHead;

    for (int i = 1; i < n; ++i) {
       
        sCurr->next = new SNode(data[i]);
        sCurr = sCurr->next;

       
        DNode* newNode = new DNode(data[i]);
        dCurr->next = newNode;
        newNode->prev = dCurr;
        dCurr = newNode;
    }
    DNode* dTail = dCurr; 

    long long singlyTraversals = 0;
    long long doublyHeadTraversals = 0;
    long long doublyBiTraversals = 0;

    for (int i = 0; i < n; ++i) {
        int targetPos = dist(gen); 
        int targetVal = data[targetPos];

        searchSingly(sHead, targetVal, singlyTraversals);
        searchDoublyHead(dHead, targetVal, doublyHeadTraversals);
        searchDoublyBidirectional(dHead, dTail, targetPos, n, doublyBiTraversals);
    }

    std::cout << "=== MEASURED EMPIRICAL RESULTS (n = 10,000) ===\n";
    std::cout << "Singly Linked List (Head Search) Avg Traversals: " 
              << (double)singlyTraversals / n << "\n";
    std::cout << "Doubly Linked List (Head Search) Avg Traversals: " 
              << (double)doublyHeadTraversals / n << "\n";
    std::cout << "Doubly Linked List (Bi-directional) Avg Traversals: " 
              << (double)doublyBiTraversals / n << "\n";

    return 0;
}