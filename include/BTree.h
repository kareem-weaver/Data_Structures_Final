#ifndef BTREE_H
#define BTREE_H

#include <SFML/Graphics.hpp>
#include <vector>

class BTreeNode {
public:
    int* keys; // Array of keys
    int t;     // Minimum degree
    BTreeNode** children; // Array of child pointers
    int numKeys;
    bool leaf;

    BTreeNode(int t, bool leaf);
    void insertNonFull(int key);
    void splitChild(int i, BTreeNode* y);
    void traverse();

    // Allow access to private members
    friend class BTree;
};

class BTree {
    BTreeNode* root;
    int t;

public:
    BTree(int t) : root(nullptr), t(t) {}
    ~BTree() { delete root; }

    void insert(int key);
    void display() const;
    void visualize(sf::RenderWindow& window, sf::Font& font); // Add declaration
};

#endif // BTREE_H
