#ifndef BST_H
#define BST_H

#include "ADTInterface.h"
#include <SFML/Graphics.hpp>
#include <string>

class BST : public ADTInterface {
public:
    BST();
    ~BST();

    void insert(int value) override;
    void remove(int value) override;
    void draw(sf::RenderWindow& window, sf::Font& font) override;
    void loadFromFile(const std::string& filename) override;

private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Helper functions
    Node* insertNode(Node* node, int value);
    Node* removeNode(Node* node, int value);
    Node* findMin(Node* node);
    void deleteTree(Node* node);
    void drawNode(sf::RenderWindow& window, sf::Font& font, Node* node, int x, int y, int offset);
};

#endif // BST_H
