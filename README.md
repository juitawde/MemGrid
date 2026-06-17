# 🧠 MemGrid – Distributed Shared Memory Directory Core

A C++ simulation of a **Distributed Shared Memory (DSM) System** that manages memory blocks across multiple computers in a cluster. The project demonstrates the practical application of Data Structures and Algorithms such as AVL Trees, Queues, Stacks, Priority Queues, Graphs, and Dijkstra's Algorithm in High Performance Computing (HPC) environments.

---

# 📌 2.2 Problem Statement

MemGrid is a system that allows multiple computers in a cluster to share a unified memory space. Traditional distributed memory systems often suffer from inconsistent memory tracking, lack of rollback support, inefficient request handling, poor cache utilization, and suboptimal communication paths.

The goal is to design and implement a system that efficiently manages shared memory locations, supports rollback operations, processes requests in order, verifies computer identities, ranks memory blocks by access frequency, models cluster topology, computes minimum-latency paths, and optimizes memory allocation.

---

# 🎯 2.3 Objectives

- ✅ Maintain a balanced index of all memory blocks.
- ✅ Support rollback of memory movements.
- ✅ Process memory requests in FIFO order.
- ✅ Verify computer identities efficiently.
- ✅ Rank memory blocks based on access frequency.
- ✅ Model network topology of cluster computers.
- ✅ Find shortest latency paths between nodes.
- ✅ Optimize memory allocation and reduce fragmentation.

---

# 🏗️ 2.4 System Overview / Architecture

### 🔹 Major Components

| Component | Purpose |
|------------|---------|
| 💻 Computer Manager | Stores computer details and memory information |
| 🧠 Memory Directory | Maintains indexed memory blocks |
| 📬 Request Handler | Handles incoming memory requests |
| 🔄 Rollback Manager | Restores previous memory states |
| 📈 Frequency Analyzer | Tracks most frequently accessed blocks |
| 🌐 Network Topology Manager | Maintains cluster connections |
| 🛣️ Path Finder | Finds minimum-latency routes |
| 📦 Memory Allocator | Allocates memory using Best-Fit strategy |

### 🔁 Architecture Flow

```text
💻 Computers
      │
      ▼
📦 Memory Allocation
      │
      ▼
🧠 AVL Memory Index
      │
      ├── 📬 Request Queue (FIFO)
      ├── 📈 Frequency Heap
      ├── 🔄 Rollback Stack
      └── 🌐 Network Graph
                    │
                    ▼
            🛣️ Dijkstra Algorithm
```

---

# 📚 2.5 Data Structures and Algorithms Used

| Requirement | Data Structure / Algorithm |
|------------|---------------------------|
| 🧠 Memory Block Indexing | AVL Tree |
| 💻 Computer Verification | Hash Map (`unordered_map`) |
| 📬 Request Processing | Queue (FIFO) |
| 🔄 Rollback Functionality | Stack (LIFO) |
| 📈 Access Frequency Ranking | Priority Queue (Max Heap) |
| 🌐 Cluster Topology | Graph (Adjacency List) |
| 🛣️ Shortest Path Calculation | Dijkstra's Algorithm |
| 📦 Memory Allocation | Best-Fit Strategy |

---

# ⚙️ 2.6 Implementation Approach

### Step 1️⃣
Register computers in the cluster along with their available memory.

### Step 2️⃣
Allocate memory blocks using the Best-Fit allocation strategy.

### Step 3️⃣
Store memory blocks in an AVL Tree for efficient searching and indexing.

### Step 4️⃣
Handle memory access requests using a FIFO Queue.

### Step 5️⃣
Track access frequency using a Priority Queue (Max Heap).

### Step 6️⃣
Move memory blocks between computers while recording changes in a Stack.

### Step 7️⃣
Perform rollback operations whenever required.

### Step 8️⃣
Create network connections between computers using a Graph.

### Step 9️⃣
Use Dijkstra's Algorithm to find minimum-latency communication paths.

---

# 📊 2.7 Time and Space Complexity Analysis

## ⏱️ Time Complexity

| Operation | Complexity |
|------------|-----------|
| Insert Memory Block (AVL) | O(log n) |
| Search Memory Block (AVL) | O(log n) |
| Verify Computer | O(1) |
| Add Request | O(1) |
| Process Request | O(1) |
| Rollback Operation | O(1) |
| Update Frequency Heap | O(log n) |
| Best-Fit Allocation | O(n) |
| Add Network Connection | O(1) |
| Dijkstra Shortest Path | O((V+E) log V) |

## 💾 Space Complexity

