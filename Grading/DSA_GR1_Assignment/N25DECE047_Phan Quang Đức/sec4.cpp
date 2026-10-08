struct SNode { int val; SNode* next; };
struct DNode { int val; DNode* prev; DNode* next; };

SNode* searchSingly(SNode* head, int target, long long& cnt) {
    SNode* cur = head;
    while (cur != nullptr && cur->val != target) {
        cur = cur->next;
        ++cnt;                      
    }
    return cur;
}

DNode* searchDoublyHead(DNode* head, int target, long long& cnt) {
    DNode* cur = head;
    while (cur != nullptr && cur->val != target) {
        cur = cur->next;
        ++cnt;
    }
    return cur;
}

DNode* searchDoublyBi(DNode* head, DNode* tail, int n, int idx, int target, long long& cnt) {
    if (idx < n - 1 - idx) {
        DNode* cur = head;
        while (cur != nullptr && cur->val != target) { cur = cur->next; ++cnt; }
        return cur;
    } else {
        DNode* cur = tail;
        while (cur != nullptr && cur->val != target) { cur = cur->prev; ++cnt; }
        return cur;
    }
}