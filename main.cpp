#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "src/window.hpp"
#include "src/cell.hpp"
#include <sys/time.h>
#include <iostream>
#include <unistd.h>


int count_alive_neighbors(bool *cell_states, int cell_number);


int main(int argc, char const *argv[])
{
    // Used when initialising the field
    bool is_initialasing = true;
    bool cell_states[X_CELLS * Y_CELLS];
    Cell cells[X_CELLS * Y_CELLS];

    sf::RectangleShape white_background;

    sf::Vertex grid[X_CELLS + Y_CELLS][2];

    sf::VideoMode my_mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(1, 1), "Game of Life");

    //=========================================================================

    // Window dimensions
    const sf::Vector2f screen_size(my_mode.width, my_mode.height);
    const sf::Vector2i window_position(screen_size * (float)WINDOW_POSITION_SCALE);
    const sf::Vector2u window_size(screen_size * (float)WINDOW_SIZE_SCALE);

    // Apply the dimensions
    window.setPosition(window_position);
    window.setSize(window_size);

    // Cell
    for (int i = 0; i < X_CELLS * Y_CELLS; ++i)
        cell_states[i] = false;    // By default, all the cells are dead
    for (int i = 0; i < X_CELLS * Y_CELLS; ++i)
        cells[i] = Cell(i, window.getSize());

    // White background
    white_background.setFillColor(sf::Color::White);
    white_background.setSize(sf::Vector2f(window_size));

    // Vertical lines
    for (int i = 0; i < X_CELLS; ++i)
    {
        grid[i][0] = sf::Vertex(sf::Vector2f(i * 1 / (float)X_CELLS, 0));
        grid[i][0].color = sf::Color::Black;
        grid[i][1] = sf::Vertex(sf::Vector2f(i * 1 / (float)X_CELLS, 1));
        grid[i][1].color = sf::Color::Black;
    }
    // Horizontal lines
    for (int i = 0; i < Y_CELLS; ++i)
    {
        grid[X_CELLS + i][0] = sf::Vertex(sf::Vector2f(
                                                0, i * 1 / (float)Y_CELLS));
        grid[X_CELLS + i][0].color = sf::Color::Black;

        grid[X_CELLS + i][1] = sf::Vertex(sf::Vector2f(
                                                1, i * 1 / (float)Y_CELLS));
        grid[X_CELLS + i][1].color = sf::Color::Black;
    }


    // // Time measurement variables
    // struct timeval start, end;

    // Start the game loop
    while (window.isOpen())
    {
        // Exit init mode
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
            ((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) ||
             (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))) {
            is_initialasing = false;
        }

        // Initializing the field
        if ((is_initialasing) &&
                            (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
            // Tag the position where had tapped
            sf::Vector2f mouse_position(sf::Mouse::getPosition(window));
            // Determine the pertinent cell
            if ((mouse_position.x < window_size.x) &&
                            (mouse_position.x > 0) &&
                            (mouse_position.y < window_size.y) &&
                            (mouse_position.y > 0)) {
                int cell_number = (float)(mouse_position.x / window_size.x) *
                                  X_CELLS + (int)((float)(mouse_position.y /
                                  window_size.y) * Y_CELLS) * X_CELLS;

                cells[cell_number].make_active();
                cells[cell_number].toggle_life();
                cell_states[cell_number] = !cell_states[cell_number];
            // Sleep for staggering effect elimination
            sf::sleep(sf::milliseconds(100));
            }
        }
        // // Punch-in
        // gettimeofday(&start, NULL);

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // =================================================

        window.clear();
        window.draw(white_background);
        for (int i = 0; i < X_CELLS + Y_CELLS; ++i)
            window.draw(grid[i], 2, sf::Lines);

        // Cells display
        for (int i = 0; i < X_CELLS * Y_CELLS; ++i) {
            // If not in the init regime, calculate the next tick
            if (!is_initialasing) {
                while (1) {
                    int number = 0;
                    std::cin >> number;
                    std::cout << count_alive_neighbors(cell_states, number)
                              << std::endl;
                }
            }

            if (cells[i].is_active())
                window.draw(cells[i].cell);
        }

        window.display();

        // // Punch-out
        // gettimeofday(&end, NULL);
        // // FPS print
        // double delta = ((end.tv_sec  - start.tv_sec) * 1000000u +
        //                  end.tv_usec - start.tv_usec) / 1.e6;
        // std::cout << "FPS: " << 1 / delta << std::endl;
    }

    return 0;
}

int count_alive_neighbors(bool *cell_states, int cell_number) {
    int alive_neighbors = 0;

    // Four corner cells
    switch(cell_number) {
        // Left upper
        case 0:
            return cell_states[cell_number + 1] +
                   cell_states[cell_number + X_CELLS] +
                   cell_states[cell_number + X_CELLS + 1];
        // Right upper
        case X_CELLS - 1:
            return cell_states[cell_number - 1] +
                   cell_states[cell_number + X_CELLS] +
                   cell_states[cell_number + X_CELLS - 1];
        // Left bottom
        case X_CELLS * (Y_CELLS - 1):
            return cell_states[cell_number + 1] +
                   cell_states[cell_number - X_CELLS] +
                   cell_states[cell_number - X_CELLS + 1];
        // Right bottom
        case X_CELLS * Y_CELLS - 1:
            return cell_states[cell_number - 1] +
                   cell_states[cell_number - X_CELLS] +
                   cell_states[cell_number - X_CELLS - 1];
        default:
            break;
    }

    // Other upper-horizontal cells
    if (cell_number < X_CELLS)
            alive_neighbors = cell_states[cell_number - 1] +
                              cell_states[cell_number + X_CELLS - 1] +
                              cell_states[cell_number + X_CELLS] +
                              cell_states[cell_number + X_CELLS + 1] +
                              cell_states[cell_number + 1];
    // Other bottom-horizontal cells
    else if (cell_number / X_CELLS == Y_CELLS - 1)
            alive_neighbors = cell_states[cell_number - 1] +
                              cell_states[cell_number - X_CELLS - 1] +
                              cell_states[cell_number - X_CELLS] +
                              cell_states[cell_number - X_CELLS + 1] +
                              cell_states[cell_number + 1];
    // Other left-vertical cells
    else if (cell_number % X_CELLS == 0)
            alive_neighbors = cell_states[cell_number - X_CELLS] +
                              cell_states[cell_number - X_CELLS + 1] +
                              cell_states[cell_number + 1] +
                              cell_states[cell_number + X_CELLS + 1] +
                              cell_states[cell_number + X_CELLS];
    // Other right-vertical cells
    else if (cell_number % X_CELLS == Y_CELLS - 1)
            alive_neighbors = cell_states[cell_number - X_CELLS] +
                              cell_states[cell_number - X_CELLS - 1] +
                              cell_states[cell_number - 1] +
                              cell_states[cell_number + X_CELLS - 1] +
                              cell_states[cell_number + X_CELLS];
    // Non-contiguous cells
    else 
            alive_neighbors = cell_states[cell_number - X_CELLS - 1] +
                              cell_states[cell_number - X_CELLS] +
                              cell_states[cell_number - X_CELLS + 1] +
                              cell_states[cell_number + 1] +
                              cell_states[cell_number + X_CELLS + 1] +
                              cell_states[cell_number + X_CELLS] +
                              cell_states[cell_number + X_CELLS - 1] +
                              cell_states[cell_number - 1];

    return alive_neighbors;
}
