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
    // Placeholder visualization logic
    std::cout << "Visualizing StackQueue (placeholder)" << std::endl;
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
