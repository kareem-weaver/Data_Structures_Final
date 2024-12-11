#include "../include/BTree.h"
#include <iostream>
#include <fstream>
#include <algorithm>

BTree::BTree(int t) : root(nullptr), t(t) {}

BTree::~BTree() {
    deleteTree(root);
}

void BTree::deleteTree(Node* node) {
    if (node) {
        for (auto child : node->children)
            deleteTree(child);
        delete node;
    }
}

void BTree::insert(int value) {
    if (!root) {
        root = new Node(true, t);
        root->keys.push_back(value);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            Node* newRoot = new Node(false, t);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0);

            int i = (newRoot->keys[0] < value) ? 1 : 0;
            insertNonFull(newRoot->children[i], value);
            root = newRoot;
        } else {
            insertNonFull(root, value);
        }
    }
}

void BTree::insertNonFull(Node* node, int value) {
    int i = node->keys.size() - 1;

    if (node->isLeaf) {
        node->keys.push_back(0);
        while (i >= 0 && node->keys[i] > value) {
            node->keys[i + 1] = node->keys[i];
            --i;
        }
        node->keys[i + 1] = value;
    } else {
        while (i >= 0 && node->keys[i] > value)
            --i;

        if (node->children[i + 1]->keys.size() == 2 * t - 1) {
            splitChild(node, i + 1);
            if (node->keys[i + 1] < value)
                ++i;
        }
        insertNonFull(node->children[i + 1], value);
    }
}

void BTree::splitChild(Node* parent, int i) {
    Node* node = parent->children[i];
    Node* newNode = new Node(node->isLeaf, t);
    parent->keys.insert(parent->keys.begin() + i, node->keys[t - 1]);
    parent->children.insert(parent->children.begin() + i + 1, newNode);

    newNode->keys.assign(node->keys.begin() + t, node->keys.end());
    node->keys.resize(t - 1);

    if (!node->isLeaf) {
        newNode->children.assign(node->children.begin() + t, node->children.end());
        node->children.resize(t);
    }
}

void BTree::remove(int value) {
    if (!root) {
        std::cerr << "BTree is empty. Cannot remove.\n";
        return;
    }

    removeFromNonLeaf(root, value);

    if (root->keys.empty()) {
        Node* temp = root;
        root = root->isLeaf ? nullptr : root->children[0];
        delete temp;
    }
}

void BTree::removeFromLeaf(Node* node, int idx) {
    node->keys.erase(node->keys.begin() + idx);
}

void BTree::removeFromNonLeaf(Node* node, int idx) {
    int value = node->keys[idx];

    if (node->isLeaf) {
        removeFromLeaf(node, idx);
    } else {
        if (node->children[idx]->keys.size() >= t) {
            Node* pred = getPredecessor(node, idx);
            node->keys[idx] = pred->keys.back();
            removeFromNonLeaf(node->children[idx], pred->keys.back());
        } else if (node->children[idx + 1]->keys.size() >= t) {
            Node* succ = getSuccessor(node, idx);
            node->keys[idx] = succ->keys[0];
            removeFromNonLeaf(node->children[idx + 1], succ->keys[0]);
        } else {
            merge(node, idx);
            removeFromNonLeaf(node->children[idx], value);
        }
    }
}

BTree::Node* BTree::getPredecessor(Node* node, int idx) {
    Node* current = node->children[idx];
    while (!current->isLeaf)
        current = current->children.back();
    return current;
}

BTree::Node* BTree::getSuccessor(Node* node, int idx) {
    Node* current = node->children[idx + 1];
    while (!current->isLeaf)
        current = current->children.front();
    return current;
}

void BTree::merge(Node* node, int idx) {
    Node* child = node->children[idx];
    Node* sibling = node->children[idx + 1];

    child->keys.push_back(node->keys[idx]);
    child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());

    if (!child->isLeaf)
        child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());

    node->keys.erase(node->keys.begin() + idx);
    node->children.erase(node->children.begin() + idx + 1);

    delete sibling;
}

void BTree::loadFromFile(const std::string& filename) {
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

void BTree::draw(sf::RenderWindow& window, sf::Font& font) {
    if (!root) {
        sf::Text emptyText("BTree is empty.", font, 20);
        emptyText.setFillColor(sf::Color::Black);
        emptyText.setPosition(300, 300);
        window.draw(emptyText);
        return;
    }

    drawNode(window, font, root, 400, 50, 200);
}

void BTree::drawNode(sf::RenderWindow& window, sf::Font& font, Node* node, int x, int y, int offset) {
    if (!node) return;

    // Draw the keys of the current node
    int keySpacing = offset / (node->keys.size() + 1); // Space keys evenly
    for (size_t i = 0; i < node->keys.size(); ++i) {
        int keyX = x - offset / 2 + (i + 1) * keySpacing; // Calculate position for each key

        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::White);
        circle.setOutlineColor(sf::Color::Black);
        circle.setOutlineThickness(2);
        circle.setPosition(keyX, y);
        window.draw(circle);

        sf::Text valueText(std::to_string(node->keys[i]), font, 20);
        valueText.setFillColor(sf::Color::Black);
        valueText.setPosition(keyX + 10, y + 5);
        window.draw(valueText);
    }

    // Draw child nodes
    if (!node->isLeaf) {
        for (size_t i = 0; i < node->children.size(); ++i) {
            int childX = x - offset / 2 + i * (offset / node->children.size());
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y + 20), sf::Color::Black),
                sf::Vertex(sf::Vector2f(childX, y + 100), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
            drawNode(window, font, node->children[i], childX, y + 100, offset / 2);
        }
    }
}
