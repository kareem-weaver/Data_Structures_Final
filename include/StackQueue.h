//
// Created by jabba on 11/24/2024.
//

#ifndef STACKQUEUE_H
#define STACKQUEUE_H

#pragma once
#include "ADTInterface.h"
#include <queue>

class Queue : public ADTInterface {
private:
    std::queue<int> q;

public:
    void insert(int value) override;
    void remove(int value) override;
    void display() const override;
    void loadFromFile(const std::string& filename) override;
};


#endif //STACKQUEUE_H
