#ifndef ADTINTERFACE_H
#define ADTINTERFACE_H

#include <SFML/Graphics.hpp>
#include <string>

class ADTInterface {
public:
    virtual ~ADTInterface() = default; // Virtual destructor
    virtual void insert(int value) = 0; // Insert a value
    virtual void remove(int value) = 0; // Remove a value
    virtual void display() const = 0; // Display contents (console)
    virtual void visualize(sf::RenderWindow& window, sf::Font& font) = 0; // Visualize (SFML)
    virtual void loadFromFile(const std::string& filename) = 0; // Load data from a file
};

#endif // ADTINTERFACE_H
