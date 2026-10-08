#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <psapi.h>

#pragma comment(lib, "psapi.lib")

using namespace std;
using namespace chrono;

// Hàm lấy RAM đỉnh (Peak Memory) đang sử dụng (đơn vị MB)
double GetPeakMemoryMB() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return (double)pmc.PeakPagefileUsage / (1024 * 1024); // Hoặc PeakWorkingSetSize
    }
    return 0.0;
}

// Hàm lấy RAM hiện tại đang sử dụng (đơn vị MB)
double GetCurrentMemoryMB() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return (double)pmc.PagefileUsage / (1024 * 1024); // Hoặc WorkingSetSize
    }
    return 0.0;
}

struct Node
{
    string data;
    struct Node* next;
    struct Node* prev;
};
using NODE = struct Node;

struct BrowserHistory
{
    NODE* head;
    NODE* tail;
    NODE* current;
    int size;
};
using BROWSER = struct BrowserHistory;


void Initialize(BROWSER &b)
{
    b.head = nullptr;
    b.tail = nullptr;
    b.current = nullptr;
    b.size = 0;
}

NODE* CreateNode (const string &url)
{
    NODE* p = new NODE;
    if (p == nullptr) return nullptr;
    
    else
    {
        p->data = url;
        p->next = nullptr;
        p->prev = nullptr;
        
        return p;
    }
}

void ClearFowardHistory(NODE* startNode)
{
    NODE* k = startNode;
    while (k != nullptr)
    {
        NODE* temp = k;
        k = k->next;
        delete temp;
    }
}

void ClearAllHistory(BROWSER &b)
{
    ClearFowardHistory(b.head);
    Initialize(b);
}

void VisitPage(BROWSER &b, const string &url)
{
    NODE* p = CreateNode(url);
    if (p == nullptr) return;

    else if (b.head == nullptr)
    {
        b.head = b.tail = b.current = p;
    }
    
    else 
    {
        if(b.current->next != nullptr)
        {
            for (NODE* k = b.current->next; k != nullptr; k = k->next)
            {
                b.size--;
            }
            ClearFowardHistory(b.current->next);
            b.current->next = nullptr;
        }

        b.current->next = p;
        p->prev = b.current;
        b.current = p;
        b.tail = p;
    }
    b.size++;
}

bool Back(BROWSER &b)
{
    if(b.current != nullptr && b.current->prev != nullptr)
    {
        b.current = b.current->prev;
        return true;
    }
    return false;
}

bool Forward(BROWSER &b)
{
    if (b.current != nullptr && b.current->next != nullptr)
    {
        b.current = b.current->next;
        return true;
    }
    return false;
}

void ShowHistory(BROWSER &b)
{
    if (b.head == nullptr)
    {
        cout<<"EMPTY LIST!\n";
        return;
    }

    for (NODE* k = b.head; k != nullptr; k = k->next)
    {
        if (k == b.current) cout<<"["<<k->data<<"]\n";

        else cout<<k->data<<endl;
    }
}

void GenerateCSVDataset(const string &filename, int totalRecords)
{
    ofstream file(filename);
    if (!file.is_open()) return;

    file << "id,url\n";
    for (int i = 1; i <= totalRecords; i++)
    {
        file << i << ",https://domain_" << i << ".org\n";
    }
    file.close();
}

void DisplayCSVHead(const string &filename, int linesToRead)
{
    ifstream file(filename);
    string line;
    int count = 0;
    while (getline(file, line) && count < linesToRead)
    {
        cout << "   " << line << "\n";
        count++;
    }
    file.close();
}

