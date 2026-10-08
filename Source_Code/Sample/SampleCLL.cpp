#include <iostream>
#include <string>
using namespace std;

// Generic Node structure for Circular Doubly Linked List using Template
template <typename T>
struct Node
{
    T data;
    Node<T> *next; // Pointer to the next node
    Node<T> *prev; // Pointer to the previous node
};

// Generic Circular Doubly Linked List structure using Template
template <typename T>
struct List
{
    Node<T> *head; // Points to the first node
    Node<T> *tail; // Points to the last node
};

// Initialize an empty circular doubly linked list
template <typename T>
void Initialize(List<T> &l)
{
    l.head = nullptr;
    l.tail = nullptr;
}

// Allocate memory for a new node with data x
template <typename T>
Node<T>* CreateNode(const T &x)
{
    Node<T> *p = new Node<T>;
    if (p == nullptr)
    {
        cout << "Memory allocation failed\n";
        return nullptr;
    }
    else 
    {
        p->data = x;
        p->next = nullptr;
        p->prev = nullptr;
        return p;
    }
}

// Print all elements of the circular list from head to tail
template <typename T>
void Traversal(const List<T> &l)
{
    if (l.head == nullptr)
    {
        cout << "List is empty!\n";
        return;
    }

    Node<T> *k = l.head;
    do
    {
        cout << k->data << " ";
        k = k->next;
    } while (k != l.head); // Stop when loop wraps back to head

    cout << endl;
}

// Insert a node 'p' at the head of a Circular Doubly Linked List
template <typename T>
void AddHead(List<T> &l, Node<T> *p)
{
    if (p == nullptr) return;

    // List is currently empty
    if (l.head == nullptr)
    {
        l.head = l.tail = p; // Both head and tail point to this single node p
        p->next = p;         // Point p's next to itself to form a circular link
        p->prev = p;         // Point p's prev to itself to form a circular link
    }
    // List already contains one or more nodes
    else
    {
        p->next = l.head;    // 1. Point new node's next to current head
        p->prev = l.tail;    // 2. Point new node's prev to tail (maintaining circle)
        l.head->prev = p;    // 3. Update old head's prev to point backward to p
        l.tail->next = p;    // 4. Update tail's next to point forward to p
        l.head = p;          // 5. Update head pointer to new node p
    }
}

// Insert a node 'p' at the tail of a Circular Doubly Linked List
template <typename T>
void AddTail(List<T> &l, Node<T> *p)
{
    if (p == nullptr) return;

    // List is currently empty
    if (l.head == nullptr)
    {
        l.head = l.tail = p; // Both head and tail point to this single node p
        p->next = p;         // Point p's next to itself to form a circular link
        p->prev = p;         // Point p's prev to itself to form a circular link
    }
    // List already contains one or more nodes
    else 
    {
        p->next = l.head;    // Point new node's next forward to head (maintaining circle)
        p->prev = l.tail;    // Point new node's prev back to current tail
        l.tail->next = p;    // Update old tail's next to point forward to p
        l.head->prev = p;    // Update head's prev to point backward to p
        l.tail = p;          // Update tail pointer to new node p
    }
}

// Insert a node at 1-based position k (range: 1 to n+1)
template <typename T>
void Add_at_k_position(List<T> &l, Node<T> *p, int position, int n)
{
    if (p == nullptr) return;

    // Empty list or insertion at first position
    if (l.head == nullptr || position == 1)
    {
        AddHead(l, p);
    }
    // Insertion right after last node (tail)
    else if (position == n + 1)
    {
        AddTail(l, p);
    }
    // Insertion in the middle of list
    else 
    {
        int count = 0;
        Node<T> *k = l.head; // Pointer k starts from head

        do
        {
            count++;

            // Target position reached
            if (count == position)
            {
                Node<T> *temp2 = k->prev; // Node preceding k

                p->next = k;     // Set p's next pointer to k
                p->prev = temp2; // Set p's prev pointer to temp2
                temp2->next = p; // Set temp2's next pointer to p
                k->prev = p;     // Set k's prev pointer back to p

                break; 
            }

            k = k->next;

        } while (k != l.head); // Loop stops when wrapped back to head
    }
}

// Delete the node at the head
template <typename T>
void DeleteAtHead(List<T> &l)
{
    // Empty list -> do nothing, exit function
    if (l.head == nullptr) return;

    // Save old head address to delete at the end
    Node<T> *p = l.head;

    // List has EXACTLY 1 node (head equals tail)
    if (l.head == l.tail)
    {
        l.head = nullptr;
        l.tail = nullptr;
    }
    // List has 2 OR MORE nodes
    else
    {
        l.head = l.head->next; // Move head to 2nd node
        l.head->prev = l.tail; // Link new head's prev back to tail
        l.tail->next = l.head; // Link tail's next forward to new head
    }

    delete p;
}

// Delete the node at the tail
template <typename T>
void DeleteAtTail(List<T> &l)
{
    // Empty list -> exit function immediately
    if (l.head == nullptr) return;

    // Store old tail address to free memory at the end
    Node<T> *p = l.tail;

    // List has EXACTLY 1 node (head equals tail)
    if (l.head == l.tail)
    {
        l.head = l.tail = nullptr; // Reset head and tail pointers to nullptr
    }
    // List has 2 OR MORE nodes
    else
    {
        l.tail = l.tail->prev; // Advance tail backward to preceding node
        l.tail->next = l.head; // Connect new tail's next forward to head
        l.head->prev = l.tail; // Connect head's prev backward to new tail
    }

    delete p;
}

