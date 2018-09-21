#include <SFML/Graphics.hpp>

#define X_CELLS 160
#define Y_CELLS 80

class Cell {
// Represents one living entity
private:
    bool active; // true means alive
    bool alive; // true means alive
public:
    sf::RectangleShape cell;
    Cell();
    Cell(int number, const sf::Vector2u window_size);
    bool is_alive();
    void make_alive();
    void make_dead();
    void toggle_life();
    bool is_active();
    void make_active();
    void make_inactive();
};