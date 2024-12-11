#ifndef STACK_H
#define STACK_H

#include "ADTInterface.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Stack : public ADTInterface {
public:
    void insert(int value) override { push(value); } // Alias for push
    void remove(int value) override { pop(); }      // Alias for pop
    void draw(sf::RenderWindow& window, sf::Font& font) override;
    void loadFromFile(const std::string& filename) override;

    void push(int value);
    void pop();

private:
    std::vector<int> stack;
};

#endif // STACK_H
