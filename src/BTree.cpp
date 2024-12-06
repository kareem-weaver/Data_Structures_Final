#include "BTree.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

BTreeNode::BTreeNode(int t, bool leaf) : t(t), leaf(leaf), numKeys(0) {
    keys = new int[2 * t - 1];
    children = new BTreeNode*[2 * t];
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->numKeys = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }

    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->children[j] = y->children[j + t];
        }
    }

    y->numKeys = t - 1;

    for (int j = numKeys; j >= i + 1; j--) {
        children[j + 1] = children[j];
    }

    children[i + 1] = z;

    for (int j = numKeys - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
    }

    keys[i] = y->keys[t - 1];
    numKeys++;
}

void BTreeNode::insertNonFull(int key) {
    int i = numKeys - 1;

    if (leaf) {
        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = key;
        numKeys++;
    } else {
        while (i >= 0 && keys[i] > key) {
            i--;
        }

        if (children[i + 1]->numKeys == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);

            if (keys[i + 1] < key) {
                i++;
            }
        }
        children[i + 1]->insertNonFull(key);
    }
}

void BTreeNode::traverse() {
    for (int i = 0; i < numKeys; i++) {
        if (!leaf) {
            children[i]->traverse();
        }
        std::cout << " " << keys[i];
    }
    if (!leaf) {
        children[numKeys]->traverse();
    }
}

void BTree::insert(int key) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys[0] = key;
        root->numKeys = 1;
    } else {
        if (root->numKeys == 2 * t - 1) {
            BTreeNode* newNode = new BTreeNode(t, false);
            newNode->children[0] = root;
            newNode->splitChild(0, root);

            int i = 0;
            if (newNode->keys[0] < key) {
                i++;
            }
            newNode->children[i]->insertNonFull(key);
            root = newNode;
        } else {
            root->insertNonFull(key);
        }
    }
}

void BTree::display() const {
    if (root) {
        root->traverse();
    }
    std::cout << std::endl;
}

void BTree::visualize(sf::RenderWindow& window, sf::Font& font) {
    if (!root) return;

    int x = window.getSize().x / 2;
    int y = 50;
    int xOffset = window.getSize().x / 4;

    drawNode(root, window, font, x, y, xOffset);
}

void BTree::drawNode(BTreeNode* node, sf::RenderWindow& window, sf::Font& font, int x, int y, int xOffset) {
    if (!node) return;

    // Draw the node as a rectangle
    sf::RectangleShape rect(sf::Vector2f(node->numKeys * 40, 40));
    rect.setFillColor(sf::Color::Blue);
    rect.setOutlineColor(sf::Color::White);
    rect.setOutlineThickness(2);
    rect.setPosition(x - rect.getSize().x / 2, y);
    window.draw(rect);

    // Draw each key in the node
    for (int i = 0; i < node->numKeys; i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(node->keys[i]));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(x - rect.getSize().x / 2 + i * 40 + 10, y + 10);
        window.draw(text);
    }

    // Recursively draw children and lines connecting them
    if (!node->leaf) {
        int childX = x - xOffset;
        for (int i = 0; i <= node->numKeys; i++) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y + 40), sf::Color::White),
                sf::Vertex(sf::Vector2f(childX, y + 100), sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);

            drawNode(node->children[i], window, font, childX, y + 100, xOffset / 2);
            childX += xOffset / node->numKeys; // Adjust spacing based on the number of keys
        }
    }
}
