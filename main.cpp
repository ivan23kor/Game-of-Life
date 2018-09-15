#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "src/GUI/window.hpp"
#include "src/GUI/cell.hpp"
#include <sys/time.h>
#include <iostream>


void initField(const sf::RenderWindow &window);


int main(int argc, char const *argv[])
{
    // Window dimensions
    sf::VideoMode my_mode = sf::VideoMode::getDesktopMode();
    const sf::Vector2f screen_size(my_mode.width, my_mode.height);
    const sf::Vector2i window_position(screen_size * (float)WINDOW_POSITION_SCALE);
    const sf::Vector2u window_size(screen_size * (float)WINDOW_SIZE_SCALE);

    // Apply the dimensions
    sf::RenderWindow window(sf::VideoMode(1, 1), "Game of Life");
    window.setPosition(window_position);
    window.setSize(window_size);

    // Cell
    Cell cells[X_CELLS * Y_CELLS];
    for (int i = 0; i < X_CELLS * Y_CELLS; ++i)
        cells[i] = Cell(i, window.getSize());

    // White background
    sf::RectangleShape white_background;
    white_background.setFillColor(sf::Color::White);
    white_background.setSize(sf::Vector2f(window_size));

    sf::Vertex grid[X_CELLS + Y_CELLS][2];
    for (int i = 0; i < X_CELLS; ++i)
    {
        grid[i][0] = sf::Vertex(sf::Vector2f(i * 1 / (float)X_CELLS, 0));
        grid[i][0].color = sf::Color::Black;
        grid[i][1] = sf::Vertex(sf::Vector2f(i * 1 / (float)X_CELLS, 1));
        grid[i][1].color = sf::Color::Black;
    }
    for (int i = 0; i < Y_CELLS; ++i)
    {
        grid[X_CELLS + i][0] = sf::Vertex(sf::Vector2f(0, i * 1 / (float)Y_CELLS));
        grid[X_CELLS + i][0].color = sf::Color::Black;
        grid[X_CELLS + i][1] = sf::Vertex(sf::Vector2f(1, i * 1 / (float)Y_CELLS));
        grid[X_CELLS + i][1].color = sf::Color::Black;
    }

    
    // Time measurement variables
    struct timeval start, end;

    // Start the game loop
    while (window.isOpen())
    {
        // Punch-in
        gettimeofday(&start, NULL);

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();
        // for (int i = 0; i < X_CELLS * Y_CELLS; ++i)
        // {
        //     cell.setPosition(sf::Vector2f((i % X_CELLS) / X_CELLS, ((int)(i / Y_CELLS)) / Y_CELLS));
        //     if (cells_previous_tick[i])
        //         cell.setFillColor(sf::Color::Red);
        //     else
        //         cell.setFillColor(sf::Color::Green);
        //     window.draw(cell);
        // }

        // White background
        window.draw(white_background);

        // Grid
        for (int i = 0; i < X_CELLS + Y_CELLS; ++i)
            window.draw(grid[i], 2, sf::Lines);

        // Cell coloring
        for (int i = 0; i < X_CELLS * Y_CELLS; ++i) {
            window.draw(cells[i].cell);
        }

        window.display();
        
        // Punch-out
        gettimeofday(&end, NULL);
        
        // FPS print
        double delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
                         end.tv_usec - start.tv_usec) / 1.e6;
        // std::cout << "FPS: " << 1 / delta << std::endl;
    }

    return 0;
}

void initField(const sf::RenderWindow &window) {
    bool still_setting = true;
    sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));
    while (still_setting){
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            // Which cell was selected
            mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));
            std::cout << window.getSize().x << " " << window.getSize().y << "\n" << std::endl;
            std::cout << mouse_position.x << " " << mouse_position.y << "\n" << std::endl;
    }

    return;
}