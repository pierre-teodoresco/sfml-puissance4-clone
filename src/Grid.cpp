#include "Grid.h"
#include "Utils.h"

#include <SFML/Graphics.hpp>

Grid::Grid(int width, int height) : m_width(width), m_height(height)
{
    m_grid = new CellState*[m_width];
    for (int i = 0; i < m_width; i++)
    {
        m_grid[i] = new CellState[m_height];
        for (int j = 0; j < m_height; j++)
        {
            m_grid[i][j] = CellState::Empty;
        }
    }
}

Grid::~Grid()
{
    for (int i = 0; i < m_width; i++)
    {
        delete[] m_grid[i];
    }
    delete[] m_grid;
}

const Grid::CellState& Grid::get(int x, int y) const
{
    return m_grid[x][y];
}

void Grid::set(int x, int y, const CellState& state)
{
    m_grid[x][y] = state;
}

void Grid::draw(sf::RenderWindow& window) const
{
    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height; j++)
        {
            sf::CircleShape circle(utils::CELL_RADIUS);
            circle.setPosition(sf::Vector2f(i * utils::CELL_WIDTH + utils::CELL_RADIUS, 
                j * utils::CELL_HEIGHT + utils::CELL_RADIUS));
            switch (m_grid[i][j])
            {
            case CellState::Empty:
                circle.setFillColor(sf::Color::White);
                break;
            case CellState::Red:
                circle.setFillColor(sf::Color::Red);
                break;
            case CellState::Yellow:
                circle.setFillColor(sf::Color::Yellow);
                break;
            }
            window.draw(circle);
        }
    }
}

int Grid::getHeight() const
{
    return m_height;
}

int Grid::getWidth() const
{
    return m_width;
}

void Grid::clear()
{
    for (int i = 0; i < m_width; i++)
    {
        for (int j = 0; j < m_height; j++)
        {
            m_grid[i][j] = CellState::Empty;
        }
    }
}