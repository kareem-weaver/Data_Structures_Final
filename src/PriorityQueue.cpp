//
// Created by jabba on 11/24/2024.
//

#include "PriorityQueue.h"
#include <iostream>

void PriorityQueue::insert(int value) {
    pq.push(value);
}

void PriorityQueue::remove(int value) {
    // Priority queues do not support direct removal of arbitrary elements.
    // Placeholder for advanced removal logic.
}

void PriorityQueue::display() const {
    std::priority_queue<int> temp = pq;
    while (!temp.empty()) {
        std::cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << std::endl;
}

void PriorityQueue::loadFromFile(const std::string& filename) {
    // Placeholder for file loading logic
}
