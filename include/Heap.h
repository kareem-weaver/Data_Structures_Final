#ifndef HEAP_H
#define HEAP_H

#include "ADTInterface.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Heap : public ADTInterface {
public:
    void insert(int value) override;
    void remove(int value) override;
    void draw(sf::RenderWindow& window, sf::Font& font) override;
    void loadFromFile(const std::string& filename) override;

private:
    std::vector<int> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);
};

#endif // HEAP_H
