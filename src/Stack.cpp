#include "../include/Stack.h"
#include <fstream>
#include <iostream>

void Stack::push(int value) {
    stack.push_back(value);
}

void Stack::pop() {
    if (!stack.empty()) {
        stack.pop_back();
    } else {
        std::cerr << "Stack is empty. Cannot pop.\n";
    }
}

void Stack::draw(sf::RenderWindow& window, sf::Font& font) {
    if (stack.empty()) {
        sf::Text emptyText("Stack is empty.", font, 20);
        emptyText.setFillColor(sf::Color::Black);
        emptyText.setPosition(300, 300);
        window.draw(emptyText);
        return;
    }
    sf::Text title("Stack", font, 30);
    title.setPosition(50, 10);
    window.draw(title);

    for (size_t i = 0; i < stack.size(); ++i) {
        sf::RectangleShape box(sf::Vector2f(50, 50));
        box.setFillColor(sf::Color::White);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(2);
        box.setPosition(400, 50 + i * 60);
        window.draw(box);

        sf::Text valueText(std::to_string(stack[i]), font, 20);
        valueText.setFillColor(sf::Color::Black);
        valueText.setPosition(415, 55 + i * 60);
        window.draw(valueText);
    }
}

void Stack::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    int value;
    while (file >> value) {
        push(value);
    }
    file.close();
}
