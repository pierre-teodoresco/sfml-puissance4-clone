#include "Application.h"
#include "Grid.h"
#include "Utils.h"

#include <SFML/Graphics.hpp>

Application::Application():
    m_window(sf::VideoMode(sf::Vector2u(utils::WINDOW_WIDTH, utils::WINDOW_HEIGHT)), utils::WINDOW_TITLE),
    m_clock(),
    m_grid(utils::GRID_WIDTH, utils::GRID_HEIGHT),
    m_game()
{
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);
}

void Application::update()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();

        if (m_game.isRunning()) {
            m_game.play(event, m_grid);
        } else if (m_game.isWinned()) {
            m_game.win(event, m_grid, m_clock);
        } else {
            m_game.start(m_grid);
        }
    }

    // Game win
    if (m_game.isWinned()) {
        m_game.win(event, m_grid, m_clock);
    }
}

void Application::render()
{
    m_window.clear(sf::Color::Black);

    m_grid.draw(m_window);

    m_window.display();
}

void Application::run()
{
    // Clock for measuring time
    sf::Clock clock;
    // Time since last update
    const double timestep = 0.002;
    // Time accumulator
    double unprocessedTime = 0.0;

    // Game loop
    while (m_window.isOpen())
    {
        // Calculate time since last frame
        unprocessedTime += clock.restart().asSeconds();

        // Update game as long as there is enough time
        while (unprocessedTime >= timestep)
        {
            unprocessedTime -= timestep;
            update();
        }

        // Render game
        render();
    }
}