#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    explicit Node(int value) : data(value), next(nullptr) {}
};

Node* findMiddle(Node* head) {
    if (head == nullptr) return nullptr;

    Node* slow = head;
    Node* fast = head;

    // slow moves 1 node; fast moves 2 nodes.
    // For an even-length list, this returns the SECOND middle node
    // (e.g. 1 -> 2 -> 3 -> 4 returns node 3), as required.
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

void append(Node*& head, int value) {
    Node* node = new Node(value);
    if (head == nullptr) {
        head = node;
        return;
    }
    Node* current = head;
    while (current->next != nullptr) current = current->next;
    current->next = node;
}

void deleteList(Node*& head) {
    while (head != nullptr) {
        Node* old = head;
        head = head->next;
        delete old;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input: n followed by n integers.
    int n;
    if (!(cin >> n) || n < 0 || n > 1000000) {
        cerr << "Invalid n. Expected 0 <= n <= 1000000.\n";
        return 1;
    }

    Node* head = nullptr;
    for (int i = 0; i < n; ++i) {
        int value;
        if (!(cin >> value)) {
            cerr << "Not enough input integers.\n";
            deleteList(head);
            return 1;
        }
        append(head, value);
    }

    Node* middle = findMiddle(head);
    if (middle == nullptr) {
        cout << "List is empty; no middle node.\n";
    } else {
        cout << "Middle node: " << middle->data << '\n';
    }

    // Time: O(N), because fast advances two nodes per loop and the
    // loop executes about N/2 times; asymptotically this is O(N).
    // Auxiliary space: O(1), because only slow and fast pointers are used.
    deleteList(head);
    return 0;
}
