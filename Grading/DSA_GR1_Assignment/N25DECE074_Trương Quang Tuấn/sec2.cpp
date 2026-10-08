#include <iostream>
#include <chrono>
using namespace std;


struct Node {
    int val;
    Node* next;
};


double minDouble(double a, double b) {
    return (a < b) ? a : b;
}


template<typename F>
double timeIt(F f) {
    double best = 1e18;
    for (int i = 0; i < 5; i++) {
        auto t0 = chrono::high_resolution_clock::now();
        f();
        auto t1 = chrono::high_resolution_clock::now();
        best = minDouble(best, chrono::duration<double, milli>(t1 - t0).count());
    }
    return best; 
}


void insertSorted(Node*& head, int v) {
    Node* nut = new Node;
    nut->val = v;

    if (head == nullptr || v <= head->val) {
        nut->next = head;
        head = nut;
        return;
    }

    Node* cur = head;
    while (cur->next != nullptr && cur->next->val < v) {
        cur = cur->next;
    }
    nut->next = cur->next; 
    cur->next = nut;
}

void printList(const Node* head) {
    const Node* cur = head;
    while (cur != nullptr) {
        cout << cur->val;
        if (cur->next != nullptr) cout << ' ';
        cur = cur->next;
    }
    cout << '\n';
}

void freeList(Node*& head) {
    while (head != nullptr) {
        Node* tam = head;
        head = head->next;
        delete tam;
    }
}

void buildList(Node*& head, const int* a, int n) {
    for (int i = 0; i < n; i++) {
        insertSorted(head, a[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n) || n < 0) n = 0;           
    int* a = new int[n > 0 ? n : 1];          
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    Node* head = nullptr;
    double ms = timeIt([&]() {
        freeList(head);
        buildList(head, a, n);
    });
    printList(head);                           
    cout.setf(ios::fixed);                     
    cout.precision(3);
    cout << "SortedLinkedList: " << ms << " ms\n"; 
    freeList(head);
    delete[] a;
    return 0;
}
