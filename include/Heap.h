//
// Created by jabba on 11/24/2024.
//

#ifndef HEAP_H
#define HEAP_H

#pragma once
#include "ADTInterface.h"
#include <vector>

class Heap : public ADTInterface {
private:
    std::vector<int> heap;
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void insert(int value) override;
    void remove(int value) override;
    void display() const override;
    void loadFromFile(const std::string& filename) override;
};

#endif //HEAP_H
