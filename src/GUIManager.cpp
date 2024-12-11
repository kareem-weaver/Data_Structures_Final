#include "../include/Stack.h"
#include "../include/Queue.h"
#include <iostream>
#include "../include/GUIManager.h"
#include "../include/BST.h"
#include <limits> // For input validation

// Global Instances
Stack stackADT;
Queue queueADT;
BST bstADT;

// Define the global pointer
ADTInterface* currentADT = nullptr;

// Add cases in selectADT
void selectADT(int option) {
    switch (option) {
        case 0:
            currentADT = &stackADT;
            std::cout << "Stack selected.\n";
        break;
        case 1:
            currentADT = &queueADT;
            std::cout << "Queue selected.\n";
        break;
        case 2:
            currentADT = &bstADT;
            std::cout << "BST selected.\n";
        break;
        default:
            std::cerr << "Invalid ADT option.\n";
        currentADT = nullptr;
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

    currentADT->loadFromFile(filename);
    std::cout << "Data loaded from file: " << filename << "\n";
}

void performOperation(int operation) {
    if (!currentADT) {
        std::cerr << "No ADT selected. Please select an ADT first.\n";
        return;
    }

    switch (operation) {
        case 0: { // Insert
            int value;
            std::cout << "Enter the number to insert: ";
            while (!(std::cin >> value)) {
                std::cerr << "Invalid input. Please enter an integer: ";
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            }
            currentADT->insert(value);
            std::cout << "Inserted " << value << " into the selected ADT.\n";
            break;
        }
        case 1: {
            currentADT->remove(0); // 0 is a placeholder since no input is needed
            std::cout << "Removed the appropriate value from the selected ADT.\n";
            break;
        }
        break;
        case 2: { // Draw (Display)
            std::cout << "Displaying the selected ADT.\n";

            sf::RenderWindow window(sf::VideoMode(800, 600), "ADT Visualization");
            sf::Font font;
            if (!font.loadFromFile("/mnt/c/Users/jabba/Desktop/Morehouse_classes_2024-2025/Data Structures and Algorithms/Data_Structures_Final/resources/arial.ttf")) {
                std::cerr << "Error loading font.\n";
                return;
            }

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                window.clear(sf::Color::White);
                currentADT->draw(window, font);
                window.display();
            }
            break;
        }
        default:
            std::cerr << "Invalid operation.\n";
        break;
    }
}


