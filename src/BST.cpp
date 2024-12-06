#include "BST.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

BST::BST() : root(nullptr) {}

BST::~BST() {
    deleteTree(root);
}

void BST::insert(int value) {
    insert(root, value);
}

void BST::remove(int value) {
    remove(root, value);
}

void BST::display() const {
    display(root);
}

void BST::visualize(sf::RenderWindow& window, sf::Font& font) {
    if (!root) return;

    int x = window.getSize().x / 2; // Start in the center
    int y = 50; // Start near the top
    int xOffset = window.getSize().x / 4; // Spacing between levels

    drawTree(root, window, font, x, y, xOffset);
}

void BST::drawTree(Node* node, sf::RenderWindow& window, sf::Font& font, int x, int y, int xOffset) {
    if (!node) return;

    // Draw the node as a circle
    sf::CircleShape circle(20); // Radius = 20
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(x - 20, y - 20); // Center the circle
    window.draw(circle);

    // Draw the node value as text
    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(node->value));
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(x - 10, y - 15);
    window.draw(text);

    // Draw lines to children and recursively draw them
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

void BST::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    int value;
    while (file >> value) {
        insert(value);
    }
    file.close();
}

void BST::deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void BST::insert(Node*& node, int value) {
    if (!node) {
        node = new Node(value);
        return;
    }
    if (value < node->value) {
        insert(node->left, value);
    } else {
        insert(node->right, value);
    }
}

void BST::remove(Node*& node, int value) {
    if (!node) return;

    if (value < node->value) {
        remove(node->left, value);
    } else if (value > node->value) {
        remove(node->right, value);
    } else {
        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
        } else if (node->left && !node->right) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else if (!node->left && node->right) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else {
            Node* successor = node->right;
            while (successor->left) {
                successor = successor->left;
            }
            node->value = successor->value;
            remove(node->right, successor->value);
        }
    }
}

void BST::display(Node* node) const {
    if (!node) return;
    display(node->left);
    std::cout << node->value << " ";
    display(node->right);
}
