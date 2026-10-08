#include <iostream>
#include <chrono>
#include <algorithm>
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
    explicit Node(int v) : val(v), next(nullptr) {}
};

struct SortedList {
    Node* head = nullptr;
    Node* tail = nullptr;
};

void insertSorted(SortedList& L, int x) {
    Node* node = new Node(x);
    if (L.head == nullptr) {            
        L.head = L.tail = node;
    } else if (x < L.head->val) {       
        node->next = L.head;
        L.head = node;
    } else if (x >= L.tail->val) {      
        L.tail->next = node;
        L.tail = node;
    } else {                           
        Node* cur = L.head;
        while (cur->next != nullptr && cur->next->val <= x) cur = cur->next;
        node->next = cur->next;
        cur->next = node;
    }
}

void printList(const SortedList& L) {
    for (const Node* p = L.head; p != nullptr; p = p->next)
        printf("%d%c", p->val, p->next ? ' ' : '\n');
    if (L.head == nullptr) printf("\n");
}

void freeList(SortedList& L) {
    Node* p = L.head;
    while (p != nullptr) {
        Node* nxt = p->next;
        delete p;
        p = nxt;
    }
    L.head = L.tail = nullptr;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) n = 0;
    int* a = new int[n > 0 ? n : 1];
    for (int i = 0; i < n; i++)
        if (scanf("%d", &a[i]) != 1) a[i] = 0;

    SortedList L;
    double ms = timeIt([&]() {
        freeList(L);
        for (int i = 0; i < n; i++) insertSorted(L, a[i]);
    });

    printList(L);
    printf("SortedLinkedList: %.3f ms\n", ms);

    freeList(L);
    delete[] a;
    return 0;
}