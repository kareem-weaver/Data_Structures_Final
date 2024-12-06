#include "AVL.h"
#include <iostream>
#include <fstream>
#include <algorithm>

int AVL::getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

int AVL::getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLNode* AVL::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T = x->right;

    x->right = y;
    y->left = T;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* AVL::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T = y->left;

    y->left = x;
    x->right = T;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVLNode* AVL::insert(AVLNode* node, int key) {
    if (!node) return new AVLNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // No duplicates allowed

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVL::insert(int key) {
    root = insert(root, key);
}

void AVL::display() const {
    // Optional: Implement traversal for display
}

void AVL::visualize(sf::RenderWindow& window, sf::Font& font) {
    if (!root) return;

    int x = window.getSize().x / 2;
    int y = 50;
    int xOffset = window.getSize().x / 4;

    drawTree(root, window, font, x, y, xOffset);
}

void AVL::drawTree(AVLNode* node, sf::RenderWindow& window, sf::Font& font, int x, int y, int xOffset) {
    if (!node) return;

    // Draw the node
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::Cyan);
    circle.setPosition(x - 20, y - 20);
    window.draw(circle);

    // Draw the value inside the circle
    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(node->key));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x - 10, y - 15);
    window.draw(text);

    // Draw connections to children
    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
            sf::Vertex(sf::Vector2f(x - xOffset, y + 100), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(node->left, window, font, x - xOffset, y + 100, xOffset / 2);
    }

    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x, y), sf::Color::White),
            sf::Vertex(sf::Vector2f(x + xOffset, y + 100), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        drawTree(node->right, window, font, x + xOffset, y + 100, xOffset / 2);
    }
}

