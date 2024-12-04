//
// Created by jabba on 11/24/2024.
//
#include "ADTInterface.h"
#include "Heap.h"
#include "BST.h"

// Global pointers to current ADT
ADTInterface* currentADT = nullptr;
Heap heapADT;
BST bstADT;

// Menu Actions
void selectADT(int option) {
    if (option == 0) currentADT = &heapADT;
    else if (option == 1) currentADT = &bstADT;
}

void performOperation(int operation) {
    if (currentADT) {
        if (operation == 0) currentADT->insert(10);
        else if (operation == 1) currentADT->remove(10);
        else if (operation == 2) currentADT->display();
    }
}
