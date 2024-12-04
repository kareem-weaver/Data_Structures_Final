//
// Created by jabba on 11/24/2024.
//

#ifndef BST_H
#define BST_H

#pragma once
#include "ADTInterface.h"

class BST : public ADTInterface {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node(int val) : value(val), left(nullptr), right(nullptr) {}
    };
    Node* root = nullptr;
    void insert(Node*& node, int value);
    void remove(Node*& node, int value);
    void display(Node* node) const;
    void deleteTree(Node* node);

public:
    ~BST();
    void insert(int value) override;
    void remove(int value) override;
    void display() const override;
    void loadFromFile(const std::string& filename) override;
};

#endif //BST_H
