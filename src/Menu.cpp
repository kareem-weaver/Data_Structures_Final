#include "../include/Menu.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Menu::Menu(float width, float height, const std::vector<std::string>& options)
    : selectedItemIndex(0) {
    if (!font.loadFromFile("/mnt/c/Users/jabba/Desktop/Morehouse_classes_2024-2025/Data Structures and Algorithms/Data_Structures_Final/resources/arial.ttf")) {
        std::cerr << "Error loading font\n";
    }

    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text item;
        item.setFont(font);
        item.setString(options[i]);
        item.setCharacterSize(30);
        item.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        item.setPosition(sf::Vector2f(width / 2 - 100, height / 2 - 100 + i * 50));
        menuItems.push_back(item);

        sf::RectangleShape border(sf::Vector2f(300, 40));
        border.setFillColor(sf::Color::Transparent);
        border.setOutlineThickness(2);
        border.setOutlineColor(i == 0 ? sf::Color::Red : sf::Color::White);
        border.setPosition(item.getPosition().x - 10, item.getPosition().y - 5);
        borders.push_back(border);
    }
}

void Menu::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < menuItems.size(); ++i) {
        window.draw(borders[i]);
        window.draw(menuItems[i]);
    }
}

void Menu::moveUp() {
    if (selectedItemIndex > 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        borders[selectedItemIndex].setOutlineColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
        borders[selectedItemIndex].setOutlineColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex < menuItems.size() - 1) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        borders[selectedItemIndex].setOutlineColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
        borders[selectedItemIndex].setOutlineColor(sf::Color::Red);
    }
}

int Menu::getSelectedItemIndex() const {
    return selectedItemIndex;
}
