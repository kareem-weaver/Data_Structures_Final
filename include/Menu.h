#ifndef MENU_H
#define MENU_H

#include <vector>
#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(float width, float height, const std::vector<std::string>& options);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
    std::vector<sf::RectangleShape> borders;
};

#endif // MENU_H
