#include <iostream>

using namespace std;

struct Node{
    int value;
    Node* next;
    //Constructor
    Node(int val): value(val), next(nullptr){};
};

/*
Time Complexity: O(N)
Explanation: The fast pointer traverses the list at twice the speed of the slow pointer. 
To cover N elements, the loop only runs N/2 times. Dropping the constant factor, the time complexity is linear, O(N).

Auxiliary Space Complexity: O(1)
Explanation: The algorithm only uses two additional pointer variables (slow and fast). 
It does not allocate any new arrays or auxiliary data structures, thus requiring constant space.
*/
Node* findMiddle(Node* head){
    // Edge case: Empty list (nullptr)
    if(head == nullptr) return nullptr;

    Node* slow = head;
    Node* fast = head;

    // Fast pointer advances 2 steps, slow pointer advances 1 step per iteration
    // Stopping condition: when fast reaches nullptr or fast->next reaches nullptr
    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }

    // At loop termination, slow is positioned at the middle node
    return slow;
}

// Helper function to insert a new node at the tail of the list
void insertAtTail(Node*& head, Node*& tail, int value){
    Node* newNode = new Node(value);
    if(head == nullptr){
        head = tail = newNode;
        return;
    }
    tail->next = newNode;
    tail = newNode;
}

// Helper function to print elements in the list
void printList(const Node* head){
    const Node* curr = head;
    while(curr != nullptr){
        cout << curr->value;
        if(curr->next != nullptr) cout << " -> ";
        curr = curr->next;
    }
    cout << "\n";
}

// Helper function to deallocate memory
void clearList(Node*& head){
    while(head != nullptr){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while(cin >> n){
        Node* head = nullptr, *tail = nullptr;
        for(int i = 0; i < n; i++){
            int val;
            cin >> val;
            insertAtTail(head, tail, val);
        }

        Node* mid = findMiddle(head);
        if(mid != nullptr){
            cout << mid->value << "\n";
        }else{
            cout << "nullptr\n";
        }

        clearList(head);
    }

    return 0;
}
