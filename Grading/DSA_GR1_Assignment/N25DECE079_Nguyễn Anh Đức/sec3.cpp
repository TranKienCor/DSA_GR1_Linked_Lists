#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Fast and Slow pointers algorithm
Node* findMiddle(Node* head) {
    if (!head) return nullptr; // Edge case: Empty list
    
    Node* slow = head;
    Node* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; // For even elements (1->2->3->4), returns node 3
}

// Hàm hỗ trợ tạo danh sách từ mảng để test
Node* createList(int arr[], int n) {
    if (n == 0) return nullptr;
    Node* head = new Node(arr[0]);
    Node* tail = head;
    for (int i = 1; i < n; i++) {
        tail->next = new Node(arr[i]);
        tail = tail->next;
    }
    return head;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    Node* head1 = createList(arr1, 5);
    Node* mid1 = findMiddle(head1);
    cout << "Test 1 (1->2->3->4->5) Middle: " << (mid1 ? mid1->data : -1) << endl;

    int arr2[] = {1, 2, 3, 4};
    Node* head2 = createList(arr2, 4);
    Node* mid2 = findMiddle(head2);
    cout << "Test 2 (1->2->3->4) Middle: " << (mid2 ? mid2->data : -1) << endl;

    Node* head3 = nullptr;
    Node* mid3 = findMiddle(head3);
    cout << "Test 3 (Empty) Middle: " << (mid3 ? mid3->data : -1) << endl;

    return 0;
}

/*
 * Time Complexity: O(N)
 * Explanation: The fast pointer traverses the list at twice the speed of the slow pointer. 
 * To cover N elements, the loop only runs N/2 times. Dropping the constant factor, 
 * the time complexity is linear, O(N).
 *
 * Auxiliary Space Complexity: O(1)
 * Explanation: The algorithm only uses two additional pointer variables (slow and fast). 
 * It does not allocate any new arrays or auxiliary data structures, thus requiring constant space.
 */