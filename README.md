# Student Records Management System (Binary Search Tree)

An efficient, object-oriented Student Database Management System developed in C++. The project uses a custom-built **Binary Search Tree (BST)** data structure to handle data tracking, retrieval, and sorting of student records according to their Unique IDs, alongside a custom **Queue-based Linked List** implementation to handle breadth-first (level-order) tree operations.

---

## 🏗️ Architecture & Data Structures

The project is modularized into cohesive classes and object definitions:
1. **Student Class (`Student.h / .cpp`):** Manages essential record fields including Name, Student ID, Home Address, Date of Birth, Phone Number, Course Name, and CGPA. Outlines custom logic operators to compare primary identification numbers.
2. **Binary Tree Node (`BTNode.h / .cpp`):** Struct capturing a single tree entry. It nests a `Student` instance as its payload alongside structural pointers indicating its `left` and `right` children.
3. **Queue / Linked List (`Queue.h / .cpp`, `Node.h / .cpp`):** A auxiliary FIFO linked list managing dynamic pointers to tree nodes (`BTNode*`). Primarily leveraged during top-down tree levels inspection.
4. **Binary Search Tree Engine (`BST.h / .cpp`):** Governs fundamental data indexing logic (Binary Insertion, Node Erasure, Subtree Cloning, Tree Depth calculation, and Traversal operations).

---

## 🚀 Key Features & Operations

* **Efficient Data Operations:** Automated binary sorting arrangement upon inserting records into the BST context based on numerical Student ID profiles.
* **Flexible Visualizations:** * Standard Tree Traversals: `Pre-Order`, `In-Order`, and `Post-Order`.
  * Multi-Directional Outputs: View records instantly grouped in sorted `Ascending` or `Descending` sequences.
  * Level-Order Tracing: Traverses data layers dynamically from the tree peak downward utilizing the custom Queue layout.
* **Deepest Nodes Identifier:** Dynamically evaluates total branch heights to print information stored only at the lowest tier branches of the database tree.
* **Subtree Isolation/Cloning:** Extracts and clones an entire branch segment from an external source array into a clean container given a target item boundary condition.

---

## 🛠️ Environment Configuration & Building

### Target Environment
* Native C++ Compiler (GCC / MinGW or Microsoft Visual Studio)

### Development Configurations
If compiling the code inside **Microsoft Visual Studio**, you might encounter standard compiler configuration alerts regarding legacy C-string methods (`strcpy`). This can be seamlessly handled by bypassing secure check policies inside your project configurations:
1. Navigate to your Project Properties.
2. Go to **C/C++** -> **Preprocessor**.
3. Append `_CRT_SECURE_NO_WARNINGS` to your **Preprocessor Definitions**.

### Compilation
Compile all code modules concurrently using a terminal environment or your preferred integrated IDE:
```bash
g++ -o StudentSystem main.cpp BST.cpp BTNode.cpp Node.cpp Queue.cpp Student.cpp
