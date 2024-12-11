#ifndef REDBLACK_H
#define REDBLACK_H

#include "../include/ADTInterface.h"
#include <SFML/Graphics.hpp>

class RedBlack : public ADTInterface {
public:
    RedBlack();
    ~RedBlack();

    void insert(int value) override;
    void remove(int value) override;
    void loadFromFile(const std::string& filename) override;
    void draw(sf::RenderWindow& window, sf::Font& font) override;

private:
    enum Color { RED, BLACK };

    struct Node {
        int data;
        Color color;
        Node* parent;
        Node* left;
        Node* right;
        Node(int value) : data(value), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
    };

    Node* root;
    Node* TNULL;

    void initializeTNULL();
    void deleteTree(Node* node);
    void insertFix(Node* node);
    void deleteFix(Node* node);
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    Node* minimum(Node* node);
    void drawNode(sf::RenderWindow& window, sf::Font& font, Node* node, int x, int y, int offset);
};

#endif // REDBLACK_H