#include <iostream>

using namespace std;

// Define the Node structure for the Singly Linked List
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

/**
 * Finds the middle node of a Singly Linked List using the Fast and Slow Pointers technique.
 * - For an odd number of nodes (e.g., 1 -> 2 -> 3), it returns node 2.
 * - For an even number of nodes (e.g., 1 -> 2 -> 3 -> 4), it returns node 3 (the second middle node).
 */
Node* findMiddle(Node* head) {
    // Handle edge case: empty list or a list with a single element
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    Node* slow = head;
    Node* fast = head;
    
    // Fast pointer moves 2 steps, slow pointer moves 1 step per iteration.
    // When fast reaches the end (nullptr) or the last node (fast->next == nullptr), 
    // the slow pointer will be pointing directly at the middle node.
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;          // Moves 1 step
        fast = fast->next->next;    // Moves 2 steps
    }
    
    return slow;
}

/*
 * ==============================================================================
 * Complexity Explanation (Required):
 * ==============================================================================
 * 
 * Time Complexity: O(N)
 * Explanation: The fast pointer traverses the list at twice the speed of the slow pointer. 
 * To cover N elements, the loop only runs N/2 times. Dropping the constant factor, 
 * the time complexity is linear, O(N).
 * 
 * Auxiliary Space Complexity: O(1)
 * Explanation: The algorithm only uses two additional pointer variables (slow and fast). 
 * It does not allocate any new arrays or auxiliary data structures, thus requiring constant space.
 * ==============================================================================
 */

int main() {
    // Example test case 1: Even number of nodes (1 -> 2 -> 3 -> 4)
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    
    Node* mid = findMiddle(head);
    if (mid != nullptr) {
        cout << "Middle node value: " << mid->data << "\n"; // Expected output: 3
    }
    
    // Clean up memory
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    
    return 0;
}
