#include "../include/PriorityQueue.h"
#include <iostream>
#include <fstream>
#include <cmath> // For visualization positioning
PriorityQueue::PriorityQueue() {}

void PriorityQueue::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

void PriorityQueue::remove(int value) {
    if (heap.empty()) {
        std::cerr << "Priority queue is empty. Cannot remove.\n";
        return;
    }

    // Replace root with the last element
    if (value == heap.front()) {
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        std::cout << "Removed " << value << " from the priority queue.\n";
    } else {
        std::cerr << "Only the highest priority element can be removed.\n";
    }
}

void PriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent]) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void PriorityQueue::heapifyDown(int index) {
    int leftChild, rightChild, smallest;
    while (true) {
        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;
        smallest = index;

        if (leftChild < heap.size() && heap[leftChild] < heap[smallest])
            smallest = leftChild;

        if (rightChild < heap.size() && heap[rightChild] < heap[smallest])
            smallest = rightChild;

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

void PriorityQueue::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    int value;
    while (file >> value) {
        insert(value);
    }
    file.close();
}

void PriorityQueue::draw(sf::RenderWindow& window, sf::Font& font) {
    if (heap.empty()) {
        sf::Text emptyText("Priority Queue is empty.", font, 20);
        emptyText.setFillColor(sf::Color::Black);
        emptyText.setPosition(300, 300);
        window.draw(emptyText);
        return;
    }

    drawNode(window, font, 0, 400, 50, 200);
}

void PriorityQueue::drawNode(sf::RenderWindow& window, sf::Font& font, int index, int x, int y, int offset) {
    if (index >= heap.size()) return;

    // Draw connections to children
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < heap.size()) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x - offset + 20, y + 100), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawNode(window, font, leftChild, x - offset, y + 100, offset / 2);
    }
    if (rightChild < heap.size()) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x + offset + 20, y + 100), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawNode(window, font, rightChild, x + offset, y + 100, offset / 2);
    }

    // Draw the node itself
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(x, y);
    window.draw(circle);

    sf::Text valueText(std::to_string(heap[index]), font, 20);
    valueText.setFillColor(sf::Color::Black);
    valueText.setPosition(x + 10, y + 5);
    window.draw(valueText);
}
