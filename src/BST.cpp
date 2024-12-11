#include "../include/BST.h"
#include <iostream>
#include <fstream>
#include <cmath>

BST::BST() : root(nullptr) {}

BST::~BST() {
    deleteTree(root);
}

void BST::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void BST::insert(int value) {
    root = insertNode(root, value);
}

BST::Node* BST::insertNode(Node* node, int value) {
    if (!node) return new Node(value);
    if (value < node->data)
        node->left = insertNode(node->left, value);
    else if (value > node->data)
        node->right = insertNode(node->right, value);
    return node;
}

void BST::remove(int value) {
    root = removeNode(root, value);
}

BST::Node* BST::removeNode(Node* node, int value) {
    if (!node) {
        std::cerr << "Value " << value << " not found in BST.\n";
        return nullptr;
    }

    if (value < node->data) {
        node->left = removeNode(node->left, value);
    } else if (value > node->data) {
        node->right = removeNode(node->right, value);
    } else {
        // Node to be deleted found
        if (!node->left && !node->right) {
            // Case 1: No children (leaf node)
            delete node;
            return nullptr;
        } else if (!node->left) {
            // Case 2: One child (right child)
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            // Case 2: One child (left child)
            Node* temp = node->left;
            delete node;
            return temp;
        } else {
            // Case 3: Two children
            Node* temp = findMin(node->right); // Find minimum in right subtree
            node->data = temp->data;          // Replace data with successor
            node->right = removeNode(node->right, temp->data); // Delete successor
        }
    }
    return node;
}

BST::Node* BST::findMin(Node* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

void BST::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    int value;
    while (file >> value) {
        insert(value);
    }
    file.close();
}

void BST::draw(sf::RenderWindow& window, sf::Font& font) {
    if (!root) {
        sf::Text emptyText("BST is empty.", font, 20);
        emptyText.setFillColor(sf::Color::Black);
        emptyText.setPosition(300, 300);
        window.draw(emptyText);
        return;
    }

    drawNode(window, font, root, 400, 50, 200);
}

void BST::drawNode(sf::RenderWindow& window, sf::Font& font, Node* node, int x, int y, int offset) {
    if (!node) return;

    // Draw connections to children
    if (node->left) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x - offset + 20, y + 100), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawNode(window, font, node->left, x - offset, y + 100, offset / 2);
    }
    if (node->right) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x + offset + 20, y + 100), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawNode(window, font, node->right, x + offset, y + 100, offset / 2);
    }

    // Draw the node itself
    sf::CircleShape circle(20);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(x, y);
    window.draw(circle);

    sf::Text valueText(std::to_string(node->data), font, 20);
    valueText.setFillColor(sf::Color::Black);
    valueText.setPosition(x + 10, y + 5);
    window.draw(valueText);
}
