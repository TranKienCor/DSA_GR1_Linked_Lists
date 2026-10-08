#include <iostream>
using namespace std;

struct SNode { int data; SNode* next; };
struct DNode { int data; DNode* next; DNode* prev; };

bool searchSingly(SNode* head, int target, long long& counter) {
    SNode* current = head;
    while (current != nullptr) {
        if (current->data == target) return true;
        current = current->next;
        ++counter; // exact pointer traversal: current = current->next
    }
    return false;
}

bool searchDoublyHead(DNode* head, int target, long long& counter) {
    DNode* current = head;
    while (current != nullptr) {
        if (current->data == target) return true;
        current = current->next;
        ++counter; // exact pointer traversal
    }
    return false;
}

// Use this only when the target position/proximity to an end is known.
bool searchDoublyBi(DNode* head, DNode* tail, int target, long long& counter) {
    DNode* left = head;
    DNode* right = tail;

    while (left != nullptr && right != nullptr) {
        if (left->data == target) return true;
        if (right->data == target) return true;
        if (left == right) break;

        left = left->next;
        ++counter; // left traversal
        if (left == right) {
            if (left->data == target) return true;
            break;
        }

        right = right->prev;
        ++counter; // right traversal
    }
    return false;
}