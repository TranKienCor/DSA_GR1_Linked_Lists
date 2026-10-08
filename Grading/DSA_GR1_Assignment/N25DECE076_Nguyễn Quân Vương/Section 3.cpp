#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

/*
 * Time Complexity: O(N)
 * Explanation: The fast pointer traverses the list at twice the speed of the slow pointer. 
 * To cover N elements, the loop only runs N/2 times. Dropping the constant factor, 
 * the time complexity is linear, O(N).
 *
 * Auxiliary Space Complexity: O(1)
 * Explanation: The algorithm only uses two additional pointer variables (slow and fast). 
 * It does not allocate any new arrays or auxiliary data structures, thus requiring constant space.
 */
Node* findMiddle(Node* head) {
    if (head == nullptr) return nullptr;
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow; // Points to the middle node
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
    // Example test: 1 -> 2 -> 3 -> 4 (Even length returns 3)
    Node *head = nullptr, *tail = nullptr;
    append(head, tail, 1);
    append(head, tail, 2);
    append(head, tail, 3);
    append(head, tail, 4);

    Node* mid = findMiddle(head);
    if (mid) {
        cout << "Middle Node Value: " << mid->data << endl;
    } else {
        cout << "List is empty." << endl;
    }

    freeList(head);
    return 0;
}