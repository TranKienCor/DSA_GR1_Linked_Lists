#include <iostream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

/*
 * Complexity Explanation:
 * Time Complexity: O(N)
 * Explanation: The fast pointer traverses the list at twice the speed of the slow pointer. 
 * To cover N elements, the loop only runs N/2 times. Dropping the constant factor, the time complexity is linear, O(N).
 * 
 * Auxiliary Space Complexity: O(1)
 * Explanation: The algorithm only uses two additional pointer variables (slow and fast). 
 * It does not allocate any new arrays or auxiliary data structures, thus requiring constant space.
 */
Node* findMiddle(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }
    
    Node* slow = head;
    Node* fast = head;
    
    // When fast reaches nullptr (even length) or its next is nullptr (odd length), 
    // the loop terminates and slow is exactly at the middle.
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

// Helper functions for testing
void appendNode(Node*& head, Node*& tail, int val) {
    Node* newNode = new Node(val);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

void clearList(Node*& head) {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

int main() {
    // 1. Empty list (nullptr)
    Node* head1 = nullptr;
    Node* mid1 = findMiddle(head1);
    cout << "Empty list middle: " << (mid1 ? to_string(mid1->data) : "nullptr") << "\n";
    
    // 2. List with a single element
    Node* head2 = nullptr;
    Node* tail2 = nullptr;
    appendNode(head2, tail2, 1);
    Node* mid2 = findMiddle(head2);
    cout << "Single element list middle: " << (mid2 ? to_string(mid2->data) : "nullptr") << "\n";
    clearList(head2);
    
    // 3. List with an even number of elements (1 -> 2 -> 3 -> 4)
    Node* head3 = nullptr;
    Node* tail3 = nullptr;
    appendNode(head3, tail3, 1);
    appendNode(head3, tail3, 2);
    appendNode(head3, tail3, 3);
    appendNode(head3, tail3, 4);
    Node* mid3 = findMiddle(head3);
    cout << "Even number of elements (1->2->3->4) middle: " << (mid3 ? to_string(mid3->data) : "nullptr") << "\n";
    clearList(head3);
    
    return 0;
}
