#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* findMiddle(Node* head) {
    if (head == nullptr) return nullptr;

    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;          // 1 step
        fast = fast->next->next;    // 2 steps
    }

    return slow; // For 1->2->3->4, returns node 3.
}

int main() {
    // Example list: 1 -> 2 -> 3 -> 4
    Node* n1 = new Node{1, nullptr};
    Node* n2 = new Node{2, nullptr};
    Node* n3 = new Node{3, nullptr};
    Node* n4 = new Node{4, nullptr};
    n1->next = n2; n2->next = n3; n3->next = n4;

    Node* middle = findMiddle(n1);

    if (middle != nullptr)
        cout << "Middle: " << middle->data << '\n';
    else
        cout << "Middle: empty list\n";

    while (n1 != nullptr) {
        Node* temp = n1;
        n1 = n1->next;
        delete temp;
    }
    return 0;
}