#include <SFML/Graphics.hpp>

// Node structure for the BST
struct Node {
    int key;
    Node* left;
    Node* right;
    int x, y; // Position for visualization

    Node(int k) : key(k), left(nullptr), right(nullptr), x(0), y(0) {}
};

// BST Class
class BST {
private:
    Node* root;

    // Recursive function to insert a key into the BST
    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);

        return node;
    }

    // Recursive function to calculate positions for each node
    void calculatePositions(Node* node, int x, int y, int xOffset) {
        if (!node) return;

        node->x = x;
        node->y = y;

        // Recur for left and right children
        calculatePositions(node->left, x - xOffset, y + 100, xOffset / 2);
        calculatePositions(node->right, x + xOffset, y + 100, xOffset / 2);
    }

    // Recursive function to draw the BST
    void drawTree(Node* node, sf::RenderWindow& window, sf::Font& font) {
        if (!node) return;

        // Draw edges (lines)
        if (node->left) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(node->x, node->y)),
                sf::Vertex(sf::Vector2f(node->left->x, node->left->y))
            };
            window.draw(line, 2, sf::Lines);
        }

        if (node->right) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(node->x, node->y)),
                sf::Vertex(sf::Vector2f(node->right->x, node->right->y))
            };
            window.draw(line, 2, sf::Lines);
        }

        // Draw node (circle)
        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Blue);
        circle.setPosition(node->x - 20, node->y - 20); // Center the circle
        window.draw(circle);

        // Draw node value (text)
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(node->key));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition(node->x - 10, node->y - 15); // Center the text
        window.draw(text);

        // Recur for left and right children
        drawTree(node->left, window, font);
        drawTree(node->right, window, font);
    }

public:
    BST() : root(nullptr) {}

    // Insert a key into the BST
    void insert(int key) {
        root = insert(root, key);
    }

    // Visualize the BST
    void visualize(sf::RenderWindow& window, sf::Font& font) {
        if (!root) return;

        // Calculate positions for each node
        calculatePositions(root, 400, 50, 200); // Start at root (400, 50) with offset 200

        // Draw the tree
        drawTree(root, window, font);
    }
};

// Main Function
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "BST Visualization");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        tree.visualize(window, font); // Visualize the BST
        window.display();
    }

    return 0;
}
