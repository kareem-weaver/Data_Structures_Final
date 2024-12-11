#ifndef REDBLACK_H
#define REDBLACK_H

#include "../include/ADTInterface.h"
#include <SFML/Graphics.hpp>

class RedBlack : public ADTInterface {
public:
    RedBlack();
    ~RedBlack();

    void insert(int value) override;
    void remove(int value) override; // Node removal
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

    Node* root;    // Root of the Red-Black Tree
    Node* TNULL;   // Null node for Red-Black Tree

    void initializeTNULL();        // Initialize the TNULL sentinel node
    void deleteTree(Node* node);   // Delete all nodes recursively
    void insertFix(Node* node);    // Fix tree after insertion
    void deleteFix(Node* node);    // Fix tree after deletion
    void rotateLeft(Node* node);   // Left rotation
    void rotateRight(Node* node);  // Right rotation
    Node* minimum(Node* node);     // Find the minimum value in the subtree
    void transplant(Node* u, Node* v); // Replace one subtree with another
    void drawNode(sf::RenderWindow& window, sf::Font& font, Node* node, int x, int y, int offset); // Draw tree visualization
};

#endif // REDBLACK_H
