#pragma once

namespace utils 
{
    /* CONSTANTES */

    // WINDOW
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 720;
    constexpr char const* WINDOW_TITLE = "Puissance 4";

    // GRID
    constexpr int GRID_WIDTH = 6;
    constexpr int GRID_HEIGHT = 7;

    // CELL
    constexpr int CELL_WIDTH = WINDOW_WIDTH / GRID_WIDTH;
    constexpr int CELL_HEIGHT = WINDOW_HEIGHT / GRID_HEIGHT;
    constexpr int CELL_RADIUS = 20;

    // WIN
    constexpr int WIN_CONDITION = 4;
}