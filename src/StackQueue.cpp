#include "StackQueue.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>

void StackQueue::enqueue(int value) {
    s1.push(value);
}

int StackQueue::dequeue() {
    if (s2.empty()) {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
    }

    if (!s2.empty()) {
        int value = s2.top();
        s2.pop();
        return value;
    }

    return -1; // Indicates empty queue
}

void StackQueue::display() const {
    std::stack<int> temp1 = s1, temp2 = s2;

    while (!temp2.empty()) {
        std::cout << temp2.top() << " ";
        temp2.pop();
    }

    std::stack<int> reversedStack;
    while (!temp1.empty()) {
        reversedStack.push(temp1.top());
        temp1.pop();
    }

    while (!reversedStack.empty()) {
        std::cout << reversedStack.top() << " ";
        reversedStack.pop();
    }
    std::cout << std::endl;
}

void StackQueue::visualize(sf::RenderWindow& window, sf::Font& font) {
    int x = 50; // Starting x position
    int y = 50; // Starting y position

    // Draw the stack
    sf::Text stackLabel;
    stackLabel.setFont(font);
    stackLabel.setString("Stack:");
    stackLabel.setCharacterSize(20);
    stackLabel.setFillColor(sf::Color::White);
    stackLabel.setPosition(x, y);
    window.draw(stackLabel);

    y += 30; // Move down for stack contents
    for (int value : stack) {
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(x, y);
        window.draw(circle);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(value));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(x + 10, y + 5);
        window.draw(text);

        y += 50; // Move down for the next stack element
    }

    // Draw the queue
    x += 150; // Move right for queue
    y = 50;   // Reset y position
    sf::Text queueLabel;
    queueLabel.setFont(font);
    queueLabel.setString("Queue:");
    queueLabel.setCharacterSize(20);
    queueLabel.setFillColor(sf::Color::White);
    queueLabel.setPosition(x, y);
    window.draw(queueLabel);

    y += 30; // Move down for queue contents
    for (int value : queue) {
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Blue);
        circle.setPosition(x, y);
        window.draw(circle);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(value));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(x + 10, y + 5);
        window.draw(text);

        x += 50; // Move right for the next queue element
    }
}


void StackQueue::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    int value;
    while (file >> value) {
        enqueue(value);
    }
    file.close();
}
