#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include "ADTInterface.h"
#include "Heap.h"
#include "BST.h"
#include <SFML/Graphics.hpp>

// Global ADT pointers
extern ADTInterface* currentADT;

// Function declarations
void selectADT(int option);
void performOperation(int operation);
void importFromFile();

#endif // GUIMANAGER_H
