#ifndef STACKQUEUE_H
#define STACKQUEUE_H

#include "ADTInterface.h"
#include <SFML/Graphics.hpp>
#include <stack>

class StackQueue : public ADTInterface {
    std::stack<int> s1, s2;

public:
    void enqueue(int value);
    int dequeue();
    void display() const override;
    void visualize(sf::RenderWindow& window, sf::Font& font) override; // Add declaration
    void insert(int value) override { enqueue(value); }
    void remove(int value) override { dequeue(); }
    void loadFromFile(const std::string& filename) override;
};

#endif // STACKQUEUE_H
