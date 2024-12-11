#ifndef QUEUE_H
#define QUEUE_H

#include "ADTInterface.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Queue : public ADTInterface {
public:
    void insert(int value) override { enqueue(value); } // Alias for enqueue
    void remove(int value) override { dequeue(); }      // Alias for dequeue
    void draw(sf::RenderWindow& window, sf::Font& font) override;
    void loadFromFile(const std::string& filename) override;

    void enqueue(int value);
    void dequeue();

private:
    std::vector<int> queue;
};

#endif // QUEUE_H
