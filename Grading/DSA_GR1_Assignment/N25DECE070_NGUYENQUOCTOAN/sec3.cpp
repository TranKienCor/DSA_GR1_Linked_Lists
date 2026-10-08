#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;

    explicit Node(int value) : data(value), next(nullptr) {}
};

void append(Node*& head, Node*& tail, int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = tail = newNode;
        return;
    }

    tail->next = newNode;
    tail = newNode;
}

Node* findMiddle(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }

    Node* slow = head;
    Node* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

void clearList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n) || n < 0) {
        return 0;
    }

    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;
        append(head, tail, value);
    }

    Node* middle = findMiddle(head);

    if (middle == nullptr) {
        cout << "Empty list\n";
    } else {
        cout << middle->data << '\n';
    }

    clearList(head);
    return 0;
}
