#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../include/GUIManager.h"
#include "../include/Menu.h"
#include "../include/ADTInterface.h"
#include "../include/AVL.h"
#include "../include/BTree.h"
#include "../include/Heap.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Data Structures GUI");
    std::vector<std::string> mainMenuOptions = {"ADT Selection", "Operations", "Import from File"};
    Menu mainMenu(window.getSize().x, window.getSize().y, mainMenuOptions);

    std::vector<std::string> adtMenuOptions = {"Stack", "Queue", "BST", "Priority Queue", "AVL", "BTree", "Heap"};
    Menu adtMenu(window.getSize().x, window.getSize().y, adtMenuOptions);

    std::vector<std::string> operationsMenuOptions = {"Insert", "Delete", "Display"};
    Menu operationsMenu(window.getSize().x, window.getSize().y, operationsMenuOptions);

    int currentMenu = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (currentMenu == 0) { // Main Menu
                    if (event.key.code == sf::Keyboard::Up) mainMenu.moveUp();
                    else if (event.key.code == sf::Keyboard::Down) mainMenu.moveDown();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int selectedIndex = mainMenu.getSelectedItemIndex();
                        if (selectedIndex == 0) currentMenu = 1; // ADT Menu
                        else if (selectedIndex == 1) currentMenu = 2; // Operations Menu
                        else if (selectedIndex == 2) importFromFile();
                    }
                } else if (currentMenu == 1) { // ADT Menu
                    if (event.key.code == sf::Keyboard::Up) adtMenu.moveUp();
                    else if (event.key.code == sf::Keyboard::Down) adtMenu.moveDown();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        selectADT(adtMenu.getSelectedItemIndex());
                        currentMenu = 0; // Return to Main Menu
                    }
                } else if (currentMenu == 2) { // Operations Menu
                    if (event.key.code == sf::Keyboard::Up) operationsMenu.moveUp();
                    else if (event.key.code == sf::Keyboard::Down) operationsMenu.moveDown();
                    else if (event.key.code == sf::Keyboard::Enter) {
                        performOperation(operationsMenu.getSelectedItemIndex());
                        currentMenu = 0; // Return to Main Menu
                    }
                }
            }
        }

        window.clear();
        if (currentMenu == 0) mainMenu.draw(window);
        else if (currentMenu == 1) adtMenu.draw(window);
        else if (currentMenu == 2) operationsMenu.draw(window);
        window.display();
    }

    return 0;
}
