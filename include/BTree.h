#ifndef BTREE_H
#define BTREE_H

#include "../include/ADTInterface.h"
#include <vector>
#include <SFML/Graphics.hpp>

class BTree : public ADTInterface {
public:
    BTree(int t); // Constructor with minimum degree t
    ~BTree();

    void insert(int value) override;
    void remove(int value) override;
    void loadFromFile(const std::string& filename) override;
    void draw(sf::RenderWindow& window, sf::Font& font) override;

private:
    struct Node {
        std::vector<int> keys; // Keys in the node
        std::vector<Node*> children; // Pointers to child nodes
        bool isLeaf; // True if leaf node
        int t; // Minimum degree

        Node(bool isLeaf, int t) : isLeaf(isLeaf), t(t) {}
    };

    Node* root;
    int t; // Minimum degree

    void insertNonFull(Node* node, int value);
    void splitChild(Node* parent, int i);
    void removeFromLeaf(Node* node, int idx);
    void removeFromNonLeaf(Node* node, int idx);
    Node* getPredecessor(Node* node, int idx);
    Node* getSuccessor(Node* node, int idx);
    void merge(Node* node, int idx);
    void deleteTree(Node* node);
    void drawNode(sf::RenderWindow& window, sf::Font& font, Node* node, int x, int y, int offset);
};

#endif // BTREE_H