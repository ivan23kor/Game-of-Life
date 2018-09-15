#include <SFML/Graphics.hpp>

#define X_CELLS 160
#define Y_CELLS 80

class Cell {
// Represents one living entity
private:
    // Previous- and current-tick states
    bool current_state; // true means alive
    bool previous_state; // true means alive
public:
    sf::RectangleShape cell;
    Cell();
    Cell(int number, const sf::Vector2u window_size);
    // void set_state(bool new_state){previous_state = current_state;
    //                                current_state = new_state;};
    // bool get_current_state(void){return current_state;};
    // bool get_previous_state(void){return previous_state;};
};