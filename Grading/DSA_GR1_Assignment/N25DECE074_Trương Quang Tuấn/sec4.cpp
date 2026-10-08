#include <iostream>
using namespace std;

struct SNode {            
    int val;
    SNode* next;
};

struct DNode {            
    int val;
    DNode* prev;
    DNode* next;
};

unsigned int seed = 20240901u;
unsigned int nextRand() {
    seed = seed * 1664525u + 1013904223u;
    return seed >> 8;     
}

void taoDuLieu(int* a, int n) {
    for (int i = 0; i < n; i++) a[i] = i + 1;
    for (int i = n - 1; i > 0; i--) {
        int j = (int)(nextRand() % (unsigned int)(i + 1));
        int tam = a[i];
        a[i] = a[j];
        a[j] = tam;
    }
}

SNode* buildSingly(const int* a, int n) {
    SNode* head = nullptr;
    SNode* tail = nullptr;
    for (int i = 0; i < n; i++) {
        SNode* nut = new SNode;
        nut->val = a[i];
        nut->next = nullptr;
        if (head == nullptr) head = nut;
        else tail->next = nut;
        tail = nut;
    }
    return head;
}

void buildDoubly(const int* a, int n, DNode*& head, DNode*& tail) {
    head = nullptr;
    tail = nullptr;
    for (int i = 0; i < n; i++) {
        DNode* nut = new DNode;
        nut->val = a[i];
        nut->next = nullptr;
        nut->prev = tail;
        if (head == nullptr) head = nut;
        else tail->next = nut;
        tail = nut;
    }
}

void freeSingly(SNode*& head) {
    while (head != nullptr) {
        SNode* tam = head;
        head = head->next;
        delete tam;
    }
}

void freeDoubly(DNode*& head) {
    while (head != nullptr) {
        DNode* tam = head;
        head = head->next;
        delete tam;
    }
}

SNode* searchSingly(SNode* head, int target, long long& counter) {
    SNode* cur = head;
    while (cur != nullptr && cur->val != target) {
        cur = cur->next;
        counter++;              
    }
    return cur;
}

DNode* searchDoublyHead(DNode* head, int target, long long& counter) {
    DNode* cur = head;
    while (cur != nullptr && cur->val != target) {
        cur = cur->next;
        counter++;              
    }
    return cur;
}

DNode* searchDoublyClosest(DNode* head, DNode* tail, int n, int hintIndex, int target, long long& counter) {
    if (hintIndex < n - 1 - hintIndex) {       
        DNode* cur = head;
        while (cur != nullptr && cur->val != target) {
            cur = cur->next;
            counter++;                        
        }
        return cur;
    } else {                                   
        DNode* cur = tail;
        while (cur != nullptr && cur->val != target) {
            cur = cur->prev;
            counter++;                         
        }
        return cur;
    }
}


void inDong(const char* ten, long long tongTraversal, int Q,
            int lyThuyetWorst, double lyThuyetAvg) {
    double tb = (double)tongTraversal / (double)Q; 
    cout << ten << " | " << tb << " | " << lyThuyetWorst
         << " | " << lyThuyetAvg << " | " << (tb / lyThuyetAvg) << "\n";
}

int main() {
    const int n = 10000;
    const int Q = 10000;

    int* a = new int[n];
    int* viTri = new int[Q];  
    taoDuLieu(a, n);
    for (int q = 0; q < Q; q++) viTri[q] = (int)(nextRand() % (unsigned int)n);

    SNode* sHead = buildSingly(a, n);
    DNode* dHead = nullptr;
    DNode* dTail = nullptr;
    buildDoubly(a, n, dHead, dTail);

    long long cntSingly = 0, cntDoublyHead = 0, cntDoublyBi = 0;
    for (int q = 0; q < Q; q++) {
        int idx = viTri[q];
        int target = a[idx];
        searchSingly(sHead, target, cntSingly);
        searchDoublyHead(dHead, target, cntDoublyHead);
        searchDoublyClosest(dHead, dTail, n, idx, target, cntDoublyBi);
    }

    cout << "n = " << n << ", so truy van Q = " << Q << "\n";
    cout << "Tong traversal: singly=" << cntSingly
         << ", doubly(head)=" << cntDoublyHead
         << ", doubly(bi)=" << cntDoublyBi << "\n\n";
    cout << "Structure / Strategy | Empirical (TB/truy van) | Theo. Worst | Theo. Avg | Ratio (Emp/Avg)\n";
    inDong("Singly (Head Search)       ", cntSingly,     Q, 10000, 5000);
    inDong("Doubly (Head Search)       ", cntDoublyHead, Q, 10000, 5000);
    inDong("Doubly (Bi-directional)    ", cntDoublyBi,   Q, 10000, 2500);

    freeSingly(sHead);
    freeDoubly(dHead);
    delete[] a;
    delete[] viTri;
    return 0;
}

