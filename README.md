# **Data Structures Visualization Using SFML**

## **Overview**
This project is an interactive application to visualize various data structures using the **SFML** library. Users can:
- Select a data structure from a menu.
- Perform operations like insertion, deletion, and file import.
- Visualize the selected data structure in an intuitive graphical format.

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
- Supports dynamic input for insertion and deletion.

### **File Import**
- Load data for ADTs from a file for bulk operations.

### **Visualization**
- Uses SFML to render the data structures graphically, providing a clear representation of their hierarchy and relationships.

---

## **Challenges Addressed**

### **1. BST Selection Issue**
- **Problem**: BST was not appearing in the menu or was incorrectly selected.
- **Resolution**: Added a missing `break` in the `selectADT` function to prevent falling through to the default case.

### **2. Deletion in BST**
- **Problem**: The `remove` operation for BST wasn't prompting for a value and did not delete nodes properly.
- **Resolution**: Updated `performOperation` to prompt for a value and fixed the `BST::remove` logic to handle all cases (leaf, one child, two children).

### **4. Display for ADTs**
- **Problem**: ADTs like Stack, Queue, and BST were not rendering properly in the SFML window.
- **Resolution**: Enhanced `draw` methods for all ADTs to visualize their structures using circles, text, and lines in SFML.

### **6. Integration and Compilation Errors**
- **Problem**: Missing files in compilation commands caused "undefined reference" and linkage errors.
- **Resolution**: Updated `g++` commands to include all source files and verified correct directory structures.

### **8. B-Tree Deletion Issue**
- **Problem**: Attempting to delete a node in the B-Tree caused a segmentation fault, as shown in the following image:

![B-Tree Segmentation Fault](https://github.com/user-attachments/assets/e8f109af-402d-4523-890e-f87ea9b005bd)

- **Details**: When trying to remove a node, such as 50, the program crashes due to incorrect handling of pointers during the deletion process.
- **Resolution**: Further debugging is required to ensure proper pointer management and restructuring of the B-Tree after deletion.

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
```

#### **Compile the code**:
Use the following `g++` command to compile the project:
```bash
g++ src/main.cpp src/GUIManager.cpp src/Menu.cpp src/Stack.cpp src/Queue.cpp src/BST.cpp src/PriorityQueue.cpp src/AVL.cpp src/BTree.cpp src/Heap.cpp src/RedBlack.cpp -o ADT_GUI -Iinclude -lsfml-graphics -lsfml-window -lsfml-system
```

#### **Run the executable**:
```bash
./ADT_GUI
```

---

## **Usage**
1. Launch the application.
2. Use the menu to select a data structure.
3. Perform operations like insertion, deletion, or file loading.
4. Visualize the changes in real-time.

---

## **Known Issues**
- Visualization may not scale well for very large data sets.
- Some ADTs, like B-Tree and Red-Black Tree, require further refinement for edge cases.
- B-Tree deletion operation causes segmentation faults in certain scenarios.

---

## **Future Enhancements**
- Improve visualization scaling and layout for larger data sets.
- Integrate mouse and keyboard interactivity for better user experience.
- Add Makefile
---

## **Contributors**
- [Kareem Weaver](https://github.com/kareem-weaver/Data_Structures_Final/tree/main)
