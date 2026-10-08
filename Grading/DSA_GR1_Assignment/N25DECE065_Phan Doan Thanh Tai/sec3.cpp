#include <iostream>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

Node* findMiddle(Node* head) {
    if (head == nullptr) return nullptr;      

    Node* slow = head;
    Node* fast = head;

    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;           
        fast = fast->next->next;     
    }
    return slow;                     
}


Node* buildList(const int* a, int n) {
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < n; i++) {
        Node* node = new Node(a[i]);
        if (head == nullptr) head = tail = node;
        else { tail->next = node; tail = node; }
    }
    return head;
}

void freeList(Node* head) {
    while (head != nullptr) {
        Node* nxt = head->next;
        delete head;
        head = nxt;
    }
}

void test(const int* a, int n) {
    Node* head = buildList(a, n);
    Node* mid = findMiddle(head);
    cout << "N = " << n << " -> ";
    if (mid == nullptr) cout << "nullptr\n";
    else cout << mid->val << "\n";
    freeList(head);
}

int main() {
    int e1[] = {1};
    int e2[] = {1, 2, 3, 4};
    int e3[] = {1, 2, 3, 4, 5};

    test(nullptr, 0); 
    test(e1, 1);        
    test(e2, 4);        
    test(e3, 5);        
    return 0;
}