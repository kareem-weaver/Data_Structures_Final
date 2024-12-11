#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "ADTInterface.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

class PriorityQueue : public ADTInterface {
public:
    PriorityQueue();

    void insert(int value) override;
    void remove(int value) override;
    void draw(sf::RenderWindow& window, sf::Font& font) override;
    void loadFromFile(const std::string& filename) override;

private:
    std::vector<int> heap;

    // Helper functions
    void heapifyUp(int index);
    void heapifyDown(int index);
    void drawNode(sf::RenderWindow& window, sf::Font& font, int index, int x, int y, int offset);
};

#endif // PRIORITYQUEUE_H
