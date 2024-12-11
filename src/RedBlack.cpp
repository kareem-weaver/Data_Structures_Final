#include "../include/RedBlack.h"
#include <iostream>
#include <fstream>

RedBlack::RedBlack() {
    initializeTNULL();
    root = TNULL;
}

RedBlack::~RedBlack() {
    deleteTree(root);
    delete TNULL;
}

void RedBlack::initializeTNULL() {
    TNULL = new Node(0);
    TNULL->color = BLACK;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
}

void RedBlack::deleteTree(Node* node) {
    if (node != TNULL) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void RedBlack::insert(int value) {
    Node* node = new Node(value);
    node->parent = nullptr;
    node->data = value;
    node->left = TNULL;
    node->right = TNULL;
    node->color = RED;

    Node* y = nullptr;
    Node* x = this->root;

    while (x != TNULL) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }

    insertFix(node);
}

void RedBlack::insertFix(Node* node) {
    Node* uncle;
    while (node->parent->color == RED) {
        if (node->parent == node->parent->parent->right) {
            uncle = node->parent->parent->left;
            if (uncle->color == RED) {
                uncle->color = BLACK;
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateLeft(node->parent->parent);
            }
        } else {
            uncle = node->parent->parent->right;
            if (uncle->color == RED) {
                uncle->color = BLACK;
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeft(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateRight(node->parent->parent);
            }
        }
        if (node == root) {
            break;
        }
    }
    root->color = BLACK;
}

void RedBlack::deleteFix(Node* x) {
    Node* sibling;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            sibling = x->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                sibling = x->parent->right;
            }
            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                x = x->parent;
            } else {
                if (sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = x->parent->right;
                }
                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->right->color = BLACK;
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            sibling = x->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                sibling = x->parent->left;
            }
            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                x = x->parent;
            } else {
                if (sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = x->parent->left;
                }
                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->left->color = BLACK;
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RedBlack::transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void RedBlack::rotateLeft(Node* node) {
    Node* y = node->right;
    node->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == nullptr) {
        this->root = y;
    } else if (node == node->parent->left) {
        node->parent->left = y;
    } else {
        node->parent->right = y;
    }
    y->left = node;
    node->parent = y;
}

void RedBlack::rotateRight(Node* node) {
    Node* y = node->left;
    node->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == nullptr) {
        this->root = y;
    } else if (node == node->parent->right) {
        node->parent->right = y;
    } else {
        node->parent->left = y;
    }
    y->right = node;
    node->parent = y;
}

void RedBlack::remove(int value) {
    Node* node = root;
    Node* z = TNULL;
    Node* x, *y;

    // Find the node containing the value
    while (node != TNULL) {
        if (node->data == value) {
            z = node;
        }
        if (node->data <= value) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (z == TNULL) {
        std::cerr << "Value not found in the tree.\n";
        return;
    }

    y = z;
    Color yOriginalColor = y->color;
    if (z->left == TNULL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == TNULL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (yOriginalColor == BLACK) {
        deleteFix(x);
    }
}

RedBlack::Node* RedBlack::minimum(Node* node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}

void RedBlack::loadFromFile(const std::string& filename) {
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

void RedBlack::draw(sf::RenderWindow& window, sf::Font& font) {
    if (root == TNULL) {
        sf::Text emptyText("Red-Black Tree is empty.", font, 20);
        emptyText.setFillColor(sf::Color::Black);
        emptyText.setPosition(300, 300);
        window.draw(emptyText);
        return;
    }

    drawNode(window, font, root, 400, 50, 200);
}

void RedBlack::drawNode(sf::RenderWindow& window, sf::Font& font, Node* node, int x, int y, int offset) {
    if (node == TNULL) return;

    // Draw connections to children
    if (node->left != TNULL) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x - offset + 20, y + 100), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawNode(window, font, node->left, x - offset, y + 100, offset / 2);
    }
    if (node->right != TNULL) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(x + 20, y + 20), sf::Color::Black),
            sf::Vertex(sf::Vector2f(x + offset + 20, y + 100), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        drawNode(window, font, node->right, x + offset, y + 100, offset / 2);
    }

    // Draw the node itself
    sf::CircleShape circle(20);
    circle.setFillColor(node->color == RED ? sf::Color::Red : sf::Color::Black);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(2);
    circle.setPosition(x, y);
    window.draw(circle);

    sf::Text valueText(std::to_string(node->data), font, 20);
    valueText.setFillColor(sf::Color::White);
    valueText.setPosition(x + 10, y + 5);
    window.draw(valueText);
}