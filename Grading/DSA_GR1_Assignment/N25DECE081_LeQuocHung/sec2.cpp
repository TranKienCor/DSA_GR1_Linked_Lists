#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdio>

using namespace std;

template<typename F>
double timeIt(F f) {
    double best = 1e18;
    for (int i = 0; i < 5; i++) {
        auto t0 = chrono::high_resolution_clock::now();
        f();
        auto t1 = chrono::high_resolution_clock::now();
        best = min(best, chrono::duration<double, milli>(t1 - t0).count());
    }
    return best;
}

struct Node {
    int val;
    Node* next;
};


void insertSorted(Node*& head, Node*& tail, int v) {
    
    if (head == nullptr) {
        head = tail = new Node{v, nullptr};
        return;
    }

    if (v >= tail->val) {
        tail->next = new Node{v, nullptr};
        tail = tail->next;
        return;
    }
  
    if (v < head->val) {
        head = new Node{v, head};
        return;
    }
   
    Node* cur = head;
    while (cur->next != nullptr && cur->next->val <= v) cur = cur->next;
    cur->next = new Node{v, cur->next};
}

void printList(const Node* head) {
    for (const Node* p = head; p != nullptr; p = p->next) {
        if (p != head) putchar(' ');
        printf("%d", p->val);
    }
    putchar('\n');
}


void freeList(Node*& head, Node*& tail) {
    while (head != nullptr) {
        Node* nxt = head->next;
        delete head;
        head = nxt;
    }
    tail = nullptr;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) n = 0;

    int* arr = new int[n > 0 ? n : 1];
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) arr[i] = 0;
    }

  
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < n; i++) insertSorted(head, tail, arr[i]);
    printList(head);
    freeList(head, tail);

   
    double ms = timeIt([&]() {
        Node* h = nullptr;
        Node* t = nullptr;
        for (int i = 0; i < n; i++) insertSorted(h, t, arr[i]);
        freeList(h, t);
    });

    printf("SortedLinkedList: %.4f ms\n", ms);

    delete[] arr;
    return 0;
}