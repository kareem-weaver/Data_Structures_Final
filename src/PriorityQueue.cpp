#include "PriorityQueue.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <queue>

void PriorityQueue::insert(int value) {
    queue.push(value);
}

void PriorityQueue::remove(int value) {
    std::priority_queue<int, std::vector<int>, std::greater<int>> tempQueue;

    while (!queue.empty()) {
        int top = queue.top();
        queue.pop();
        if (top != value) {
            tempQueue.push(top);
        }
    }

    queue = tempQueue;
}

void PriorityQueue::display() const {
    std::priority_queue<int, std::vector<int>, std::greater<int>> tempQueue = queue;

    while (!tempQueue.empty()) {
        std::cout << tempQueue.top() << " ";
        tempQueue.pop();
    }
    std::cout << std::endl;
}

void PriorityQueue::visualize(sf::RenderWindow& window, sf::Font& font) {
    if (queue.empty()) return;

    std::priority_queue<int, std::vector<int>, std::greater<int>> tempQueue = queue;

    int x = 50; // Starting x position
    int y = window.getSize().y / 2; // Center vertically
    int spacing = 50; // Spacing between elements

    while (!tempQueue.empty()) {
        int value = tempQueue.top();
        tempQueue.pop();

        // Draw the element as a rectangle
        sf::RectangleShape rect(sf::Vector2f(40, 40));
        rect.setFillColor(sf::Color::Cyan);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(2);
        rect.setPosition(x, y);
        window.draw(rect);

        // Draw the value inside the rectangle
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(value));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x + 10, y + 5);
        window.draw(text);

        // Move to the next position
        x += spacing;
    }
}
