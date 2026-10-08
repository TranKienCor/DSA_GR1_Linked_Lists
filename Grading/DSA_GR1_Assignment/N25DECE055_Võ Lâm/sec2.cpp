#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

void insertSorted(Node*& head, int val) {
    Node* newNode = new Node(val);

    if (head == nullptr || val <= head->data) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* curr = head;
    while (curr->next != nullptr && curr->next->data < val) {
        curr = curr->next;
    }

    newNode->next = curr->next;
    curr->next = newNode;
}

void printList(const Node* head) {
    const Node* curr = head;
    bool first = true;
    while (curr != nullptr) {
        if (!first) cout << " ";
        cout << curr->data;
        first = false;
        curr = curr->next;
    }
    cout << "\n";
}

void clearList(Node*& head) {
    while (head != nullptr) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

template<typename F>
double timeIt(F f) {
    double best = 1e18;
    for (int i = 0; i < 5; i++) {
        auto t0 = chrono::high_resolution_clock::now();
        f();
        auto t1 = chrono::high_resolution_clock::now();
        best = min(best, chrono::duration<double, milli>(t1 - t0).count());
    }
    return best; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    //buffer
    vector<int> inputs(n);
    for (int i = 0; i < n; ++i) {
        cin >> inputs[i];
    }

    Node* displayList = nullptr;
    for (int val : inputs) {
        insertSorted(displayList, val);
    }
    printList(displayList);
    clearList(displayList);

    double bestTime = timeIt([&]() {
        Node* benchmarkList = nullptr;
        for (int val : inputs) {
            insertSorted(benchmarkList, val);
        }
        clearList(benchmarkList);
    });

    cout << "SortedLinkedList: " << bestTime << " ms\n";

    return 0;
}