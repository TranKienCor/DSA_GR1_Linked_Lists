# Linked List Data Structures & Multi-Language Performance Benchmark

A comprehensive repository containing generic **Linked List** data structure implementations in **C++**, a real-world **Browser History** application demo, and a multi-language performance profiling suite across **C++, Go, Java, JavaScript (Node.js), and Python**.

---

## 📌 Repository Structure & Overview

The project is structured into three main categories:

```text
.
├── 1. Core Data Structures (C++ Generic Templates)
│   ├── SampleSLL.cpp                # Singly Linked List (SLL)
│   ├── SampleDLL.cpp                # Standardized Singly/Doubly Linked List template
│   ├── SampleCLL.cpp                # Circular Doubly Linked List (CLL)
│   └── Sample_SortedLinkedLists.cpp # Merge Sort & Merging for Linked Lists
│
├── 2. Real-World Applications
│   └── Demo_BrowserHistory.cpp      # Web Browser History Simulation (Visit, Back, Forward)
│
└── 3. Multi-Language Benchmarks (N = 1,000,000 Nodes)
    ├── comparison.cpp               # C++ Benchmark (Windows PSAPI & High-res Clock)
    ├── compare.go                   # Go Benchmark (Runtime MemStats)
    ├── compare.java                 # Java Benchmark (JVM Runtime Memory)
    ├── compare.js                   # Node.js Benchmark (Perf Hooks & Heap Usage)
    └── compare.py                   # Python Benchmark (Psutil Memory Profiling)
```

---

## 🛠️ Detailed File Breakdown

### 1. Core Data Structures (C++ Generic Templates)

* **`SampleSLL.cpp`**
  * Implements a generic **Singly Linked List** using C++ templates (`template <typename T>`).
  * Features core methods: `AddHead`, `AddTail`, `Add_at_k_position`, `DeleteAtHead`, `DeleteAtTail`, `DeleteByValue`, `Traversal`, and `ClearList`.

* **`SampleDLL.cpp`**
  * Provides a standardized implementation of a linear linked list structure using C++ templates.

* **`SampleCLL.cpp`**
  * Implements a generic **Circular Doubly Linked List**.
  * Links the head and tail nodes to form a closed loop. Supports safe element insertion and deletion at arbitrary positions without risking infinite loops during traversal.

* **`Sample_SortedLinkedLists.cpp`**
  * Implements **Merge Sort** tailored specifically for linked lists with $O(N \log N)$ time complexity.
  * Employs the two-pointer (*tortoise and hare*) technique to split lists (`splitList`).
  * Includes list merging utilities (`mergeSortedLists`) to join two pre-sorted lists.

---

### 2. Real-World Application

* **`Demo_BrowserHistory.cpp`**
  * Simulates a browser history stack (similar to Chrome or Firefox) using a Doubly Linked List.
  * **Key Operations**:
    * `VisitPage`: Navigate to a new URL and automatically purge forward history branches.
    * `Back`: Navigate backward in history.
    * `Forward`: Navigate forward in history.
    * `GenerateCSVDataset`: Generates a simulated dataset file (`data.csv`) with $1,000,000$ entries.
    * `Stress Test & Memory Profiling`: Evaluates execution speed and memory consumption for $1,000,000$ visits alongside $200,000$ `Back` and $100,000$ `Forward` operations.

---

### 3. Multi-Language Benchmark Suite

All `compare.*` files perform standardized performance profiling on $N = 1,000,000$ nodes using a **Circular Linked List**:

1. **INSERT TAIL ($N = 1,000,000$)**: Measures insertion time ($O(1)$ per operation) and RAM growth (total MB & bytes/node).
2. **SEARCH Worst-Case**: Executes an $O(N)$ lookup for the last element in the circular list to evaluate read performance and memory stability.

| File | Language | Memory & Time Measurement Tools |
| :--- | :--- | :--- |
| `comparison.cpp` | **C++** | `<chrono>`, `windows.h`, `psapi.h` (`GetProcessMemoryInfo`) |
| `compare.go` | **Go** | `runtime.ReadMemStats`, `time.Now()` |
| `compare.java` | **Java** | `Runtime.getRuntime()`, `System.nanoTime()` |
| `compare.js` | **Node.js** | `process.memoryUsage()`, `perf_hooks` |
| `compare.py` | **Python** | `psutil.Process()`, `time.perf_counter()` |

---

## 🚀 Build & Run Instructions

### 1. C++
> **Note:** Benchmark and demo C++ files (`comparison.cpp`, `Demo_BrowserHistory.cpp`) utilize the Windows API (`psapi.lib`). Compilation on Windows (via MinGW, Clang, or MSVC) is recommended.

```bash
# Compile and run generic structure samples
g++ -O2 SampleSLL.cpp -o SampleSLL.exe
./SampleSLL.exe

# Compile C++ files requiring PSAPI library
g++ -O2 Demo_BrowserHistory.cpp -o Demo_BrowserHistory.exe -lpsapi
./Demo_BrowserHistory.exe

g++ -O2 comparison.cpp -o comparison.exe -lpsapi
./comparison.exe
```

### 2. Go
```bash
go run compare.go
```

### 3. Java
```bash
javac compare.java
java compare
```

### 4. Node.js
```bash
# Optional: expose garbage collection for manual GC invocation
node --expose-gc compare.js
```

### 5. Python
Requires `psutil` installed (`pip install psutil`):
```bash
python compare.py
```

---

## 📊 Benchmark Output Format

When running any benchmark script, output is formatted according to the following report standard:

```text
==================================================
BANG PHAN TICH BO NHO & THOI GIAN
==================================================
1. Thao tac INSERT TAIL (1000000 nodes):
   - Thoi gian chay   : ... ms
   - RAM tang them    : ... MB
   - Trung binh/Node  : ... bytes/node

2. Thao tac SEARCH Worst-Case (THANH CONG):
   - Thoi gian chay   : ... ms
   - RAM thay doi     : ... MB
```

---

## 💡 Implementation Details

* **Generics & Templates**: C++ samples utilize `template <typename T>` to allow flexible operations on various data types (`int`, `std::string`, custom structs).
* **Memory Management**: All C++ deletion operations feature explicit memory deallocation (`delete`, `ClearList`, `freeList`) to prevent memory leaks during stress testing.