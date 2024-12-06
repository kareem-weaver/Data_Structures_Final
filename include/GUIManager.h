
#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "ADTInterface.h"
#include "Heap.h"
#include "BST.h"
#include "AVL.h"
#include "BTree.h"
#include "PriorityQueue.h"
#include "StackQueue.h"
#include "RedBlack.h"

// Manages current ADT selection and menu operations
void selectADT(int option);
void performOperation(int operation);
void importFromFile();

#endif // GUIMANAGER_H
