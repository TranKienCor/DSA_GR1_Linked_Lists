#include <iostream>
#include <string>
using namespace std;

// Generic Node structure using Template
template <typename T>
struct Node
{
    T data;
    Node<T> *next;
};

// Generic Singly Linked List structure using Template
template <typename T>
struct List
{
    Node<T> *head;
    Node<T> *tail;
};

// Initialize the list
template <typename T>
void Initialize(List<T> &l)
{
    l.head = nullptr;
    l.tail = nullptr;
}

// Create a new node with data x
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
        return p;
    }
}

// Traverse and print the list elements
template <typename T>
void Traversal(const List<T> &l)
{
    if (l.head == nullptr)
    {
        cout << "List is empty!\n" << endl;
        return;
    }
    
    for (Node<T> *k = l.head; k != nullptr; k = k->next)
    {
        cout << k->data << " ";
    }
    cout << "\n";
}

// Insert a node at the head of the list
template <typename T>
void AddHead(List<T> &l, Node<T> *p)
{
    if (p == nullptr) return;

    if (l.head == nullptr)
    {
        l.head = l.tail = p; 
    }
    else 
    {
        p->next = l.head; 
        l.head = p;
    }
}

// Insert a node at the tail of the list
template <typename T>
void AddTail(List<T> &l, Node<T> *p)
{
    if (p == nullptr) return;

    if (l.head == nullptr)
    {
        l.head = l.tail = p;
    }
    else 
    {
        l.tail->next = p;
        l.tail = p;
    }
}   

// Insert node p at 1-based index position
template <typename T>
void Add_at_k_position(List<T> &l, Node<T> *p, int position, int n)
{
    if (p == nullptr) return;

    // If position is 1 or list is empty, add to head
    if (l.head == nullptr || position == 1)
    {
        AddHead(l, p);
        return;
    }
    // If position is n + 1, add to tail
    else if (position == n + 1)
    {
        AddTail(l, p);
        return;
    }
    else 
    {
        int count = 0;
        Node<T> *g = nullptr; // Pointer to store the previous node
        for (Node<T> *k = l.head; k != nullptr; k = k->next)
        {
            count++;
            if (count == position)
            {
                p->next = k;
                g->next = p;
                return;
            }
            g = k; // Update previous node pointer
        }
    }
}

// Delete the node at the head
template <typename T>
void DeleteAtHead(List<T> &l)
{
    if (l.head == nullptr) return;

    // List contains only 1 node
    if (l.head == l.tail)
    {
        delete l.head;
        l.head = nullptr;
        l.tail = nullptr;
    }
    else 
    {
        Node<T> *temp = l.head;
        l.head = l.head->next;
        delete temp;
    }
}

// Delete the node at the tail
template <typename T>
void DeleteAtTail(List<T> &l)
{
    if (l.head == nullptr) return;

    // List contains only 1 node
    if (l.head->next == nullptr)
    {
        DeleteAtHead(l);
    }
    else
    {
        for (Node<T> *k = l.head; k != nullptr; k = k->next)
        {
            if (k->next == l.tail)
            {
                delete l.tail;
                k->next = nullptr;
                l.tail = k;
                return;
            }
        }
    }
}

// Delete first occurrence matching target value
template <typename T>
void DeleteByValue(List<T> &l, const T &x)
{
    if (l.head == nullptr) return;

    if (l.head->data == x)
    {
        DeleteAtHead(l);
        return;
    }
    else if (l.tail->data == x)
    {
        DeleteAtTail(l);
        return;
    }
    else
    {
        Node<T> *temp = nullptr;
        for (Node<T> *k = l.head; k != nullptr; k = k->next)
        {
            if (k->data == x)
            {
                temp->next = k->next;
                delete k;
                return;
            }
            temp = k;
        }
    }
}

// Clear all nodes and deallocate memory
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
    int n = 0;

    cout << "=== 1. TEST ADDHEAD & ADDTAIL (STRING) ===\n";
    AddTail(l, CreateNode<string>("B")); n++;
    AddHead(l, CreateNode<string>("A")); n++;
    AddTail(l, CreateNode<string>("D")); n++;
    Traversal(l); // Expected: A B D 

    cout << "\n=== 2. TEST ADD_AT_K_POSITION ===\n";
    Add_at_k_position(l, CreateNode<string>("C"), 3, n); n++;
    Add_at_k_position(l, CreateNode<string>("FIRST"), 1, n); n++;
    Add_at_k_position(l, CreateNode<string>("LAST"), n + 1, n); n++;
    Traversal(l); // Expected: FIRST A B C D LAST 

    cout << "\n=== 3. TEST DELETEBYVALUE ===\n";
    DeleteByValue(l, string("C")); n--;
    DeleteByValue(l, string("FIRST")); n--;
    DeleteByValue(l, string("LAST")); n--;
    Traversal(l); // Expected: A B D 

    cout << "\n=== 4. TEST DELETEATHEAD & DELETEATTAIL ===\n";
    DeleteAtHead(l); n--;
    DeleteAtTail(l); n--;
    Traversal(l); // Expected: B 

    DeleteAtHead(l); n--;
    Traversal(l); // Expected: List is empty!

    ClearList(l);

    // =======================================================
    // 2. TEST WITH INT DATA TYPE (DEMONSTRATING TEMPLATE FLEXIBILITY)
    // =======================================================
    cout << "\n=== 5. DEMO WITH INTEGER DATA TYPE ===\n";
    List<int> intList;
    Initialize(intList);

    AddTail(intList, CreateNode(10));
    AddTail(intList, CreateNode(20));
    AddTail(intList, CreateNode(30));
    AddHead(intList, CreateNode(5));

    cout << "Integer List: ";
    Traversal(intList); // Expected: 5 10 20 30

    ClearList(intList);
    return 0;
}