int main()
{
    BROWSER history;
    Initialize(history);

    // =================================================================
    // BƯỚC 1: DATA VERIFICATION
    // =================================================================
    cout << "\n==================================================\n";
    cout << "BUOC 1: DATA VERIFICATION (Xac minh du lieu)\n";
    cout << "==================================================\n";
    
    int DATASET_SIZE = 1000000;
    string filename = "data.csv";
    
    cout << "[1.1] Dang sinh tap du lieu " << DATASET_SIZE << " dong vao file " << filename << "...\n";
    GenerateCSVDataset(filename, DATASET_SIZE);
    
    cout << "[1.2] Xem truoc 5 dong dau trong file data.csv:\n";
    DisplayCSVHead(filename, 6);
    
    cout << "[1.3] Trang thai ban dau cua Linked List: Size = " << history.size << " (Xac nhan bo nho sach)\n";


    // =================================================================
    // BƯỚC 2: EDGE CASE EXECUTION
    // =================================================================
    cout << "\n==================================================\n";
    cout << "BUOC 2: EDGE CASE EXECUTION (Xu ly ngoai le)\n";
    cout << "==================================================\n";
    
    cout << "-> Edge Case 1: An Back() khi danh sach RONG: ";
    if (!Back(history)) cout << "THANH CONG (Khong bi crash!)\n";

    cout << "-> Edge Case 2: An Forward() khi danh sach RONG: ";
    if (!Forward(history)) cout << "THANH CONG (Khong bi crash!)\n";

    VisitPage(history, "facebook.com");
    cout << "-> Edge Case 3: An Back() khi dang o DAU danh sach (pHead): ";
    if (!Back(history)) cout << "THANH CONG (Da chan an toan!)\n";

    cout << "-> Edge Case 4: An Forward() khi dang o CUOI danh sach (pTail): ";
    if (!Forward(history)) cout << "THANH CONG (Da chan an toan!)\n";

    ClearAllHistory(history);


    // =================================================================
    // BƯỚC 3: CORE ALGORITHM EXECUTION
    // =================================================================
    cout << "\n==================================================\n";
    cout << "BUOC 3: CORE ALGORITHM EXECUTION (Mau nho n = 50)\n";
    cout << "==================================================\n";
    
    cout << "[3.1] Them 50 trang web vao danh sach...\n";
    for (int i = 1; i <= 50; i++)
    {
        VisitPage(history, "page_" + to_string(i) + ".com");
    }
    
    cout << "[3.2] In toan bo danh sach 50 phan tu:\n";
    ShowHistory(history);

    cout << "\n[3.3] Lui lai (Back) 3 lan...\n";
    for (int i = 0; i < 3; i++) Back(history);
    ShowHistory(history);

    cout << "\n[3.4] Mo trang web moi [new_branch.com]:\n";
    VisitPage(history, "new_branch.com");
    ShowHistory(history);

    ClearAllHistory(history);


    // =================================================================
    // BƯỚC 4: STRESS TEST & MEMORY PROFILING
    // =================================================================
    
    cout << "\n==================================================\n";
    cout << "BUOC 4: STRESS TEST & MEMORY PROFILING (n = " << DATASET_SIZE << ")\n";
    cout << "==================================================\n";

    double ram_before_visit = GetCurrentMemoryMB();

    // 1. Thao tác VISIT
    auto start_visit = high_resolution_clock::now();
    for (int i = 1; i <= DATASET_SIZE; i++)
    {
        VisitPage(history, "https://domain_" + to_string(i) + ".org");
    }
    auto stop_visit = high_resolution_clock::now();
    
    double ram_after_visit = GetCurrentMemoryMB();
    double peak_ram_visit = GetPeakMemoryMB();

    // 2. Thao tác BACK (200.000 lần)
    int TARGET_BACK = 200000;
    history.current = history.tail;
    
    double ram_before_back = GetCurrentMemoryMB();
    auto start_back = high_resolution_clock::now();
    int back_count = 0;
    while (back_count < TARGET_BACK && Back(history)) {
        back_count++;
    }
    auto stop_back = high_resolution_clock::now();
    double ram_after_back = GetCurrentMemoryMB();

    // 3. Thao tác FORWARD (100.000 lần)
    int TARGET_FORWARD = 100000;
    
    double ram_before_forward = GetCurrentMemoryMB();
    auto start_forward = high_resolution_clock::now();
    int forward_count = 0;
    while (forward_count < TARGET_FORWARD && Forward(history)) {
        forward_count++;
    }
    auto stop_forward = high_resolution_clock::now();
    double ram_after_forward = GetCurrentMemoryMB();

    // --- KẾT QUẢ TỔNG HỢP TIME & MEMORY ---
    cout << fixed << setprecision(6);
    cout << "\n==================================================\n";
    cout << "BANG PHAN TICH BO NHO (PEAK MEMORY) & THOI GIAN\n";
    cout << "==================================================\n";
    
    cout << "1. Thao tac VISIT (" << DATASET_SIZE << " nodes):\n";
    cout << "   - Thoi gian chay   : " << duration_cast<milliseconds>(stop_visit - start_visit).count() << " ms\n";
    cout << "   - RAM tang them    : " << (ram_after_visit - ram_before_visit) << " MB\n";
    cout << "   - Peak Memory      : " << peak_ram_visit << " MB\n";
    cout << "   - Trung binh/Node  : " << ((ram_after_visit - ram_before_visit) * 1024 * 1024) / DATASET_SIZE << " bytes/node\n\n";

    cout << "2. Thao tac BACK (" << back_count << " lan):\n";
    cout << "   - Thoi gian chay   : " << duration_cast<milliseconds>(stop_back - start_back).count() << " ms\n";
    cout << "   - RAM thay doi     : " << (ram_after_back - ram_before_back) << " MB (Khong ton RAM moi)\n\n";

    cout << "3. Thao tac FORWARD (" << forward_count << " lan):\n";
    cout << "   - Thoi gian chay   : " << duration_cast<milliseconds>(stop_forward - start_forward).count() << " ms\n";
    cout << "   - RAM thay doi     : " << (ram_after_forward - ram_before_forward) << " MB (Khong ton RAM moi)\n";
    cout << "--------------------------------------------------\n";

    system("pause");
    ClearAllHistory(history);
    return 0;
}