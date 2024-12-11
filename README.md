# **Data Structures Visualization Using SFML**

## **Overview**
This project is an interactive application to visualize various data structures using the **SFML** library. Users can:
- Select a data structure from a menu.
- Perform operations like insertion, deletion, and file import.
- *(Currently in progress)* Visualize the selected data structure.

While the menu and operations are functional, the visual representation of the ADTs is under development due to time constraints.

---

## **Features**
### **Implemented Data Structures**
- AVL Tree
- Binary Search Tree (BST)
- Red-Black Tree
- B-Tree
- Heap
- Stack and Queue
- Priority Queue

### **Functional Menu**
- Allows users to select an ADT and perform basic operations.

### **File Import**
- Load data for ADTs from a file.

---

## **Challenges**


#### 1. BST Selection Issue:
- Problem: BST was not appearing in the menu or incorrectly selected.
Resolution: Added missing break in the selectADT function to prevent falling through to the default case.

#### 2. Deletion in BST Not Working:
- Problem: The remove operation for BST wasn't prompting for a value and did not delete nodes properly.
Resolution: Updated performOperation to prompt for a value and fixed the BST::remove logic to handle all cases (leaf, one child, two children).

#### 3. Duplicate findMin Definition in BST:
- Problem: Multiple definitions of findMin caused a compilation error, and private Node access was blocked.
Resolution: Removed duplicate definitions and ensured findMin was declared and used correctly in the private section.

#### 4. Display for ADTs:
- Problem: ADTs like Stack, Queue, and BST were not rendering properly in the SFML window.
Resolution: Enhanced draw methods for all ADTs to visualize their structures using circles, text, and lines in SFML.

#### 5. Hardcoded Values in Insert/Remove Operations:
-Problem: Insert and remove operations used fixed values (e.g., 10 or 0), leading to incorrect functionality.
Resolution: Modified performOperation to prompt the user for dynamic input during these operations.

#### 6. Integration and Compilation Errors:
- problem: Missing files in compilation commands caused "undefined reference" and linkage errors.
Resolution: Updated g++ commands to include all source files and verified correct directory structures.

---

## **How to Build and Run**

### **Prerequisites**
- SFML 2.5.1 installed.
- A C++17-compatible compiler.
- Git for cloning the repository.

### **Setup Instructions**

#### **Clone the repository**:
```bash
git clone https://github.com/yourusername/DataStructuresVisualization.git
cd DataStructuresVisualization
