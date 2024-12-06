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
    // Placeholder for visualization logic
    std::cout << "Visualizing Heap (placeholder)" << std::endl;
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
