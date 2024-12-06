#include "Heap.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <fstream>

void Heap::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

void Heap::remove(int value) {
    auto it = std::find(heap.begin(), heap.end(), value);
    if (it != heap.end()) {
        int index = std::distance(heap.begin(), it);
        std::swap(heap[index], heap.back());
        heap.pop_back();
        heapifyDown(index);
    }
}

void Heap::display() const {
    for (int val : heap) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void Heap::visualize(sf::RenderWindow& window, sf::Font& font) {
    if (heap.empty()) return;

    int x = window.getSize().x / 2; // Centered horizontally
    int y = 50; // Start near the top
    int xOffset = window.getSize().x / 4; // Horizontal spacing between nodes

    for (size_t i = 0; i < heap.size(); i++) {
        // Draw the node as a circle
        sf::CircleShape circle(20); // Radius = 20
        circle.setFillColor(sf::Color::Blue);
        circle.setPosition(x - 20, y - 20); // Center the circle
        window.draw(circle);

        // Draw the value inside the circle
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(heap[i]));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(x - 10, y - 15);
        window.draw(text);

        // Draw lines to children
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        if (leftChild < heap.size()) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
                sf::Vertex(sf::Vector2f(x - xOffset, y + 100), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
        }

        if (rightChild < heap.size()) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
                sf::Vertex(sf::Vector2f(x + xOffset, y + 100), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
        }

        // Move to the next position
        x += xOffset;
        if ((i + 1) & i == 0) { // Move to the next level
            y += 100;
            x = window.getSize().x / 2 - xOffset / 2;
            xOffset /= 2;
        }
    }
}


void Heap::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    int value;
    while (file >> value) {
        insert(value);
    }
}

void Heap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] > heap[parent]) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void Heap::heapifyDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (left < heap.size() && heap[left] > heap[largest]) {
        largest = left;
    }
    if (right < heap.size() && heap[right] > heap[largest]) {
        largest = right;
    }
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}
