#ifndef HEAP_H
#define HEAP_H

#include "ADTInterface.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Heap : public ADTInterface {
    std::vector<int> heap;

    void heapifyUp(int index); // Declare heapifyUp
    void heapifyDown(int index); // Declare heapifyDown

public:
    void insert(int value) override;
    void remove(int value) override;
    void display() const override;
    void visualize(sf::RenderWindow& window, sf::Font& font) override;
    void loadFromFile(const std::string& filename) override;
};

#endif // HEAP_H
