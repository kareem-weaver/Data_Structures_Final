#ifndef AVL_H
#define AVL_H

#include "../include/ADTInterface.h"
#include <SFML/Graphics.hpp>

class AVL : public ADTInterface {
public:
    AVL();
    ~AVL();

    void insert(int value) override;
    void remove(int value) override;
    void loadFromFile(const std::string& filename) override;
    void draw(sf::RenderWindow& window, sf::Font& font) override;

private:
    struct Node {
        int data;
        int height;
        Node* left;
        Node* right;
        Node(int value) : data(value), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insertNode(Node* node, int value);
    Node* removeNode(Node* node, int value);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    int getBalanceFactor(Node* node);
    int getHeight(Node* node);
    Node* findMin(Node* node);
    void deleteTree(Node* node);
    void drawNode(sf::RenderWindow& window, sf::Font& font, Node* node, int x, int y, int offset);
};

#endif // AVL_H