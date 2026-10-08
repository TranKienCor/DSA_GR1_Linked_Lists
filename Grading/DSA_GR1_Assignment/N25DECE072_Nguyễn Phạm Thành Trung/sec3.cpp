#include 

using namespace std;

struct Node {
int data;
Node* next;
Node(int val) : data(val), next(nullptr) {}
};

/**

Finds the middle node of a singly linked list using Floyd's Fast & Slow Pointer technique.


Edge Case Handling:
Empty List (head == nullptr): Returns nullptr.
Single Element (head->next == nullptr): Returns head.
Even number of nodes (e.g., 1 -> 2 -> 3 -> 4): Loop terminates when fast reaches nullptr
or fast->next reaches nullptr. Returns second middle node (node 3).


@param head Pointer to the head of the Singly Linked List
@return Pointer to the middle Node (or nullptr if empty)
/
Node findMiddle(Node* head) {
if (head == nullptr) return nullptr; // Handle empty list

Node* slow = head;
Node* fast = head;

// Fast pointer advances 2 steps while slow pointer advances 1 step
while (fast != nullptr && fast->next != nullptr) {
slow = slow->next;          // 1 step
fast = fast->next->next;    // 2 steps
}return slow; // Slow pointer is now at the middle nod
e
}

## Complexity Explanation:

* **Time Complexity: O(N)**

  * *Explanation:* The fast pointer traverses the list at twice the speed of the slow pointer. To cover N elements, the loop only runs N/2 times. Dropping the constant factor 1/2, the time complexity is linear, O(N).

* **Auxiliary Space Complexity: O(1)**

  * *Explanation:* The algorithm only uses two additional pointer variables (slow and fast). It does not allocate any new arrays or auxiliary data structures, thus requiring constant space.
