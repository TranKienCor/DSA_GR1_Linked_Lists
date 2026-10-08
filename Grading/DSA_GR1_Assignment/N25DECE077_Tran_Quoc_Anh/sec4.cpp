#include <iostream>
#include <random>
#include <iomanip>
using namespace std;

struct SNode {
    int data; SNode* next;
    SNode(int x) : data(x), next(nullptr) {}
};
struct DNode {
    int data; DNode* next; DNode* prev;
    DNode(int x) : data(x), next(nullptr), prev(nullptr) {}
};

long long searchSingly(SNode* head, int target) {
    long long count = 0; SNode* current = head;
    while (current != nullptr) {
        ++count;
        if (current->data == target) return count;
        current = current->next;
    }
    return count;
}

long long searchDoublyHead(DNode* head, int target) {
    long long count = 0; DNode* current = head;
    while (current != nullptr) {
        ++count;
        if (current->data == target) return count;
        current = current->next;
    }
    return count;
}

long long searchBidirectional(DNode* head, DNode* tail,
                              int target, int index, int n) {
    long long count = 0;
    if (index <= n / 2) {
        DNode* current = head;
        for (int i = 0; i <= index; ++i) {
            ++count;
            if (current->data == target) return count;
            current = current->next;
        }
    } else {
        DNode* current = tail;
        for (int i = n - 1; i >= index; --i) {
            ++count;
            if (current->data == target) return count;
            current = current->prev;
        }
    }
    return count;
}

int main() {
    const int n = 10000;
    SNode* sHead = nullptr; SNode* sTail = nullptr;
    DNode* dHead = nullptr; DNode* dTail = nullptr;

    mt19937 rng(12345);
    uniform_int_distribution<int> dist(1, 1000000000);
    int* values = new int[n];

    for (int i = 0; i < n; ++i) values[i] = dist(rng);

    for (int i = 0; i < n; ++i) {
        SNode* s = new SNode(values[i]);
        if (sHead == nullptr) sHead = s;
        else sTail->next = s;
        sTail = s;

        DNode* d = new DNode(values[i]);
        if (dHead == nullptr) dHead = d;
        else { dTail->next = d; d->prev = dTail; }
        dTail = d;
    }

    long long singlyTotal = 0, doublyHeadTotal = 0, bidirectionalTotal = 0;
    for (int i = 0; i < n; ++i) {
        singlyTotal += searchSingly(sHead, values[i]);
        doublyHeadTotal += searchDoublyHead(dHead, values[i]);
        bidirectionalTotal += searchBidirectional(dHead, dTail, values[i], i, n);
    }

    cout << fixed << setprecision(2);
    cout << "Singly average: " << (double)singlyTotal / n << '\n';
    cout << "Doubly Head average: " << (double)doublyHeadTotal / n << '\n';
    cout << "Doubly Bidirectional average: " << (double)bidirectionalTotal / n << '\n';

    delete[] values;
    return 0;
}