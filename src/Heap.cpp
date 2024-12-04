//
// Created by jabba on 11/24/2024.
//

#include "Heap.h"
#include <iostream>
#include <algorithm>

void Heap::heapifyUp(int index) {
    if (index == 0) return;
    int parent = (index - 1) / 2;
    if (heap[parent] < heap[index]) {
        std::swap(heap[parent], heap[index]);
        heapifyUp(parent);
    }
}

void Heap::heapifyDown(int index) {
    int left = 2 * index + 1, right = 2 * index + 2, largest = index;
    if (left < heap.size() && heap[left] > heap[largest]) largest = left;
    if (right < heap.size() && heap[right] > heap[largest]) largest = right;
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

void Heap::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

void Heap::remove(int value) {
    auto it = std::find(heap.begin(), heap.end(), value);
    if (it != heap.end()) {
        *it = heap.back();
        heap.pop_back();
        heapifyDown(std::distance(heap.begin(), it));
    }
}

void Heap::display() const {
    for (int val : heap) std::cout << val << " ";
    std::cout << std::endl;
}

void Heap::loadFromFile(const std::string& filename) {
    // Placeholder for file loading logic
}
