#include "Heap.h"
#include "BST.h"
#include "AVL.h"
#include "BTree.h"
#include "PriorityQueue.h"
#include "StackQueue.h"
#include "RedBlack.h"
#include "Menu.h"
#include <iostream>
#include <fstream>
#include <algorithm>
// Global pointers to current ADT
ADTInterface* currentADT = nullptr;
Heap heapADT;
BST bstADT;

// Menu Actions
void selectADT(int option) {
    switch (option) {
        case 0:
            currentADT = &heapADT; // Example for Heap
            break;
        case 1:
            currentADT = &bstADT; // Example for BST
            break;
        // Add cases for other ADTs
        default:
            std::cerr << "Invalid ADT option." << std::endl;
            currentADT = nullptr; // Reset if invalid
            break;
    }
}


void performOperation(int operation) {
    if (!currentADT) {
        std::cerr << "No ADT selected. Please select an ADT first.\n";
        return;
    }

    switch (operation) {
        case 0:
            currentADT->insert(10); // Example value
        std::cout << "Inserted 10 into the ADT.\n";
        break;
        case 1:
            currentADT->remove(10);
        std::cout << "Removed 10 from the ADT.\n";
        break;
        case 2:
            currentADT->display();
        break;
        default:
            std::cerr << "Invalid operation.\n";
        break;
    }
}

void importFromFile() {
    if (!currentADT) {
        std::cerr << "No ADT selected. Please select an ADT first.\n";
        return;
    }

    std::string filename;
    std::cout << "Enter filename to import: ";
    std::cin >> filename;

    currentADT->loadFromFile(filename); // Delegate to the current ADT
}

// Adding instances for RedBlack and StackQueue ADTs
RedBlackTree redBlackADT;
StackQueue stackQueueADT;
