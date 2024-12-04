//
// Created by jabba on 11/24/2024.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#pragma once
#include "ADTInterface.h"
#include <queue>

class PriorityQueue : public ADTInterface {
private:
    std::priority_queue<int> pq;

public:
    void insert(int value) override;
    void remove(int value) override;
    void display() const override;
    void loadFromFile(const std::string& filename) override;
};


#endif //PRIORITYQUEUE_H
