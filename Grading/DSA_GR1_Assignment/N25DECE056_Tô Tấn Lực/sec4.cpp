#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <iomanip>
using namespace std;

struct SNode {
    int data;
    SNode* next;
    explicit SNode(int value) : data(value), next(nullptr) {}
};

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    explicit DNode(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class SinglyList {
public:
    SNode* head = nullptr;
    SNode* tail = nullptr;

    void append(int value) {
        SNode* node = new SNode(value);
        if (!head) head = tail = node;
        else { tail->next = node; tail = node; }
    }

    // Counter increases exactly when current advances to current->next.
    long long searchHead(int target) const {
        long long traversals = 0;
        SNode* current = head;
        while (current != nullptr) {
            if (current->data == target) return traversals + 1; // count visit/advance to this node
            current = current->next;
            ++traversals;
        }
        return traversals;
    }

    void clear() {
        while (head) {
            SNode* old = head;
            head = head->next;
            delete old;
        }
        tail = nullptr;
    }
    ~SinglyList() { clear(); }
};

class DoublyList {
public:
    DNode* head = nullptr;
    DNode* tail = nullptr;
    int size = 0;

    void append(int value) {
        DNode* node = new DNode(value);
        if (!head) head = tail = node;
        else {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        ++size;
    }

    // Head-only search, counting each node visited as one traversal unit.
    long long searchHead(int target) const {
        long long visited = 0;
        DNode* current = head;
        while (current != nullptr) {
            ++visited;
            if (current->data == target) return visited;
            current = current->next;
        }
        return visited;
    }

    // Bidirectional search is useful when the target's index/proximity
    // is known. This function receives the target's known zero-based index,
    // then starts at the nearer end and counts pointer moves to the target.
    // Values are not used to infer an index (duplicates could make it ambiguous).
    long long traversalsToIndex(int index) const {
        if (index < 0 || index >= size) return 0;
        if (index <= size - 1 - index) {
            long long moves = 0;
            DNode* current = head;
            while (moves < index) {
                current = current->next;
                ++moves;
            }
            return moves + 1; // include arrival/inspection of target node
        } else {
            long long moves = 0;
            DNode* current = tail;
            while (moves < size - 1 - index) {
                current = current->prev;
                ++moves;
            }
            return moves + 1;
        }
    }

    void clear() {
        while (head) {
            DNode* old = head;
            head = head->next;
            delete old;
        }
        tail = nullptr;
        size = 0;
    }
    ~DoublyList() { clear(); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // The assignment refers to an instructor-provided sample dataset, but it
    // was not included with the PDF. This reproducible demo uses 10,000 unique
    // integers in shuffled order and 10,000 uniformly selected target indices.
    // Replace this data-generation block with the instructor's dataset for
    // submission of the required empirical measurements.
    const int n = 10000;
    vector<int> data(n);
    iota(data.begin(), data.end(), 0);
    mt19937 rng(20261004);
    shuffle(data.begin(), data.end(), rng);

    SinglyList singly;
    DoublyList doubly;
    for (int value : data) {
        singly.append(value);
        doubly.append(value);
    }

    vector<int> queries(n);
    iota(queries.begin(), queries.end(), 0);
    shuffle(queries.begin(), queries.end(), rng);

    long long singlyTotal = 0, doublyHeadTotal = 0, doublyBiTotal = 0;
    for (int target : queries) {
        singlyTotal += singly.searchHead(target);
        doublyHeadTotal += doubly.searchHead(target);

        // Each integer is unique in this demo, so its index in the shuffled
        // dataset is found here. For the instructor's data, track each target's
        // actual index or use a search strategy that does not assume uniqueness.
        auto it = find(data.begin(), data.end(), target);
        int index = static_cast<int>(it - data.begin());
        doublyBiTotal += doubly.traversalsToIndex(index);
    }

    double sAvg = static_cast<double>(singlyTotal) / n;
    double dhAvg = static_cast<double>(doublyHeadTotal) / n;
    double dbAvg = static_cast<double>(doublyBiTotal) / n;

    cout << "n = " << n << ", queries = " << n << '\n';
    cout << fixed << setprecision(2);
    cout << "Structure / Strategy                         Empirical average traversals"
         << "   Theoretical average   Worst\n";
    cout << "Singly Linked List (Head Search)             " << setw(10) << sAvg
         << "                  5000.00       10000\n";
    cout << "Doubly Linked List (Head Search)             " << setw(10) << dhAvg
         << "                  5000.00       10000\n";
    cout << "Doubly Linked List (Bi-directional by index) " << setw(10) << dbAvg
         << "                  2500.00       10000\n";
    cout << "\nRatio (empirical average / theoretical average):\n";
    cout << "Singly Head: " << sAvg / 5000.0 << '\n';
    cout << "Doubly Head: " << dhAvg / 5000.0 << '\n';
    cout << "Doubly Bi-directional: " << dbAvg / 2500.0 << '\n';

    return 0;
}
