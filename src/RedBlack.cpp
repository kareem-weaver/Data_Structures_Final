#include "RedBlack.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>

// Constructor
RedBlackTree::RedBlackTree() : root(nullptr) {}

// Destructor
RedBlackTree::~RedBlackTree() {
    deleteTree(root);
}

// Insert
void RedBlackTree::insert(int key) {
    RBNode* newNode = new RBNode(key);
    root = bstInsert(root, newNode);
    fixViolation(newNode);
}

// BST Insert Helper
RBNode* RedBlackTree::bstInsert(RBNode* root, RBNode* newNode) {
    if (!root) return newNode;

    if (newNode->key < root->key) {
        root->left = bstInsert(root->left, newNode);
        root->left->parent = root;
    } else if (newNode->key > root->key) {
        root->right = bstInsert(root->right, newNode);
        root->right->parent = root;
    }
    return root;
}

// Fix Red-Black Tree Violations
void RedBlackTree::fixViolation(RBNode* newNode) {
    while (newNode != root && newNode->parent->color == RED) {
        RBNode* grandparent = newNode->parent->parent;
        if (newNode->parent == grandparent->left) {
            RBNode* uncle = grandparent->right;
            if (uncle && uncle->color == RED) {
                grandparent->color = RED;
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                if (newNode == newNode->parent->right) {
                    newNode = newNode->parent;
                    leftRotate(newNode);
                }
                newNode->parent->color = BLACK;
                grandparent->color = RED;
                rightRotate(grandparent);
            }
        } else {
            RBNode* uncle = grandparent->left;
            if (uncle && uncle->color == RED) {
                grandparent->color = RED;
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                if (newNode == newNode->parent->left) {
                    newNode = newNode->parent;
                    rightRotate(newNode);
                }
                newNode->parent->color = BLACK;
                grandparent->color = RED;
                leftRotate(grandparent);
            }
        }
    }
    root->color = BLACK;
}

// Left Rotate
void RedBlackTree::leftRotate(RBNode* node) {
    RBNode* rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left) rightChild->left->parent = node;

    rightChild->parent = node->parent;
    if (!node->parent) {
        root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent = rightChild;
}

// Right Rotate
void RedBlackTree::rightRotate(RBNode* node) {
    RBNode* leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right) leftChild->right->parent = node;

    leftChild->parent = node->parent;
    if (!node->parent) {
        root = leftChild;
    } else if (node == node->parent->left) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;
}

// Remove
void RedBlackTree::remove(int key) {
    RBNode* nodeToDelete = search(root, key);
    if (!nodeToDelete) {
        std::cerr << "Key not found in Red-Black Tree.\n";
        return;
    }
    deleteNode(nodeToDelete);
}

// Delete Node
void RedBlackTree::deleteNode(RBNode* node) {
    RBNode* replacement = node;
    RBNode* fixNode;
    bool originalColor = replacement->color;

    if (!node->left) {
        fixNode = node->right;
        replaceNode(node, node->right);
    } else if (!node->right) {
        fixNode = node->left;
        replaceNode(node, node->left);
    } else {
        replacement = getMin(node->right);
        originalColor = replacement->color;
        fixNode = replacement->right;
        if (replacement->parent == node) {
            if (fixNode) fixNode->parent = replacement;
        } else {
            replaceNode(replacement, replacement->right);
            replacement->right = node->right;
            replacement->right->parent = replacement;
        }
        replaceNode(node, replacement);
        replacement->left = node->left;
        replacement->left->parent = replacement;
        replacement->color = node->color;
    }
    delete node;
    if (originalColor == BLACK) fixDelete(fixNode);
}

// Fix Delete Violations
void RedBlackTree::fixDelete(RBNode* fixNode) {
    while (fixNode != root && (!fixNode || fixNode->color == BLACK)) {
        if (fixNode == fixNode->parent->left) {
            RBNode* sibling = fixNode->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                fixNode->parent->color = RED;
                leftRotate(fixNode->parent);
                sibling = fixNode->parent->right;
            }
            if ((!sibling->left || sibling->left->color == BLACK) &&
                (!sibling->right || sibling->right->color == BLACK)) {
                sibling->color = RED;
                fixNode = fixNode->parent;
            } else {
                if (!sibling->right || sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rightRotate(sibling);
                    sibling = fixNode->parent->right;
                }
                sibling->color = fixNode->parent->color;
                fixNode->parent->color = BLACK;
                if (sibling->right) sibling->right->color = BLACK;
                leftRotate(fixNode->parent);
                fixNode = root;
            }
        } else {
            RBNode* sibling = fixNode->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                fixNode->parent->color = RED;
                rightRotate(fixNode->parent);
                sibling = fixNode->parent->left;
            }
            if ((!sibling->left || sibling->left->color == BLACK) &&
                (!sibling->right || sibling->right->color == BLACK)) {
                sibling->color = RED;
                fixNode = fixNode->parent;
            } else {
                if (!sibling->left || sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    leftRotate(sibling);
                    sibling = fixNode->parent->left;
                }
                sibling->color = fixNode->parent->color;
                fixNode->parent->color = BLACK;
                if (sibling->left) sibling->left->color = BLACK;
                rightRotate(fixNode->parent);
                fixNode = root;
            }
        }
    }
    if (fixNode) fixNode->color = BLACK;
}

// Search
RBNode* RedBlackTree::search(RBNode* node, int key) {
    if (!node || node->key == key) return node;
    if (key < node->key) return search(node->left, key);
    return search(node->right, key);
}

// Get Minimum Node
RBNode* RedBlackTree::getMin(RBNode* node) {
    while (node->left) node = node->left;
    return node;
}

// Replace Node
void RedBlackTree::replaceNode(RBNode* oldNode, RBNode* newNode) {
    if (!oldNode->parent) root = newNode;
    else if (oldNode == oldNode->parent->left) oldNode->parent->left = newNode;
    else oldNode->parent->right = newNode;
    if (newNode) newNode->parent = oldNode->parent;
}

// Display
void RedBlackTree::display() const {
    inOrderTraversal(root);
    std::cout << std::endl;
}

// In-Order Traversal
void RedBlackTree::inOrderTraversal(RBNode* node) const {
    if (!node) return;
    inOrderTraversal(node->left);
    std::cout << node->key << (node->color == RED ? "R " : "B ");
    inOrderTraversal(node->right);
}

// Delete Tree
void RedBlackTree::deleteTree(RBNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
