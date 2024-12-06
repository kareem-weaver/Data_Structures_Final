#include "PriorityQueue.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void PriorityQueue::insert(int value) {
    pq.push(value);
}

void PriorityQueue::removeTop() {
    if (!pq.empty())
        pq.pop();
}

int PriorityQueue::peek() const {
    if (!pq.empty())
        return pq.top();
    return -1; // Indicates an empty queue
}

void PriorityQueue::display() const {
    std::priority_queue<int> temp = pq;
    while (!temp.empty()) {
        std::cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << std::endl;
}
