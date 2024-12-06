#include "RedBlack.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>

void RedBlackTree::insert(int key) {
    // Placeholder: Implement Red-Black Tree insertion logic here
    std::cout << "Inserting key " << key << " into Red-Black Tree" << std::endl;
}

void RedBlackTree::remove(int key) {
    // Placeholder: Implement Red-Black Tree deletion logic here
    std::cout << "Removing key " << key << " from Red-Black Tree" << std::endl;
}

void RedBlackTree::display() const {
    // Placeholder: Implement Red-Black Tree traversal display logic
    std::cout << "Displaying Red-Black Tree (placeholder)" << std::endl;
}

void RedBlackTree::visualize(sf::RenderWindow& window, sf::Font& font) {
    // Placeholder visualization logic
    std::cout << "Visualizing Red-Black Tree (placeholder)" << std::endl;
}

void RedBlackTree::loadFromFile(const std::string& filename) {
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

void RedBlackTree::deleteTree(RBNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
