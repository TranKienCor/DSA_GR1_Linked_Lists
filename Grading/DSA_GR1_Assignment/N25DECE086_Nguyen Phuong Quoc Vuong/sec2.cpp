#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;
//There are no way to create a sort-inside-linked-list that run with n = 1e6
// in acceptable time, so I sort the data first.
template <typename F>
double timeIt(F f){
    double best = 1e18;
    for(int i = 0; i < 5; i++){
        auto t0 = chrono::high_resolution_clock::now();
        f();
        auto t1 = chrono::high_resolution_clock::now();
        best = min(best, chrono::duration<double, milli>(t1 - t0).count());
    }
    return best;
}

struct Node {
    int value;
    Node* next;
    Node(int val): value(val), next(nullptr) {}
};

const int MAXN = 1000005;
int arr[MAXN], backupArr[MAXN], tempArr[MAXN];

void mergeParts(int* a, int l, int mid, int r) {
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) tempArr[k++] = a[i++];
        else tempArr[k++] = a[j++];
    }
    while (i <= mid) tempArr[k++] = a[i++];
    while (j <= r)   tempArr[k++] = a[j++];
    for (int p = l; p <= r; p++) a[p] = tempArr[p];
}

void mergeSort(int* a, int l, int r) {
    if (l >= r) return;
    int mid = l + (r - l) / 2;
    mergeSort(a, l, mid);
    mergeSort(a, mid + 1, r);
    mergeParts(a, l, mid, r);
}

void insertSorted(Node*& head, Node*& tail, int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = tail = newNode;
        return;
    }

    if (value <= head->value) {
        newNode->next = head;
        head = newNode;
        return;
    }

    if (value >= tail->value) {
        tail->next = newNode;
        tail = newNode;
        return;
    }

    Node* curr = head;
    while (curr->next != nullptr && curr->next->value < value) {
        curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
}

void printList(const Node* head) {
    const Node* curr = head;
    while (curr != nullptr) {
        cout << curr->value;
        if (curr->next != nullptr) cout << " ";
        curr = curr->next;
    }
    cout << "\n";
}

void clearList(Node*& head, Node*& tail) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    if (n < 0) n = 0;

    int actualN = 0;
    for (int i = 0; i < n && i < MAXN; i++) {
        if (cin >> arr[i]) {
            backupArr[i] = arr[i];
            actualN++;
        } else {
            break;
        }
    }
    n = actualN;

    Node* head = nullptr;
    Node* tail = nullptr;

    double bestTime = timeIt([&]() {
        clearList(head, tail);

        for (int i = 0; i < n; i++) {
            arr[i] = backupArr[i];
        }

        if (n > 0) {
            mergeSort(arr, 0, n - 1);
        }

        for (int i = 0; i < n; i++) {
            insertSorted(head, tail, arr[i]);
        }
    });

    printList(head);
    cout << "SortedLinkedList: " << bestTime << " ms\n";

    clearList(head, tail);

    return 0;
}