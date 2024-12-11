#ifndef HEAP_H
#define HEAP_H

#include "../include/ADTInterface.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Heap : public ADTInterface {
public:
    Heap();

    void insert(int value) override;
    void remove(int value) override;
    void loadFromFile(const std::string& filename) override;
    void draw(sf::RenderWindow& window, sf::Font& font) override;

private:
    std::vector<int> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void drawNode(sf::RenderWindow& window, sf::Font& font, int index, int x, int y, int offset);
};

#endif // HEAP_H