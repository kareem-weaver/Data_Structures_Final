#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <queue>
#include <functional>
#include <vector>

class PriorityQueue {
private:
    std::priority_queue<int> pq; // Max-heap implementation by default

public:
    PriorityQueue() {}
    void insert(int value);
    void removeTop();
    int peek() const;
    void display() const;
};

#endif // PRIORITYQUEUE_H
