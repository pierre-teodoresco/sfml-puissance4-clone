#pragma once

#include <SFML/Graphics.hpp>

class Grid
{
public:
    enum class CellState
    {
        Empty = 0,
        Red,
        Yellow
    };
private:
    int m_width;
    int m_height;
    CellState** m_grid;
public:
    Grid(int width, int height);
    ~Grid();
    const CellState& get(int x, int y) const;
    void set(int x, int y, const CellState& state);
    void draw(sf::RenderWindow& window) const;
    int getHeight() const;
    int getWidth() const;
    void clear();
};
