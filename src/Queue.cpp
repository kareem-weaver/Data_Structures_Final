#include "../include/Queue.h"
#include <fstream>
#include <iostream>

void Queue::enqueue(int value) {
    queue.push_back(value);
}

void Queue::dequeue() {
    if (!queue.empty()) {
        queue.erase(queue.begin());
    } else {
        std::cerr << "Queue is empty. Cannot dequeue.\n";
    }
}

void Queue::draw(sf::RenderWindow& window, sf::Font& font) {
    sf::Text title("Queue", font, 30);
    title.setPosition(50, 10);
    window.draw(title);

    for (size_t i = 0; i < queue.size(); ++i) {
        sf::RectangleShape box(sf::Vector2f(50, 50));
        box.setFillColor(sf::Color::White);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(2);
        box.setPosition(100 + i * 60, 200);
        window.draw(box);

        sf::Text valueText(std::to_string(queue[i]), font, 20);
        valueText.setFillColor(sf::Color::Black);
        valueText.setPosition(115 + i * 60, 205);
        window.draw(valueText);
    }
}

void Queue::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    int value;
    while (file >> value) {
        enqueue(value);
    }
    file.close();
}
