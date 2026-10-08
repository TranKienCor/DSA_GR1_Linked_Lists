const { performance } = require('perf_hooks');

class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

function getMemoryMB() {
    return process.memoryUsage().heapUsed / (1024 * 1024);
}

function insertTail(tail, val) {
    const newNode = new Node(val);
    if (!tail) {
        newNode.next = newNode;
        return newNode;
    } else {
        newNode.next = tail.next;
        tail.next = newNode;
        return newNode;
    }
}

function main() {
    let tail = null;
    const N = 1000000;

    console.log(`=== DANG CHAY CHUONG TRINH VOI N = ${N} ===`);

    // 1. Đo thời gian & RAM khi Insert
    if (global.gc) global.gc();
    const ramBeforeInsert = getMemoryMB();
    const startInsert = performance.now();

    for (let i = 1; i <= N; i++) {
        tail = insertTail(tail, i);
    }

    const endInsert = performance.now();
    const insertTime = endInsert - startInsert;
    const ramAfterInsert = getMemoryMB();

    // 2. Đo thời gian Search Worst-Case
    const ramBeforeSearch = getMemoryMB();
    const startSearch = performance.now();

    let found = false;
    const target = N;
    const head = tail.next;
    let curr = head;

    do {
        if (curr.data === target) {
            found = true;
            break;
        }
        curr = curr.next;
    } while (curr !== head);

    const endSearch = performance.now();
    const searchTime = endSearch - startSearch;
    const ramAfterSearch = getMemoryMB();

    // 3. Báo cáo
    console.log("\n==================================================");
    console.log("BANG PHAN TICH BO NHO & THOI GIAN");
    console.log("==================================================");
    console.log(`1. Thao tac INSERT TAIL (${N} nodes):`);
    console.log(`   - Thoi gian chay   : ${insertTime.toFixed(6)} ms`);
    console.log(`   - RAM tang them    : ${(ramAfterInsert - ramBeforeInsert).toFixed(6)} MB`);
    console.log(`   - Trung binh/Node  : ${(((ramAfterInsert - ramBeforeInsert) * 1024 * 1024) / N).toFixed(6)} bytes/node\n`);
    console.log(`2. Thao tac SEARCH Worst-Case (${found ? "THANH CONG" : "THAT BAI"}):`);
    console.log(`   - Thoi gian chay   : ${searchTime.toFixed(6)} ms`);
    console.log(`   - RAM thay doi     : ${(ramAfterSearch - ramBeforeSearch).toFixed(6)} MB`);
}

main();