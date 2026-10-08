#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int x) : data(x), next(nullptr) {}
};

class SortedLinkedList {
private:
    Node* head;

public:
    SortedLinkedList() : head(nullptr) {}

    void insertSorted(int x) {
        Node* newNode = new Node(x);

        if (head == nullptr || x <= head->data) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* cur = head;

        while (cur->next != nullptr &&
               cur->next->data < x) {
            cur = cur->next;
        }

        newNode->next = cur->next;
        cur->next = newNode;
    }

    void print() {
        Node* cur = head;

        while (cur != nullptr) {
            cout << cur->data << " ";
            cur = cur->next;
        }

        cout << endl;
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    ~SortedLinkedList() {
        clear();
    }
};

template<typename F>
double timeIt(F f) {
    double best = 1e18;

    for (int i = 0; i < 5; i++) {
        auto t0 = chrono::high_resolution_clock::now();
        f();
        auto t1 = chrono::high_resolution_clock::now();

        best = min(best,
            chrono::duration<double, milli>
            (t1 - t0).count());
    }

    return best;
}

int main() {
    int n;
    cin >> n;

    int* a = new int[n];

    for (int i = 0; i < n; i++)
        cin >> a[i];

    double runtime = timeIt([&]() {
        SortedLinkedList list;

        for (int i = 0; i < n; i++)
            list.insertSorted(a[i]);
    });

    SortedLinkedList list;

    for (int i = 0; i < n; i++)
        list.insertSorted(a[i]);

    list.print();

    cout << "SortedLinkedList: "
         << runtime << " ms\n";

    delete[] a;

    return 0;
}