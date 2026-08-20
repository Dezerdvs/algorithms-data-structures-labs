# Algorithms & Data Structures Labs (C++)

A collection of classic data structure and algorithm implementations written from scratch in C++, built for a university Algorithms & Data Structures course. Each lab is self-contained and benchmarks its own implementation.

## What's inside

| Folder | Data structure / algorithm |
|---|---|
| `lab3-queue/` | Custom `Cherga` (Queue) and `PriorityCherga` (Priority Queue), with operations like multiplying two queues element-wise and reversing a stack via a queue |
| `lab4-avl-redblack-tree/` | Self-balancing binary search trees: **AVL Tree** and **Red-Black Tree**, with random insertion and timing comparison between the two |
| `lab5/` | Indexed d-ary priority queue used to implement and compare **Dijkstra's algorithm** and the **Floyd–Warshall algorithm** for all-pairs shortest paths on a weighted graph |
| `lab6/` | **Quicksort** implementation (Lomuto partition scheme) |
| `lab7/` | Custom hash table (hopscotch-style open addressing) comparing two hashing strategies — **multiplication method** vs **folding method** |

## Tech stack

C++ (Windows/MSVC, uses `<chrono>` for timing and `<windows.h>` in a couple of labs), no external libraries — everything (trees, queues, hash tables, graph algorithms) is implemented manually.

## Building & running

Each lab folder is a standalone `main.cpp` (plus its own headers). Compile any lab directly, e.g.:

```bash
g++ -std=c++17 lab4-avl-redblack-tree/main.cpp lab4-avl-redblack-tree/AVLTree.cpp lab4-avl-redblack-tree/RedBlackTree.cpp -o lab4
./lab4
```

## Why it matters

These labs demonstrate hands-on understanding of core CS fundamentals — tree balancing, shortest-path algorithms, hashing, and sorting — implemented without relying on standard library containers for the core logic, plus practical performance benchmarking of the results.
