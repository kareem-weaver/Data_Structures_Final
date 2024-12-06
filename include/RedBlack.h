#ifndef REDBLACK_H
#define REDBLACK_H

#include "ADTInterface.h"
#include <SFML/Graphics.hpp>

class RBNode {
public:
    int key;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    bool color; // true for Red, false for Black

    RBNode(int key) : key(key), left(nullptr), right(nullptr), parent(nullptr), color(true) {}
};

class RedBlackTree : public ADTInterface {
    RBNode* root;

    void rotateLeft(RBNode*& node);
    void rotateRight(RBNode*& node);
    void fixViolation(RBNode*& node);
    void deleteTree(RBNode* node);

public:
    RedBlackTree() : root(nullptr) {}
    ~RedBlackTree() { deleteTree(root); }
    void insert(int key) override;
    void remove(int key) override;
    void display() const override;
    void visualize(sf::RenderWindow& window, sf::Font& font) override; // Declaration
    void loadFromFile(const std::string& filename) override;
};

#endif // REDBLACK_H
