#include <iostream>
#include <chrono>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Node {
    int data;
    Node* next;
    explicit Node(int value) : data(value), next(nullptr) {}
};

class SortedLinkedList {
private:
    Node* head;

public:
    SortedLinkedList() : head(nullptr) {}

    // Keep the list in ascending order. Equal values are allowed.
    void insertSorted(int value) {
        Node* node = new Node(value);

        // Insert before the current head (also handles an empty list).
        if (head == nullptr || value < head->data) {
            node->next = head;
            head = node;
            return;
        }

        // Move until the next node is absent or has a value >= value.
        Node* current = head;
        while (current->next != nullptr && current->next->data < value) {
            current = current->next;
        }

        node->next = current->next;
        current->next = node;
    }

    void print() const {
        const Node* current = head;
        bool first = true;
        while (current != nullptr) {
            if (!first) cout << ' ';
            cout << current->data;
            first = false;
            current = current->next;
        }
        cout << '\n';
    }

    void clear() {
        while (head != nullptr) {
            Node* oldHead = head;
            head = head->next;
            delete oldHead;
        }
    }

    ~SortedLinkedList() { clear(); }

    // Avoid accidental shallow copies and double deletion.
    SortedLinkedList(const SortedLinkedList&) = delete;
    SortedLinkedList& operator=(const SortedLinkedList&) = delete;
};

template <typename F>
double timeIt(F f) {
    double best = 1e18;
    for (int i = 0; i < 5; ++i) {
        auto t0 = chrono::high_resolution_clock::now();
        f();
        auto t1 = chrono::high_resolution_clock::now();
        best = min(best, chrono::duration<double, milli>(t1 - t0).count());
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n) || n < 0 || n > 1000000) {
        cerr << "Invalid n. Expected 0 <= n <= 1000000.\n";
        return 1;
    }

    // Read values once. The input array is only used to repeat the timed build.
    int* values = (n > 0) ? new int[n] : nullptr;
    for (int i = 0; i < n; ++i) {
        if (!(cin >> values[i])) {
            cerr << "Not enough input integers.\n";
            delete[] values;
            return 1;
        }
    }

    SortedLinkedList result;
    double bestMs = timeIt([&]() {
        // Clear prior run so every timing measures construction from scratch.
        result.clear();
        for (int i = 0; i < n; ++i) result.insertSorted(values[i]);
    });

    result.print();
    cout << fixed << setprecision(3)
         << "SortedLinkedList: " << bestMs << " ms\n";

    delete[] values;
    return 0;
}