// Delete the first node matching target value x
template <typename T>
void DeleteByValue(List<T> &l, const T &x)
{
    // Case 1: Empty list -> exit function
    if (l.head == nullptr) return;

    // Case 2: Target value x is at Head
    if (l.head->data == x)
    {
        DeleteAtHead(l);
        return;
    }

    // Case 3: Target value x is at Tail
    else if (l.tail->data == x)
    {
        DeleteAtTail(l);
        return;
    }

    // Case 4: Target value x is in middle (starts from 2nd node up to before Tail)
    Node<T> *k = l.head->next;
    while (k != l.head)
    {
        // Check if current node holds value x
        if (k->data == x)
        {
            Node<T> *temp1 = k->prev; // Node before k
            Node<T> *temp2 = k->next; // Node after k

            temp1->next = temp2;   // Bypass k forward
            temp2->prev = temp1;   // Bypass k backward

            delete k;              // Free memory of node k
            return;                // Exit after deleting first matching node
        }

        k = k->next; // Advance to next node
    }
}

// Deallocate all nodes memory in circular list
template <typename T>
void ClearList(List<T> &l)
{
    while (l.head != nullptr)
    {
        DeleteAtHead(l);
    }
}

int main()
{
    // =======================================================
    // 1. TEST WITH STRING DATA TYPE
    // =======================================================
    List<string> l;
    Initialize(l);
    int n = 0; // Tracks current number of elements in list

    cout << "=== 1. TEST ADDTAIL (CREATE INITIAL LIST) ===" << endl;
    AddTail(l, CreateNode<string>("Laptop")); n++;
    cout << "AddTail('Laptop') into empty list: ";
    Traversal(l);

    AddTail(l, CreateNode<string>("Phone")); n++;
    AddTail(l, CreateNode<string>("Tablet")); n++;
    cout << "AddTail('Phone', 'Tablet') to tail: ";
    Traversal(l);

    cout << "\n=== 2. TEST ADDHEAD ===" << endl;
    AddHead(l, CreateNode<string>("Smartwatch")); n++;
    cout << "AddHead('Smartwatch') to head: ";
    Traversal(l);

    cout << "\n=== 3. TEST ADD_AT_K_POSITION ===" << endl;
    Add_at_k_position(l, CreateNode<string>("Headphones"), 3, n); n++;
    cout << "Insert 'Headphones' at position 3: ";
    Traversal(l);

    Add_at_k_position(l, CreateNode<string>("Camera"), 1, n); n++;
    cout << "Insert 'Camera' at position 1 (Head): ";
    Traversal(l);

    Add_at_k_position(l, CreateNode<string>("Speaker"), n + 1, n); n++;
    cout << "Insert 'Speaker' at tail position (n+1): ";
    Traversal(l);

    cout << "\n=== 4. TEST DELETEBYVALUE ===" << endl;
    DeleteByValue(l, string("Headphones")); n--;
    cout << "Delete value 'Headphones' in middle: ";
    Traversal(l);

    DeleteByValue(l, string("Camera")); n--;
    cout << "Delete value 'Camera' at Head: ";
    Traversal(l);

    DeleteByValue(l, string("Speaker")); n--;
    cout << "Delete value 'Speaker' at Tail: ";
    Traversal(l);

    DeleteByValue(l, string("TV"));
    cout << "Delete non-existent value 'TV' (no change): ";
    Traversal(l);

    cout << "\n=== 5. TEST DELETEATHEAD & DELETEATTAIL ===" << endl;
    DeleteAtHead(l); n--;
    cout << "DeleteAtHead (removes 'Smartwatch'): ";
    Traversal(l);

    DeleteAtTail(l); n--;
    cout << "DeleteAtTail (removes 'Tablet'): ";
    Traversal(l);

    DeleteAtHead(l); n--;
    cout << "DeleteAtHead (removes 'Laptop', 1 node left): ";
    Traversal(l);

    DeleteAtTail(l); n--;
    cout << "DeleteAtTail on 1-node list: ";
    Traversal(l);

    cout << "\n=== 6. TEST SAFETY ON EMPTY LIST ===" << endl;
    cout << "Executing deletion on empty list: ";
    DeleteAtHead(l);
    DeleteAtTail(l);
    DeleteByValue(l, string("Phone"));
    cout << "Executed safely without crashing!" << endl;

    ClearList(l);

    // =======================================================
    // 2. DEMO WITH INTEGER DATA TYPE (TEMPLATE FLEXIBILITY)
    // =======================================================
    cout << "\n=== 7. DEMO WITH INTEGER DATA TYPE ===" << endl;
    List<int> intList;
    Initialize(intList);

    AddTail(intList, CreateNode(10));
    AddTail(intList, CreateNode(20));
    AddHead(intList, CreateNode(5));

    cout << "Circular Integer List: ";
    Traversal(intList); // Expected: 5 10 20

    ClearList(intList);
    return 0;
}