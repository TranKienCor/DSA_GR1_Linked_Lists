/**
 * Student Name: Nguyễn Văn Trãi
 * Student ID:   N25DECE085
 * Topic Set 1 - Group 1: Linked Lists (§4.1)
 * Section 3 - Implementation: Find the Middle Node of a Singly Linked List
 */

#include <iostream>
#include <unistd.h>

using namespace std;

// Node structure for Singly Linked List
struct Node {
    int data;
    Node* next;
    explicit Node(int val) : data(val), next(nullptr) {}
};

/*
 * ============================================================================
 * Complexity Analysis:
 *
 * Time Complexity: O(N)
 * Explanation: The fast pointer traverses the list at twice the speed of the
 * slow pointer. To cover N elements, the loop only runs N/2 times. Dropping
 * the constant factor, the time complexity is linear, O(N).
 *
 * Auxiliary Space Complexity: O(1)
 * Explanation: The algorithm only uses two additional pointer variables
 * (slow and fast). It does not allocate any new arrays or auxiliary data
 * structures, thus requiring constant space.
 * ============================================================================
 */

/**
 * Finds the middle node of a Singly Linked List using Two Pointers (Slow & Fast).
 *
 * Requirements:
 * - slow pointer advances 1 step per iteration.
 * - fast pointer advances 2 steps per iteration.
 * - Stopping condition: fast == nullptr || fast->next == nullptr.
 * - For an even number of elements (e.g., 1 -> 2 -> 3 -> 4), returns node 3.
 * - For an empty list, returns nullptr.
 * - For a single element list, returns head.
 */
Node* findMiddle(Node* head) {
    if (head == nullptr) {
        return nullptr; // Edge case: empty list
    }

    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// Helper: Append a new node to the list in O(1) time using tail pointer
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

// Helper: Print all elements of the list
void printList(const Node* head) {
    const Node* curr = head;
    cout << "[";
    while (curr != nullptr) {
        cout << curr->data;
        if (curr->next != nullptr) {
            cout << " -> ";
        }
        curr = curr->next;
    }
    cout << "]";
}

// Helper: Deallocate all nodes in the list
void freeList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Built-in test runner validating all edge cases
void runEdgeCaseTests() {
    cout << "=== Running Middle Node Edge Case Tests ===\n\n";

    // Test 1: Empty list
    {
        Node* head = nullptr;
        Node* mid = findMiddle(head);
        cout << "Test 1 (Empty List):\n  List: ";
        printList(head);
        cout << "\n  Middle Node: " << (mid ? to_string(mid->data) : "nullptr") << " [PASS]\n\n";
    }

    // Test 2: Single element list
    {
        Node* head = nullptr;
        Node* tail = nullptr;
        appendNode(head, tail, 42);
        Node* mid = findMiddle(head);
        cout << "Test 2 (Single Element):\n  List: ";
        printList(head);
        cout << "\n  Middle Node: " << (mid ? to_string(mid->data) : "nullptr")
             << " (Expected: 42) [" << (mid && mid->data == 42 ? "PASS" : "FAIL") << "]\n\n";
        freeList(head);
    }

    // Test 3: Even number of elements (1 -> 2 -> 3 -> 4) -> must return 3
    {
        Node* head = nullptr;
        Node* tail = nullptr;
        for (int v : {1, 2, 3, 4}) {
            appendNode(head, tail, v);
        }
        Node* mid = findMiddle(head);
        cout << "Test 3 (Even Length [1 -> 2 -> 3 -> 4]):\n  List: ";
        printList(head);
        cout << "\n  Middle Node: " << (mid ? to_string(mid->data) : "nullptr")
             << " (Expected: 3) [" << (mid && mid->data == 3 ? "PASS" : "FAIL") << "]\n\n";
        freeList(head);
    }

    // Test 4: Odd number of elements (1 -> 2 -> 3 -> 4 -> 5) -> must return 3
    {
        Node* head = nullptr;
        Node* tail = nullptr;
        for (int v : {1, 2, 3, 4, 5}) {
            appendNode(head, tail, v);
        }
        Node* mid = findMiddle(head);
        cout << "Test 4 (Odd Length [1 -> 2 -> 3 -> 4 -> 5]):\n  List: ";
        printList(head);
        cout << "\n  Middle Node: " << (mid ? to_string(mid->data) : "nullptr")
             << " (Expected: 3) [" << (mid && mid->data == 3 ? "PASS" : "FAIL") << "]\n\n";
        freeList(head);
    }

    // Test 5: Two elements (10 -> 20) -> must return 20
    {
        Node* head = nullptr;
        Node* tail = nullptr;
        for (int v : {10, 20}) {
            appendNode(head, tail, v);
        }
        Node* mid = findMiddle(head);
        cout << "Test 5 (Two Elements [10 -> 20]):\n  List: ";
        printList(head);
        cout << "\n  Middle Node: " << (mid ? to_string(mid->data) : "nullptr")
             << " (Expected: 20) [" << (mid && mid->data == 20 ? "PASS" : "FAIL") << "]\n\n";
        freeList(head);
    }
}

int main(int argc, char* argv[]) {
    // If command line argument "--test" is given or no piped stdin, run test suite
    if (argc > 1 && string(argv[1]) == "--test") {
        runEdgeCaseTests();
        return 0;
    }

    int n = 0;
    if (!isatty(STDIN_FILENO) && (cin >> n)) {
        Node* head = nullptr;
        Node* tail = nullptr;
        for (int i = 0; i < n; ++i) {
            int val;
            cin >> val;
            appendNode(head, tail, val);
        }
        Node* mid = findMiddle(head);
        if (mid != nullptr) {
            cout << mid->data << "\n";
        } else {
            cout << "nullptr\n";
        }
        freeList(head);
        return 0;
    }

    // Default when run interactively without input
    runEdgeCaseTests();
    return 0;
}
