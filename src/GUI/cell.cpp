#include "cell.hpp"
#include "window.hpp"
#include <iostream>

Cell::Cell() {
    current_state = previous_state = false;
    cell.setFillColor(sf::Color::Red);
    cell.setSize(sf::Vector2f(1 / (float)X_CELLS, 1 / (float)Y_CELLS));
}

Cell::Cell(int number, const sf::Vector2u window_size) {
    cell.setSize(sf::Vector2f(1 / (float)X_CELLS, 1 / (float)Y_CELLS));
    if (number % 2 == 0) {
        current_state = previous_state = true;
        cell.setFillColor(sf::Color::Green);
    }
    else {
        current_state = previous_state = false;
        cell.setFillColor(sf::Color::Red);   
    }

    cell.setPosition((number % X_CELLS) / (float)X_CELLS,
                     (number / X_CELLS) / (float)Y_CELLS);
}