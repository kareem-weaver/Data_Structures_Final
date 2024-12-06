
#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <SFML/Graphics.hpp>

class AVLNode {
public:
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(int key) : key(key), height(1), left(nullptr), right(nullptr) {}
};

class AVL {
    AVLNode* root;

    int getHeight(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* insert(AVLNode* node, int key);

public:
    AVL() : root(nullptr) {}
    void insert(int key);
    void display() const;
    void visualize(sf::RenderWindow& window, sf::Font& font); // Declaration
};

#endif // AVL_H
