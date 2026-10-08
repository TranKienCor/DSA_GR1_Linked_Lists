#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int x) : data(x), next(nullptr), prev(nullptr) {}
};

// Singly Linked List Search
int searchSingly(Node* head, int target, int& counter) {
    Node* current = head;

    while (current != nullptr) {
        if (current->data == target)
            return counter;

        current = current->next;
        counter++;
    }

    return counter;
}

// Doubly Linked List Search from Head
int searchDoublyHead(Node* head, int target, int& counter) {
    Node* current = head;

    while (current != nullptr) {
        if (current->data == target)
            return counter;

        current = current->next;
        counter++;
    }

    return counter;
}

// Doubly Linked List Bidirectional Search
int searchDoublyBidirectional(
    Node* head,
    Node* tail,
    int target,
    int& counter,
    int n
) {
    Node* left = head;
    Node* right = tail;

    for (int i = 0; i <= n / 2; i++) {

        if (left != nullptr) {
            counter++;
            if (left->data == target)
                return counter;

            left = left->next;
        }

        if (right != nullptr) {
            counter++;
            if (right->data == target)
                return counter;

            right = right->prev;
        }
    }

    return counter;
}

int main() {
    const int n = 10000;

    // Example list
    Node* head = nullptr;
    Node* tail = nullptr;

    // Create 10,000 nodes
    for (int i = 0; i < n; i++) {
        Node* newNode = new Node(i);

        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    int target = 9999;

    int counterSingly = 0;
    int counterDoublyHead = 0;
    int counterBidirectional = 0;

    searchSingly(head, target, counterSingly);

    searchDoublyHead(head, target, counterDoublyHead);

    searchDoublyBidirectional(
        head,
        tail,
        target,
        counterBidirectional,
        n
    );

    cout << "Singly Linked List: "
         << counterSingly << " traversals\n";

    cout << "Doubly Linked List (Head): "
         << counterDoublyHead << " traversals\n";

    cout << "Doubly Linked List (Bi-directional): "
         << counterBidirectional << " traversals\n";

    // Free memory
    Node* current = head;

    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    return 0;
}