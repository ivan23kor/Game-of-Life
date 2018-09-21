#include "cell.hpp"
#include "window.hpp"

Cell::Cell() {
    // By default, all cells are dead
    alive = false;
    cell.setFillColor(sf::Color::Red);
    cell.setSize(sf::Vector2f(1 / (float)X_CELLS, 1 / (float)Y_CELLS));
}

Cell::Cell(int number, const sf::Vector2u window_size) {
    cell.setSize(sf::Vector2f(1 / (float)X_CELLS, 1 / (float)Y_CELLS));

    cell.setPosition((number % X_CELLS) / (float)X_CELLS,
                     (number / X_CELLS) / (float)Y_CELLS);
}

bool Cell::is_alive() {
    return alive;
}

void Cell::make_alive() {
    alive = true;
    cell.setFillColor(sf::Color::Green);
}

void Cell::make_dead() {
    alive = false;
    cell.setFillColor(sf::Color::Red);
}

void Cell::toggle_life() {
    alive = !alive;
    if (alive)
        cell.setFillColor(sf::Color::Green);
    else
        cell.setFillColor(sf::Color::Red);
}

bool Cell::is_active() {
    return active;
}

void Cell::make_active() {
    active = true;
}

void Cell::make_inactive() {
    active = false;
}
