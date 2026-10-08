#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
};

Node* findMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; 
}

Node* buildFromArray(const int* a, int n) {
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int i = 0; i < n; i++) {
        Node* nut = new Node;
        nut->val = a[i];
        nut->next = nullptr;
        if (head == nullptr) head = nut;
        else tail->next = nut;
        tail = nut;
    }
    return head;
}

void printList(const Node* head) {
    if (head == nullptr) {
        cout << "(rong)";
        return;
    }
    const Node* cur = head;
    while (cur != nullptr) {
        cout << cur->val;
        if (cur->next != nullptr) cout << " -> ";
        cur = cur->next;
    }
}

void freeList(Node*& head) {
    while (head != nullptr) {
        Node* tam = head;
        head = head->next;
        delete tam;
    }
}

void chayTest(const char* ten, const int* a, int n) {
    Node* head = buildFromArray(a, n);
    Node* mid = findMiddle(head);
    cout << ten << ": ";
    printList(head);
    cout << "\n   Nut giua: ";
    if (mid == nullptr) cout << "nullptr";
    else cout << mid->val;
    cout << "\n";
    freeList(head);
}

int main() {
    int a1[1] = {42};
    int a2[2] = {1, 2};
    int a3[3] = {1, 2, 3};
    int a4[4] = {1, 2, 3, 4};     
    int a5[5] = {1, 2, 3, 4, 5};  
    int a6[6] = {10, 20, 30, 40, 50, 60}; 

    chayTest("Test 1 (rong)      ", a1, 0);
    chayTest("Test 2 (1 phan tu) ", a1, 1);
    chayTest("Test 3 (2 phan tu) ", a2, 2);
    chayTest("Test 4 (3 phan tu) ", a3, 3);
    chayTest("Test 5 (4 phan tu) ", a4, 4);
    chayTest("Test 6 (5 phan tu) ", a5, 5);
    chayTest("Test 7 (6 phan tu) ", a6, 6);

    cout << "\nTime Complexity: O(N)\n"
         << "Auxiliary Space Complexity: O(1)\n";
    return 0;
}