| Structure | Complexity |
|-----------|-----------|
| AVL Tree | O(n) |
| Hash Map | O(n) |
| Queue | O(n) |
| Stack | O(n) |
| Graph | O(V + E) |

---

# 🚀 2.8 Execution Steps

## 🔨 Compile

```bash
g++ memgrid.cpp -o memgrid
```

## ▶️ Run

```bash
./memgrid
```

## 📋 Available Operations

```text
1. Add Computer
2. Verify Computer
3. Allocate Memory Block
4. Search Memory Block
5. Display Memory Blocks
6. Move Memory Block
7. Undo Last Move
8. Add Request
9. Process Request
10. Access Memory Block
11. Show Most Used Blocks
12. Add Network Connection
13. Display Network
14. Find Shortest Path
15. Display Computers
16. Exit
```

---

# 📝 2.9 Sample Inputs and Outputs

## 💻 Add Computer

### Input

```text
Computer ID : 101
Total Memory : 500
```

### Output

```text
Computer Added Successfully
```

---

## 📦 Allocate Memory Block

### Input

```text
Block ID : 1
Block Size : 100
```

### Output

```text
Allocated To Computer 101
```

---

## 📬 Add Request

### Input

```text
Request ID : 1
Computer ID : 101
Block ID : 1
```

### Output

```text
Request Added
```

---

## 🛣️ Find Shortest Path

### Input

```text
Source : 101
Destination : 103
```

### Output

```text
Minimum Latency = 12
```

---

## 🔄 Undo Last Move

### Output

```text
Rollback Successful
Block restored to previous computer
```

---

# 📸 2.10 Screenshots

<img width="1401" height="592" alt="Screenshot 2026-06-17 at 3 53 07 AM" src="https://github.com/user-attachments/assets/b23c0313-ecf0-4044-95d8-982dbd8eff2f" />

<img width="1386" height="251" alt="Screenshot 2026-06-17 at 3 53 39 AM" src="https://github.com/user-attachments/assets/cbb264e6-253d-48c5-bf00-9e5b4d96b196" />

<img width="1376" height="588" alt="Screenshot 2026-06-17 at 3 54 26 AM" src="https://github.com/user-attachments/assets/8c2f153d-9d56-46b6-969c-ce228faf335d" />

<img width="1404" height="624" alt="Screenshot 2026-06-17 at 3 55 19 AM" src="https://github.com/user-attachments/assets/cad56a1f-842c-4a1c-bb11-79889b259181" />

<img width="1366" height="607" alt="Screenshot 2026-06-17 at 3 56 09 AM" src="https://github.com/user-attachments/assets/9b748f4d-0dd6-4027-8bf2-8b47b06751a5" />

<img width="1195" height="652" alt="Screenshot 2026-06-17 at 4 20 18 AM" src="https://github.com/user-attachments/assets/efefff0a-08ed-48f8-9e86-08877db00e19" />

<img width="1187" height="670" alt="Screenshot 2026-06-17 at 4 49 35 AM" src="https://github.com/user-attachments/assets/ca79da02-e50e-4e14-9a55-cdcd57897f5f" />

---

# 📈 2.11 Results and Observations

- ✅ AVL Tree provided fast and balanced memory indexing.
- ✅ Queue ensured fair and ordered request processing.
- ✅ Stack enabled efficient rollback functionality.
- ✅ Priority Queue successfully identified frequently accessed memory blocks.
- ✅ Dijkstra's Algorithm accurately computed minimum-latency paths.
- ✅ Best-Fit allocation improved memory utilization and reduced fragmentation.
- ✅ Hash Map enabled constant-time computer verification.

---

# ✅ 2.12 Conclusion

MemGrid successfully demonstrates a **Distributed Shared Memory Directory Core** using efficient Data Structures and Algorithms.

The project integrates:

- 🧠 AVL Trees for memory indexing
- 📬 Queues for request handling
- 🔄 Stacks for rollback operations
- 📈 Priority Queues for frequency analysis
- 🌐 Graphs for cluster topology
- 🛣️ Dijkstra's Algorithm for shortest path computation
- 📦 Best-Fit allocation for memory optimization

The system effectively simulates real-world distributed memory management concepts used in modern High Performance Computing (HPC) environments while showcasing the practical implementation of core DSA concepts in C++.

---

# 👨‍💻 Technologies Used

- 💻 C++
- 🌳 AVL Tree
- 📬 Queue
- 🔄 Stack
- 🗂️ Hash Map (`unordered_map`)
- 📈 Priority Queue (Max Heap)
- 🌐 Graphs
- 🛣️ Dijkstra's Algorithm
- 📦 Best-Fit Memory Allocation

---

⭐ If you found this project useful, consider giving it a star on GitHub!
