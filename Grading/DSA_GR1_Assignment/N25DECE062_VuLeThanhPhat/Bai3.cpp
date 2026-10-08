#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
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

void append(Node*& head, Node*& tail, int val) {
    Node* newNode = new Node(val);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void freeList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* head1 = nullptr;
    Node* mid1 = findMiddle(head1);
    cout << "Empty List Middle: " << (mid1 ? to_string(mid1->data) : "nullptr") << "\n";

    Node *head2 = nullptr, *tail2 = nullptr;
    append(head2, tail2, 10);
    Node* mid2 = findMiddle(head2);
    cout << "Single Element (10) Middle: " << mid2->data << "\n";
    freeList(head2);

    Node *head3 = nullptr, *tail3 = nullptr;
    for (int i = 1; i <= 4; i++) append(head3, tail3, i);
    Node* mid3 = findMiddle(head3);
    cout << "Even Elements (1->2->3->4) Middle: " << mid3->data << "\n";
    freeList(head3);

    Node *head4 = nullptr, *tail4 = nullptr;
    for (int i = 1; i <= 5; i++) append(head4, tail4, i);
    Node* mid4 = findMiddle(head4);
    cout << "Odd Elements (1->2->3->4->5) Middle: " << mid4->data << "\n";
    freeList(head4);

    return 0;
}
