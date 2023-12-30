#pragma once

#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "Game.h"

class Application
{
private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;
    Grid m_grid;
    Game m_game;
public:
    Application();
private:
    void update();
    void render();
public:
    void run();
};