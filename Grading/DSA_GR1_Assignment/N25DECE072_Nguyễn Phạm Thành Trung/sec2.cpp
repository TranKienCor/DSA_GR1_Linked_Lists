#include <iostream>

#include <chrono>

#include <algorithm>

using namespace std;


struct Node {

    int data;

    Node* next;

    Node(int val) : data(val), next(nullptr) {}

};


void insertSorted(Node*& head, int val) {

    Node* newNode = new Node(val);


    if (head == nullptr || val < head->data) {

        newNode->next = head;

        head = newNode;

        return;

    }


    Node* current = head;

    while (current->next != nullptr && current->next->data <= val) {

        current = current->next;

    }


    newNode->next = current->next;

    current->next = newNode;

}


void printList(const Node* head) {

    const Node* current = head;

    bool first = true;

    while (current != nullptr) {

        if (!first) cout << " ";

        cout << current->data;

        first = false;

        current = current->next;

    }

    cout << "\n";

}

void freeList(Node*& head) {

    Node* current = head;

    while (current != nullptr) {

        Node* temp = current;

        current = current->next;

        delete temp;

    }

    head = nullptr;

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

    int* arr = new int[n];

    for (int i = 0; i < n; ++i) {

        cin >> arr[i];

    }

    Node* head = nullptr;

    double runtime = timeIt([&]() {

        freeList(head);

        for (int i = 0; i < n; ++i) {

            insertSorted(head, arr[i]);

        }

    });

    printList(head);

    cout << "SortedLinkedList: " << runtime << " ms\n";

    freeList(head);

    delete[] arr;

    return 0;

}
