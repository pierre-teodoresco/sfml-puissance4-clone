#include "Game.h"
#include "Utils.h"

#include <SFML/Graphics.hpp>

#include <iostream>

Game::Game() : 
    m_state(Grid::CellState::Red), m_isRunning(false), m_winners(new Winner[utils::WIN_CONDITION]), 
    m_winned(false), m_winBlink(false)
{
}

int Game::throwToken(int col, Grid& grid)
{
    int row = grid.getHeight() - 1;
    while (row >= 0 && grid.get(col, row) != Grid::CellState::Empty)
    {
        row--;
    }
    if (row >= 0)
    {
        grid.set(col, row, m_state);
        m_state = (m_state == Grid::CellState::Red) ? Grid::CellState::Yellow : Grid::CellState::Red;
        return row;
    }
    return -1;
}

bool Game::checkLeftAndRight(int col, int row, Grid& grid) const {
    auto playedToken = grid.get(col, row);
    
    int cpt = 1;
    int i = 1;
    int j = 1;
    bool righty = col+i <= grid.getWidth()-1;
    bool lefty = col-j >= 0;
    while (cpt < utils::WIN_CONDITION && (righty || lefty)) {
        if (righty) {
            // right
            bool sameToken = grid.get(col+i, row) == playedToken;
            if (sameToken) {
                m_winners[cpt].col = col+i;
                m_winners[cpt].row = row;
                m_winners[cpt].state = grid.get(col+i, row);
                cpt++;
            }
            i++;
            righty = col+i <= grid.getWidth()-1 && sameToken;
        }

        if (cpt >= utils::WIN_CONDITION) break;

        if (lefty) {
            // left
            bool sameToken = grid.get(col-j, row) == playedToken;
            if (sameToken) {
                m_winners[cpt].col = col-j;
                m_winners[cpt].row = row;
                m_winners[cpt].state = grid.get(col-j, row);
                cpt++;
            }
            j++;
            lefty = col-j >= 0 && sameToken;
        }
    }
    return cpt >= utils::WIN_CONDITION;
}

bool Game::checkDown(int col, int row, Grid& grid) const {
    if (row <= grid.getHeight() - utils::WIN_CONDITION) {
        int i = 1;
        int cpt = 1;
        bool sameToken = true;
        while (i < utils::WIN_CONDITION && sameToken) {
            if (grid.get(col, row+i) == grid.get(col, row)) {
                m_winners[cpt].col = col;
                m_winners[cpt].row = row+i;
                m_winners[cpt].state = grid.get(col, row+i);
                cpt++;
            } else {
                sameToken = false;
            }
            i++;
        }
        return cpt == utils::WIN_CONDITION;
    }
    return false;
}

bool Game::checkDiagRL(int col, int row, Grid& grid) const {
    auto playedToken = grid.get(col, row);
    
    int cpt = 1;
    int i = 1;
    int j = 1;
    bool righty = col+i <= grid.getWidth()-1 && row-i <= grid.getHeight()-1;
    bool lefty = col-j >= 0 && row+j >= 0;
    while (cpt < utils::WIN_CONDITION && (righty || lefty)) {
        if (righty) {
            // right
            bool sameToken = grid.get(col+i, row-i) == playedToken;
            if (sameToken) {
                m_winners[cpt].col = col+i;
                m_winners[cpt].row = row-i;
                m_winners[cpt].state = grid.get(col+i, row-i);
                cpt++;
            }
            i++;
            righty = col+i <= grid.getWidth()-1 && row-i <= grid.getHeight()-1 && sameToken;
        }

        if (cpt >= utils::WIN_CONDITION) break;

        if (lefty) {
            // left
            bool sameToken = grid.get(col-j, row+j) == playedToken;
            if (sameToken) {
                m_winners[cpt].col = col-j;
                m_winners[cpt].row = row+j;
                m_winners[cpt].state = grid.get(col-j, row+j);
                cpt++;
            }
            j++;
            lefty = col-j >= 0 && row+j >= 0 && sameToken;
        }
    }
    return cpt >= utils::WIN_CONDITION;
}

bool Game::checkDiagLR(int col, int row, Grid& grid) const {
    auto playedToken = grid.get(col, row);
    
    int cpt = 1;
    int i = 1;
    int j = 1;
    bool righty = col+i <= grid.getWidth()-1 && row+i <= grid.getHeight()-1;
    bool lefty = col-j >= 0 && row-j >= 0;
    while (cpt < utils::WIN_CONDITION && (righty || lefty)) {
        if (righty) {
            // right
            bool sameToken = grid.get(col+i, row+i) == playedToken;
            if (sameToken) {
                m_winners[cpt].col = col+i;
                m_winners[cpt].row = row+i;
                m_winners[cpt].state = grid.get(col+i, row+i);
                cpt++;
            }
            i++;
            righty = col+i <= grid.getWidth()-1 && row+i <= grid.getHeight()-1 && sameToken;
        }

        if (cpt >= utils::WIN_CONDITION) break;

        if (lefty) {
            // left
            bool sameToken = grid.get(col-j, row-j) == playedToken;
            if (sameToken) {
                m_winners[cpt].col = col-j;
                m_winners[cpt].row = row-j;
                m_winners[cpt].state = grid.get(col-j, row-j);
                cpt++;
            }
            j++;
            lefty = col-j >= 0 && row-j >= 0 && sameToken;
        }
    }
    return cpt >= utils::WIN_CONDITION;
}

bool Game::checkWin(int col, int row, Grid& grid)
{
    // adding to winners the played token
    m_winners[0].col = col;
    m_winners[0].row = row;
    m_winners[0].state = grid.get(col, row);

    // checking up is useless because the last token is always the upper one

    // down
    if (checkDown(col, row, grid)) {
        m_winned = true;
        return true;
    }

    // left and right
    if (checkLeftAndRight(col, row, grid)) {
        m_winned = true;
        return true;
    }

    // Diags
    if (checkDiagLR(col, row, grid) || checkDiagRL(col, row, grid)) {
        m_winned = true;
        return true;
    }

    return false;
}

void Game::play(const sf::Event& event, Grid& grid)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        int col = event.mouseButton.x / utils::CELL_WIDTH;
        int row = throwToken(col, grid);

        // Game keep going while the grid is not full and no player won
        m_isRunning = !(grid.isFull() || checkWin(col, row, grid));
    }
}

void Game::start(Grid& grid)
{
    m_isRunning = true;
    m_state = Grid::CellState::Red;
    grid.clear();
}

bool Game::isRunning() const
{
    return m_isRunning;
}

void Game::win(const sf::Event& event, Grid& grid, sf::Clock& clock) {
    if (m_isRunning) return;

    if (event.type == sf::Event::KeyPressed) {
        m_winned = false;
    } else if (clock.getElapsedTime().asSeconds() >= 0.2f) {
        // Changing state = changing color
        Grid::CellState state;
        if (m_winBlink) {
            state = m_winners[0].state;
        } else {
            state = Grid::CellState::Empty;
        }

        // Blink winning line and restart clock
        for (int i = 0; i < utils::WIN_CONDITION; i++) {
            grid.set(m_winners[i].col, m_winners[i].row, state);
        }
        m_winBlink = !m_winBlink;
        clock.restart();
    }
}

bool Game::isWinned() const {
    return m_winned;
}