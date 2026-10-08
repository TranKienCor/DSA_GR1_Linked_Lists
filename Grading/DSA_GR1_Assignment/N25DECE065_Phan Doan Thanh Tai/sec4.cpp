#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <cstdio>

using namespace std;

struct SNode { int val; SNode* next; };
struct DNode { int val; DNode* prev; DNode* next; };


bool searchSingly(SNode* head, int target, long long& cnt) {
    SNode* cur = head;
    while (cur != nullptr) {
        if (cur->val == target) return true;
        cur = cur->next;
        cnt++;                      
    }
    return false;
}


bool searchDoublyHead(DNode* head, int target, long long& cnt) {
    DNode* cur = head;
    while (cur != nullptr) {
        if (cur->val == target) return true;
        cur = cur->next;
        cnt++;
    }
    return false;
}


bool searchDoublyBi(DNode* head, DNode* tail, int n, int pos, int target, long long& cnt) {
    DNode* cur;
    if (pos < n - 1 - pos) {       
        cur = head;
        while (cur != nullptr) {
            if (cur->val == target) return true;
            cur = cur->next;
            cnt++;
        }
    } else {                        
        cur = tail;
        while (cur != nullptr) {
            if (cur->val == target) return true;
            cur = cur->prev;
            cnt++;
        }
    }
    return false;
}

void freeSingly(SNode* head) {
    while (head != nullptr) {
        SNode* nxt = head->next;
        delete head;
        head = nxt;
    }
}

void freeDoubly(DNode* head) {
    while (head != nullptr) {
        DNode* nxt = head->next;
        delete head;
        head = nxt;
    }
}

int main() {
    const int n = 10000;
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    mt19937 rng(42);
    shuffle(a.begin(), a.end(), rng);       

    SNode* sh = nullptr; SNode* st = nullptr;
    DNode* dh = nullptr; DNode* dt = nullptr;
    for (int i = 0; i < n; i++) {
        SNode* s = new SNode{a[i], nullptr};
        if (!sh) sh = st = s; else { st->next = s; st = s; }
        DNode* d = new DNode{a[i], dt, nullptr};
        if (!dh) dh = dt = d; else { dt->next = d; dt = d; }
    }

    long long cS = 0, cD = 0, cB = 0;
    long long worstS = 0, worstD = 0, worstB = 0;

    for (int i = 0; i < n; i++) {           
        long long before;

        before = cS;
        searchSingly(sh, a[i], cS);
        worstS = max(worstS, cS - before);

        before = cD;
        searchDoublyHead(dh, a[i], cD);
        worstD = max(worstD, cD - before);

        before = cB;
        searchDoublyBi(dh, dt, n, i, a[i], cB);
        worstB = max(worstB, cB - before);
    }

    double avgS = (double)cS / n;
    double avgD = (double)cD / n;
    double avgB = (double)cB / n;

    printf("n = %d\n\n", n);
    printf("%-22s %12s %10s %10s %10s %10s\n",
           "Strategy", "Total", "Avg", "Worst", "TheoAvg", "Ratio");
    printf("%-22s %12lld %10.2f %10lld %10.0f %10.4f\n",
           "Singly (Head)", cS, avgS, worstS, 5000.0, avgS / 5000.0);
    printf("%-22s %12lld %10.2f %10lld %10.0f %10.4f\n",
           "Doubly (Head)", cD, avgD, worstD, 5000.0, avgD / 5000.0);
    printf("%-22s %12lld %10.2f %10lld %10.0f %10.4f\n",
           "Doubly (Bi-directional)", cB, avgB, worstB, 2500.0, avgB / 2500.0);

    freeSingly(sh);
    freeDoubly(dh);
    return 0;
}