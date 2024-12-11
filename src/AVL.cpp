#include "../include/AVL.h"
#include <iostream>
#include <fstream>
#include <algorithm>

AVL::AVL() : root(nullptr) {}

AVL::~AVL() {
    deleteTree(root);
}

void AVL::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void AVL::insert(int value) {
    root = insertNode(root, value);
}

AVL::Node* AVL::insertNode(Node* node, int value) {
    if (!node) return new Node(value);

    if (value < node->data)
        node->left = insertNode(node->left, value);
    else if (value > node->data)
        node->right = insertNode(node->right, value);
    else
        return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balanceFactor = getBalanceFactor(node);

    // Left Left Case
    if (balanceFactor > 1 && value < node->left->data)
        return rotateRight(node);

    // Right Right Case
    if (balanceFactor < -1 && value > node->right->data)
        return rotateLeft(node);

    // Left Right Case
    if (balanceFactor > 1 && value > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balanceFactor < -1 && value < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVL::remove(int value) {
    root = removeNode(root, value);
}

AVL::Node* AVL::removeNode(Node* node, int value) {
    if (!node) return node;

    if (value < node->data)
        node->left = removeNode(node->left, value);
    else if (value > node->data)
        node->right = removeNode(node->right, value);
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeNode(node->right, temp->data);
        }
    }

    if (!node) return node;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balanceFactor = getBalanceFactor(node);

    // Left Left Case
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);

    // Left Right Case
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right Case
    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);

    // Right Left Case
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVL::Node* AVL::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    Node* temp = newRoot->left;

    newRoot->left = node;
    node->right = temp;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

AVL::Node* AVL::rotateRight(Node* node) {
    Node* newRoot = node->left;
    Node* temp = newRoot->right;

    newRoot->right = node;
    node->left = temp;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

int AVL::getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

int AVL::getHeight(Node* node) {
    return node ? node->height : 0;
}

AVL::Node* AVL::findMin(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

void AVL::loadFromFile(const std::string& filename) {
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

void AVL::draw(sf::RenderWindow& window, sf::Font& font) {
    if (!root) {
        sf::Text emptyText("AVL is empty.", font, 20);
        emptyText.setFillColor(sf::Color::Black);
        emptyText.setPosition(300, 300);
        window.draw(emptyText);
        return;
    }

    drawNode(window, font, root, 400, 50, 200);
}

void AVL::drawNode(sf::RenderWindow& window, sf::Font& font, Node* node, int x, int y, int offset) {
    if (!node) return;

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
