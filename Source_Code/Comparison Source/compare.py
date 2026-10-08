import os
import time
import psutil


class Node:

  def __init__(self, val):
    self.data = val
    self.next = None


def get_memory_mb():
  process = psutil.Process(os.getpid())
  return process.memory_info().rss / (1024 * 1024)


def insert_tail(tail, val):
  new_node = Node(val)
  if tail is None:
    new_node.next = new_node
    return new_node
  else:
    new_node.next = tail.next
    tail.next = new_node
    return new_node


def main():
  tail = None
  N = 1000000

  print(f"=== DANG CHAY CHUONG TRINH VOI N = {N} ===")

  # 1. Đo thời gian & RAM khi Insert
  ram_before_insert = get_memory_mb()
  start_insert = time.perf_counter()

  for i in range(1, N + 1):
    tail = insert_tail(tail, i)

  end_insert = time.perf_counter()
  insert_time = (end_insert - start_insert) * 1000
  ram_after_insert = get_memory_mb()

  # 2. Đo thời gian Search Worst-Case
  ram_before_search = get_memory_mb()
  start_search = time.perf_counter()

  found = False
  target = N
  head = tail.next
  curr = head

  while True:
    if curr.data == target:
      found = True
      break
    curr = curr.next
    if curr == head:
      break

  end_search = time.perf_counter()
  search_time = (end_search - start_search) * 1000
  ram_after_search = get_memory_mb()

  # 3. Báo cáo
  print("\n==================================================")
  print("BANG PHAN TICH BO NHO & THOI GIAN")
  print("==================================================")
  print(f"1. Thao tac INSERT TAIL ({N} nodes):")
  print(f"   - Thoi gian chay   : {insert_time:.6f} ms")
  print(f"   - RAM tang them    : {ram_after_insert - ram_before_insert:.6f} MB")
  print(
      "   - Trung binh/Node  :"
      f" {((ram_after_insert - ram_before_insert) * 1024 * 1024) / N:.6f}"
      " bytes/node\n"
  )
  print(f"2. Thao tac SEARCH Worst-Case ({'THANH CONG' if found else 'THAT BAI'}):")
  print(f"   - Thoi gian chay   : {search_time:.6f} ms")
  print(f"   - RAM thay doi     : {ram_after_search - ram_before_search:.6f} MB")


if __name__ == "__main__":
  main()