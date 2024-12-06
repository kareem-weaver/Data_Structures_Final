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
    // Placeholder for visualization logic
    std::cout << "Visualizing BST (placeholder)" << std::endl;
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
