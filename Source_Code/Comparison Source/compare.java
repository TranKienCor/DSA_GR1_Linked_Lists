public class compare {

    static class Node {
        int data;
        Node next;

        Node(int data) {
            this.data = data;
        }
    }

    private static double getMemoryMB() {
        Runtime runtime = Runtime.getRuntime();
        return (double) (runtime.totalMemory() - runtime.freeMemory()) / (1024 * 1024);
    }

    private static Node insertTail(Node tail, int val) {
        Node newNode = new Node(val);
        if (tail == null) {
            newNode.next = newNode;
            return newNode;
        } else {
            newNode.next = tail.next;
            tail.next = newNode;
            return newNode;
        }
    }

    public static void main(String[] args) {
        Node tail = null;
        int N = 1000000;

        System.out.println("=== DANG CHAY CHUONG TRINH VOI N = " + N + " ===");

        // 1. Đo thời gian & RAM khi Insert
        System.gc(); // Gợi ý dọn dẹp trước khi đo
        double ramBeforeInsert = getMemoryMB();
        long startInsert = System.nanoTime();

        for (int i = 1; i <= N; i++) {
            tail = insertTail(tail, i);
        }

        long endInsert = System.nanoTime();
        double insertTime = (endInsert - startInsert) / 1_000_000.0;
        double ramAfterInsert = getMemoryMB();

        // 2. Đo thời gian Search Worst-Case
        double ramBeforeSearch = getMemoryMB();
        long startSearch = System.nanoTime();

        boolean found = false;
        int target = N;
        Node head = tail.next;
        Node curr = head;

        do {
            if (curr.data == target) {
                found = true;
                break;
            }
            curr = curr.next;
        } while (curr != head);

        long endSearch = System.nanoTime();
        double searchTime = (endSearch - startSearch) / 1_000_000.0;
        double ramAfterSearch = getMemoryMB();

        // 3. Báo cáo
        System.out.printf("\n==================================================\n");
        System.out.printf("BANG PHAN TICH BO NHO & THOI GIAN\n");
        System.out.printf("==================================================\n");
        System.out.printf("1. Thao tac INSERT TAIL (%d nodes):\n", N);
        System.out.printf("   - Thoi gian chay   : %.6f ms\n", insertTime);
        System.out.printf("   - RAM tang them    : %.6f MB\n", (ramAfterInsert - ramBeforeInsert));
        System.out.printf("   - Trung binh/Node  : %.6f bytes/node\n\n", ((ramAfterInsert - ramBeforeInsert) * 1024 * 1024) / N);
        System.out.printf("2. Thao tac SEARCH Worst-Case (%s):\n", (found ? "THANH CONG" : "THAT BAI"));
        System.out.printf("   - Thoi gian chay   : %.6f ms\n", searchTime);
        System.out.printf("   - RAM thay doi     : %.6f MB\n", (ramAfterSearch - ramBeforeSearch));
    }
}