#include <iostream>
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

void appendSingly(SNode*& head, SNode*& tail, int value, SNode*& created) {
    created = new SNode(value);
    if (head == nullptr) {
        head = tail = created;
    } else {
        tail->next = created;
        tail = created;
    }
}

void appendDoubly(DNode*& head, DNode*& tail, int value, DNode*& created) {
    created = new DNode(value);
    if (head == nullptr) {
        head = tail = created;
    } else {
        created->prev = tail;
        tail->next = created;
        tail = created;
    }
}

bool searchSinglyFromHead(SNode* head, const SNode* target, long long& traversals) {
    traversals = 0;
    SNode* current = head;

    while (current != nullptr) {
        if (current == target) {
            return true;
        }
        current = current->next;
        ++traversals;
    }
    return false;
}

bool searchDoublyFromHead(DNode* head, const DNode* target, long long& traversals) {
    traversals = 0;
    DNode* current = head;

    while (current != nullptr) {
        if (current == target) {
            return true;
        }
        current = current->next;
        ++traversals;
    }
    return false;
}

bool searchDoublyClosestEnd(
    DNode* head,
    DNode* tail,
    const DNode* target,
    int targetIndex,
    int n,
    long long& traversals
) {
    traversals = 0;

    if (targetIndex < n / 2) {
        DNode* current = head;
        while (current != nullptr) {
            if (current == target) {
                return true;
            }
            current = current->next;
            ++traversals;
        }
    } else {
        DNode* current = tail;
        while (current != nullptr) {
            if (current == target) {
                return true;
            }
            current = current->prev;
            ++traversals;
        }
    }

    return false;
}

void clearSingly(SNode*& head) {
    while (head != nullptr) {
        SNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void clearDoubly(DNode*& head) {
    while (head != nullptr) {
        DNode* temp = head;
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

    int* values = (n > 0) ? new int[n] : nullptr;
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    SNode* sHead = nullptr;
    SNode* sTail = nullptr;
    DNode* dHead = nullptr;
    DNode* dTail = nullptr;

    SNode** sNodes = (n > 0) ? new SNode*[n] : nullptr;
    DNode** dNodes = (n > 0) ? new DNode*[n] : nullptr;

    for (int i = 0; i < n; ++i) {
        appendSingly(sHead, sTail, values[i], sNodes[i]);
        appendDoubly(dHead, dTail, values[i], dNodes[i]);
    }

    long long totalSingly = 0;
    long long totalDoublyHead = 0;
    long long totalDoublyBi = 0;

    for (int i = 0; i < n; ++i) {
        long long count = 0;

        searchSinglyFromHead(sHead, sNodes[i], count);
        totalSingly += count;

        searchDoublyFromHead(dHead, dNodes[i], count);
        totalDoublyHead += count;

        searchDoublyClosestEnd(dHead, dTail, dNodes[i], i, n, count);
        totalDoublyBi += count;
    }

    const double empiricalSingly = (n == 0) ? 0.0 : static_cast<double>(totalSingly) / n;
    const double empiricalDoublyHead = (n == 0) ? 0.0 : static_cast<double>(totalDoublyHead) / n;
    const double empiricalDoublyBi = (n == 0) ? 0.0 : static_cast<double>(totalDoublyBi) / n;

    const double theoreticalWorst = static_cast<double>(n);
    const double theoreticalAvgHead = (n == 0) ? 0.0 : (n + 1.0) / 2.0;
    const double theoreticalAvgBi = (n == 0) ? 0.0 : n / 4.0;

    auto ratio = [](double empirical, double average) {
        return (average == 0.0) ? 0.0 : empirical / average;
    };

    cout << fixed << setprecision(2);
    cout << "n\tStructure / Strategy\tEmpirical Traversals\tTheoretical Worst\tTheoretical Avg\tRatio\n";
    cout << n << "\tSingly Linked List (Head Search)\t"
         << empiricalSingly << '\t' << theoreticalWorst << '\t'
         << theoreticalAvgHead << '\t' << ratio(empiricalSingly, theoreticalAvgHead) << '\n';

    cout << n << "\tDoubly Linked List (Head Search)\t"
         << empiricalDoublyHead << '\t' << theoreticalWorst << '\t'
         << theoreticalAvgHead << '\t' << ratio(empiricalDoublyHead, theoreticalAvgHead) << '\n';

    cout << n << "\tDoubly Linked List (Bi-directional)\t"
         << empiricalDoublyBi << '\t' << theoreticalWorst << '\t'
         << theoreticalAvgBi << '\t' << ratio(empiricalDoublyBi, theoreticalAvgBi) << '\n';

    cout << "\nWritten analysis:\n";
    cout << "Head-only search in both singly and doubly linked lists has essentially the same "
            "average traversal cost, about n/2, because both start at the head and move one node at a time.\n";
    cout << "A doubly linked list can reduce the average distance to about n/4 when the target's "
            "position/proximity is known, because the search can start from whichever end is closer.\n";
    cout << "A singly linked list cannot do this because it has no prev pointer and is therefore "
            "restricted to forward traversal from the head.\n";
    cout << "The empirical pointer-traversal counts can be about one less than node-comparison formulas "
            "because reaching the first node requires zero pointer moves; this is only an off-by-one "
            "counting convention and does not change the O(N) complexity.\n";

    delete[] values;
    delete[] sNodes;
    delete[] dNodes;
    clearSingly(sHead);
    clearDoubly(dHead);

    return 0;
}
