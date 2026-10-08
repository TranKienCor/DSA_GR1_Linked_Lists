#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstdlib> // Thêm thư viện này để dùng system("pause")
#include <windows.h>
#include <psapi.h>

#pragma comment(lib, "psapi.lib") // Liên kết thư viện Windows PSAPI

using namespace std;
using namespace std::chrono;

// Hàm lấy RAM đỉnh (Peak Memory) đang sử dụng (đơn vị MB)
double GetPeakMemoryMB() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return (double)pmc.PeakPagefileUsage / (1024 * 1024);
    }
    return 0.0;
}

// Hàm lấy RAM hiện tại đang sử dụng (đơn vị MB)
double GetCurrentMemoryMB() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return (double)pmc.PagefileUsage / (1024 * 1024);
    }
    return 0.0;
}

struct Node {
    int data;
    Node* next;
};

// Hàm chèn vào cuối - O(1)
void insertTail(Node*& tail, int val) {
    Node* newNode = new Node();
    newNode->data = val;
    
    if (tail == NULL) {
        newNode->next = newNode;
        tail = newNode;
    } else {
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }
}

// Hàm giải phóng bộ nhớ sạch sẽ cho 1 triệu Node
void freeList(Node*& tail) {
    if (tail == NULL) return;
    
    Node* head = tail->next;
    Node* curr = head;
    
    // Duyệt vòng để delete từng node
    while (curr != tail) {
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete tail;
    tail = NULL;
}

int main() {
    // Tối ưu tốc độ xuất dữ liệu ra màn hình
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Node* tail = NULL;
    int N = 1000000; // 1 Triệu Testcases

    cout << "=== DANG CHAY CHUONG TRINH VOI N = " << N << " ===\n";

    // --- 1. Đo thời gian & RAM khi Insert 1 triệu phần tử ---
    double ram_before_insert = GetCurrentMemoryMB();
    auto startInsert = high_resolution_clock::now();
    
    for (int i = 1; i <= N; ++i) {
        insertTail(tail, i);
    }
    
    auto endInsert = high_resolution_clock::now();
    double insertTime = duration<double, milli>(endInsert - startInsert).count();
    double ram_after_insert = GetCurrentMemoryMB();
    double peak_ram_insert = GetPeakMemoryMB();

    // --- 2. Đo thời gian & RAM khi Tìm kiếm phần tử ở cuối (Worst-case O(n)) ---
    double ram_before_search = GetCurrentMemoryMB();
    auto startSearch = high_resolution_clock::now();
    
    bool found = false;
    int target = N; // Tìm phần tử nằm ở vị trí cuối cùng
    Node* head = tail->next;
    Node* curr = head;
    
    do {
        if (curr->data == target) {
            found = true;
            break;
        }
        curr = curr->next;
    } while (curr != head);

    auto endSearch = high_resolution_clock::now();
    double searchTime = duration<double, milli>(endSearch - startSearch).count();
    double ram_after_search = GetCurrentMemoryMB();

    // --- 3. BẢNG PHÂN TÍCH PROFILING ---
    cout << fixed << setprecision(6);
    cout << "\n==================================================\n";
    cout << "BANG PHAN TICH BO NHO (PEAK MEMORY) & THOI GIAN\n";
    cout << "==================================================\n";

    cout << "1. Thao tac INSERT TAIL (" << N << " nodes):\n";
    cout << "   - Thoi gian chay   : " << insertTime << " ms (~" << insertTime / 1000.0 << " s)\n";
    cout << "   - RAM tang them    : " << (ram_after_insert - ram_before_insert) << " MB\n";
    cout << "   - Peak Memory      : " << peak_ram_insert << " MB\n";
    cout << "   - Trung binh/Node  : " << ((ram_after_insert - ram_before_insert) * 1024 * 1024) / N << " bytes/node\n\n";

    cout << "2. Thao tac SEARCH Worst-Case (" << (found ? "THANH CONG" : "THAT BAI") << "):\n";
    cout << "   - Thoi gian chay   : " << searchTime << " ms\n";
    cout << "   - RAM thay doi     : " << (ram_after_search - ram_before_search) << " MB (Khong ton RAM moi)\n";
    cout << "--------------------------------------------------\n";

    // --- 4. Dọn dẹp bộ nhớ RAM ---
    freeList(tail);
    cout << "-> Da giai phong bo nho RAM an toan.\n";

    system("pause");
    return 0;
}