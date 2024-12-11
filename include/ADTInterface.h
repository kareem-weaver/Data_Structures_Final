#ifndef ADT_INTERFACE_H
#define ADT_INTERFACE_H

#include <SFML/Graphics.hpp>
#include <string>

class ADTInterface {
public:
    virtual void insert(int value) = 0;
    virtual void remove(int value) = 0;
    virtual void draw(sf::RenderWindow& window, sf::Font& font) = 0;
    virtual void loadFromFile(const std::string& filename) = 0;
    virtual ~ADTInterface() = default;
};

#endif // ADT_INTERFACE_H
