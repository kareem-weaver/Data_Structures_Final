#ifndef BST_H
#define BST_H

#include "ADTInterface.h"
#include <SFML/Graphics.hpp>

struct Node {
    int value;
    int x, y; // For visualization
    Node* left;
    Node* right;
    Node(int val) : value(val), x(0), y(0), left(nullptr), right(nullptr) {}
};

class BST : public ADTInterface {
    Node* root;

    void insert(Node*& node, int value);
    void remove(Node*& node, int value);
    void deleteTree(Node* node);
    void display(Node* node) const;
    void calculatePositions(Node* node, int x, int y, int xOffset);
    void drawTree(Node* node, sf::RenderWindow& window, sf::Font& font);

public:
    BST();
    ~BST();
    void insert(int value) override;
    void remove(int value) override;
    void display() const override;
    void loadFromFile(const std::string& filename) override;
    void visualize(sf::RenderWindow& window, sf::Font& font) override;
};

#endif // BST_H
