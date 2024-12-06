
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
    std::vector<sf::Text> menuItems;
    std::vector<sf::RectangleShape> borders;
    sf::Font font;
    int selectedItemIndex;

public:
    Menu(float width, float height, const std::vector<std::string>& options);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;
};

#endif // MENU_H
