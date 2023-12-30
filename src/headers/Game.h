#pragma once

#include "Grid.h"

class Game
{
private:
    struct Winner {
        int col;
        int row;
        Grid::CellState state;

        void clear() {
            col = 0;
            row = 0;
            state = Grid::CellState::Empty;
        }
    };

    Grid::CellState m_state;
    bool m_isRunning;
    Winner* m_winners;
    bool m_winned;
    bool m_winBlink;
public:
    Game();
private:
    int throwToken(int col, Grid& grid);
    bool checkWin(int col, int row, Grid& grid);
    bool checkLeftAndRight(int col, int row, Grid& grid) const;
    bool checkDown(int col, int row, Grid& grid) const;
    bool checkDiagLR(int col, int row, Grid& grid) const;
    bool checkDiagRL(int col, int row, Grid& grid) const;
public:
    void play(const sf::Event& event, Grid& grid);
    void start(Grid& grid);
    bool isRunning() const;
    void win(const sf::Event& event, Grid& grid, sf::Clock& clock);
    bool isWinned() const;
};


