#include <iostream>
#include <string>

using namespace std;

// Generic Node structure using Template
template <typename T>
struct Node
{
    T data;
    Node<T>* next;
};

// Generic Singly Linked List structure using Template
template <typename T>
struct List
{
    Node<T>* head;
    Node<T>* tail;
};

// Initialize an empty list
template <typename T>
void initializeList(List<T>& list)
{
    list.head = nullptr;
    list.tail = nullptr;
}

// Append a new value to the end of the list
template <typename T>
void append(List<T>& list, const T& value)
{
    Node<T>* newNode = new Node<T>{value, nullptr};

    if (list.head == nullptr)
    {
        list.head = newNode;
        list.tail = newNode;
        return;
    }

    list.tail->next = newNode;
    list.tail = newNode;
}

// Split the list into two halves using slow/fast pointer strategy
template <typename T>
void splitList(Node<T>* source, Node<T>*& firstHalf, Node<T>*& secondHalf)
{
    if (source == nullptr || source->next == nullptr)
    {
        firstHalf = source;
        secondHalf = nullptr;
        return;
    }

    Node<T>* slow = source;
    Node<T>* fast = source->next;

    while (fast != nullptr)
    {
        fast = fast->next;
        if (fast != nullptr)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    firstHalf = source;
    secondHalf = slow->next;
    slow->next = nullptr;
}

// Recursively merge two sorted sublists into a single sorted sublist
template <typename T>
Node<T>* mergeSortedLists(Node<T>* first, Node<T>* second)
{
    if (first == nullptr)
    {
        return second;
    }
    if (second == nullptr)
    {
        return first;
    }

    if (first->data <= second->data)
    {
        first->next = mergeSortedLists(first->next, second);
        return first;
    }

    second->next = mergeSortedLists(first, second->next);
    return second;
}

// Merge two sorted List objects and clear original handles
template <typename T>
List<T> mergeLists(List<T>& firstList, List<T>& secondList)
{
    List<T> mergedList{mergeSortedLists(firstList.head, secondList.head), nullptr};
    mergedList.tail = mergedList.head;

    while (mergedList.tail != nullptr && mergedList.tail->next != nullptr)
    {
        mergedList.tail = mergedList.tail->next;
    }

    firstList.head = nullptr;
    firstList.tail = nullptr;
    secondList.head = nullptr;
    secondList.tail = nullptr;

    return mergedList;
}

// Recursively sort a linked list using Merge Sort algorithm
template <typename T>
void mergeSort(List<T>& list)
{
    if (list.head == nullptr || list.head->next == nullptr)
    {
        return;
    }

    Node<T>* firstHalf = nullptr;
    Node<T>* secondHalf = nullptr;
    splitList(list.head, firstHalf, secondHalf);

    List<T> firstList{firstHalf, nullptr};
    List<T> secondList{secondHalf, nullptr};

    mergeSort(firstList);
    mergeSort(secondList);

    list.head = mergeSortedLists(firstList.head, secondList.head);
    list.tail = list.head;
    while (list.tail != nullptr && list.tail->next != nullptr)
    {
        list.tail = list.tail->next;
    }
}

// Print all node data separated by arrow notation
template <typename T>
void printList(const List<T>& list)
{
    if (list.head == nullptr)
    {
        cout << "List is empty!\n";
        return;
    }

    Node<T>* current = list.head;
    while (current != nullptr)
    {
        cout << current->data;
        if (current->next != nullptr)
        {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << '\n';
}

// Deallocate memory for all nodes in the list
template <typename T>
void deleteList(List<T>& list)
{
    while (list.head != nullptr)
    {
        Node<T>* nodeToDelete = list.head;
        list.head = list.head->next;
        delete nodeToDelete;
    }
    list.tail = nullptr;
}

int main()
{
    // =======================================================
    // 1. TEST WITH INTEGER DATA TYPE
    // =======================================================
    cout << "=== 1. INTEGER MERGE SORT DEMO ===\n";
    List<int> firstList;
    List<int> secondList;
    initializeList(firstList);
    initializeList(secondList);

    int firstValues[] = {42, 7, 19, 3, 25};
    int secondValues[] = {12, 1, 30, 8, 16};
    int firstSize = sizeof(firstValues) / sizeof(firstValues[0]);
    int secondSize = sizeof(secondValues) / sizeof(secondValues[0]);

    for (int index = 0; index < firstSize; ++index)
    {
        append(firstList, firstValues[index]);
    }

    for (int index = 0; index < secondSize; ++index)
    {
        append(secondList, secondValues[index]);
    }

    cout << "Original first list:  ";
    printList(firstList);
    cout << "Original second list: ";
    printList(secondList);

    mergeSort(firstList);
    mergeSort(secondList);

    cout << "\nSorted first list:   ";
    printList(firstList);
    cout << "Sorted second list:  ";
    printList(secondList);

    List<int> mergedList = mergeLists(firstList, secondList);

    cout << "\nMerged sorted list:  ";
    printList(mergedList);

    deleteList(mergedList);

    // =======================================================
    // 2. TEST WITH STRING DATA TYPE (TEMPLATE FLEXIBILITY)
    // =======================================================
    cout << "\n=== 2. STRING MERGE SORT DEMO ===\n";
    List<string> strList1, strList2;
    initializeList(strList1);
    initializeList(strList2);

    append(strList1, string("Banana"));
    append(strList1, string("Apple"));
    append(strList1, string("Elderberry"));

    append(strList2, string("Date"));
    append(strList2, string("Cherry"));

    cout << "Original strList1: ";
    printList(strList1);
    cout << "Original strList2: ";
    printList(strList2);

    mergeSort(strList1);
    mergeSort(strList2);

    List<string> mergedStrList = mergeLists(strList1, strList2);
    cout << "Merged sorted string list: ";
    printList(mergedStrList);

    deleteList(mergedStrList);

    return 0;
}