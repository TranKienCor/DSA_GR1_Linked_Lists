package main

import (
	"fmt"
	"runtime"
	"time"
)

type Node struct {
	data int
	next *Node
}

func getMemoryMB() float64 {
	var m runtime.MemStats
	runtime.ReadMemStats(&m)
	return float64(m.Alloc) / (1024 * 1024)
}

func insertTail(tail *Node, val int) *Node {
	newNode := &Node{data: val}
	if tail == nil {
		newNode.next = newNode
		return newNode
	} else {
		newNode.next = tail.next
		tail.next = newNode
		return newNode
	}
}

func main() {
	var tail *Node
	N := 1000000

	fmt.Printf("=== DANG CHAY CHUONG TRINH VOI N = %d ===\n", N)

	// 1. Đo thời gian & RAM khi Insert
	runtime.GC()
	ramBeforeInsert := getMemoryMB()
	startInsert := time.Now()

	for i := 1; i <= N; i++ {
		tail = insertTail(tail, i)
	}

	insertTime := time.Since(startInsert).Seconds() * 1000
	ramAfterInsert := getMemoryMB()

	// 2. Đo thời gian Search Worst-Case
	ramBeforeSearch := getMemoryMB()
	startSearch := time.Now()

	found := false
	target := N
	head := tail.next
	curr := head

	for {
		if curr.data == target {
			found = true
			break
		}
		curr = curr.next
		if curr == head {
			break
		}
	}

	searchTime := time.Since(startSearch).Seconds() * 1000
	ramAfterSearch := getMemoryMB()

	// 3. Báo cáo
	status := "THAT BAI"
	if found {
		status = "THANH CONG"
	}

	fmt.Println("\n==================================================")
	fmt.Println("BANG PHAN TICH BO NHO & THOI GIAN")
	fmt.Println("==================================================")
	fmt.Printf("1. Thao tac INSERT TAIL (%d nodes):\n", N)
	fmt.Printf("   - Thoi gian chay   : %.6f ms\n", insertTime)
	fmt.Printf("   - RAM tang them    : %.6f MB\n", ramAfterInsert-ramBeforeInsert)
	fmt.Printf("   - Trung binh/Node  : %.6f bytes/node\n\n", ((ramAfterInsert-ramBeforeInsert)*1024*1024)/float64(N))
	fmt.Printf("2. Thao tac SEARCH Worst-Case (%s):\n", status)
	fmt.Printf("   - Thoi gian chay   : %.6f ms\n", searchTime)
	fmt.Printf("   - RAM thay doi     : %.6f MB\n", ramAfterSearch-ramBeforeSearch)
}